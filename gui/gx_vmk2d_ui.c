#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "./paintbox.h"
#include "./gtkknob.h"

#include "lv2/lv2plug.in/ns/ext/urid/urid.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

#include "./gx_vmk2d.h"

struct gx_args;

typedef struct {
    LV2UI_Write_Function write;
    LV2UI_Controller     controller;
    int block;

    GtkWidget* pbox;
    GtkWidget* pfbox;
    GtkWidget* pf1box;
    GtkWidget* pf2box;
    GtkWidget* pf3box;
    GtkWidget* pf4box;
    GtkWidget* box;
    GtkWidget* hbox;
    GtkWidget* vbox;
    GtkWidget* logo;
    GtkWidget* vlbox;
    GtkWidget* vkbox[10];
    GtkObject* adj[10];
    GtkWidget* knob[10];
    GtkWidget* label[10];
    struct gx_args *args[10];
    GtkWidget* window;  /* For optional show interface. */
} gx_vmk2dUI;

struct gx_args {
    gx_vmk2dUI* ui;
    int port_index;
} ;

static void ref_value_changed(GtkAdjustment *adj, gpointer* args) {

	gx_args * arg = (gx_args*)args;
	gx_vmk2dUI* ui = (gx_vmk2dUI*)arg->ui;
    if (ui->block) {
        ui->block = 0;
        return;
    }
	int port_index = arg->port_index;
	float value = gtk_adjustment_get_value(adj);
	ui->write(ui->controller, (PortIndex)port_index, sizeof(float), 0,
                                    (void*)&value);
}

