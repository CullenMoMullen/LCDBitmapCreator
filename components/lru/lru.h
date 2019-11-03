////////////////////////////////////////////////////////////////////////////////
//! \addtogroup util_lru
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    lru.h
//! \brief   Contains public header data for the LRU software cache.
//! \version 1.0
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __LRU_H
#define __LRU_H

#include "lru_errordefs.h"

//! \brief Structure defining a Least Recently Used software cache
//!
//! \note This has nothing to do with the Hardware cache on the STMP 36xx device.
//!       This structure is used to implement a software implementation of
//!       a cache using a least recently used replacement algorithm.
typedef struct _util_lru_Cache
{
	//! \brief Size in bytes of a key
	uint8_t     u8KeySize;
	//! \brief Size in bytes of an item
	uint8_t     u8ItemSize;
	//! \brief Number of elements available in the cache
	uint16_t    u16CacheSize;
	//! \brief Current number of active entries in the cache
	uint16_t    u16CacheActiveEntries;
	//! \brief Buffer to temporarily hold a key while re-ordering the cache
	void* pTempKey;
	//! \brief Key array (each key corresponds to an item)
	void* pKeyBuffer;
	//! \brief Buffer to temporarily hold an item while re-ordering the cache
	void* pTempItem;
	//! \brief The item arrach (each item corresponds to a key in the key array)
	void* pItemBuffer;
} util_lru_Cache_t;

////////////////////////////////////////////////////////////////////////////////
//! \brief Adds an item to an LRU Software Cache
//!
//! This function adds an item from an LRU Software Cache.
//!
//! \param[in] pCache           Pointer to LRU Cache Structure
//! \param[in] pKey      	Pointer to Key of Key/Value pair to add to the cache
//! \param[in] pItem		Pointer to Value of Key/Value pair to add to the cache
//! \param[out] pEjectedItem    Pointer to Buffer for Ejected Item of Key/Value pair ejected from cache
//!
//! \note	If pEjectedItem is NULL it will not be populated upon ejection of an item
//!
//! \internal
//! \see To view the function definition, see lru.c.
////////////////////////////////////////////////////////////////////////////////
RtStatus_t util_lru_AddItemToCache(util_lru_Cache_t* pCache, void* pKey, void* pItem, void* pEjectedItem);
////////////////////////////////////////////////////////////////////////////////
//! \brief Finds an item in an LRU Cache
//!
//! Based on the key provided as input the function will search an LRU cache to find an item.
//! If found the item will be marked as the youngest in the cache so it will be the most recently
//! used and therefore least likely to be ejected upon future additions to the cache.
//!
//! \param[in] pCache           Pointer to LRU Cache Structure
//! \param[in] pKey      	Pointer to Key of Key/Value pair in the cache
//! \param[out] pItem		Pointer to populate with Value of Key/Value pair in the cache
//!
//! \internal
//! \see To view the function definition, see lru.c.
////////////////////////////////////////////////////////////////////////////////
RtStatus_t util_lru_FindCachedItem(util_lru_Cache_t* pCache, void* pKey, void* pItem);
////////////////////////////////////////////////////////////////////////////////
//! \brief Removes and item from an LRU software cache
//!
//! This function removes an item from an LRU software cache.
//!
//! \param[in] pCache               Pointer to LRU Cache Structure
//! \param[in] pKeyToEject          Pointer to Key of Key/Value pair to eject from the cache
//! \param[out] pEjectedItem        Pointer to Buffer for Ejected Item of Key/Value pair ejected from cache
//!
//! \note	If pEjectedItem is NULL, it will not be populated upon ejection of an item
//!
//! \internal
//! \see To view the function definition, see lru.c.
////////////////////////////////////////////////////////////////////////////////
RtStatus_t util_lru_RemoveItemFromCache(util_lru_Cache_t* pCache, void* pKeyToEject, void* pEjectedItem);
////////////////////////////////////////////////////////////////////////////////
//! \brief Initializes the LRU software cache.
//!
//! \fntype Function 
//!
//! \param[in] pCache       Pointer to the cache data structure for the cache being intialized.
//! \param[in] u16CacheSize Number of lines in the cache.
//! \param[in] u8KeySize    The size, in bytes, of a key for the cache.
//! \param[in] pKeybuffer   Pointer to a buffer of memory to store the keys of the cache.
//! \param[in] pTempKey     Pointer to a buffer in memory that is at least u8KeySize in size.
//! \param[in] u8ItemSize   The size, in bytes, of an item in the cache.
//! \param[in] pItemBuffer  Pointer to a buffer in memory to store the cache items in.
//! \param[in] pTempItem    Pointer to a buffer in memory as least u8ItemSize in size.
//!
//! \return Status of the message.
//! \retval SUCCESS
//!
//! \internal
//! \see To view the function definition, see lru_init.c.
////////////////////////////////////////////////////////////////////////////////
RtStatus_t util_lru_InitializeCache(util_lru_Cache_t* pCache,
	uint16_t u16CacheSize,
	uint8_t u8KeySize, void* pKeybuffer, void* pTempKey,
	uint8_t u8ItemSize, void* pItemBuffer, void* pTempItem);

#endif //__LRU_H
///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
//! @}

