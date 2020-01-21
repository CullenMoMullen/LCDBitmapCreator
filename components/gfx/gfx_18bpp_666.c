////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_18bpp_666.c
//! \brief   Contains 16BPP 565 routines.
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
void gfx_bitblit_18BPP_666(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                           gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset)
{
    int y;
    unsigned char *pSourceOrigin;
    unsigned char *pDestOrigin;
    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;
    pDestOrigin = &((unsigned char *)pDest->pData)[(iDestStride * Rect.y + Rect.x) * 3];
    pSourceOrigin=&((unsigned char *)pSrc ->pData)[(iSourceStride*SourceYoffset + SourceXoffset) * 3];
    //! \todo:  optimize:   pre-calculate what the range and offsets will be so no comparisons happen
    //!                     during the blit
    //! \todo:  optimize:   perhaps make a 'get multiple pixels' so the penalty of function calling
    //!                     will be lessoned.
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
void gfx_PutPixel_18BPP_666(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap, uint16_t u16x, uint16_t u16y, gfx_Color_t cRGB)
{
    unsigned char *pData;
    uint8_t alphaValue = GET_ALPHA(cRGB);
    assert(pBitmap);
    pData = (unsigned char*)pBitmap->pData;
    if(alphaValue == ALPHA_OPAQUE){ //opaque
        pData[(u16y*pBitmap->uWidth+u16x)*3  ] = (cRGB & 0x000000fc) >> 2;  //red
        pData[(u16y*pBitmap->uWidth+u16x)*3+1] = (cRGB & 0x0000fc00) >> 10; //green
        pData[(u16y*pBitmap->uWidth+u16x)*3+2] = (cRGB & 0x00fc0000) >> 18; //blue
    }
    else if(alphaValue != ALPHA_TRANSPARENT){    //make sure it isn't fully transparent
        uint16_t BgRComponent, FgRComponent;
        uint16_t BgGComponent, FgGComponent;
        uint16_t BgBComponent, FgBComponent;
        gfx_Color_t BgTrueColor;
        //optimization (do not call GetPixel here) instead index into pData
        gfx_GetPixel_18BPP_666(pPalette, pBitmap, u16x, u16y, &BgTrueColor);
        BgRComponent = GET_RED(BgTrueColor) * (256-alphaValue);
        BgGComponent = GET_GREEN(BgTrueColor) * (256-alphaValue);
        BgBComponent = GET_BLUE(BgTrueColor) * (256-alphaValue);
        FgRComponent = GET_RED(cRGB) * (alphaValue);
        FgGComponent = GET_GREEN(cRGB) * (alphaValue);
        FgBComponent = GET_BLUE(cRGB) * (alphaValue);
        FgRComponent = (FgRComponent + BgRComponent) >> 8;
        FgGComponent = (FgGComponent + BgGComponent) >> 8;
        FgBComponent = (FgBComponent + BgBComponent) >> 8;
        pData[(u16y*pBitmap->uWidth+u16x)*3  ] = (FgRComponent & 0x00fc) >> 2;  //red
        pData[(u16y*pBitmap->uWidth+u16x)*3+1] = (FgGComponent & 0x00fc) >> 2;  //green
        pData[(u16y*pBitmap->uWidth+u16x)*3+2] = (FgBComponent & 0x00fc) >> 2;  //blue   
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_18BPP_666(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap, uint16_t x, uint16_t y, gfx_Color_t *pRGB)
{
    unsigned char *pData;
    gfx_Color_t uPixel;
    assert(pBitmap);
    assert(pRGB);
    pData = (unsigned char*)pBitmap->pData + (y*pBitmap->uWidth+x)*3;
    uPixel = (gfx_Color_t)(((pData[0]&0x3f) << 2) | ((pData[1]&0x3f) << 10) | ((pData[2]&0x3f)<<18));
    *pRGB = uPixel;
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_18BPP_666(uint16_t u16x, uint16_t u16y)
{
    return u16x*u16y*3;
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_DrawClippedLine_18BPP_666(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, int x0, int y0, int x1, int y1, gfx_Color_t color)
{
    uint32_t u32Stride;
    uint8_t *pData;
    assert(pDest);
    u32Stride = pDest->uWidth * 3;
    if((y0==y1) && (GET_ALPHA(color) == ALPHA_OPAQUE))
    {//its a horizontal line
        //convert the ideal color to 18BPP.
        uint32_t u32Color =    ((color & 0x00FCFCFC) >> 2);
        //make sure we draw from left to right
        if(x0 > x1)
        {
            uint16_t temp = x0;
            x0 = x1;
            x1 = temp;
        }
        //get the starting position.
        pData = &((uint8_t*)(pDest->pData))[x0*3 + y0*u32Stride];
        rt_24bitset(pData, u32Color,x1-x0+1);
    }
    else if ((x0==x1) && (GET_ALPHA(color) == ALPHA_OPAQUE))
    {//a vertical line
        //get the individual byte components
        uint8_t u8r = (color >> 2 )&0xcf;
        uint8_t u8g = (color >> 10)&0xcf;
        uint8_t u8b = (color >> 18)&0xcf;
        //make sure we draw from top to bottom
        if(y0 > y1)
        {
            uint16_t temp = y0;
            y0 = y1;
            y1 = temp;
        }
        //get the starting position
        pData = &((uint8_t*)(pDest->pData))[x0*3 + y0*u32Stride];
        for(;y0<=y1;y0++)
        {
            *(pData  ) = u8r;
            *(pData+1) = u8g;
            *(pData+2) = u8b;
            pData += u32Stride;
        }
    }
    else
    {
        //just use the unoptimized generic for now
        gfx_2d_DrawClippedLineGeneric(pPalette, pDest, x0, y0, x1, y1, color);   
    }
}


////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
