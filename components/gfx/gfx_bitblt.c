////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_bitblt.c
//! \brief   Contains runtime code for the Graphics subsystem.
//!
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "types.h"
#include "components/gfx/gfx.h"
#include "components/gfx/gfx_format.h"
#include "components/gfx/gfx_internal.h"
#include "os/os_resource_api.h"
#include "components/handlealloc/handlealloc.h"
#include "components/lru/lru.h"
#include "os/filesystem/fsapi.h"

#define MAX_BITMAP_SZ (320 * 4)
////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bmp_RotateBitmap(gfx_Color_t *pPalette, gfx_Bmp_t * pSrc, gfx_Bmp_t * pDest, gfx_OrientationEnum_t eOrientation)
{
    gfx_Color_t cRGB;
    unsigned int x, y;
    gfx_format_PutPixel_t *pPutPixel  = gfx_format_PutPixel(pDest);
    gfx_format_GetPixel_t *pGetPixel = gfx_format_GetPixel(pSrc);

    assert(pPutPixel);
    assert(pGetPixel);

    switch (eOrientation)
    {
        default:
        case GFX_ROTATE_0:
            for(y=0; y<pSrc->uHeight; y++)
                for(x=0; x<pSrc->uWidth; x++)
                {
                    pGetPixel(pPalette, pSrc,(uint16_t)x,(uint16_t)y,&cRGB);                       
                    pPutPixel(pPalette, pDest,(uint16_t)x,(uint16_t)y,cRGB);
                }       
            break;
        case GFX_ROTATE_90:
            for(y=0; y<pSrc->uHeight; y++)
                for(x=0; x<pSrc->uWidth; x++)
                {
                    pGetPixel(pPalette, pSrc,(uint16_t)x,(uint16_t)y,&cRGB);
                    pPutPixel(pPalette, pDest,(uint16_t)y,(uint16_t)(pDest->uHeight-x-1),cRGB);
                }       
            break;
        case GFX_ROTATE_180:
            for(y=0; y<pSrc->uHeight; y++)
                for(x=0; x<pSrc->uWidth; x++)
                {
                    pGetPixel(pPalette, pSrc,(uint16_t)x,(uint16_t)y,&cRGB);
                    pPutPixel(pPalette, pDest,(uint16_t)(pDest->uWidth-x-1),(uint16_t)(pDest->uHeight-y-1),cRGB);
                }
            break;
        case GFX_ROTATE_270:
            for(y=0; y<pSrc->uHeight; y++)
                for(x=0; x<pSrc->uWidth; x++)
                {
                    pGetPixel(pPalette, pSrc,(uint16_t)x,(uint16_t)y,&cRGB);
                    pPutPixel(pPalette, pDest,(uint16_t)(pDest->uWidth-y-1),(uint16_t)x,cRGB);
                }       
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
gfx_Bmp_t*gfx_bmp_CreateBitmap(unsigned char uBitmapTypeIdentifier, uint16_t uWidth, uint16_t uHeight)
{
    gfx_format_GetDataSize_t *pGetDataSize;
    gfx_Bmp_t*pBmp = NULL;
    uint32_t uSize;
    pGetDataSize = gfx_format_GetDataSize(uBitmapTypeIdentifier);
    uSize = sizeof(gfx_Bmp_t) + pGetDataSize (uWidth,uHeight);
    pBmp = (gfx_Bmp_t*)util_hndl_AllocLocked(uSize, true);
    if(pBmp)
    {
        pBmp->uType = uBitmapTypeIdentifier;
        pBmp->uHeight= uHeight;
        pBmp->uWidth = uWidth;
    }
    return pBmp;
}


////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
bool gfx_bmp_GetPixel(gfx_Color_t *pPalette, gfx_Bmp_t*pSrc, int x , int y, gfx_Color_t *pRGB)
{
    if(x <(int)pSrc->uWidth && y < (int)pSrc->uHeight)
    {
        gfx_format_GetPixel_t *pGetPixel = gfx_format_GetPixel(pSrc);
        assert(pGetPixel);
        pGetPixel(pPalette, pSrc, (uint16_t)x, (uint16_t)y, pRGB);
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
bool gfx_bmp_PutPixel(gfx_Color_t *pPalette, gfx_Bmp_t*pDest, int x , int y, gfx_Color_t cRGB)
{
    if(x <(int)pDest->uWidth && y < (int)pDest->uHeight)
    {
        gfx_format_PutPixel_t *pPutPixel  = gfx_format_PutPixel(pDest);
        assert(pPutPixel);
        pPutPixel(pPalette, pDest,(uint16_t)x,(uint16_t)y,cRGB);
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bitblt_Generic(gfx_Color_t *pPalette, gfx_Bmp_t*pDest, gfx_Rect_t Rect, gfx_Bmp_t*pSrc, int SourceXoffset, int SourceYoffset)
{
    gfx_Color_t cRGB;
    int x, y;
    gfx_format_PutPixel_t *pPutPixel  = gfx_format_PutPixel(pDest);
    gfx_format_GetPixel_t *pGetPixel = gfx_format_GetPixel(pSrc);

    assert(pPutPixel);
    assert(pGetPixel);

    //! \todo:  optimize:   pre-calculate what the range and offsets will be so no comparisons happen during the blit
    //! \todo:  optimize:   perhaps make a 'get multiple pixels' so the penalty of function calling will be lessoned.
    for(y=0;y<Rect.height;y++)
    {
        if(y+SourceYoffset >= 0 && y+SourceYoffset < (int)pSrc->uHeight)
        {
            for(x=0;x<Rect.width;x++)
            {
                if(x+SourceXoffset >= 0 && x+SourceXoffset < (int)pSrc->uWidth)
                {
                    pGetPixel(pPalette,pSrc,x+SourceXoffset,y+SourceYoffset,&cRGB);
                    if(cRGB & 0xff000000)
                    {
                        pPutPixel(pPalette,pDest,x+Rect.x,y+Rect.y,cRGB);
                    }
                }
            }
        }
    }
}



////////////////////////////////////////////////////////////////////////////////
//! \internal
//! \brief This function copies a bitmap onto another bitmap, bounded by the ClipRect.
//!
//! \param[in] pPalette Pointer to the color palette
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] ClipRect             The rectangle to draw within
//! \param[in] x                    The X position (relative to the upper left corner of the destination bitmap)
//!                                     to draw the source bitmap.
//! \param[in] y                    The Y position (relative to the upper left corner of the destination bitmap)
//!                                     to draw the source bitmap.
//! \note This function is an internal function and (probably) should not be called from the outside.
////////////////////////////////////////////////////////////////////////////////
void gfx_bitblt_Simple(gfx_Color_t *pPalette, gfx_Bmp_t*pDest, gfx_Rect_t ClipRect, int x, int y, gfx_Bmp_t* pSrc)
{
    void (*pBitBlt)(gfx_Color_t *pPalette, gfx_Bmp_t*,gfx_Rect_t, gfx_Bmp_t*,int,int);
    int SourceXOffset=0,SourceYOffset=0;
    //four easy early escapes because destination coordinates are
    //entirely outside of the destination rect
    if(x> ClipRect.x + ClipRect.width-1)
        return;
    if(y> ClipRect.y + ClipRect.height-1)
        return;
    if((int)(x + pSrc->uWidth-1) < ClipRect.x)
        return;
    if((int)(y + pSrc->uHeight-1)< ClipRect.y)
        return;

    // The following 4 if blocks will make sure that the clipping rectangle lies completely within the destination rect.
    // It is possible that this is already guranteed, however only becuase of the User Interface Manager.  To make this
    // function useable elsewhere, it is good to have this code.  Consider removing to save space if you find it
    // unnecessary.

    //This should fix the right hand edge
    if(ClipRect.x + ClipRect.width > (int)(pDest->uWidth))
    {
        ClipRect.width = pDest->uWidth - ClipRect.x;
    }

    //and the left hand edge.
    if(ClipRect.x < 0)
    {
        ClipRect.width += ClipRect.x;   //decrease the width of the clipping rect
        ClipRect.x = 0; //move the ClipRect left edge
    }

    //This should fix the bottom edge
    if(ClipRect.y + ClipRect.height> (int)(pDest->uHeight))
    {
        ClipRect.height= pDest->uHeight- ClipRect.y;
    }

    //and the top edge
    if(ClipRect.y < 0)
    {
        ClipRect.height += ClipRect.y;   //decrease the width of the clipping rect
        ClipRect.y = 0; //move the ClipRect left edge
    }

    //     (so the bounds checking can be removed from the optimized bitblt functions)
    //This should fix the right hand edge
    if(ClipRect.x + ClipRect.width > (int)(x + pSrc->uWidth))
    {
        ClipRect.width = x+pSrc->uWidth - ClipRect.x;
    }

    //and the left hand edge.
    if(ClipRect.x>x)
    {
        SourceXOffset = ClipRect.x-x;
    }
    else
    {
        ClipRect.width-= (x-ClipRect.x);
        ClipRect.x = x;
    }

    //This should fix the right bottom edge
    if(ClipRect.y + ClipRect.height> (int)(y + pSrc->uHeight))
    {
        ClipRect.height= y+pSrc->uHeight- ClipRect.y;
    }

    //and the top edge
    if(ClipRect.y>y)
    {
        SourceYOffset = ClipRect.y-y;
    }
    else
    {
        ClipRect.height -= (y-ClipRect.y);
        ClipRect.y = y;
    }



    pBitBlt = gfx_format_BitBlt(pSrc,pDest);
    pBitBlt(pPalette,pDest, ClipRect,pSrc,SourceXOffset, SourceYOffset);

}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bmp_DrawBitmapByAddr(gfx_DeviceContext_t *pDC, gfx_Bmp_t*pSrc, int x, int y )
{
    assert(pDC);
    assert(pSrc);
    //each entry in the clipping chain is a valid area to draw in
    if(pDC && pSrc)
    {
        gfx_RectNode_t *pClipNode = pDC->pActiveClipRegion;
        while(pClipNode)
        {   //cycle through each node and draw what's within it.
            gfx_bitblt_Simple(pDC->pPalette,pDC->pBitmap, pClipNode->Rect, x+pDC->i16xOffset, y + pDC->i16yOffset, pSrc);
            pClipNode = pClipNode->pNext;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
//! \brief Used to release the memory used by a bitmap back to the pool.
//!
//! \param[in] pBitmap Pointer to the gfx_Bmp_t to release
////////////////////////////////////////////////////////////////////////////////
void gfx_bmp_DeleteBitmap(gfx_Bmp_t* pBitmap)
{
    free(pBitmap);
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
gfx_Bmp_t*gfx_rsrc_LoadBitmap(uint32_t uResourceID, util_Handle_t *pHndl)
{
    util_Handle_t hndl=INVALID_HANDLE;
    gfx_Bmp_t*pBitmap = NULL;
    uint32_t u32Size;

    int32_t iFileHandle = os_resource_Open(uResourceID,&u32Size,NULL);

    if (iFileHandle < 0) return NULL;

    hndl = util_hndl_Alloc(u32Size);
    if(hndl) {
    int32_t  iRetValue;

    pBitmap = (gfx_Bmp_t*)util_hndl_Lock(hndl);
    iRetValue = Fread(iFileHandle,(uint8_t *) pBitmap,u32Size);

    assert(iRetValue == u32Size);

    if (iRetValue < 0) {
        util_hndl_Unlock(hndl);
        util_hndl_Free(hndl);
        hndl=INVALID_HANDLE;
        pBitmap = NULL;
    }//if
    }//if

    Fclose(iFileHandle);

    if (pHndl) *pHndl = hndl;

    return pBitmap;
}

static void gfx_bmp_DrawLargeBitmap(int FileHandle, uint32_t size,
                    gfx_DeviceContext_t *pDC,
                    uint32_t uResourceID,
                    int x0, int y0)
{
    uint32_t stride, length;
    uint32_t scratch_buffer;

    gfx_Bmp_t* pBitmap;

    int ret;

    /* Retrieve of uType, uWidth, and uHeight */
    ret = Fread(FileHandle, (uint8_t*) &scratch_buffer, 4);
    if (ret < 0) return;

    size -= 4;
    pBitmap = (gfx_Bmp_t*) &scratch_buffer;

    stride = gfx_format_GetDataSize(pBitmap->uType)(pBitmap->uWidth, 1);
    if (stride == 0) stride = pBitmap->uWidth * 2;

    length = util_hndl_GetLargestFreeBlock();
    if (length < stride) length = stride;

    length -= (length % stride);

    pBitmap = (gfx_Bmp_t*)util_hndl_AllocLocked(length + sizeof(gfx_Bmp_t), false);
    if (pBitmap == NULL) return;

    /* Copy off uType, uWidth, and uHeight */
    memcpy(pBitmap, &scratch_buffer, 4);

    do {
    uint32_t bytes_to_copy = (length < size) ? length : size;
    int ret;

    ret = Fread(FileHandle, (uint8_t*) pBitmap->pData, bytes_to_copy);
    if (ret < 0) break;

    pBitmap->uHeight = bytes_to_copy / stride;

    gfx_bmp_DrawBitmapByAddr(pDC, pBitmap, x0, y0);

    y0 += pBitmap->uHeight;
    size -= bytes_to_copy;
    } while (size > 0);

    util_hndl_FreeByAddress(pBitmap);
}//gfx_bmp_DrawLargeBitmap

static void gfx_bmp_DrawSmallBitmap(int FileHandle, uint32_t size,
                    gfx_DeviceContext_t *pDC,
                    uint32_t uResourceID,
                    int x0, int y0)
{
    util_Handle_t handle;
    util_Handle_t hEjectedHndl = INVALID_HANDLE;

    gfx_Bmp_t* pBitmap;

    int ret;

    handle = util_hndl_Alloc(size);
    if (handle == INVALID_HANDLE){ 
        gfx_bmp_DrawLargeBitmap(FileHandle, size,pDC,uResourceID,x0, y0);    
        return;
    }

    pBitmap = (gfx_Bmp_t*)util_hndl_Lock(handle);
    if (pBitmap == NULL) {
    util_hndl_Free(handle);
    return;
    }//if

    ret = Fread(FileHandle, (uint8_t*) pBitmap, size);
    if (ret < 0) {
    util_hndl_Unlock(handle);
    util_hndl_Free(handle);

    return;
    }//if

    //finish housekeeping on the handle
    util_hndl_SetPurgeable(handle, true);
    util_lru_AddItemToCache(g_gfx_Globals.pBitmapCache,
                &uResourceID,
                &handle,
                &hEjectedHndl);

    if (hEjectedHndl != INVALID_HANDLE)
    util_hndl_Free(hEjectedHndl);

    gfx_bmp_DrawBitmapByAddr(pDC, pBitmap, x0, y0);

    util_hndl_Unlock(handle);
}//gfx_bmp_DrawSmallBitmap

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bmp_DrawBitmap(gfx_DeviceContext_t *pDC,
            uint32_t uResourceID,
            int x0, int y0)
{
    util_Handle_t hndl;
    gfx_Bmp_t*pBitmap = NULL;

    assert(pDC);

    //see if its in the cache.
    if (util_lru_FindCachedItem(g_gfx_Globals.pBitmapCache,
                &uResourceID,
                &hndl) == SUCCESS) {
    //found a handle, lets try to lock it.
        pBitmap = (gfx_Bmp_t*)util_hndl_Lock(hndl);

        if (!pBitmap) {
        //no pointer returned from lock, it must have been purged.
            util_lru_RemoveItemFromCache(g_gfx_Globals.pBitmapCache,
                     &uResourceID,
                     NULL);
    }//if
    }//if

    if (pBitmap) {
    gfx_bmp_DrawBitmapByAddr(pDC, pBitmap, x0, y0);

    if (hndl) util_hndl_Unlock(hndl);
    } else {
    int FileHandle;
    uint32_t size;

    FileHandle = os_resource_Open(uResourceID, &size, NULL);
    if (FileHandle < 0) return;

    if (size < MAX_BITMAP_SZ)
        gfx_bmp_DrawSmallBitmap(FileHandle, size,
                    pDC, uResourceID,
                    x0, y0);
    else
        gfx_bmp_DrawLargeBitmap(FileHandle, size,
                    pDC, uResourceID,
                    x0, y0);

    Fclose(FileHandle);
    }//if
}//gfx_bmp_DrawBitmap


////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}

