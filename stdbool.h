#ifndef __STDBOOL_H
#define __STDBOOL_H

#ifdef WIN32

#ifndef __cplusplus
typedef uint8_t bool;
#define false 0
#define true !false
#endif

#else
#pragma error "Shouldn't be included from a non-windows file"
#endif

#endif //__STDINT_H