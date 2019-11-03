////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_1bpp_ideal.c
//! \brief   Contains Ideal 1 bit per pixel routines.
//! \version 1.0
//!
////////////////////////////////////////////////////////////////////////////////
#include "types.h"
#include "components/gfx/gfx.h"
#include "gfx_internal.h"




////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_1BPP_Ideal_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t Rect, gfx_Bitmap_t *pSrc, int SourceXoffset, int SourceYoffset){
    int x,y;
    unsigned char *pSourceOrigin;
    unsigned short *pDestOrigin;
    int iSourceStride = (pSrc->uWidth - 1)/8 + 1;   //num bytes per source line
    int iDestStride = pDest->uWidth;
    uint16_t numBitsInFirstByte = SourceXoffset % 8;    //save it off so we only perform the modulo once per call
    unsigned char bitMask;
    unsigned short BackgroundColor =
        ((pPalette[1] & 0x00F80000) >> 19) | ((pPalette[1] & 0x0000FC00) >> 5) | ((pPalette[1] & 0x000000F8) << 8);
    unsigned short ForegroundColor = 
        ((pPalette[0] & 0x00F80000) >> 19) | ((pPalette[0] & 0x0000FC00) >> 5) | ((pPalette[0] & 0x000000F8) << 8);
    bool bOpaque = (pPalette[1] & 0xff000000) ? true : false;
    pDestOrigin = &((unsigned short *)pDest->pData)[iDestStride * Rect.y + Rect.x];
    pSourceOrigin=&((unsigned char *)pSrc ->pData)[iSourceStride*SourceYoffset + SourceXoffset/8];

    if((Rect.height > 0) && (Rect.width > 0))
    {
        unsigned char *pSourceData;
        unsigned short *pDestData;
        y = Rect.height;
        do{ //for each line in the clipping rectangle
            bitMask = 0x80 >> numBitsInFirstByte; //setup the initial bitMask
            pDestData = pDestOrigin;
            pSourceData = pSourceOrigin;
            x = Rect.width;
            do{
                if(bitMask & (*pSourceData)){
                    *pDestData = ForegroundColor;
                }
                else{
                    if(bOpaque)
                        *pDestData = BackgroundColor;
                }
                pDestData++;
                bitMask >>= 1;
                if(!bitMask){
                    bitMask = 0x80;
                    pSourceData++;
                }
            }while(--x);
            pSourceOrigin += iSourceStride;
            pDestOrigin += iDestStride;
        }while(--y);
    }
}


////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_1BPP_Ideal(gfx_Color_t *pPalette, gfx_Bitmap_t *pBitmap, uint16_t x, uint16_t y, gfx_Color_t cRGB)
{
    unsigned char *pData = (unsigned char*)pBitmap->pData;
    unsigned char uByte = 1<<((8-(x%8))-1);


    pData = &pData[y*((pBitmap->uWidth+7)/8)+ ((x)/8)];
    
    if((cRGB & 0x00FFFFFF) == (pPalette[1] & 0x00FFFFFF))//if the color is the background color,compare RGB color only
        *pData &= ~uByte;
    else
        *pData |= uByte;

}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_1BPP_Ideal(gfx_Color_t *pPalette, gfx_Bitmap_t *pBitmap, uint16_t x, uint16_t y, gfx_Color_t *pRGB)
{
    unsigned char *pData = (unsigned char*)pBitmap->pData;
    unsigned char uByte = 1<<((8-(x%8))-1);

    pData = &pData[y*((pBitmap->uWidth+7)/8)+ ((x)/8)];

    if(*pData & uByte)
        *pRGB = pPalette[0];
    else
        *pRGB = pPalette[1];
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_1BPP_Ideal(uint16_t width, uint16_t height)
{
    return ((width+7)/8) * height;
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}

