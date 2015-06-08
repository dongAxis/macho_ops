
#ifndef _CONST_VARIABLE_
#define _CONST_VARIABLE_

#ifndef EXPORT_FUNCTION
#define EXPORT_FUNCTION __attribute__((visibility("default")))
#endif

#ifndef DIM
#define DIM(arr) (sizeof((arr))/sizeof((arr)[0]))
#endif

#ifndef PLUGIN_ID
#define PLUGIN_ID(id) ((id)>>8)
#endif

#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif

#ifndef INOUT
#define INOUT
#endif

#endif