static LV2UI_Handle instantiate(const LV2UI_Descriptor*   descriptor,
            const char*               plugin_uri,
            const char*               bundle_path,
            LV2UI_Write_Function      write_function,
            LV2UI_Controller          controller,
            LV2UI_Widget*             widget,
            const LV2_Feature* const* features) {

    gx_vmk2dUI* ui = (gx_vmk2dUI*)malloc(sizeof(gx_vmk2dUI));
    ui->write       = write_function;
    ui->controller  = controller;
    ui->block       = 0;
    ui->pbox        = NULL;
    ui->pfbox       = NULL;
    ui->pf1box      = NULL;
    ui->pf2box      = NULL;
    ui->pf3box      = NULL;
    ui->pf4box      = NULL;
    ui->box         = NULL;
    ui->hbox        = NULL;
    ui->vbox        = NULL;
    ui->logo        = NULL;
    ui->vlbox       = NULL;
    ui->window      = NULL;
    for (int i = 0; i<10;i++) {
        ui->vkbox[i]   = NULL;
        ui->knob[i]    = NULL;
        ui->label[i]   = NULL;
    }

    *widget = NULL;

    const char* plug_name = "GxVMK2" ;
    ui->logo = gtk_label_new(plug_name);
    GdkColor color;
    gdk_color_parse("#888888", &color);
    gtk_widget_modify_fg (ui->logo, GTK_STATE_NORMAL, &color);
    GtkStyle *style = gtk_widget_get_style(ui->logo);
    pango_font_description_set_size(style->font_desc, 9*PANGO_SCALE);
    //pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->logo, style->font_desc);

    ui->pbox = gx_paint_box_new(GTK_ORIENTATION_VERTICAL,false, 0);
    set_expose_func(GX_VMK_PAINT_BOX(ui->pbox),"pedal_expose");
    gtk_container_set_border_width(GTK_CONTAINER(ui->pbox),4);
    ui->box = gtk_vbox_new(FALSE, 4);
    ui->hbox = gtk_hbox_new(FALSE, 4);
    gtk_container_set_border_width(GTK_CONTAINER(ui->hbox),4);
    ui->vbox = gtk_vbox_new(TRUE, 0);
    ui->vlbox = gtk_vbox_new(TRUE, 0);

    gtk_box_pack_start(GTK_BOX(ui->pbox), ui->box, TRUE, TRUE, 4);
    gtk_box_pack_start(GTK_BOX(ui->box), ui->hbox, TRUE, TRUE, 4);
    gtk_box_pack_start(GTK_BOX(ui->box), ui->vbox, TRUE, TRUE, 0);

    ui->pfbox = gx_paint_box_new(GTK_ORIENTATION_HORIZONTAL,false, 10);
    set_expose_func(GX_VMK_PAINT_BOX(ui->pfbox),"frame_expose");
    gtk_container_set_border_width(GTK_CONTAINER(ui->pfbox),10);
    ui->pf1box = gx_paint_box_new(GTK_ORIENTATION_HORIZONTAL,false, 10);
    set_expose_func(GX_VMK_PAINT_BOX(ui->pf1box),"frame_expose");
    gtk_container_set_border_width(GTK_CONTAINER(ui->pf1box),10);
    ui->pf2box = gx_paint_box_new(GTK_ORIENTATION_HORIZONTAL,false, 10);
    set_expose_func(GX_VMK_PAINT_BOX(ui->pf2box),"frame_expose");
    gtk_container_set_border_width(GTK_CONTAINER(ui->pf2box),10);
    ui->pf3box = gx_paint_box_new(GTK_ORIENTATION_HORIZONTAL,false, 10);
    set_expose_func(GX_VMK_PAINT_BOX(ui->pf3box),"frame_expose");
    gtk_container_set_border_width(GTK_CONTAINER(ui->pf3box),10);
    ui->pf4box = gx_paint_box_new(GTK_ORIENTATION_VERTICAL,false, 10);
    set_expose_func(GX_VMK_PAINT_BOX(ui->pf4box),"frame_expose");
    gtk_container_set_border_width(GTK_CONTAINER(ui->pf4box),10);

    gtk_box_pack_end(GTK_BOX(ui->hbox), ui->pf4box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(ui->pf4box), ui->logo, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(ui->pf4box), ui->vlbox, TRUE, TRUE, 0);
    gdk_color_parse("#888888", &color);

    ui->adj[9] = gtk_adjustment_new( 0.5, 0.0, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[9] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[9]));
    ui->label[9] = gtk_label_new("VOLUME");
    ui->vkbox[9] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[9], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[9]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[9], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->pfbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->pfbox), ui->vkbox[9], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[9]), ui->knob[9], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[9]), ui->label[9], FALSE, FALSE, 0);
    ui->args[9] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[9]->ui = ui;
    ui->args[9]->port_index = (int)VOLUME;
    g_signal_connect(G_OBJECT(ui->adj[9]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[9]);

    ui->adj[0] = gtk_adjustment_new( 0.5, 0.0, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[0] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[0]));
    ui->label[0] = gtk_label_new("BASS");
    ui->vkbox[0] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[0], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[0]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[0], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->pfbox), ui->vkbox[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[0]), ui->knob[0], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[0]), ui->label[0], FALSE, FALSE, 0);
    ui->args[0] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[0]->ui = ui;
    ui->args[0]->port_index = (int)BASS;
    g_signal_connect(G_OBJECT(ui->adj[0]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[0]);

    ui->adj[7] = gtk_adjustment_new( 0.5, 0.0, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[7] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[7]));
    ui->label[7] = gtk_label_new("TREBLE");
    ui->vkbox[7] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[7], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[7]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[7], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->pfbox), ui->vkbox[7], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[7]), ui->knob[7], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[7]), ui->label[7], FALSE, FALSE, 0);
    ui->args[7] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[7]->ui = ui;
    ui->args[7]->port_index = (int)TREBLE;
    g_signal_connect(G_OBJECT(ui->adj[7]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[7]);


    ui->adj[8] = gtk_adjustment_new( 1.0, 0.0, 1.0, 1.0, 1.0*10.0, 0);
    ui->knob[8] = gtk_switch_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[8]));
    ui->label[8] = gtk_label_new("VIBE");
    ui->vkbox[8] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[8], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[8]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[8], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->pf3box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->pf3box), ui->vkbox[8], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[8]), ui->knob[8], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[8]), ui->label[8], FALSE, FALSE, 0);
    ui->args[8] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[8]->ui = ui;
    ui->args[8]->port_index = (int)VIBE;
    g_signal_connect(G_OBJECT(ui->adj[8]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[8]);

    ui->adj[6] = gtk_adjustment_new( 0.5, 0.01, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[6] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[6]));
    ui->label[6] = gtk_label_new("SPEED");
    ui->vkbox[6] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[6], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[6]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[6], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->pf3box), ui->vkbox[6], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[6]), ui->knob[6], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[6]), ui->label[6], FALSE, FALSE, 0);
    ui->args[6] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[6]->ui = ui;
    ui->args[6]->port_index = (int)SPEED;
    g_signal_connect(G_OBJECT(ui->adj[6]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[6]);

    ui->adj[1] = gtk_adjustment_new( 0.5, 0.0, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[1] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[1]));
    ui->label[1] = gtk_label_new("DEPTH");
    ui->vkbox[1] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[1], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[1]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[1], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->pf3box), ui->vkbox[1], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[1]), ui->knob[1], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[1]), ui->label[1], FALSE, FALSE, 0);
    ui->args[1] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[1]->ui = ui;
    ui->args[1]->port_index = (int)DEPTH;
    g_signal_connect(G_OBJECT(ui->adj[1]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[1]);


    ui->adj[5] = gtk_adjustment_new( 1.0, 0.0, 1.0, 1.0, 1.0*10.0, 0);
    ui->knob[5] = gtk_switch_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[5]));
    ui->label[5] = gtk_label_new("REVERB");
    ui->vkbox[5] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[5], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[5]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[5], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->pf2box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->pf2box), ui->vkbox[5], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[5]), ui->knob[5], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[5]), ui->label[5], FALSE, FALSE, 0);
    ui->args[5] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[5]->ui = ui;
    ui->args[5]->port_index = (int)REVERB;
    g_signal_connect(G_OBJECT(ui->adj[5]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[5]);

    ui->adj[4] = gtk_adjustment_new( 0.5, 0.0, 1.0, 0.01, 0.01*10.0, 0);
    ui->knob[4] = gtk_knob_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[4]));
    ui->label[4] = gtk_label_new("BLEND");
    ui->vkbox[4] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[4], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[4]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[4], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->pf2box), ui->vkbox[4], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[4]), ui->knob[4], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[4]), ui->label[4], FALSE, FALSE, 0);
    ui->args[4] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[4]->ui = ui;
    ui->args[4]->port_index = (int)REVERBLEVEL;
    g_signal_connect(G_OBJECT(ui->adj[4]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[4]);


    ui->adj[3] = gtk_adjustment_new( 0.0, 0.0, 1.0, 1.0, 1.0*10.0, 0);
    ui->knob[3] = gtk_switch_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[3]));
    ui->label[3] = gtk_label_new("MRB");
    ui->vkbox[3] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[3], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[3]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[3], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->hbox), ui->pf1box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->pf1box), ui->vkbox[3], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[3]), ui->knob[3], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[3]), ui->label[3], FALSE, FALSE, 0);
    ui->args[3] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[3]->ui = ui;
    ui->args[3]->port_index = (int)MRB;
    g_signal_connect(G_OBJECT(ui->adj[3]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[3]);

    ui->adj[2] = gtk_adjustment_new( 0.0, 0.0, 2.0, 1.0, 1.0*10.0, 0);
    ui->knob[2] = gtk_select_new_with_adjustment(GTK_ADJUSTMENT(ui->adj[2]));
    ui->label[2] = gtk_label_new("SELECT");
    ui->vkbox[2] = gtk_vbox_new(FALSE, 0);

    gtk_widget_modify_fg (ui->label[2], GTK_STATE_NORMAL, &color);
    style = gtk_widget_get_style(ui->label[2]);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(ui->label[2], style->font_desc);

    gtk_box_pack_start(GTK_BOX(ui->pf1box), ui->vkbox[2], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[2]), ui->knob[2], TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ui->vkbox[2]), ui->label[2], FALSE, FALSE, 0);
    ui->args[2] = (struct gx_args*) malloc(sizeof(struct gx_args));
    ui->args[2]->ui = ui;
    ui->args[2]->port_index = (int)MRBSELECT;
    g_signal_connect(G_OBJECT(ui->adj[2]), "value-changed",
          G_CALLBACK(ref_value_changed),(gpointer*)ui->args[2]);


    *widget = ui->pbox;

    return ui;
}

