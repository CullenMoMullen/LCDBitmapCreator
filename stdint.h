#ifndef __STDINT_H
#define __STDINT_H

#ifdef WIN32

typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned char uint8_t;
typedef char int8_t;

#else
#pragma error Shouldn't be included from a non-windows file
#endif


#endif //__STDINT_H