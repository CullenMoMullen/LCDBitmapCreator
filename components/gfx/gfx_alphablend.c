////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_alphablend.c
//! \brief   Contains runtime code for the Graphics subsystem.
//!
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////
#include "types.h"
#include "components/gfx/gfx.h"
#include "components/gfx/gfx_format.h"
#include "gfx_internal.h"
#include "os/os_resource_api.h"
#include "components/handlealloc/handlealloc.h"
#include "components/lru/lru.h"
#include "os/filesystem/fsapi.h"
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_alphablend_Generic(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t Rect, gfx_Bitmap_t *pSrc, int SourceXoffset, int SourceYoffset, uint8_t alphaValue)
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
                    cRGB |= (alphaValue << 24);     //add in the alpha channel.
                    pPutPixel(pPalette,pDest,x+Rect.x,y+Rect.y,cRGB);
                }
            }
        }
    }
}



////////////////////////////////////////////////////////////////////////////////
//! \internal
//! \brief This function bleds a bitmap into bitmap, bounded by the ClipRect.
//!
//! \param[in] pPalette Pointer to the color palette
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] ClipRect             The rectangle to draw within
//! \param[in] x                    The X position (relative to the upper left corner of the destination bitmap)
//!                                     to draw the source bitmap.
//! \param[in] y                    The Y position (relative to the upper left corner of the destination bitmap)
//!                                     to draw the source bitmap.
//! \param[in] alphaValue           Opacity value for the source bitmap
//! \note This function is an internal function and (probably) should not be called from the outside.
////////////////////////////////////////////////////////////////////////////////
void gfx_alphablend_Simple(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t ClipRect, int x, int y, gfx_Bitmap_t *pSrc, uint8_t alphaValue)
{
    void (*pAlphaBlend)(gfx_Color_t *pPalette, gfx_Bitmap_t*,gfx_Rect_t,
                                        gfx_Bitmap_t*,int,int, uint8_t);
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


    pAlphaBlend = gfx_format_AlphaBlend(pSrc,pDest);
    pAlphaBlend(pPalette,pDest, ClipRect,pSrc,SourceXOffset, SourceYOffset, alphaValue);

}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bmp_AlphaBlendBitmapByAddr(gfx_DeviceContext_t *pDC, gfx_Bitmap_t *pSrc, int x, int y, uint8_t alphaValue)
{
    assert(pDC);
    assert(pSrc);
    //each entry in the clipping chain is a valid area to draw in
    if(pDC && pSrc)
    {
        gfx_RectNode_t *pClipNode = pDC->pActiveClipRegion;
        while(pClipNode)
        {   //cycle through each node and draw what's within it.
            gfx_alphablend_Simple(pDC->pPalette,pDC->pBitmap, pClipNode->Rect, x+pDC->i16xOffset, y + pDC->i16yOffset, pSrc, alphaValue);
            pClipNode = pClipNode->pNext;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bmp_AlphaBlendBitmap(gfx_DeviceContext_t *pDC, uint32_t uResourceID, int x0, int y0, uint8_t alphaValue)
{
    util_Handle_t hndl;
    gfx_Bitmap_t *pBitmap = NULL;

    assert(pDC);

    //see if its in the cache.
    if(util_lru_FindCachedItem(g_gfx_Globals.pBitmapCache,&uResourceID, &hndl)== SUCCESS)
    {//found a handle, lets try to lock it.
        pBitmap = (gfx_Bitmap_t*)util_hndl_Lock(hndl);
        if(!pBitmap)
        {//no pointer returned from lock, it must have been purged.
            util_lru_RemoveItemFromCache(g_gfx_Globals.pBitmapCache,&uResourceID, NULL);
        }
    }
    if(!pBitmap)
    {
        pBitmap = gfx_rsrc_LoadBitmap(uResourceID, &hndl);
        if(pBitmap)
        {
            util_Handle_t hEjectedHndl = INVALID_HANDLE;
            //finish housekeeping on the handle
            util_hndl_SetPurgeable(hndl, true);
            util_lru_AddItemToCache(g_gfx_Globals.pBitmapCache, &uResourceID, &hndl, &hEjectedHndl);
            if(hEjectedHndl != INVALID_HANDLE)
                util_hndl_Free(hEjectedHndl);

        }
    }
    //draw bitmap.
    if(pBitmap)
        gfx_bmp_AlphaBlendBitmapByAddr(pDC,pBitmap,x0,y0, alphaValue);
    if(hndl)
    {   //make sure the handle is unlocked for later
        util_hndl_Unlock(hndl);
    }
}
////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}

