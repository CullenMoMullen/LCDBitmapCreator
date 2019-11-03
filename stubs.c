// stubs.c : Defines functions that are not needed by the image convert utility
//
#include "types.h"
#include "components/gfx/gfx.h"
#include "components/gfx/gfx_internal.h"
#include "components/handlealloc/handlealloc.h"
#include "components/lru/lru.h"
#include "os/filesystem/fsapi.h"
#include <stdlib.h>
#include  <memory.h>

gfx_Globals_t g_gfx_Globals;

gfx_Color_t g_Pallete[16] = {
									COLOR_BLACK,
									COLOR_WHITE,
									COLOR_TEAL,
									COLOR_PURPLE,
									COLOR_BLUE,
									COLOR_LIGHT_GRAY,
									COLOR_DARK_GRAY,
									COLOR_DARK_TEAL,
									COLOR_DARK_PURPLE,
									COLOR_DARK_BLUE,
									COLOR_YELLOW,
									COLOR_GREEN,
									COLOR_DARK_YELLOW,
									COLOR_DARK_GREEN,
									COLOR_RED,
									COLOR_DARK_RED
};

REENTRANT RtStatus_t Fclose(int32_t HandleNumber) {
	return SUCCESS;
}

REENTRANT int32_t Fread(int32_t HandleNumber, uint8_t* Buffer, int32_t NumBytesToRead) {
	return 0;
}


util_Handle_t util_hndl_Alloc(uint32_t size) {
	
	return 0;
}

void* util_hndl_AllocLocked(uint32_t size, bool bClear) {
	void* p = NULL;
	p = malloc(size);
	if (bClear && p != NULL) {
		memset(p, 0, size);
	}
	return p;
}

void* util_hndl_Lock(util_Handle_t handle) {
	return NULL;
}

void util_hndl_Free(util_Handle_t handle) {
	return;
}

void util_hndl_FreeByAddress(void* pPtr) {
	free(pPtr);
	return;
}

void util_hndl_Unlock(util_Handle_t handle) {
	return;
}

bool util_hndl_SetPurgeable(util_Handle_t handle, bool bPurgeable) {
	return true;
}

uint32_t util_hndl_GetLargestFreeBlock(void) {
	return 0;
}

int32_t os_resource_Open(uint32_t ResourceID, uint32_t* ResourceSize, uint16_t* ResourceValue) {
	return 0;
}

RtStatus_t util_lru_AddItemToCache(util_lru_Cache_t* pCache, void* pKey, void* pItem, void* pEjectedItem) {
	return SUCCESS;
}

RtStatus_t util_lru_FindCachedItem(util_lru_Cache_t* pCache, void* pKey, void* pItem) {
	return SUCCESS;
}

RtStatus_t util_lru_RemoveItemFromCache(util_lru_Cache_t* pCache, void* pKeyToEject, void* pEjectedItem) {
	return SUCCESS;
}

bool gfx_rect_And(gfx_Rect_t* pRect, gfx_Rect_t* pRectB) {
	return 0;
}


