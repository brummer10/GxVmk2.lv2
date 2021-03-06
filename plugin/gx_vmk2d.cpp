/*
 * Copyright (C) 2014 Guitarix project MOD project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 */


#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cassert>
#include <unistd.h>

///////////////////////// MACRO SUPPORT ////////////////////////////////

#define __rt_func __attribute__((section(".rt.text")))
#define __rt_data __attribute__((section(".rt.data")))

///////////////////////// FAUST SUPPORT ////////////////////////////////

#define FAUSTFLOAT float
#ifndef N_
#define N_(String) (String)
#endif
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

#define always_inline inline __attribute__((always_inline))

template <int32_t N> inline float faustpower(float x)
{
  return powf(x, N);
}
template <int32_t N> inline double faustpower(double x)
{
  return pow(x, N);
}
template <int32_t N> inline int32_t faustpower(int32_t x)
{
  return faustpower<N/2>(x) * faustpower<N-N/2>(x);
}
template <>      inline int32_t faustpower<0>(int32_t x)
{
  return 1;
}
template <>      inline int32_t faustpower<1>(int32_t x)
{
  return x;
}

////////////////////////////// LOCAL INCLUDES //////////////////////////

#include "gx_vmk2d.h"        // define struct PortIndex
#include "gx_pluginlv2.h"   // define struct PluginLV2
#include "resampler.cc"   // define struct PluginLV2
#include "resampler-table.cc"   // define struct PluginLV2
#include "zita-resampler/resampler.h"
//#include "vmk2d.cc"    // dsp class generated by faust -> dsp2cc
#include "mbr.cc"
#include "mbr1.cc"
#include "mbr2.cc"
#include "mbron.cc"
#include "mbr1on.cc"
#include "mbr2on.cc"
#include "reverb.cc"
#include "tremolo.cc"
#include "viberev.cc"
#include "driver.cc"

////////////////////////////// PLUG-IN CLASS ///////////////////////////


//////////////////////// define dsp namespaces /////////////////////////

#define declare(n) namespace n { PluginLV2 *plugin(); }

declare(mbr);
declare(mbr1);
declare(mbr2);
declare(mbron);
declare(mbr1on);
declare(mbr2on);


static plug mbrs_model [] = {
    mbr::plugin, //0
    mbr1::plugin, //1
    mbr2::plugin, //2
    mbron::plugin, //3
    mbr1on::plugin, //4
    mbr2on::plugin, //5
};

static const size_t MBR_COUNT = sizeof(mbrs_model) / sizeof(mbrs_model[0]);

declare(reverb);
declare(tremolo);
declare(viberev);

static plug viberevs_model [] = {
    reverb::plugin, //0
    tremolo::plugin, //1
    viberev::plugin, //2
};

static const size_t VIBEREV_COUNT = sizeof(viberevs_model) / sizeof(viberevs_model[0]);

namespace vmk2d {

class SimpleResampler {
 private:
    Resampler r_up, r_down;
    int m_fact;
 public:
    SimpleResampler(): r_up(), r_down(), m_fact() {}
    void setup(int sampleRate, unsigned int fact);
    void up(int count, float *input, float *output);
    void down(int count, float *input, float *output);
};

void SimpleResampler::setup(int sampleRate, unsigned int fact)
{
	m_fact = fact;
	const int qual = 16; // resulting in a total delay of 2*qual (0.7ms @44100)
	// upsampler
	r_up.setup(sampleRate, sampleRate*fact, 1, qual);
	// k == inpsize() == 2 * qual
	// pre-fill with k-1 zeros
	r_up.inp_count = r_up.inpsize() - 1;
	r_up.out_count = 1;
	r_up.inp_data = r_up.out_data = 0;
	r_up.process();
	// downsampler
	r_down.setup(sampleRate*fact, sampleRate, 1, qual);
	// k == inpsize() == 2 * qual * fact
	// pre-fill with k-1 zeros
	r_down.inp_count = r_down.inpsize() - 1;
	r_down.out_count = 1;
	r_down.inp_data = r_down.out_data = 0;
	r_down.process();
}

void SimpleResampler::up(int count, float *input, float *output)
{
	r_up.inp_count = count;
	r_up.inp_data = input;
	r_up.out_count = count * m_fact;
	r_up.out_data = output;
	r_up.process();
	assert(r_up.inp_count == 0);
	assert(r_up.out_count == 0);
}

void SimpleResampler::down(int count, float *input, float *output)
{
	r_down.inp_count = count * m_fact;
	r_down.inp_data = input;
	r_down.out_count = count+1; // +1 == trick to drain input
	r_down.out_data = output;
	r_down.process();
	assert(r_down.inp_count == 0);
	assert(r_down.out_count == 1);
}

class Gx_vmk2d_
{
private:
  // pointer to buffer
  float*          output;
  float*          input;
  // pointer to dsp class
  PluginLV2*      mbr[MBR_COUNT];
  PluginLV2*      viberev[VIBEREV_COUNT];
  PluginLV2*      driver;

