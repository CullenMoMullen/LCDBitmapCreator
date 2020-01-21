////////////////////////////////////////////////////////////////////////////////
//! \addtogroup gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_format.c
//! \brief   Contains the setup code to define support for different bitmap formats.
//! \version 1.0
//!
//! \internal
//!
//! The tables in this file define support for specific bitmap formats and acceleration.
//!
////////////////////////////////////////////////////////////////////////////////
#include "types.h"
#include "components/gfx/gfx.h"
#include "components/gfx/gfx_format.h"


//! \brief Internal function to search the supported format list
//!
//! \internal
//!
//! The other functions below use this common function to return a pointer to the
//! format specifying structure.
//!
//! \param[in] uFormatCode the format code to find the supporting support structure for.
//! \return a pointer to the \ref _gfx_BitmapFormat "gfx_BitmapFormat_t" for the bitmap
//!                         type in question.
const gfx_BitmapFormat_t *gfx_format_GetFormat(uint8_t uFormatCode)
{
    const gfx_BitmapFormat_t *pFormat = g_gfx_BitmapSupportTable;
    while(pFormat->uUniqueIdentifier != BMP_TYPE_COUNT)
    {
        if(pFormat->uUniqueIdentifier == uFormatCode)
            break;
        pFormat ++;
    }
    if(pFormat->uUniqueIdentifier == BMP_TYPE_COUNT)
        pFormat = NULL;
    assert(pFormat);
    return pFormat;
}

////////////////////////////////////////////////////////////////////////////////
// For information about this function please see gfx_format.h
////////////////////////////////////////////////////////////////////////////////
gfx_format_GetPixel_t    *gfx_format_GetPixel(gfx_Bmp_t* pBmp)
{
    gfx_format_GetPixel_t *pGetPixel = gfx_format_GetFormat(pBmp->uType)->GetPixelFunction;

    assert(pGetPixel);
    return pGetPixel;
}

////////////////////////////////////////////////////////////////////////////////
// For information about this function please see gfx_format.h
////////////////////////////////////////////////////////////////////////////////
gfx_format_PutPixel_t    *gfx_format_PutPixel(gfx_Bmp_t* pBmp)
{
    gfx_format_PutPixel_t *pPutPixel = gfx_format_GetFormat(pBmp->uType)->PutPixelFunction;

    assert(pPutPixel);
    return pPutPixel;
}

////////////////////////////////////////////////////////////////////////////////
// For information about this function please see gfx_format.h
////////////////////////////////////////////////////////////////////////////////
gfx_format_GetDataSize_t *gfx_format_GetDataSize(uint8_t uFormatCode)
{
    gfx_format_GetDataSize_t *pGetDataSize = gfx_format_GetFormat(uFormatCode)->GetBitmapDataSize;

    assert(pGetDataSize);
    return pGetDataSize;
}

////////////////////////////////////////////////////////////////////////////////
// For information about this function please see gfx_format.h
////////////////////////////////////////////////////////////////////////////////
gfx_format_LineDraw_t    *gfx_format_GetLineDraw(gfx_Bmp_t* pBmp)
{

    gfx_format_LineDraw_t *pLineDraw=gfx_format_GetFormat(pBmp->uType)->DrawLineFunction;
    assert(pLineDraw);
    return pLineDraw;
}

////////////////////////////////////////////////////////////////////////////////
// For information about this function please see gfx_format.h
////////////////////////////////////////////////////////////////////////////////
gfx_format_GetBitBlt_t   *gfx_format_BitBlt(gfx_Bmp_t*pSource, gfx_Bmp_t*pDest)
{
    const gfx_format_BitBltEntry_t *pEntry = g_gfx_BitBltFunctions;
    gfx_format_GetBitBlt_t *pBitBlt = gfx_bitblt_Generic;

    while(pEntry->pBitBltFunction)
    {
        if((pEntry->uSourceIdentifier==pSource->uType) &&
           (pEntry->uDestinationIdentifier== pDest->uType))
        {
            pBitBlt = pEntry->pBitBltFunction;
            break;
        }
        pEntry++;
    }
    return pBitBlt;
}

//! \brief Internal function to obtain the 'AlphaBlend' function between two bitmaps.
//!
//! \internal
//!
//! \param[in] pSource a pointer to the source bitmap.
//! \param[in] pDest   a pointer to destination bitmap.
//! \return a pointer to the function for 'AlphaBlend'.
gfx_format_GetAlphaBlend_t *gfx_format_AlphaBlend(gfx_Bmp_t*pSource, gfx_Bmp_t*pDest){
    const gfx_format_AlphaBlendEntry_t *pEntry = g_gfx_AlphaBlendFunctions;
    gfx_format_GetAlphaBlend_t *pAlphaBlend = gfx_alphablend_Generic;

    while(pEntry->pAlphaBlendFunction)
    {
        if((pEntry->uSourceIdentifier==pSource->uType) &&
           (pEntry->uDestinationIdentifier== pDest->uType))
        {
            pAlphaBlend = pEntry->pAlphaBlendFunction;
            break;
        }
        pEntry++;
    }
    return pAlphaBlend;
}


//! \brief Internal function to obtain the 'StretchBlt' function between two bitmaps.
//!
//! \internal
//!
//! \param[in] pSource a pointer to the source bitmap.
//! \param[in] pDest   a pointer to destination bitmap.
//! \return a pointer to the function for 'StretchBlt'.
gfx_format_GetStretchBlt_t *gfx_format_StretchBlt(gfx_Bmp_t*pSource, gfx_Bmp_t*pDest){
    const gfx_format_StretchBltEntry_t *pEntry = g_gfx_StretchBltFunctions;
    gfx_format_GetStretchBlt_t *pStretchBlt = gfx_stretchblt_Generic;

    while(pEntry->pStretchBltFunction)
    {
        if((pEntry->uSourceIdentifier==pSource->uType) &&
           (pEntry->uDestinationIdentifier== pDest->uType))
        {
            pStretchBlt = pEntry->pStretchBltFunction;
            break;
        }
        pEntry++;
    }
    return pStretchBlt;
}
////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
