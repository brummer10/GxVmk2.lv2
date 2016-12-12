#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.resource"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[1366]; const double alignment; void * const ptr;}  resource_resource_data = { {
  0x47, 0x56, 0x61, 0x72, 0x69, 0x61, 0x6e, 0x74, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x28, 0x04, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
  0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
  0xd8, 0xf9, 0xf9, 0xdc, 0x02, 0x00, 0x00, 0x00, 
  0x90, 0x00, 0x00, 0x00, 0x09, 0x00, 0x76, 0x00, 
  0xa0, 0x00, 0x00, 0x00, 0xa5, 0x01, 0x00, 0x00, 
  0xd4, 0xb5, 0x02, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0xa5, 0x01, 0x00, 0x00, 0x01, 0x00, 0x4c, 0x00, 
  0xa8, 0x01, 0x00, 0x00, 0xac, 0x01, 0x00, 0x00, 
  0xfa, 0xcc, 0x8a, 0xf4, 0x01, 0x00, 0x00, 0x00, 
  0xac, 0x01, 0x00, 0x00, 0x07, 0x00, 0x4c, 0x00, 
  0xb4, 0x01, 0x00, 0x00, 0xbc, 0x01, 0x00, 0x00, 
  0xb3, 0x0e, 0xee, 0x35, 0x02, 0x00, 0x00, 0x00, 
  0xbc, 0x01, 0x00, 0x00, 0x09, 0x00, 0x76, 0x00, 
  0xc8, 0x01, 0x00, 0x00, 0x56, 0x05, 0x00, 0x00, 
  0x66, 0x72, 0x61, 0x6d, 0x65, 0x2e, 0x70, 0x6e, 
  0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 
  0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 
  0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 0x28, 
  0x08, 0x06, 0x00, 0x00, 0x00, 0x08, 0x78, 0x5f, 
  0x43, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 
  0x73, 0x00, 0x00, 0x0b, 0x13, 0x00, 0x00, 0x0b, 
  0x13, 0x01, 0x00, 0x9a, 0x9c, 0x18, 0x00, 0x00, 
  0x00, 0x07, 0x74, 0x49, 0x4d, 0x45, 0x07, 0xe0, 
  0x0c, 0x0c, 0x04, 0x16, 0x19, 0x2a, 0x4c, 0x56, 
  0x50, 0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 
  0x74, 0x43, 0x6f, 0x6d, 0x6d, 0x65, 0x6e, 0x74, 
  0x00, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 
  0x20, 0x77, 0x69, 0x74, 0x68, 0x20, 0x47, 0x49, 
  0x4d, 0x50, 0x57, 0x81, 0x0e, 0x17, 0x00, 0x00, 
  0x00, 0x6f, 0x49, 0x44, 0x41, 0x54, 0x68, 0xde, 
  0xed, 0xdb, 0xb1, 0x0d, 0xc0, 0x20, 0x0c, 0x00, 
  0x41, 0x40, 0x99, 0xc9, 0xfb, 0xb7, 0xf6, 0x52, 
  0xa4, 0x02, 0x31, 0x41, 0x42, 0x71, 0x5f, 0x51, 
  0xfb, 0x64, 0x3a, 0xf7, 0xcc, 0x9c, 0x4d, 0xd7, 
  0x34, 0x8c, 0xe0, 0xae, 0x9e, 0xf5, 0x88, 0x88, 
  0x6e, 0x1c, 0xff, 0x55, 0x55, 0xd3, 0x86, 0xf8, 
  0xb2, 0x04, 0x04, 0x88, 0x80, 0x00, 0x11, 0x10, 
  0x20, 0x02, 0x22, 0x20, 0x40, 0x04, 0x04, 0x88, 
  0x80, 0x00, 0x11, 0x10, 0x20, 0x02, 0x02, 0x44, 
  0x40, 0x04, 0x04, 0x88, 0x80, 0x00, 0x11, 0x10, 
  0x20, 0x02, 0x02, 0x44, 0x40, 0x04, 0x04, 0x88, 
  0x80, 0x00, 0x11, 0x10, 0x20, 0xfa, 0xb0, 0x7d, 
  0x63, 0xb8, 0x6e, 0xdc, 0x64, 0x43, 0x74, 0xf4, 
  0x02, 0xdf, 0xf1, 0x0b, 0x0b, 0xf0, 0x3a, 0xf7, 
  0x7a, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 
  0x44, 0xae, 0x42, 0x60, 0x82, 0x00, 0x00, 0x28, 
  0x75, 0x75, 0x61, 0x79, 0x29, 0x2f, 0x00, 0x00, 
  0x02, 0x00, 0x00, 0x00, 0x67, 0x78, 0x70, 0x6c, 
  0x75, 0x67, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x00, 0x00, 0x00, 0x70, 0x65, 0x64, 0x61, 
  0x6c, 0x2e, 0x70, 0x6e, 0x67, 0x00, 0x00, 0x00, 
  0x7e, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 
  0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 
  0x00, 0x00, 0x02, 0xc9, 0x00, 0x00, 0x00, 0xaf, 
  0x08, 0x06, 0x00, 0x00, 0x00, 0x0f, 0x07, 0x43, 
  0x83, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 
  0x73, 0x00, 0x00, 0x0b, 0x13, 0x00, 0x00, 0x0b, 
  0x13, 0x01, 0x00, 0x9a, 0x9c, 0x18, 0x00, 0x00, 
  0x00, 0x07, 0x74, 0x49, 0x4d, 0x45, 0x07, 0xe0, 
  0x0c, 0x0c, 0x03, 0x01, 0x07, 0xd0, 0x8f, 0xf9, 
  0x20, 0x00, 0x00, 0x00, 0x19, 0x74, 0x45, 0x58, 
  0x74, 0x43, 0x6f, 0x6d, 0x6d, 0x65, 0x6e, 0x74, 
  0x00, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x64, 
  0x20, 0x77, 0x69, 0x74, 0x68, 0x20, 0x47, 0x49, 
  0x4d, 0x50, 0x57, 0x81, 0x0e, 0x17, 0x00, 0x00, 
  0x02, 0xf8, 0x49, 0x44, 0x41, 0x54, 0x78, 0xda, 
  0xed, 0xd6, 0x31, 0x01, 0x00, 0x30, 0x08, 0xc0, 
  0xb0, 0x31, 0x4d, 0xfb, 0xa6, 0x01, 0xff, 0x72, 
  0xe0, 0xe3, 0x44, 0x41, 0x22, 0xa1, 0x57, 0xe3, 
  0xfd, 0xac, 0x03, 0x00, 0x00, 0x8c, 0x2b, 0x01, 
  0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x30, 0xc9, 
  0x00, 0x00, 0x60, 0x92, 0x01, 0x00, 0xc0, 0x24, 
  0x03, 0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 
  0x0c, 0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 0x4c, 
  0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x30, 
  0xc9, 0x00, 0x00, 0x60, 0x92, 0x01, 0x00, 0xc0, 
  0x24, 0x03, 0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 
  0x93, 0x0c, 0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 
  0x4c, 0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 
  0xc0, 0x24, 0x03, 0x00, 0x80, 0x49, 0x06, 0x00, 
  0x00, 0x93, 0x0c, 0x00, 0x00, 0x26, 0x19, 0x00, 
  0x00, 0x4c, 0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 
  0x00, 0x30, 0xc9, 0x00, 0x00, 0x60, 0x92, 0x01, 
  0x00, 0xc0, 0x24, 0x03, 0x00, 0x80, 0x49, 0x06, 
  0x00, 0x00, 0x93, 0x0c, 0x00, 0x00, 0x26, 0x19, 
  0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x98, 0x64, 
  0x00, 0x00, 0x30, 0xc9, 0x00, 0x00, 0x60, 0x92, 
  0x01, 0x00, 0xc0, 0x24, 0x03, 0x00, 0x00, 0x26, 
  0x19, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x98, 
  0x64, 0x00, 0x00, 0x30, 0xc9, 0x00, 0x00, 0x60, 
  0x92, 0x01, 0x00, 0xc0, 0x24, 0x03, 0x00, 0x80, 
  0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 0x00, 0x00, 
  0x26, 0x19, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 
  0x98, 0x64, 0x00, 0x00, 0x30, 0xc9, 0x00, 0x00, 
  0x60, 0x92, 0x01, 0x00, 0xc0, 0x24, 0x03, 0x00, 
  0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 0x00, 
  0x00, 0x26, 0x19, 0x00, 0x00, 0x30, 0xc9, 0x00, 
  0x00, 0x60, 0x92, 0x01, 0x00, 0xc0, 0x24, 0x03, 
  0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 
  0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 0x4c, 0x32, 
  0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x30, 0xc9, 
  0x00, 0x00, 0x60, 0x92, 0x01, 0x00, 0xc0, 0x24, 
  0x03, 0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 
  0x0c, 0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 0x4c, 
  0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x30, 
  0xc9, 0x00, 0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 
  0x93, 0x0c, 0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 
  0x4c, 0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 
  0x30, 0xc9, 0x00, 0x00, 0x60, 0x92, 0x01, 0x00, 
  0xc0, 0x24, 0x03, 0x00, 0x80, 0x49, 0x06, 0x00, 
  0x00, 0x93, 0x0c, 0x00, 0x00, 0x26, 0x19, 0x00, 
  0x00, 0x4c, 0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 
  0x00, 0x30, 0xc9, 0x00, 0x00, 0x60, 0x92, 0x01, 
  0x00, 0xc0, 0x24, 0x03, 0x00, 0x80, 0x49, 0x06, 
  0x00, 0x00, 0x93, 0x2c, 0x01, 0x00, 0x00, 0x98, 
  0x64, 0x00, 0x00, 0x30, 0xc9, 0x00, 0x00, 0x60, 
  0x92, 0x01, 0x00, 0xc0, 0x24, 0x03, 0x00, 0x80, 
  0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 0x00, 0x00, 
  0x26, 0x19, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 
  0x98, 0x64, 0x00, 0x00, 0x30, 0xc9, 0x00, 0x00, 
  0x60, 0x92, 0x01, 0x00, 0xc0, 0x24, 0x03, 0x00, 
  0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 0x00, 
  0x00, 0x26, 0x19, 0x00, 0x00, 0x4c, 0x32, 0x00, 
  0x00, 0x98, 0x64, 0x00, 0x00, 0xc0, 0x24, 0x03, 
  0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 
  0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 0x4c, 0x32, 
  0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x30, 0xc9, 
  0x00, 0x00, 0x60, 0x92, 0x01, 0x00, 0xc0, 0x24, 
  0x03, 0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 
  0x0c, 0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 0x4c, 
  0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x30, 
  0xc9, 0x00, 0x00, 0x60, 0x92, 0x01, 0x00, 0xc0, 
  0x24, 0x03, 0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 
  0x4c, 0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 
  0x30, 0xc9, 0x00, 0x00, 0x60, 0x92, 0x01, 0x00, 
  0xc0, 0x24, 0x03, 0x00, 0x80, 0x49, 0x06, 0x00, 
  0x00, 0x93, 0x0c, 0x00, 0x00, 0x26, 0x19, 0x00, 
  0x00, 0x4c, 0x32, 0x00, 0x00, 0x98, 0x64, 0x00, 
  0x00, 0x30, 0xc9, 0x00, 0x00, 0x60, 0x92, 0x01, 
  0x00, 0xc0, 0x24, 0x03, 0x00, 0x80, 0x49, 0x06, 
  0x00, 0x00, 0x93, 0x0c, 0x00, 0x00, 0x26, 0x19, 
  0x00, 0x00, 0x30, 0xc9, 0x00, 0x00, 0x60, 0x92, 
  0x01, 0x00, 0xc0, 0x24, 0x03, 0x00, 0x80, 0x49, 
  0x06, 0x00, 0x00, 0x93, 0x0c, 0x00, 0x00, 0x26, 
  0x19, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x98, 
  0x64, 0x00, 0x00, 0x30, 0xc9, 0x00, 0x00, 0x60, 
  0x92, 0x01, 0x00, 0xc0, 0x24, 0x03, 0x00, 0x80, 
  0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 0x00, 0x00, 
  0x26, 0x19, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 
  0x98, 0x64, 0x00, 0x00, 0x30, 0xc9, 0x00, 0x00, 
  0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 0x00, 
  0x00, 0x26, 0x19, 0x00, 0x00, 0x4c, 0x32, 0x00, 
  0x00, 0x98, 0x64, 0x00, 0x00, 0x30, 0xc9, 0x00, 
  0x00, 0x60, 0x92, 0x01, 0x00, 0xc0, 0x24, 0x03, 
  0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 0x0c, 
  0x00, 0x00, 0x26, 0x19, 0x00, 0x00, 0x4c, 0x32, 
  0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 0x30, 0xc9, 
  0x00, 0x00, 0x60, 0x92, 0x01, 0x00, 0xc0, 0x24, 
  0x03, 0x00, 0x80, 0x49, 0x06, 0x00, 0x00, 0x93, 
  0x2c, 0x01, 0x00, 0x00, 0x98, 0x64, 0x00, 0x00, 
  0x58, 0x35, 0xce, 0x20, 0x03, 0x19, 0xd3, 0xf3, 
  0xa5, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 
  0x4e, 0x44, 0xae, 0x42, 0x60, 0x82, 0x00, 0x00, 
  0x28, 0x75, 0x75, 0x61, 0x79, 0x29
} };

static GStaticResource static_resource = { resource_resource_data.data, sizeof (resource_resource_data.data), NULL, NULL, NULL };
extern GResource *resource_get_resource (void);
GResource *resource_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a sane way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif


#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}