  uint32_t fSamplingFreq;
  SimpleResampler smp;
  unsigned int fact;

  float*          mbr_model;
  float*          mbr_sel;
  uint32_t        mbr_model_;
  uint32_t        mbr_sel_;
  float*          rev_model;
  float*          tremolo_model;
  uint32_t        rev_model_;
  uint32_t        tremolo_model_;
  bool            run_first;
 
  bool            needs_ramp_down;
  bool            needs_ramp_up;
  float           ramp_down;
  float           ramp_up;
  float           ramp_up_step;
  float           ramp_down_step;

  // private functions
  inline void     run_dsp_(uint32_t n_samples);
  inline void     connect_(uint32_t port,void* data);
  inline void     init_dsp_(uint32_t rate);
  inline void     connect_all__ports(uint32_t port, void* data);
  inline void     activate_f();
  inline void     clean_up();
  inline void     deactivate_f();
  inline uint32_t check_rev_model(float* rev_on,float* vibe_on);
  inline uint32_t check_mrb_model(float* mbr_on,float* mbr_select);

public:
  // LV2 Descriptor
  static const LV2_Descriptor descriptor;
  // static wrapper to private functions
  static void deactivate(LV2_Handle instance);
  static void cleanup(LV2_Handle instance);
  static void run(LV2_Handle instance, uint32_t n_samples);
  static void activate(LV2_Handle instance);
  static void connect_port(LV2_Handle instance, uint32_t port, void* data);
  static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
  Gx_vmk2d_();
  ~Gx_vmk2d_();
};

// constructor
Gx_vmk2d_::Gx_vmk2d_() :
  output(NULL),
  input(NULL),
  driver(driver::plugin()),
  run_first(true),
  needs_ramp_down(false),
  needs_ramp_up(false) {};

// destructor
Gx_vmk2d_::~Gx_vmk2d_()
{
  // just to be sure the plug have given free the allocated mem
  // it didn't hurd if the mem is already given free by clean_up()
  if (driver->activate_plugin !=0)
    driver->activate_plugin(false, driver);
  // delete DSP class
  driver->delete_instance(driver);
  for(uint32_t i=0; i<MBR_COUNT; i++) {
	if (mbr[i]->activate_plugin !=0)
      mbr[i]->activate_plugin(false, mbr[i]);  
    mbr[i]->delete_instance(mbr[i]);
  }
  for(uint32_t i=0; i<VIBEREV_COUNT; i++) {
	if (viberev[i]->activate_plugin !=0)
      viberev[i]->activate_plugin(false, viberev[i]);  
    viberev[i]->delete_instance(viberev[i]);
  }
};

///////////////////////// PRIVATE CLASS  FUNCTIONS /////////////////////

void Gx_vmk2d_::init_dsp_(uint32_t rate)
{
  fSamplingFreq = rate;
  // samplerate check
  fact = fSamplingFreq/48000;
  if (fact>1) {
    smp.setup(fSamplingFreq, fact);
    fSamplingFreq = 48000;
  }
  // set values for internal ramping
  ramp_down_step =   16 * (256 * rate) / 48000; 
  ramp_up_step =  ramp_down_step;
  ramp_down = ramp_down_step;
  ramp_up = 0.0;
  // init the DSP classes
  driver->set_samplerate(fSamplingFreq, driver); 
  for(uint32_t i=0; i<MBR_COUNT; i++) {
        mbr[i] = mbrs_model[i]();
        mbr[i]->set_samplerate(fSamplingFreq, mbr[i]);
    }
  for(uint32_t i=0; i<VIBEREV_COUNT; i++) {
        viberev[i] = viberevs_model[i]();
        viberev[i]->set_samplerate(fSamplingFreq, viberev[i]);
    }
}

// connect the Ports used by the plug-in class
void Gx_vmk2d_::connect_(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case EFFECTS_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case EFFECTS_INPUT:
      input = static_cast<float*>(data);
      break;
	case MRBSELECT: 
      mbr_sel = static_cast<float*>(data); // , 0.0, 0.0, 2.0, 1.0 
      break;
	case MRB: 
      mbr_model = static_cast<float*>(data); // , 0.0, 0.0, 1.0, 1.0 
      break;
	case REVERB: 
      rev_model = static_cast<float*>(data); // , 0.0, 0.0, 1.0, 1.0 
      break;
	case VIBE: 
      tremolo_model = static_cast<float*>(data); // , 0.0, 0.0, 1.0, 1.0 
      break;
    default:
      break;
    }
}

