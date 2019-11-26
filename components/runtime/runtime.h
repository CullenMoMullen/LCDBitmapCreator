////////////////////////////////////////////////////////////////////////////////
//! \addtogroup cmp_runtime
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    runtime.h
//! \brief   Contains public prototypes for the runtime library.
//! \version 1.0
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __RUNTIME_H
#define __RUNTIME_H

#include "types.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

	////////////////////////////////////////////////////////////////////////////////
	//! \brief Performs 'half word set' (writing out a half word pattern).
	//! 
	//! \param[in] pPtr     Pointer to pool of half words that should be set.
	//! \param[in] u16Data  Data representing the pattern to set the half words to.
	//! \param[in] u16Count Number of half words to set.
	//! 
	//! \internal
	//! \see To view the function definition, see rt_halfwordset.arm.
	////////////////////////////////////////////////////////////////////////////////
	void  rt_halfwordset(uint16_t* pPtr, uint16_t u16Data, uint16_t u16Count);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief TBD
	//! 
	//! \param[in] pPtr     Pointer to pool of 24-bit words that should be set.
	//! \param[in] u32Data  Data representing the 24-bit pattern to set the 24-bit words to.
	//! \param[in] u16Count Number of 24 bit words to set.
	//! 
	//! \internal
	//! \see To view the function definition, see rt_halfwordset.arm.
	////////////////////////////////////////////////////////////////////////////////
	void  rt_24bitset(void* pPtr, uint32_t u32Data, uint16_t u16Count);

	////////////////////////////////////////////////////////////////////////////////
	//! \brief Small stack implementation of the vprintf()
	//! 
	//!  Supports %i, %d, %x, %X, %c, and %s
	//!  Does not currently support:
	//!      Formating      (%#.#)
	//!      Floating point (%f)
	//!      Zero padding   (%0d)
	//!      Justify        (%-)
	//!
	//! \param[in] pFormat  Formatter
	//! \param[in] args     Variable aurgument list
	////////////////////////////////////////////////////////////////////////////////
	int rt_vprintf(const char* pFormat, va_list args);

#ifdef __cplusplus
}
#endif

#endif //__RUNTIME_H
///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
//! @}