static void cleanup(LV2UI_Handle handle) {

    gx_vmk2dUI* ui = (gx_vmk2dUI*)handle;
    if (GTK_IS_WIDGET(ui->pbox)) {
        for(int i = 0;i<10;i++) {
            if (GTK_IS_WIDGET(ui->knob[i])) {
                gtk_widget_destroy(ui->knob[i]);
	        }
            if (GTK_IS_WIDGET(ui->label[i])) {
                gtk_widget_destroy(ui->label[i]);
	        }
            if (GTK_IS_WIDGET(ui->vkbox[i])) {
                gtk_widget_destroy(ui->vkbox[i]);
	        }
	        if (G_IS_OBJECT(ui->adj[i])) {
		        g_object_unref(ui->adj[i]);
	        }
        }

        if (GTK_IS_WIDGET(ui->vbox)) {
            gtk_widget_destroy(ui->vbox);
        }
        if (GTK_IS_WIDGET(ui->hbox)) {
            gtk_widget_destroy(ui->hbox);
        }
        if (GTK_IS_WIDGET(ui->box)) {
            gtk_widget_destroy(ui->box);
        }
        if (GTK_IS_WIDGET(ui->logo)) {
            gtk_widget_destroy(ui->logo);
        }
        if (GTK_IS_WIDGET(ui->vlbox)) {
            gtk_widget_destroy(ui->vlbox);
        }
        if (GTK_IS_WIDGET(ui->pfbox)) {
            gtk_widget_destroy(ui->pfbox);
        }
        if (GTK_IS_WIDGET(ui->pf1box)) {
            gtk_widget_destroy(ui->pf1box);
        }
        if (GTK_IS_WIDGET(ui->pf2box)) {
            gtk_widget_destroy(ui->pf2box);
        }
        if (GTK_IS_WIDGET(ui->pf3box)) {
            gtk_widget_destroy(ui->pf3box);
        }
        if (GTK_IS_WIDGET(ui->pbox)) {
            gtk_widget_destroy(ui->pbox);
        }
        if (GTK_IS_WINDOW(ui->window)) {
            gtk_widget_destroy(ui->window);
        }
        for(int i = 0;i<10;i++) {
            if (ui->args[i] ) free(ui->args[i]);
        }
        free(ui);
    }

}

