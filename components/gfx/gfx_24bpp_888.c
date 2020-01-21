////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_24bpp_888.c
//! \brief   Contains 24BPP 888 routines.
//! \version 1.0
//!
////////////////////////////////////////////////////////////////////////////////
#include "types.h"
#include "components/gfx/gfx.h"
#include "components/gfx/gfx_format.h"
#include "components/runtime/runtime.h"
#include "gfx_internal.h"
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_24BPP_888(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                           gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset)
{
    int y;
    unsigned char *pSourceOrigin;
    unsigned char *pDestOrigin;
    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;
    pDestOrigin = &((unsigned char *)pDest->pData)[(iDestStride * Rect.y + Rect.x) * 3];
    pSourceOrigin=&((unsigned char *)pSrc ->pData)[(iSourceStride*SourceYoffset + SourceXoffset) * 3];

    for(y=0;y<Rect.height;y++)
    {
        unsigned char *pSourceData = pSourceOrigin;
        unsigned char *pDestData = pDestOrigin;
        if(y+SourceYoffset >= 0 && y+SourceYoffset < (int)pSrc->uHeight)
        {
            memcpy(pDestData, pSourceData, Rect.width*3);
        }
        pDestOrigin += iDestStride * 3;
        pSourceOrigin+=iSourceStride * 3;
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_24BPP_888_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                           gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset)
{
    int y,x;
    unsigned char *pSourceOrigin;
    unsigned short *pDestOrigin;
    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;
    pDestOrigin = &((unsigned short *)pDest->pData)[iDestStride * Rect.y + Rect.x];
    pSourceOrigin=&((unsigned char *)pSrc ->pData)[(iSourceStride*SourceYoffset + SourceXoffset) * 3];

    for(y=0;y<Rect.height;y++)
    {
        unsigned char *pSourceData = pSourceOrigin;
        unsigned short *pDestData = pDestOrigin;
        if(y+SourceYoffset >= 0 && y+SourceYoffset < (int)pSrc->uHeight)
        {
            //copy the line of 24bpp pixels to the 16bpp surface
            x = Rect.width;
            do{
                //pSourceData points to the Red component
                *pDestData = 0;
                *pDestData |= (*pSourceData & 0xF8) << 8;    //only take top 5 bits of Red component
                pSourceData++;
                *pDestData |= (*pSourceData & 0xFC) << 3;    //only take top 6 bits of Green component
                pSourceData++;
                *pDestData |= (*pSourceData & 0xF8) >> 2;    //only take top 5 bits of Blue component
                pDestData++;
            }while(--x);
        }
        pDestOrigin += iDestStride;
        pSourceOrigin += iSourceStride * 3;
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_24BPP_888(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap, uint16_t u16x, uint16_t u16y, gfx_Color_t cRGB)
{
    unsigned char *pData;
    uint8_t alphaValue = GET_ALPHA(cRGB);
    assert(pBitmap);
    pData = (unsigned char*)pBitmap->pData;
    if(alphaValue == ALPHA_OPAQUE){ //opaque
        pData[(u16y*pBitmap->uWidth+u16x)*3  ] = (cRGB & 0x000000ff);  //red
        pData[(u16y*pBitmap->uWidth+u16x)*3+1] = (cRGB & 0x0000ff00) >> 8; //green
        pData[(u16y*pBitmap->uWidth+u16x)*3+2] = (cRGB & 0x00ff0000) >> 16; //blue
    }
    else if(alphaValue != ALPHA_TRANSPARENT){    //make sure it isn't fully transparent
        uint16_t BgRComponent, FgRComponent;
        uint16_t BgGComponent, FgGComponent;
        uint16_t BgBComponent, FgBComponent;
        gfx_Color_t BgTrueColor;
        //optimization (do not call GetPixel here) instead index into pData
        gfx_GetPixel_24BPP_888(pPalette, pBitmap, u16x, u16y, &BgTrueColor);
        BgRComponent = GET_RED(BgTrueColor) * (256-alphaValue);
        BgGComponent = GET_GREEN(BgTrueColor) * (256-alphaValue);
        BgBComponent = GET_BLUE(BgTrueColor) * (256-alphaValue);
        FgRComponent = GET_RED(cRGB) * (alphaValue);
        FgGComponent = GET_GREEN(cRGB) * (alphaValue);
        FgBComponent = GET_BLUE(cRGB) * (alphaValue);
        FgRComponent = (FgRComponent + BgRComponent) >> 8;
        FgGComponent = (FgGComponent + BgGComponent) >> 8;
        FgBComponent = (FgBComponent + BgBComponent) >> 8;
        pData[(u16y*pBitmap->uWidth+u16x)*3  ] = (FgRComponent & 0x00ff);  //red
        pData[(u16y*pBitmap->uWidth+u16x)*3+1] = (FgGComponent & 0x00ff);  //green
        pData[(u16y*pBitmap->uWidth+u16x)*3+2] = (FgBComponent & 0x00ff);  //blue   
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_24BPP_888(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap, uint16_t x, uint16_t y, gfx_Color_t *pRGB)
{
    unsigned char *pData;
    gfx_Color_t uPixel;
    assert(pBitmap);
    assert(pRGB);
    pData = (unsigned char*)pBitmap->pData + (y*pBitmap->uWidth+x)*3;
    uPixel = (gfx_Color_t)((pData[0]) | ((pData[1]) << 8) | (pData[2]<<16));
    *pRGB = uPixel;
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_24BPP_888(uint16_t u16x, uint16_t u16y)
{
    return u16x*u16y*3;
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
