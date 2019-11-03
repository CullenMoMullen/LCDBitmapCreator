////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_8bpp_palette.c
//! \brief   Contains 8BPP routines.
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
void gfx_bitblit_8BPP_Palette_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t Rect, gfx_Bitmap_t *pSrc, int SourceXoffset, int SourceYoffset){
    int x,y;
    unsigned char *pSourceOrigin;
    unsigned short *pDestOrigin;
    int iSourceStride = pSrc->uWidth;   //num bytes per source line
    int iDestStride = pDest->uWidth;
    gfx_Color_t colorValue;
    pDestOrigin = &((unsigned short *)pDest->pData)[iDestStride * Rect.y + Rect.x];
    pSourceOrigin=&((unsigned char *)pSrc ->pData)[iSourceStride*SourceYoffset + SourceXoffset];

    if((Rect.height > 0) && (Rect.width > 0))
    {
        unsigned char *pSourceData;
        unsigned short *pDestData;
        y=Rect.height;
            do
            {
                pSourceData = pSourceOrigin;
                pDestData = pDestOrigin;
                x=Rect.width;
                do
                {
                    colorValue = pPalette[*pSourceData];
                    if(GET_ALPHA(colorValue)){  //is it opaque?
                        *pDestData = ((colorValue & 0x00F80000) >> 19) | ((colorValue & 0x0000FC00) >> 5) | ((colorValue & 0x000000F8) << 8);
                    }
                    pDestData++;
                    pSourceData++;
                }while(--x);
                pDestOrigin += iDestStride;
                pSourceOrigin+=iSourceStride;
            }while(--y);
    }
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_8BPP_Palette(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t Rect,
                      gfx_Bitmap_t *pSrc, int SourceXoffset, int SourceYoffset)
{
    int y;
    unsigned char *pSourceOrigin;
    unsigned char *pDestOrigin;
    int iSourceStride = pSrc->uWidth;
    int iDestStride = pDest->uWidth;

    pDestOrigin = &((unsigned char *)pDest->pData)[iDestStride * Rect.y + Rect.x];
    pSourceOrigin=&((unsigned char *)pSrc ->pData)[iSourceStride*SourceYoffset + SourceXoffset];

    if((Rect.height > 0) && (Rect.width > 0))
    {
        unsigned char *pSourceData;
        unsigned char *pDestData;
        y=Rect.height;
        do
        {
            pSourceData = pSourceOrigin;
            pDestData = pDestOrigin;
            
            memcpy(pDestData, pSourceData, Rect.width);
            
            pDestOrigin += iDestStride;
            pSourceOrigin+=iSourceStride;
        }while(--y);
    }
}


////////////////////////////////////////////////////////////////////////////////
//! \brief This is the optimized version of BITMAP_TYPE_8BPP_PALETTE to BITMAP_TYPE_8BPP_PALETTE stretchblt operation.
//!
//! This function copies a bitmap into a rectangle within another and scales the source image apprpriately.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//!
//! \internal
//!
////////////////////////////////////////////////////////////////////////////////
void gfx_stretchblit_8BPP_Palette_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bitmap_t *pDest, gfx_Rect_t Rect,
                             gfx_Bitmap_t *pSrc, int SourceXoffset, int SourceYoffset, uint32_t scalingFactor)
{
    uint32_t i,j,k;
	uint32_t	i32Result_R, i32Result_G, i32Result_B;
	uint8_t * pData =(uint8_t *) &pSrc->pData[0];
	uint16_t * pOutbuf =(uint16_t *) &pDest->pData[0];
	uint16_t u16Scanline = pSrc->uWidth;
	uint16_t uHeight = pSrc->uHeight;
	uint32_t i32Colour;

#ifdef BMP
	int32_t i32TableLength;
	int32_t i32readflag;
	int32_t i32out;
#endif

	for (k=0; k< uHeight/scalingFactor; k++)
	{
#ifdef BMP	
	pData = (uint8_t *) &pSrc->pData[0] + k*(u16Scanline+i32remain)*scalingFactor;
#else
	pData = (uint8_t *) &pSrc->pData[0] + k*(u16Scanline)*scalingFactor;
#endif
	switch(scalingFactor)
	{
	case 1:
		for (i =0; i < u16Scanline; i = i+1)
		{
			int32_t i32pixelindex = pData[i];
	    	i32Result_R = 0;i32Result_G = 0;i32Result_B = 0;
            i32Colour = pPalette[i32pixelindex];
			i32Result_R += ( i32Colour & 0xff);
			i32Result_G += ((i32Colour >> 8) & 0xff);
			i32Result_B += ((i32Colour >> 16) & 0xff);

            i32Result_R &= 0xf8;
            i32Result_G &= 0xfc;
            i32Result_B &= 0xf8;

            *pOutbuf = ((i32Result_R << 8) | (i32Result_G << 3) | (i32Result_B>>3));
            pOutbuf++;
		}
		break;
	case 2:
		for (i =0; i < u16Scanline; i = i+2)
		{

			int32_t i32pixelindex = pData[i];

			i32Result_R = 0;i32Result_G = 0;i32Result_B = 0;

			i32Colour = pPalette[i32pixelindex];
			i32Result_R += ( i32Colour & 0xff);
			i32Result_G += ( (i32Colour >> 8) & 0xff);
			i32Result_B += ( (i32Colour >> 16) & 0xff);


			i32pixelindex = pData[i + 1];
			i32Colour = pPalette[i32pixelindex];
			i32Result_R += ( i32Colour & 0xff);
			i32Result_G += ( (i32Colour >> 8) & 0xff);
			i32Result_B += ( (i32Colour >> 16) & 0xff);

			i32pixelindex = pData[i + u16Scanline];
			i32Colour = pPalette[i32pixelindex];
			i32Result_R += ( i32Colour & 0xff);
			i32Result_G += ( (i32Colour >> 8) & 0xff);
			i32Result_B += ( (i32Colour >> 16) & 0xff);

			i32pixelindex = pData[i + 1 + u16Scanline];
			i32Colour = pPalette[i32pixelindex];
			i32Result_R += ( i32Colour & 0xff);
			i32Result_G += ( (i32Colour >> 8) & 0xff);
			i32Result_B += ( (i32Colour >> 16) & 0xff);

            i32Result_R >>= 2;
            i32Result_G >>= 2;
            i32Result_B >>= 2;

            i32Result_R &= 0xf8;
            i32Result_G &= 0xfc;
            i32Result_B &= 0xf8;

            *pOutbuf = ((i32Result_R << 8) | (i32Result_G << 3) | (i32Result_B>>3));
            pOutbuf++;

		}
		break;


	case 4:

		for (i =0; i < u16Scanline; i = i+(scalingFactor))
		{

		   i32Result_R = 0;i32Result_G = 0;i32Result_B = 0;
		   for (j=0; j < scalingFactor ; j++)
		   {
				int32_t  i32pixelindex = pData[i + (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];	
				i32Result_R += ( i32Colour  & 0xff);
				i32Result_G += ( (i32Colour  >> 8) & 0xff);
				i32Result_B += ( (i32Colour  >> 16) & 0xff);

				i32pixelindex = pData[i + 1+  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];	
				i32Result_R += ( i32Colour  & 0xff);
				i32Result_G += ( (i32Colour  >> 8) & 0xff);
				i32Result_B += ( (i32Colour  >> 16) & 0xff);

				i32pixelindex = pData[i + 2+  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];	
				i32Result_R += ( i32Colour  & 0xff);
				i32Result_G += ( (i32Colour  >> 8) & 0xff);
				i32Result_B += ( (i32Colour  >> 16) & 0xff);

				i32pixelindex = pData[i + 3+  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];	
				i32Result_R += ( i32Colour  & 0xff);
				i32Result_G += ( (i32Colour  >> 8) & 0xff);
				i32Result_B += ( (i32Colour  >> 16) & 0xff);

		   }

            i32Result_R >>= 4;
            i32Result_G >>= 4;
            i32Result_B >>= 4;

            i32Result_R &= 0xf8;
            i32Result_G &= 0xfc;
            i32Result_B &= 0xf8;

            *pOutbuf = ((i32Result_R << 8) | (i32Result_G << 3) | (i32Result_B>>3));
            pOutbuf++;

		}
		break;

	case 8:

		for (i =0; i < u16Scanline; i = i+(scalingFactor))
		{

		   i32Result_R = 0;i32Result_G = 0;i32Result_B = 0;
		   for (j=0; j < scalingFactor ; j++)
		   {

				int32_t i32pixelindex = pData[i +(j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];
				i32Result_R += ( i32Colour & 0xff);
				i32Result_G += ((i32Colour >> 8) & 0xff);
				i32Result_B += ((i32Colour >> 16) & 0xff);

				i32pixelindex = pData[i + 1 +  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];
				i32Result_R += ( i32Colour & 0xff);
				i32Result_G += ((i32Colour >> 8) & 0xff);
				i32Result_B += ((i32Colour >> 16) & 0xff);

				i32pixelindex = pData[i+ 2 +  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];
				i32Result_R += ( i32Colour & 0xff);
				i32Result_G += ((i32Colour >> 8) & 0xff);
				i32Result_B += ((i32Colour >> 16) & 0xff);

			    i32pixelindex = pData[i + 3+  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];
				i32Result_R += ( i32Colour & 0xff);
				i32Result_G += ((i32Colour >> 8) & 0xff);
				i32Result_B += ((i32Colour >> 16) & 0xff);

			    i32pixelindex = pData[i + 4+  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];
				i32Result_R += ( i32Colour & 0xff);
				i32Result_G += ((i32Colour >> 8) & 0xff);
				i32Result_B += ((i32Colour >> 16) & 0xff);

			    i32pixelindex = pData[i + 5+  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];
				i32Result_R += ( i32Colour & 0xff);
				i32Result_G += ((i32Colour >> 8) & 0xff);
				i32Result_B += ((i32Colour >> 16) & 0xff);

			    i32pixelindex = pData[i + 6+  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];
				i32Result_R += ( i32Colour & 0xff);
				i32Result_G += ((i32Colour >> 8) & 0xff);
				i32Result_B += ((i32Colour >> 16) & 0xff);

				i32pixelindex = pData[i + 7+  (j*(u16Scanline))];
				i32Colour = pPalette[i32pixelindex];
				i32Result_R += ( i32Colour & 0xff);
				i32Result_G += ((i32Colour >> 8) & 0xff);
				i32Result_B += ((i32Colour >> 16) & 0xff);

		   } 
            i32Result_R >>= 6;
            i32Result_G >>= 6;
            i32Result_B >>= 6;

            i32Result_R &= 0xf8;
            i32Result_G &= 0xfc;
            i32Result_B &= 0xf8;

            *pOutbuf = ((i32Result_R << 8) | (i32Result_G << 3) | (i32Result_B>>3));
            pOutbuf++;


		}
		break;

	}
#ifdef BMP
		i32TableLength = (3* u16Scanline*scalingFactor);
		i32out= (i32TableLength  %(4*  scalingFactor* scalingFactor));
		if(i32out== 0)
		{
			i32out= 4* scalingFactor*scalingFactor;
		}
		for(j=0; j < (4* scalingFactor*scalingFactor-i32out)/(scalingFactor*scalingFactor); j++)
			*pOutbuf++ = 0;
#endif


	}
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_8BPP_Palette(gfx_Color_t *pPalette, gfx_Bitmap_t *pBitmap,
                       uint16_t u16x, uint16_t u16y, gfx_Color_t cRGB)
{
    unsigned char *pData;
    int16_t i; 
    uint8_t minIndex = 0;
    int32_t rPalette,gPalette,bPalette, rSource, gSource, bSource;
    int32_t minRGBDistance = 0x7FFFFFFF, distance;
    assert(pBitmap);

    rSource = GET_RED(cRGB);
    gSource = GET_GREEN(cRGB);
    bSource = GET_BLUE(cRGB);
    //the closest color match (slight variation on the CIE94 color difference equation)
    //treat each (R,G,B) tuple as a point in 3D space.
    //Determine the distance from point 1 to point 2. D=[(r1-r2)^2 + (g1-g2)^2 + (b1-b2)^2]^(1/2)
    //Compare the differences and accept the mimimum distance
    for(i = 0; i < 256; i++){
        rPalette = GET_RED(pPalette[i]);
        gPalette = GET_GREEN(pPalette[i]);
        bPalette = GET_BLUE(pPalette[i]);
        //do not take sqrt since it is unnecessray for the comparison
        distance = (rSource - rPalette)*(rSource - rPalette) + (gSource - gPalette)*(gSource - gPalette) + (bSource - bPalette)*(bSource - bPalette);
        if(distance < minRGBDistance){
            minRGBDistance = distance;
            minIndex = (uint8_t) i;
        }
        if(distance == 0){  //can't get any closer than an exact match
            break;
        }
    }

    pData = (unsigned char*)pBitmap->pData;
    pData[u16y*pBitmap->uWidth+u16x] = minIndex;
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_8BPP_Palette(gfx_Color_t *pPalette, gfx_Bitmap_t *pBitmap,
                       uint16_t x, uint16_t y, gfx_Color_t *pRGB)
{
    unsigned char *pData;
    assert(pBitmap);
    assert(pRGB);
    pData = (unsigned char*)pBitmap->pData;
    *pRGB = pPalette[pData[y*pBitmap->uWidth+x]];
}

////////////////////////////////////////////////////////////////////////////////
// To view the documentation for this function, refer to gfx_format.h.
////////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_8BPP_Palette(uint16_t u16Width, uint16_t u16Height)
{
    return u16Width*u16Height;
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}