void Gx_vmk2d_::activate_f()
{
  // allocate the internal DSP mem
  if (driver->activate_plugin !=0)
    driver->activate_plugin(true, driver);
  for(uint32_t i=0; i<MBR_COUNT; i++) {
    if (mbr[i]->activate_plugin !=0)
      mbr[i]->activate_plugin(true, mbr[i]);
  }
  for(uint32_t i=0; i<VIBEREV_COUNT; i++) {
    if (viberev[i]->activate_plugin !=0)
      viberev[i]->activate_plugin(true, viberev[i]);
  }
}

void Gx_vmk2d_::clean_up()
{
  // delete the internal DSP mem
  if (driver->activate_plugin !=0)
    driver->activate_plugin(false, driver);
  for(uint32_t i=0; i<MBR_COUNT; i++) {
    if (mbr[i]->activate_plugin !=0)
      mbr[i]->activate_plugin(false, mbr[i]);
  }
  for(uint32_t i=0; i<VIBEREV_COUNT; i++) {
    if (viberev[i]->activate_plugin !=0)
      viberev[i]->activate_plugin(false, viberev[i]);
  }
}

void Gx_vmk2d_::deactivate_f()
{
  // delete the internal DSP mem
  if (driver->activate_plugin !=0)
    driver->activate_plugin(false, driver);
  for(uint32_t i=0; i<MBR_COUNT; i++) {
    if (mbr[i]->activate_plugin !=0)
      mbr[i]->activate_plugin(false, mbr[i]);
  }
  for(uint32_t i=0; i<VIBEREV_COUNT; i++) {
    if (viberev[i]->activate_plugin !=0)
      viberev[i]->activate_plugin(false, viberev[i]);
  }
}

uint32_t Gx_vmk2d_::check_mrb_model(float* mbr_on,float* mbr_select) {
  uint32_t mbr_sel = static_cast<uint32_t>(*mbr_select);
  uint32_t mbr_o = static_cast<uint32_t>(*mbr_on);
  if(!mbr_o) return mbr_sel;
  else return mbr_sel+2;
  
}

uint32_t Gx_vmk2d_::check_rev_model(float* rev_on,float* vibe_on) {
  uint32_t rev_o = static_cast<uint32_t>(*rev_on);
  uint32_t vibe_o = static_cast<uint32_t>(*vibe_on);
  if(rev_o && !vibe_o ) return 1;
  else if(!rev_o && vibe_o ) return 2;
  else if(rev_o && vibe_o ) return 3;
  else return 0;

}