static void port_event(LV2UI_Handle handle,
                   uint32_t     port_index,
                   uint32_t     buffer_size,
                   uint32_t     format,
                   const void*  buffer) {

    gx_vmk2dUI* ui = (gx_vmk2dUI*)handle;
	if ( format == 0 ) {
        ui->block = 1;
        float *value = (float*)buffer;
        gtk_adjustment_set_value(GTK_ADJUSTMENT(ui->adj[port_index-2]), (gdouble) (*value));
    }

}

/* Optional non-embedded UI show interface. */
static int ui_show(LV2UI_Handle handle) {

    gx_vmk2dUI* ui = (gx_vmk2dUI*)handle;

    int argc = 0;
    gtk_init(&argc, NULL);

    ui->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(ui->window), ui->pbox);
    gtk_widget_show_all(ui->window);
    gtk_window_present(GTK_WINDOW(ui->window));

    return 0;
}

/* Optional non-embedded UI hide interface. */
static int ui_hide(LV2UI_Handle handle) {

    cleanup( handle);
    return 0;

}

/* Idle interface for optional non-embedded UI. */
static int ui_idle(LV2UI_Handle handle) {

    gx_vmk2dUI* ui = (gx_vmk2dUI*)handle;
    if (ui->window) {
        g_main_context_iteration (NULL, true);
    }
    return 0;

}

static const void* extension_data(const char* uri) {

    static const LV2UI_Show_Interface show = { ui_show, ui_hide };
    static const LV2UI_Idle_Interface idle = { ui_idle };
    if (!strcmp(uri, LV2_UI__showInterface)) {
        return &show;
    } else if (!strcmp(uri, LV2_UI__idleInterface)) {
        return &idle;
    }
    return NULL;

}

static const LV2UI_Descriptor descriptor = {
    GXPLUGIN_UI_URI,
    instantiate,
    cleanup,
    port_event,
    extension_data
};

LV2_SYMBOL_EXPORT 
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) {

    switch (index) {
    case 0:
        return &descriptor;
    default:
        return NULL;
    }

}
