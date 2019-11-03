////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_16bpp_565.c
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
void gfx_bitblit_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t Rect,
                           gfx_Bitmap_t *pSrc, int SourceXoffset, int SourceYoffset)
{
    int y;
    unsigned short *pSourceOrigin;
    unsigned short *pDestOrigin;
    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;
    bool bOpaque = (pPalette[1] & 0xff000000) ? true : false;   //determines if the transparent bit was set in the bitmap
    pDestOrigin = &((unsigned short *)pDest->pData)[iDestStride * Rect.y + Rect.x];
    pSourceOrigin=&((unsigned short *)pSrc ->pData)[iSourceStride*SourceYoffset + SourceXoffset];

    //! It is not reccommended to change these loops as they are optimized for the Green Hills Compiler with Ospeed
    //! optimization setting and as are will fit in one cache block if properly aligned.
    if((Rect.height > 0) && (Rect.width > 0))
    {
        unsigned short *pSourceData;
        unsigned short *pDestData;
        y=Rect.height;
        if(!bOpaque){
            int x;
            unsigned short transparentColor = ((pPalette[1] & 0x00F80000) >> 19) | ((pPalette[1] & 0x0000FC00) >> 5) | ((pPalette[1] & 0x000000F8) << 8);
            do{
                pSourceData = pSourceOrigin;
                pDestData = pDestOrigin;
                x=Rect.width;
                do
                {
                    //only copy the pixel if it isn't the background color
                    if(*pSourceData != transparentColor)    //check if the source color matches the transparent color!
                        *pDestData = *pSourceData;          //if not draw the pixel
                    pDestData++;
                    pSourceData++;
                }while(--x);
                pDestOrigin += iDestStride;
                pSourceOrigin+=iSourceStride;
            }while(--y);        
        }
        else{
            do
            {
                pSourceData = pSourceOrigin;
                pDestData = pDestOrigin;

                memcpy(pDestData, pSourceData, Rect.width*2);

                pDestOrigin += iDestStride;
                pSourceOrigin+=iSourceStride;
            }while(--y);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pBitmap,
                            uint16_t u16x, uint16_t u16y, gfx_Color_t cRGB)
{
    unsigned short *pData;
    uint8_t alphaValue = GET_ALPHA(cRGB);
    assert(pBitmap);
    pData = (unsigned short*)pBitmap->pData;
    if(alphaValue == ALPHA_OPAQUE){ //opaque
        pData[u16y*pBitmap->uWidth+u16x] = ((cRGB & 0x00F80000) >>19) |
                                        ((cRGB & 0x0000FC00) >> 5) |
                                        ((cRGB & 0x000000F8) << 8);
    }
    else if(alphaValue != ALPHA_TRANSPARENT){    //make sure it isn't fully transparent
        uint16_t BgRComponent, FgRComponent;
        uint16_t BgGComponent, FgGComponent;
        uint16_t BgBComponent, FgBComponent;
        gfx_Color_t BgTrueColor;
        //optimization (do not call GetPixel here) instead index into pData
        gfx_GetPixel_16BPP_565(pPalette, pBitmap, u16x, u16y, &BgTrueColor);
        BgRComponent = GET_RED(BgTrueColor) * (256-alphaValue);
        BgGComponent = GET_GREEN(BgTrueColor) * (256-alphaValue);
        BgBComponent = GET_BLUE(BgTrueColor) * (256-alphaValue);
        FgRComponent = GET_RED(cRGB) * (alphaValue);
        FgGComponent = GET_GREEN(cRGB) * (alphaValue);
        FgBComponent = GET_BLUE(cRGB) * (alphaValue);
        FgRComponent = (FgRComponent + BgRComponent) >> 8;
        FgGComponent = (FgGComponent + BgGComponent) >> 8;
        FgBComponent = (FgBComponent + BgBComponent) >> 8;
        pData[u16y*pBitmap->uWidth+u16x] = ((FgBComponent & 0x00F8) >>3) |
                                        ((FgGComponent & 0x00FC) << 3) |
                                        ((FgRComponent & 0x00F8) << 8);    
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pBitmap,
                            uint16_t x, uint16_t y, gfx_Color_t *pRGB)
{
    unsigned short *pData;
    gfx_Color_t uPixel;
    assert(pBitmap);
    assert(pRGB);
    pData = (unsigned short*)pBitmap->pData;
    uPixel = (gfx_Color_t)(pData[y*pBitmap->uWidth+x]);
    *pRGB = 0xff000000 | ((uPixel & 0xF800) >> 8) | ((uPixel & 0x07E0) << 5) | ((uPixel & 0x001F) << 19);
}


////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_16BPP_565(uint16_t u16Width, uint16_t u16Height)
{
    return u16Width*u16Height*2;
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_DrawClippedLine_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, int x0, int y0, int x1, int y1, gfx_Color_t color)
{
    uint16_t u16Color =     ((color & 0x00F80000) >>19) |
                            ((color & 0x0000FC00) >> 5) |
                            ((color & 0x000000F8) << 8);
    uint16_t *pData;
    assert(pDest);

    if((y0==y1) && (GET_ALPHA(color) == ALPHA_OPAQUE))  //do not perform optimized line draw if an alpha value is present
    {//its a horizontal line
        if(x0 > x1)
        {
            uint16_t temp = x0;
            x0 = x1;
            x1 = temp;
        }
        pData = &((uint16_t*)(pDest->pData))[x0 + y0*pDest->uWidth];

        rt_halfwordset(pData, u16Color,x1-x0+1);
    }
    else if ((x0==x1) && (GET_ALPHA(color) == ALPHA_OPAQUE))
    {//a vertical line
        if(y0 > y1)
        {
            uint16_t temp = y0;
            y0 = y1;
            y1 = temp;
        }
        pData = &((uint16_t*)(pDest->pData))[x0 + y0*pDest->uWidth];
        for(;y0<=y1;y0++)
        {
            *pData = u16Color;
            pData += pDest->uWidth;
        }
    }
    else
    {
        //just use the unoptimized generic for now
        gfx_2d_DrawClippedLineGeneric(pPalette, pDest, x0, y0, x1, y1, color);   
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_alphablend_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t Rect,
                              gfx_Bitmap_t *pSrc, int SourceXoffset, int SourceYoffset, uint8_t alphaValue)
{
#ifdef _WIN32
    int x;
    uint16_t BgRComponent, FgRComponent;
    uint16_t BgGComponent, FgGComponent;
    uint16_t BgBComponent, FgBComponent;
#endif
    int y;
    unsigned short *pSourceOrigin;
    unsigned short *pDestOrigin;
    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;
    pDestOrigin = &((unsigned short *)pDest->pData)[iDestStride * Rect.y + Rect.x];
    pSourceOrigin=&((unsigned short *)pSrc ->pData)[iSourceStride*SourceYoffset + SourceXoffset];

    if(alphaValue == ALPHA_OPAQUE){
        gfx_bitblit_16BPP_565(pPalette, pDest, Rect, pSrc, SourceXoffset, SourceYoffset);
    }
    else if(alphaValue != ALPHA_TRANSPARENT){   //make sure it isn't completely transparent
        if((Rect.height > 0) && (Rect.width > 0))
        {
            unsigned short *pSourceData;
            unsigned short *pDestData;
            y=Rect.height;
            if(ALPHA_OPAQUE == GET_ALPHA(pPalette[1])){
                do{
                    pSourceData = pSourceOrigin;
                    pDestData = pDestOrigin;
#ifdef _WIN32                
                    x=Rect.width;
                    do
                    {
                        //do the blending

                        BgRComponent = ((*pDestData & 0xF800) >> 8) * (256-alphaValue);
                        BgGComponent = ((*pDestData & 0x07E0) >> 3) * (256-alphaValue);
                        BgBComponent = ((*pDestData & 0x001F) << 3) * (256-alphaValue);
                        FgRComponent = ((*pSourceData & 0xF800) >> 8) * (alphaValue);
                        FgGComponent = ((*pSourceData & 0x07E0) >> 3) * (alphaValue);
                        FgBComponent = ((*pSourceData & 0x001F) << 3) * (alphaValue);
                        FgRComponent = (FgRComponent + BgRComponent) >> 8;
                        FgGComponent = (FgGComponent + BgGComponent) >> 8;
                        FgBComponent = (FgBComponent + BgBComponent) >> 8;
                        *pDestData   = ((FgBComponent & 0x00F8) >>3) |
                                                        ((FgGComponent & 0x00FC) << 3) |
                                                        ((FgRComponent & 0x00F8) << 8);    
                        pDestData++;
                        pSourceData++;
                    }while(--x);
#else
                    gfx_blendline_16bpp_565(pSourceData, pDestData, Rect.width, alphaValue);
#endif
                    pDestOrigin += iDestStride;
                    pSourceOrigin+=iSourceStride;
                }while(--y);
            }
            else if(ALPHA_TRANSPARENT == GET_ALPHA(pPalette[1])){
                do{
                    uint16_t chromaColor = ((pPalette[1] & 0x00F80000) >>19) |
                                        ((pPalette[1] & 0x0000FC00) >> 5) |
                                        ((pPalette[1] & 0x000000F8) << 8);
                    pSourceData = pSourceOrigin;
                    pDestData = pDestOrigin;
#ifdef _WIN32                
                    x=Rect.width;
                    do
                    {
                        //do the blending
                        if(*pSourceData != chromaColor){
                            BgRComponent = ((*pDestData & 0xF800) >> 8) * (256-alphaValue);
                            BgGComponent = ((*pDestData & 0x07E0) >> 3) * (256-alphaValue);
                            BgBComponent = ((*pDestData & 0x001F) << 3) * (256-alphaValue);
                            FgRComponent = ((*pSourceData & 0xF800) >> 8) * (alphaValue);
                            FgGComponent = ((*pSourceData & 0x07E0) >> 3) * (alphaValue);
                            FgBComponent = ((*pSourceData & 0x001F) << 3) * (alphaValue);
                            FgRComponent = (FgRComponent + BgRComponent) >> 8;
                            FgGComponent = (FgGComponent + BgGComponent) >> 8;
                            FgBComponent = (FgBComponent + BgBComponent) >> 8;
                            *pDestData   = ((FgBComponent & 0x00F8) >>3) |
                                                            ((FgGComponent & 0x00FC) << 3) |
                                                            ((FgRComponent & 0x00F8) << 8);
                        }
                        pDestData++;
                        pSourceData++;
                    }while(--x);
#else
                    gfx_blendline_chroma_16bpp_565(pSourceData, pDestData, Rect.width, alphaValue, chromaColor);
#endif
                    pDestOrigin += iDestStride;
                    pSourceOrigin+=iSourceStride;
                }while(--y);            
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