void Gx_vmk2d_::run_dsp_(uint32_t n_samples)
{
  uint32_t ReCount = n_samples;
  if (fact>1) {
    ReCount = n_samples/fact ;
  }
  FAUSTFLOAT buf[ReCount];
  if (fact>1) {
     smp.down(ReCount, input, buf);
  } else {
    memcpy(buf, input, n_samples*sizeof(float));
  }
  // do inplace processing at default
 // memcpy(output, input, n_samples*sizeof(float));
  // run selected mbr model
  if (mbr_model_ != check_mrb_model( mbr_model, mbr_sel) || 
      rev_model_ != check_rev_model( rev_model, tremolo_model)) {
      needs_ramp_down = true;
  }
  if (run_first) {
      mbr_model_ = check_mrb_model( mbr_model, mbr_sel);
      rev_model_ = check_rev_model( rev_model, tremolo_model);
      run_first = false;
  }
  // run selected mbr instance
  mbr[mbr_model_]->mono_audio(static_cast<int>(ReCount), buf, buf, mbr[mbr_model_]);

  // run selected viberev model
  if (rev_model_) {
    viberev[rev_model_-1]->mono_audio(static_cast<int>(ReCount), buf, buf, viberev[rev_model_-1]);
  }
  // check if raming is needed
  if (needs_ramp_up) {
    for (uint32_t i=0; i<ReCount; i++) {
	  if (ramp_up <= ramp_up_step) {
		  ++ramp_up;
	  }
      buf[i] *= ramp_up /ramp_up_step;
    }
    if (ramp_up >= ramp_up_step) {
      needs_ramp_up = false;
      ramp_up = 0.0;
    }
  }
  if (needs_ramp_down) {
    for (uint32_t i=0; i<ReCount; i++) {
	  if (ramp_down >= 0.0) {
		  --ramp_down;
	  }
      buf[i] *= ramp_down /ramp_down_step ;
    }


	if (ramp_down <= 0.0) {
      // when ramped down, clear buffer from viberev class
      if (rev_model_) {
        viberev[rev_model_-1]->clear_state(viberev[rev_model_-1]);
        mbr[mbr_model_]->clear_state(mbr[mbr_model_]);
      }
      mbr_model_ = check_mrb_model( mbr_model, mbr_sel);
      rev_model_ = check_rev_model( rev_model, tremolo_model);
      needs_ramp_down = false;
      needs_ramp_up = true;
      ramp_down = ramp_down_step;
    }
  }
  // driver/mixer stage
  driver->mono_audio(static_cast<int>(ReCount), buf, buf, driver);

  if (fact>1) {
    smp.up(ReCount, buf, output);
  } else {
    memcpy(output, buf, n_samples*sizeof(float));
  }
}

void Gx_vmk2d_::connect_all__ports(uint32_t port, void* data)
{
  // connect the Ports used by the plug-in class
  connect_(port,data); 
  // connect the Ports used by the DSP classes
  driver->connect_ports(port,  data, driver);
  for(uint32_t i=0; i<MBR_COUNT; i++) {
    mbr[i]->connect_ports(port,  data, mbr[i]);
  }
  for(uint32_t i=0; i<VIBEREV_COUNT; i++) {
    viberev[i]->connect_ports(port,  data, viberev[i]);
  }
  
}

////////////////////// STATIC CLASS  FUNCTIONS  ////////////////////////

LV2_Handle 
Gx_vmk2d_::instantiate(const LV2_Descriptor* descriptor,
                            double rate, const char* bundle_path,
                            const LV2_Feature* const* features)
{
  // init the plug-in class
  Gx_vmk2d_ *self = new Gx_vmk2d_();
  if (!self)
    {
      return NULL;
    }

  self->init_dsp_((uint32_t)rate);

  return (LV2_Handle)self;
}

void Gx_vmk2d_::connect_port(LV2_Handle instance, 
                                   uint32_t port, void* data)
{
  // connect all ports
  static_cast<Gx_vmk2d_*>(instance)->connect_all__ports(port, data);
}

void Gx_vmk2d_::activate(LV2_Handle instance)
{
  // allocate needed mem
  static_cast<Gx_vmk2d_*>(instance)->activate_f();
}

void Gx_vmk2d_::run(LV2_Handle instance, uint32_t n_samples)
{
  // run dsp
  static_cast<Gx_vmk2d_*>(instance)->run_dsp_(n_samples);
}

void Gx_vmk2d_::deactivate(LV2_Handle instance)
{
  // free allocated mem
  static_cast<Gx_vmk2d_*>(instance)->deactivate_f();
}

void Gx_vmk2d_::cleanup(LV2_Handle instance)
{
  // well, clean up after us
  Gx_vmk2d_* self = static_cast<Gx_vmk2d_*>(instance);
  self->clean_up();
  delete self;
}

const LV2_Descriptor Gx_vmk2d_::descriptor =
{
  GXPLUGIN_URI "#_vmk2d_",
  Gx_vmk2d_::instantiate,
  Gx_vmk2d_::connect_port,
  Gx_vmk2d_::activate,
  Gx_vmk2d_::run,
  Gx_vmk2d_::deactivate,
  Gx_vmk2d_::cleanup,
  NULL
};


} // end namespace vmk2d

////////////////////////// LV2 SYMBOL EXPORT ///////////////////////////

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index)
    {
    case 0:
      return &vmk2d::Gx_vmk2d_::descriptor;
    default:
      return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
