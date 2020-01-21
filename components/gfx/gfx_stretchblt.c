////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_stretchblt.c
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
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_stretchblt_Generic(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect, gfx_Rect_t *dstRect, gfx_Bmp_t *pSrc, gfx_Rect_t *srcRect, gfx_StretchFilter_t filterType)
{
	
    gfx_Color_t cRGB;
    int x,y, sourceX, sourceY;
    gfx_format_PutPixel_t *pPutPixel  = gfx_format_PutPixel(pDest);
    gfx_format_GetPixel_t *pGetPixel = gfx_format_GetPixel(pSrc);

    assert(pPutPixel);
    assert(pGetPixel);
	//need to determine which corrdinates to use here for the get and putpixel

    if(filterType == NEAREST_NEIGHBOR_STRETCH){
		for(y = 0; y < Rect.height; y++){
            sourceY = ((y + Rect.y - dstRect->y) * srcRect->height)/dstRect->height + srcRect->y;
			for(x = 0; x < Rect.width; x++){
                sourceX = ((x + Rect.x - dstRect->x) * srcRect->width)/dstRect->width + srcRect->x;
				//find the nearest neighbor (no interpolation)
				pGetPixel(pPalette, pSrc, sourceX, sourceY, &cRGB);
				pPutPixel(pPalette, pDest, x+Rect.x, y+Rect.y, cRGB);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//! \internal
//! \brief This function copies a bitmap onto another bitmap (with stretching), bounded by the ClipRect.
//!
//! This function will adjust the clipping rectangle of the operation so that it is clipped to within
//! the widget's rectangle
//!
//! \param *pPalette Pointer to the color palette to use for palettized bitmaps
//! \param *pDest Pointer to the destination bitmap
//! \param clipRect Rectangle to clip the stretched bitmap to (does not affect scaling factor)
//! \param destRect complete destination rectangle (with appropriate DC offsets for the stretched bitmaps
//! \param *pSrc  pointer to the source bitmap that is to be stretched into the destination
//! \param srcRect rectangle for the source bitmap (only this portion of the source will be stretched to the output
//! \param filterType Type of interpolation filter to use for the stretching operation
//!
//! \note if NULL is passed as the as the pointer to the destRect or the srcRect
//!       then the entire rectangle for the source and destination bitmaps will be used
//!       as the dimesions for the source and destination rectangles.  This will mean
//!       that the scaling factor is determined based on the source and destination
//!       sizes and not on an application defined value
//! \note if a source rectangle is passed in that is larger than the source image,
//!       the rectangle will be reduced in size to match the size of the source
//!       rectangle.  This will also affect the scaling factor
////////////////////////////////////////////////////////////////////////////////
void gfx_stretchblt_Simple(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t ClipRect, gfx_Rect_t *dstRect, gfx_Bmp_t *pSrc, gfx_Rect_t *srcRect, gfx_StretchFilter_t filterType)
{
    gfx_Rect_t destRect, sourceRect;
	void (*pStretchBlt)(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect, 
                        gfx_Rect_t *dstRect, 
                        gfx_Bmp_t *pSrc, gfx_Rect_t *srcRect, gfx_StretchFilter_t filterType);

    //int SourceXOffset=0,SourceYOffset=0;
    
	//take care of user passing in NULL rectangle pointers for the source and destination rectangles
	//this code is placed here as opposed to inside gfx_bmp_StretchBitmapByAddr and gfx_bmp_StretchBitmap
	//because it is foreseeable that the application may want to call this API directly to avoid the
	//overhead of using a device context in the future
	if(!dstRect){
		destRect.height = pDest->uHeight;
		destRect.width = pDest->uWidth;
		destRect.x = 0;
		destRect.y = 0;
	}
	else{
		memcpy(&destRect,dstRect, sizeof(gfx_Rect_t));
	}
	
	if(!srcRect){
		sourceRect.height = pSrc->uHeight;
		sourceRect.width = pSrc->uWidth;
		sourceRect.x = 0;
		sourceRect.y = 0;
	}
	else{
		memcpy(&sourceRect,srcRect, sizeof(gfx_Rect_t));
	}


    //if the source rectangle is taller or wider than the source image than we need to adjust it
    if((sourceRect.x >= pSrc->uWidth) || (sourceRect.y >= pSrc->uHeight) || (sourceRect.x < 0) || (sourceRect.y < 0)){
        //source rectanlge is out of bounds, so return immediately
        return;
    }
    if((sourceRect.x + sourceRect.width) > pSrc->uWidth){
        sourceRect.width = pSrc->uWidth - sourceRect.x;
    }
    if((sourceRect.y + sourceRect.height) > pSrc->uHeight){
        sourceRect.height = pSrc->uHeight - sourceRect.y;
    }

    //four easy early escapes because destination coordinates are
    //entirely outside of the destination rect
    if(destRect.x >= ClipRect.x + ClipRect.width)
        return;
    if(destRect.y >= ClipRect.y + ClipRect.height)
        return;
    if((int)(destRect.x + pDest->uWidth - 1) < ClipRect.x)
        return;
    if((int)(destRect.y + pDest->uHeight - 1)< ClipRect.y)
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
    if(ClipRect.y + ClipRect.height > (int)(pDest->uHeight))
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
    if(ClipRect.x + ClipRect.width > (int)(destRect.x + destRect.width))
    {
        ClipRect.width = destRect.x + destRect.width - ClipRect.x;
    }

    //and the left hand edge.
    if(ClipRect.x <= destRect.x)
    {
        ClipRect.width-= (destRect.x - ClipRect.x);
        ClipRect.x = destRect.x;
    }

    //This should fix the right bottom edge
    if(ClipRect.y + ClipRect.height> (int)(destRect.y + destRect.height))
    {
        ClipRect.height= destRect.y + destRect.height - ClipRect.y;
    }

    //and the top edge
    if(ClipRect.y <= destRect.y)
    {
        ClipRect.height -= (destRect.y - ClipRect.y);
        ClipRect.y = destRect.y;
    }

    if(!gfx_rect_And(&ClipRect, &destRect)){
        return;     //there was no overlap
    }

    pStretchBlt = gfx_format_StretchBlt(pSrc,pDest);
    pStretchBlt(pPalette, pDest, ClipRect, &destRect, pSrc, &sourceRect, filterType);


}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bmp_StretchBitmapByAddr(gfx_DeviceContext_t *pDC, gfx_Rect_t *destRect, gfx_Bmp_t *pSrc, gfx_Rect_t *srcRect, gfx_StretchFilter_t filterType){
	gfx_Rect_t rect;
    assert(pDC);
    assert(pSrc);

    if(destRect){
        rect.height = destRect->height;
        rect.width = destRect->width;
        rect.x = destRect->x + pDC->i16xOffset; //offset the destination rectangle to the correct coordinates
        rect.y = destRect->y + pDC->i16yOffset;
    }
    else{
        rect.height = pDC->pBitmap->uHeight;
        rect.width = pDC->pBitmap->uWidth;
        rect.x = pDC->i16xOffset; //offset the destination rectangle to the correct coordinates
        rect.y = pDC->i16yOffset;        
    }

    //each entry in the clipping chain is a valid area to draw in
    if(pDC && pSrc)
    {
        gfx_RectNode_t *pClipNode = pDC->pActiveClipRegion;
        while(pClipNode)
        {   //cycle through each node and draw what's within it.
            gfx_stretchblt_Simple(pDC->pPalette, pDC->pBitmap, pClipNode->Rect, &rect, pSrc, srcRect, filterType);
            pClipNode = pClipNode->pNext;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bmp_StretchBitmap(gfx_DeviceContext_t *pDC, gfx_Rect_t *destRect, uint32_t uResourceID, gfx_Rect_t *srcRect, gfx_StretchFilter_t filterType)
{
    util_Handle_t hndl;
    gfx_Bmp_t *pBitmap = NULL;

    assert(pDC);

    //see if its in the cache.
    if(util_lru_FindCachedItem(g_gfx_Globals.pBitmapCache,&uResourceID, &hndl)== SUCCESS)
    {//found a handle, lets try to lock it.
        pBitmap = (gfx_Bmp_t*)util_hndl_Lock(hndl);
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
        gfx_bmp_StretchBitmapByAddr(pDC, destRect, pBitmap, srcRect, filterType);
    if(hndl)
    {   //make sure the handle is unlocked for later
        util_hndl_Unlock(hndl);
    }
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
