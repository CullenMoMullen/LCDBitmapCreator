////////////////////////////////////////////////////////////////////////////////
//! \addtogroup util_hndl
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    handlealloc.h
//! \brief   Contains public header data for the Handle Allocation subsystem.
//! \version 1.0
//! \date    12-August 2005
////////////////////////////////////////////////////////////////////////////////
#ifndef __HANDLE_ALLOC_H
#define __HANDLE_ALLOC_H

//! \brief Macro used to indicate an invalid handle for memory allocated through the handle alloc module.
#define INVALID_HANDLE 0

#include "types.h"

#define HANDLE_POOL_GROWTH_SIZE 128

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct _util_hndl_Stats_t {
		int32_t i32FreeHandles;
		int32_t i32UsedHandles;
		int32_t i32LockedHandles;
		int32_t i32PurgeableHandles;
		uint32_t u32TotalFreeMem;
	} util_hndl_Stats_t;


	//! \brief Type definition of a handle.
	//!
	//! The handle based allocation module allocated memory much like malloc, however instead
	//! of returning a pointer to the memory it returns a handle to the memory.  Using handles
	//! allows code to manage the heap and compact it as necessary to reclaim lost, fragmented space.
	typedef uint16_t util_Handle_t;

	////////////////////////////////////////////////////////////////////////////////
	//! \brief Initializes the handle heap and sets up the initial parameters.
	//! 
	//! \param[in] pHeap               Pointer to the heap data buffer; 
	//! \param[in] u32HeapSize         Size of the heap data buffer; 
	//! \param[in] u16SupportedHandles Number of handles in the heap;
	//!
	//! \note The values of the parameters cannot be changed after initialization.
	//!
	//! \internal
	//! \todo This function could be improved by allocating the handle heap from the VMI or DMI
	//! \todo This function could be improved by passing in the initial settings.
	//!
	//! \see To view the function definition, see handlealloc_compact.c.
	////////////////////////////////////////////////////////////////////////////////
	void            util_hndl_Initialize(void* pHeap, uint32_t u32HeapSize, uint16_t u16SupportedHandles);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Allocate relocatable memory.
	//!
	//! A relocatable memory section can be allocated using this function.
	//! It can be designated as purgable if required.
	//!
	//! \param[in] size Amount of memory, in bytes, to allocate
	//! 
	//! \return Handle of new allocation (or INVALID_HANDLE if no room in the heap)
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc_compact.c.
	////////////////////////////////////////////////////////////////////////////////
	util_Handle_t   util_hndl_Alloc(uint32_t size);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Compacts the heap using a sweep/slide mechanism. 
	//!
	//! The basic algorithm is:
	//! \code
	//! for every free segment
	//!   while something changed
	//!     try to move something to it
	//!     try to slide everything below it up into the hole.
	//! \endcode
	//!
	//! The algorithm has not been analyzed for complete optimization, and it is
	//! accepted that there likely is some room for optimization in this algorithm.
	//! One example might be completeting all the 'move to' operations available before
	//! trying to slide things up.
	//! Additionally, the algorithm isn't all that smart, as it doesn't try to do 'best fit'
	//! when moving things around, it simply takes the largest block that will fit.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc_compact.c.
	////////////////////////////////////////////////////////////////////////////////
	bool            util_hndl_CompactHeap(void);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Frees an allocation based on its handle
	//!
	//! This function takes a handle (even a purged handle) and releases it back into
	//! the heap.   This handle cannot be locked, however.
	//!
	//! \param[in] ... Handle to allocation to free.
	////////////////////////////////////////////////////////////////////////////////
	void            util_hndl_Free(util_Handle_t);
	//! \brief FOR_INTERNAL_USE_ONLY
	//! \todo [PUBS] This function is marked internal in handlealloc_compact.c; move prototype?
	uint32_t        util_hndl_GetSizeInWords(util_Handle_t);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Lock a handle and get a pointer for the allocated buffer.
	//!
	//! This function will 'lock' a handle down and return a pointer to the buffer.
	//! If the buffer pointed to by the handle  has been purged, util_hndl_Lock()
	//! will return NULL, and the handle will be released back to the system.
	//!
	//! \param[in] ... Handle to lock down.
	//! \return pointer to buffer, or NULL if the buffer has been purged.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc.c.
	////////////////////////////////////////////////////////////////////////////////
	void* util_hndl_Lock(util_Handle_t);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Unlock a handle and allow it to be relocated and/or purged.
	//!
	//! This function will 'unlock' a handle, allowing the buffer to be moved
	//! and/or purged (if the handle is marked purgeable) as required.
	//!
	//! \param[in] ... Handle to allocation to free.
	//! \return pointer to buffer, or NULL if the buffer has been purged.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc.c.
	////////////////////////////////////////////////////////////////////////////////
	void            util_hndl_Unlock(util_Handle_t);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Allocates a new buffer and returns a pointer to it.
	//!
	//! This function allocates a new buffer and returns a pointer to
	//! it.   This buffer can only be freed and not unlocked.   Call
	//! \ref util_hndl_FreeByAddress() to de-allocate this buffer.
	//!
	//! \param[in] size size, in bytes, of the new buffer
	//! \param[in] bClear whether or not to clear the buffer
	//! \return pointer to buffer, or NULL if unable to allocate.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc.c.
	////////////////////////////////////////////////////////////////////////////////
	void* util_hndl_AllocLocked(uint32_t size, bool bClear);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Set the purgeable property of an allocation.
	//!
	//! Set the property of an allocation's purgeability.
	//!
	//! \param[in] ... Handle to the allocation.
	//! \param[in] ... Set purgeability. 0 - non-purgeable, 1 - purgeable 
	//!
	//! \return Previous setting for the allocations property.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc.c.
	////////////////////////////////////////////////////////////////////////////////
	bool            util_hndl_SetPurgeable(util_Handle_t, bool);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Frees a locked allocation by pointer.
	//!
	//! This function will free a locked allocation by the
	//! pointer value.
	//!
	//! \param[in] *pPtr Pointer to allocation to free
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc.c.
	////////////////////////////////////////////////////////////////////////////////
	void            util_hndl_FreeByAddress(void* pPtr);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Report back the free memory of the heap
	//!
	//! This function is used by the handle allocation subsystem to
	//! sum up free sections in the heap.
	//!
	//! \note The total number of bytes available in the heap is not necessarily the largest
	//!       allocatable block (due to intervening unmovable allocations)
	//! \returns number of bytes available in the heap.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc.c.
	////////////////////////////////////////////////////////////////////////////////
	uint32_t        util_hndl_GetTotalFree(void);
	////////////////////////////////////////////////////////////////////////////////
	//! \brief Get the size of the largest guaranteed allocatable buffer.
	//!
	//!  This function will report the current largest free segment available
	//!  \note this does not calculate the largest possible allocation, but the
	//!         largest guaranteed allocation.
	//!  \note In a multithreaded environment, the return value may not represent the
	//!         largest guaranteed allocation by the time the calling thread is able to
	//!         actually call util_hndl_Alloc()
	//!
	//!  \return number of bytes that can be allocated.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc.c.
	////////////////////////////////////////////////////////////////////////////////
	uint32_t        util_hndl_GetLargestFreeBlock(void);

	///////////////////////////////////////////////////////////////////////////////
	//! \brief Output the heap status
	//!
	//! This function is purely a diagnostic tool and won't be linked in unless it is called.
	//! It outputs the status of the heap including the allocations and the free segments.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc_heapwalk.c.
	///////////////////////////////////////////////////////////////////////////////
	void            util_hndl_WalkHeap(void);

	///////////////////////////////////////////////////////////////////////////////
	//! \brief Returns useful heap statistics
	//!
	//! This function is a diagnostic tool that can be called at runtime to get info
	//! about the heap usage.  The calller must allocate enough memory for a util_hndl_Stats_t
	//! datastructure and pass in the address to that data structure.
	//!
	//! \param[in] pStats Handle to the allocation.
	//!
	//! \internal
	//! \see To view the function definition, see handlealloc_heapwalk.c.
	///////////////////////////////////////////////////////////////////////////////
	void            util_hndl_GetHeapStats(util_hndl_Stats_t* pStats);


#ifdef __cplusplus
}
#endif

#endif //__HANDLE_ALLOC_H
///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
//! @}
