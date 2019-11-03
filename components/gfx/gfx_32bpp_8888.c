////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_32bpp_8888.c
//! \brief   Contains 32BPP 888 routines.
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
void gfx_bitblit_32BPP_8888(gfx_Color_t *pPalette,
			    gfx_Bitmap_t *pDest,
			    gfx_Rect_t Rect,
			    gfx_Bitmap_t *pSrc,
			    int SourceXoffset,
			    int SourceYoffset)
{
    int y;
    unsigned char *pSourceOrigin;
    unsigned char *pDestOrigin;
    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;

    pDestOrigin = &((unsigned char*) pDest->pData)[(iDestStride * Rect.y + Rect.x) * 4];
    pSourceOrigin=&((unsigned char*) pSrc ->pData)[(iSourceStride * SourceYoffset + SourceXoffset) * 4];

    Rect.width *= 4;
    iDestStride *= 4;
    iSourceStride *= 4;

    for(y = 0; y < Rect.height; y++) {
        if(((y + SourceYoffset) >= 0) &&
	   ((y + SourceYoffset) < (int) pSrc->uHeight)) {
            memcpy(pDestOrigin, pSourceOrigin, Rect.width);
        }//if

        pDestOrigin += iDestStride;
        pSourceOrigin += iSourceStride;
    }//for
}//gfx_bitblit_32BPP_8888

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_32BPP_8888_To_16BPP_565(gfx_Color_t *pPalette,
					 gfx_Bitmap_t *pDest,
					 gfx_Rect_t Rect,
					 gfx_Bitmap_t *pSrc,
					 int SourceXoffset,
					 int SourceYoffset)
{
    int y, x;

    unsigned char *pSourceOrigin;
    unsigned short *pDestOrigin;

    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;

    pDestOrigin = &((unsigned short*) pDest->pData)[iDestStride * Rect.y + Rect.x];
    pSourceOrigin=&((unsigned char*) pSrc ->pData)[(iSourceStride * SourceYoffset + SourceXoffset) * 4];

    iSourceStride *= 4;

    for(y = 0; y < Rect.height; y++) {
        uint32_t* pSourceData = (uint32_t*) pSourceOrigin;
        unsigned short *pDestData = pDestOrigin;

        if(((y + SourceYoffset) >= 0) &&
	   ((y + SourceYoffset) < (int) pSrc->uHeight)) {
            //copy the line of 32bpp pixels to the 16bpp surface
            x = Rect.width;

            do {
		gfx_Color_t cRGB = *pSourceData++;

		// We store in RGB, but the system thinks 
		//it is BGR...Convert back
		cRGB = RGB(GET_BLUE(cRGB), GET_GREEN(cRGB), GET_RED(cRGB));

		*pDestData++ = (((cRGB & 0x00F80000) >> 19) |
				((cRGB & 0x0000FC00) >> 5) |
				((cRGB & 0x000000F8) << 8));
            }while(--x);
        }//if

        pDestOrigin += iDestStride;
        pSourceOrigin += iSourceStride;
    }//for
}//gfx_bitblit_32BPP_8888_To_16BPP_565

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_32BPP_8888(gfx_Color_t *pPalette, gfx_Bitmap_t *pBitmap, uint16_t u16x, uint16_t u16y, gfx_Color_t cRGB)
{
    uint32_t* pData;
    uint8_t alphaValue = GET_ALPHA(cRGB);

    assert(pBitmap);

    pData = (uint32_t*) pBitmap->pData + (u16y * pBitmap->uWidth + u16x);

    if(alphaValue == ALPHA_OPAQUE) { //opaque
	// We must store things in RGB format to be compatible with the DCP.
	*pData = RGB(GET_BLUE(cRGB), GET_GREEN(cRGB), GET_RED(cRGB));
    } else if(alphaValue != ALPHA_TRANSPARENT) {
	//make sure it isn't fully transparent

        uint16_t BgRComponent, FgRComponent;
        uint16_t BgGComponent, FgGComponent;
        uint16_t BgBComponent, FgBComponent;

        gfx_Color_t BgTrueColor;

        //optimization (do not call GetPixel here) instead index into pData
        gfx_GetPixel_32BPP_8888(pPalette, pBitmap, u16x, u16y, &BgTrueColor);

        BgRComponent = GET_RED(BgTrueColor)   * (256 - alphaValue);
        BgGComponent = GET_GREEN(BgTrueColor) * (256 - alphaValue);
        BgBComponent = GET_BLUE(BgTrueColor)  * (256 - alphaValue);

        FgRComponent = GET_RED(cRGB)   * (alphaValue);
        FgGComponent = GET_GREEN(cRGB) * (alphaValue);
        FgBComponent = GET_BLUE(cRGB)  * (alphaValue);

        FgRComponent = (FgRComponent + BgRComponent) >> 8;
        FgGComponent = (FgGComponent + BgGComponent) >> 8;
        FgBComponent = (FgBComponent + BgBComponent) >> 8;

	// We must store things in RGB format to be compatible with the DCP.
	*pData = RGB(FgBComponent, FgGComponent, FgRComponent);
    }//if/else
}//gfx_PutPixel_32BPP_8888

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_32BPP_8888(gfx_Color_t *pPalette,
			     gfx_Bitmap_t *pBitmap,
			     uint16_t x,
			     uint16_t y,
			     gfx_Color_t *pRGB)
{
    gfx_Color_t pixel;

    assert(pBitmap);
    assert(pRGB);

    pixel = *((uint32_t*) pBitmap->pData + (y * pBitmap->uWidth + x));

    // We store in RGB, but the system thinks 
    //it is BGR...Convert back
    *pRGB = RGB(GET_BLUE(pixel), GET_GREEN(pixel), GET_RED(pixel));
}//gfx_GetPixel_32BPP_8888

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_32BPP_8888(uint16_t u16x, uint16_t u16y)
{
    return u16x * u16y * 4;
}//gfx_GetDataSize_32BPP_8888

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_alphablend_32BPP_888_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t Rect,
                              gfx_Bitmap_t *pSrc, int SourceXoffset, int SourceYoffset, 
                              uint8_t alphaValue)
{
    int x,y;
    gfx_Color_t sourcePixel;
    uint16_t BgRComponent, FgRComponent;
    uint16_t BgGComponent, FgGComponent;
    uint16_t BgBComponent, FgBComponent;
    uint16_t compositeAlpha;
    uint16_t actualAlpha;
    bool useChromaKeying = false;
    unsigned int *pSourceOrigin;
    unsigned short *pDestOrigin;
    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;

    pDestOrigin = &((unsigned short *)pDest->pData)[iDestStride * Rect.y + Rect.x];
    pSourceOrigin=&((unsigned int *)pSrc ->pData)[iSourceStride*SourceYoffset + SourceXoffset];

    if(ALPHA_TRANSPARENT == GET_ALPHA(pPalette[1])){
        useChromaKeying = true;
    }
    if(alphaValue != ALPHA_TRANSPARENT){   //make sure it isn't completely transparent
        if((Rect.height > 0) && (Rect.width > 0))
        {
            unsigned int *pSourceData;
            unsigned short *pDestData;
            y=Rect.height;
            do{
                pSourceData = pSourceOrigin;
                pDestData = pDestOrigin;
                actualAlpha = alphaValue;
                x=Rect.width;
                do
                {
                    sourcePixel = *pSourceData;
                    if(useChromaKeying && ((pPalette[1] & 0x00FFFFFF) == (sourcePixel & 0x00FFFFFF))){
                        //if the background color is ALPHA_TRANSPARENT and the RGB color is the same as the source,
                        //ignoring ALPHA values, then we assume the color is a chroma key color and we ignore it
                    }
                    else{
                        if(ALPHA_TRANSPARENT != GET_ALPHA(sourcePixel)){
                            //determine the proper alpha value to use
                            if(alphaValue == ALPHA_OPAQUE){
                                actualAlpha = GET_ALPHA(sourcePixel);
                            }
                            else if(ALPHA_OPAQUE != GET_ALPHA(sourcePixel)){
                                compositeAlpha = alphaValue * GET_ALPHA(sourcePixel);
                                actualAlpha = compositeAlpha >> 8;
                            }
                            
                            BgRComponent = ((*pDestData & 0xF800) >> 8) * (256-actualAlpha);
                            BgGComponent = ((*pDestData & 0x07E0) >> 3) * (256-actualAlpha);
                            BgBComponent = ((*pDestData & 0x001F) << 3) * (256-actualAlpha);
                            FgRComponent = GET_RED(sourcePixel) * actualAlpha;
                            FgGComponent = GET_GREEN(sourcePixel) * actualAlpha;
                            FgBComponent = GET_BLUE(sourcePixel) * actualAlpha;
                            FgRComponent = (FgRComponent + BgRComponent) >> 8;
                            FgGComponent = (FgGComponent + BgGComponent) >> 8;
                            FgBComponent = (FgBComponent + BgBComponent) >> 8;
                            *pDestData   = ((FgBComponent & 0x00F8) >>3) |
                                                            ((FgGComponent & 0x00FC) << 3) |
                                                            ((FgRComponent & 0x00F8) << 8);                        
                        }
                    }

                    pDestData++;
                    pSourceData++;
                }while(--x);

                pDestOrigin += iDestStride;
                pSourceOrigin+=iSourceStride;
            }while(--y);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
