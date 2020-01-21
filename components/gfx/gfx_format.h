#pragma once
////////////////////////////////////////////////////////////////////////////////
//! \addtogroup cmp_gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_format.h
//! \brief   Contains structures and function prototypes for supported bitmap types.
//!
//! The tables in this file define support for specific bitmap formats and acceleration.
//!
//! \todo [PUBS] Add definitions for TBDs in this file.
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for BitBlt function pointer
//!
//! Function typedef for a BitBlt function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a bitblt
//! so that the appropriate bitblt function is called for the specfifc source/destination
//! format pair.
////////////////////////////////////////////////////////////////////////////////
typedef void(gfx_format_GetBitBlt_t)(gfx_Color_t *pPalette, gfx_Bmp_t*,gfx_Rect_t,
                                        gfx_Bmp_t*,int,int);

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for AlphaBlend function pointer
//!
//! Function typedef for a AlphaBlend function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during an AlphaBlend
//! so that the appropriate AlphaBlend function is called for the specfifc source/destination
//! format pair.
////////////////////////////////////////////////////////////////////////////////
typedef void(gfx_format_GetAlphaBlend_t)(gfx_Color_t *pPalette, gfx_Bmp_t*,gfx_Rect_t,
                                        gfx_Bmp_t*,int,int,uint8_t);

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for StretchBlt function pointer
//!
//! Function typedef for a StretchBlt function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a StretchBlt
//! so that the appropriate StretchBlt function is called for the specfifc source/destination
//! format pair.
////////////////////////////////////////////////////////////////////////////////
typedef void (gfx_format_GetStretchBlt_t)(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, 
                                          gfx_Rect_t ClipRect, gfx_Rect_t *dstRect, 
                                          gfx_Bmp_t *pSrc, gfx_Rect_t *srcRect, gfx_StretchFilter_t filterType);


////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for PutPixel function pointer
//!
//! Function typedef for a PutPixel function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a PutPixel
//! so that the appropriate PutPixel function is called for the specfifc color format
////////////////////////////////////////////////////////////////////////////////
typedef void(gfx_format_PutPixel_t)(gfx_Color_t *pPalette, gfx_Bmp_t *, uint16_t,
                                    uint16_t, gfx_Color_t );

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for GetPixel function pointer
//!
//! Function typedef for a GetPixel function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a GetPixel
//! so that the appropriate GetPixel function is called for the specfifc color format
////////////////////////////////////////////////////////////////////////////////
typedef void(gfx_format_GetPixel_t)(gfx_Color_t *pPalette, gfx_Bmp_t *, uint16_t,
                                    uint16_t, gfx_Color_t *);

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for GetDataSize function pointer
//!
//! Function typedef for a GetDataSize function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a GetDataSize
//! so that the appropriate GetDataSize function is called for the specfifc color format
////////////////////////////////////////////////////////////////////////////////
typedef uint32_t(gfx_format_GetDataSize_t)(uint16_t,uint16_t);

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for DrawLine function pointer
//!
//! Function typedef for a optimized DrawLine function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a DrawLine
//! so that the appropriate DrawLine function is called for the specfifc color format.  If no
//! optimized version of DrawLine is available for the color format then the graphics library
//! will use PutPixel to accomplish the drawing of a line.
////////////////////////////////////////////////////////////////////////////////
typedef void(gfx_format_DrawLine_t)(gfx_Color_t *pPalette, gfx_Bmp_t *pDest,
                      int x0, int y0, int x1, int y1, gfx_Color_t color);

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for BitBlt function pointer
//!
//! Function typedef for a BitBlt function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a bitblt
//! so that the appropriate bitblt function is called for the specfifc source/destination
//! format pair.
////////////////////////////////////////////////////////////////////////////////
typedef void (gfx_format_Bitblt_t)(gfx_Color_t *pPalette, gfx_Bmp_t*,gfx_Rect_t,
                                        gfx_Bmp_t*,int,int);

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for AlphaBlend function pointer
//!
//! Function typedef for a AlphaBlend function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a AlphaBlend
//! so that the appropriate AlphaBlend function is called for the specfifc source/destination
//! format pair.
////////////////////////////////////////////////////////////////////////////////
typedef void (gfx_format_AlphaBlend_t)(gfx_Color_t *pPalette, gfx_Bmp_t*,gfx_Rect_t,
                                        gfx_Bmp_t*,int,int,uint8_t);

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for DrawLine function pointer
//!
//! Function typedef for a optimized DrawLine function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a DrawLine
//! so that the appropriate DrawLine function is called for the specfifc color format.  If no
//! optimized version of DrawLine is available for the color format then the graphics library
//! will use PutPixel to accomplish the drawing of a line.
////////////////////////////////////////////////////////////////////////////////
typedef void (gfx_format_LineDraw_t)(gfx_Color_t *pPalette, gfx_Bmp_t *pDest,
                                     int x0, int y0, int x1, int y1, gfx_Color_t color);

////////////////////////////////////////////////////////////////////////////////
//! \brief Typedef for Stretch blit function pointer
//!
//! Function typedef for an optimized stretch blit function to be used with the gfx library.  A function
//! pointer to a function of this type is returned from a lookup table during a stretch blit
//! so that the appropriate stretch blit function is called for the specfifc color format.  If no
//! optimized version of stretch blit is available for the color format then the graphics library
//! will use GetPixel/PutPixel to accomplish the stretching of a bitmap.
////////////////////////////////////////////////////////////////////////////////
typedef void (gfx_format_StretchBlt_t)(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, 
                                       gfx_Rect_t clipRect, gfx_Rect_t *dstRect, gfx_Bmp_t *pSrc, 
                                       gfx_Rect_t *srcRect, gfx_StretchFilter_t filterType);

///////////////////////////////////////////////////////////////////////////////
//! \brief Function to obtain the 'GetPixel' function of a bitmap type.
//! 
//! \param[in] * Pointer to a bitmap for which the 'getpixel' function is needed
//!
//! \return Pointer to the function for 'get pixel'.
//!
//! \note This function is called by many of the graphics APIs internally, however
//!       it is exposed in case the customer would like to get the pointer to
//!       the GetPixel function for a particular bitmap type.
///////////////////////////////////////////////////////////////////////////////
gfx_format_GetPixel_t    *gfx_format_GetPixel(gfx_Bmp_t*);

///////////////////////////////////////////////////////////////////////////////
//! \brief Function to obtain the 'PutPixel' function of a bitmap type.
//!
//! Internal function to obtain the 'PutPixel' function of a bitmap type.
//! 
//! \param[in] * Pointer to a bitmap for which the 'putpixel' function is needed
//! \return Pointer to the function for 'put pixel'.
//!
//! \note This function is called by many of the graphics APIs internally, however
//!       it is exposed in case the customer would like to get the pointer to
//!       the PutPixel function for a particular bitmap type.
///////////////////////////////////////////////////////////////////////////////
gfx_format_PutPixel_t    *gfx_format_PutPixel(gfx_Bmp_t*);

///////////////////////////////////////////////////////////////////////////////
//! \brief Function to obtain the 'BitBlt' function between two bitmaps. 
//! 
//! \param[in] * Pointer to the source bitmap.
//! \param[in] * Pointer to destination bitmap.
//!
//! \return Pointer to the function for 'BitBlt'.
//!
//! \note This function is called by many of the graphics APIs internally, however
//!       it is exposed in case the customer would like to get the pointer to
//!       the BitBlt function for a particular bitmap pair.
///////////////////////////////////////////////////////////////////////////////
gfx_format_GetBitBlt_t   *gfx_format_BitBlt(gfx_Bmp_t*, gfx_Bmp_t*);

///////////////////////////////////////////////////////////////////////////////
//! \brief Function to obtain the 'Alphablend' function between two bitmaps.
//! 
//! \param[in] * Pointer to the source bitmap.
//! \param[in] * Pointer to destination bitmap.
//!
//! \return Pointer to the function for 'Alphablend'.
//!
//! \note This function is called by many of the graphics APIs internally, however
//!       it is exposed in case the customer would like to get the pointer to
//!       the AlphaBlend function for a particular bitmap pair.
///////////////////////////////////////////////////////////////////////////////
gfx_format_GetAlphaBlend_t *gfx_format_AlphaBlend(gfx_Bmp_t*, gfx_Bmp_t*);

///////////////////////////////////////////////////////////////////////////////
//! \brief Function to obtain the 'StretchBlt' function between two bitmaps. 
//! 
//! \param[in] * Pointer to the source bitmap.
//! \param[in] * Pointer to destination bitmap.
//!
//! \return Pointer to the function for 'StretchBlt'.
//!
//! \note This function is called by many of the graphics APIs internally, however
//!       it is exposed in case the customer would like to get the pointer to
//!       the StretchBlt function for a particular bitmap pair.
///////////////////////////////////////////////////////////////////////////////
gfx_format_GetStretchBlt_t *gfx_format_StretchBlt(gfx_Bmp_t*, gfx_Bmp_t*);

///////////////////////////////////////////////////////////////////////////////
//! \brief Function to obtain the 'Get Data Size' function of a bitmap type.
//! 
//! \param[in] ... Format code for to obtain the 'get data size' function for.
//! \return Pointer to the function for 'get pixel'.
//!
//! \note This function is called by many of the graphics APIs internally, however
//!       it is exposed in case the customer would like to get the pointer to
//!       the GetDataSize function for a particular bitmap type.
///////////////////////////////////////////////////////////////////////////////
gfx_format_GetDataSize_t *gfx_format_GetDataSize(uint8_t);

///////////////////////////////////////////////////////////////////////////////
//! \brief Function to obtain the 'DrawLine' function of a bitmap type.
//! 
//! \param[in] * Pointer to a bitmap for which the 'DrawLine' function is needed
//! \return Pointer to the function for 'DrawLine'.
//!
//! \note This function is called by many of the graphics APIs internally, however
//!       it is exposed in case the customer would like to get the pointer to
//!       the GetLineDraw function for a particular bitmap type.
///////////////////////////////////////////////////////////////////////////////
gfx_format_LineDraw_t    *gfx_format_GetLineDraw(gfx_Bmp_t*);

//! \brief Structure for encapsulating all the function handlers for a particular bitmap format.
typedef struct _gfx_BitmapFormat
{
    //! \brief Unique identifier for this format.
    unsigned char uUniqueIdentifier;
    //! \brief Get Data Size member
    gfx_format_GetDataSize_t * const GetBitmapDataSize;
    //! \brief Get Pixel Member
    gfx_format_GetPixel_t    * const GetPixelFunction;
    //! \brief Put pixel member
    gfx_format_PutPixel_t    * const PutPixelFunction;
    //! \brief Draw Line member
    gfx_format_DrawLine_t    * const DrawLineFunction;
} gfx_BitmapFormat_t;

//! \brief Structure for defining the accellerated  bitblt formats.
typedef struct _gfx_format_BitBltEntry
{
    //! \brief Identifier for source bitmap type
    unsigned char uSourceIdentifier;
    //! \brief Identifier for destination bitmap type
    unsigned char uDestinationIdentifier;
    //! \brief BitBlt function pointer.
    gfx_format_Bitblt_t *const pBitBltFunction;
} gfx_format_BitBltEntry_t;

//! Structure for defining the accellerated alphablend formats.
typedef struct _gfx_format_AlphaBlendEntry
{
    unsigned char uSourceIdentifier;                    //!< Identifier for source bitmap type
    unsigned char uDestinationIdentifier;               //!< Identifier for destination bitmap type
    gfx_format_AlphaBlend_t *const pAlphaBlendFunction; //!< AlphaBlend function pointer.
} gfx_format_AlphaBlendEntry_t;

//! Structure for defining the accellerated stretch blit formats.
typedef struct _gfx_format_StretchBltEntry
{
    unsigned char uSourceIdentifier;                    //!< Identifier for source bitmap type
    unsigned char uDestinationIdentifier;               //!< Identifier for destination bitmap type
    gfx_format_StretchBlt_t *const pStretchBltFunction; //!< AlphaBlend function pointer.
} gfx_format_StretchBltEntry_t;

//! \brief Null terminated table of supported bitmap types.
extern const gfx_BitmapFormat_t         g_gfx_BitmapSupportTable[];

//! \brief Reference to global Function pointer look up table for bitblt functions
extern const gfx_format_BitBltEntry_t   g_gfx_BitBltFunctions[];

//! \brief Reference to global function pointer look up table for alphablend functions
extern const gfx_format_AlphaBlendEntry_t   g_gfx_AlphaBlendFunctions[];

//! \brief Reference to global Function pointer look up table for stretchblt functions
extern const gfx_format_StretchBltEntry_t   g_gfx_StretchBltFunctions[];

//function prototypes for BITMAP_TYPE_16BPP_565
///////////////////////////////////////////////////////////////////////////////
//! \brief Gets a pixel's color value from a BITMAP_TYPE_16BPP_565 bitmap
//!
//! This function gets the pixel color at a given x,y converting it as best it can to match the ideal RGB
//! definition.  This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_GetPixel())
//!
//! \param[in]  pPalette             A pointer to the active palette (unused by this function)
//! \param[in]  pBitmap              A pointer to the bitmap
//! \param[in]  x                    x position of the pixel
//! \param[in]  y                    y position of the pixel
//! \param[out] pPixel               Pointer to a gfx_Color_t object to populate with the RGB color
//!
//! \note The prefered API to use instead of this function is gfx_bmp_GetPixel
//!       which will analyze the type of bitmap for which a pixel is being gotten
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                            uint16_t x, uint16_t y, gfx_Color_t *pPixel);

///////////////////////////////////////////////////////////////////////////////
//! \brief Sets a pixel in a BITMAP_TYPE_16BPP_565 bitmap
//!
//! This function sets the pixel at a given x,y to a given RGB color(converting it as best it can to match
//! the capabilities of the bitmap. This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_SetPixel())
//!
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pBitmap              A pointer to the bitmap
//! \param[in] x                 x position of the pixel
//! \param[in] y                 y position of the pixel
//! \param[in] uRGB                 Color value to place in the bitmap
//!
//! \note The prefered API to use instead of this function is gfx_bmp_PutPixel
//!       which will analyze the type of bitmap for which a pixel is being put
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                            uint16_t x, uint16_t y, gfx_Color_t uRGB);

///////////////////////////////////////////////////////////////////////////////
//! \brief Gets the size of the datablock for a BITMAP_TYPE_16BPP_565 bitmap
//!
//! \param[in] u16x     Pixels across
//! \param[in] u16y    Height in pixels
//! \return size of the data block, in bytes
//!
//! \note This function is called internally by graphics functions but is exposed
//!       in case the user would like to call it directly.
///////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_16BPP_565(uint16_t u16x, uint16_t u16y);

///////////////////////////////////////////////////////////////////////////////
//! \brief This is the optimized version of BITMAP_TYPE_16BPP_565 to BITMAP_TYPE_16BPP_565 bitblt operation.
//!
//! This function copies a bitmap into a rectangle within another.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//!
//! \note      This code has been optimized for the ARM Thumb instruction set using the Green Hills Compiler with Osize
//!            Optimization setting.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                           gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset);

///////////////////////////////////////////////////////////////////////////////
//! \brief Draws a line, pre-clipped, in a given color to a given bitmap
//!
//! This function draws a line, pre-clipped, onto a 16bpp 565 bitmap
//! \todo introduce an assembly version of the horizontal line draw.
//! 
//! \param[in] pPalette     Not used by this function
//! \param[in] pDest        The gfx_Bmp_t to draw onto
//! \param[in] x0           x of point 0
//! \param[in] y0           y of point 0
//! \param[in] x1           x of point 1
//! \param[in] y1           y of point 1
//! \param[in] color        The color of the line
//!
//! \note The prefered API to use instead of this function is gfx_2d_DrawLine
//!       which will draw a line onto a device context.  This function is exposed
//!       so that a line may be drawn directly onto a bitmap instead of a device
//!       context.  The caller should check all bounds to make sure the line
//!       will fit within the bitmap being drawn to.
///////////////////////////////////////////////////////////////////////////////
void gfx_DrawClippedLine_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, 
                                   int x0, int y0, int x1, int y1, gfx_Color_t color);

///////////////////////////////////////////////////////////////////////////////
//! \brief This is the optimized version of BITMAP_TYPE_16BPP_565 to BITMAP_TYPE_16BPP_565 AlphaBlend operation.
//!
//! This function copies a bitmap into a rectangle within another.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//! \param[in] alphaValue           Value to use for the alpha channel for the blend operation
//!
//! \note      This code has been optimized for the ARM Thumb instruction set using the Green Hills Compiler with Osize
//!            Optimization setting.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_AlphaBlendBitmap and gfx_bmp_AlphaBlendBitmapByAddress
//!       which will choose the appropriate blend function based on the types of the source and destination pair.
//!       This function is exposed so that a blend may be done directly onto a bitmap instead of a device
//!       context.  The caller should check all bounds to make sure the source bitmap
//!       will fit within the bitmap being blended onto.
///////////////////////////////////////////////////////////////////////////////
void gfx_alphablend_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                              gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset, 
                              uint8_t alphaValue);

//function prototypes for BITMAP_TYPE_16BPP_565_DD
///////////////////////////////////////////////////////////////////////////////
//! \brief Gets a pixel's color value from a BITMAP_TYPE_16BPP_565_DD bitmap
//!
//! This function gets the pixel color at a given x,y converting it as best it can to match the ideal RGB
//! definition.  This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_GetPixel())
//!
//! \param[in]  pPalette             A pointer to the active palette (unused by this function)
//! \param[in]  pBitmap              A pointer to the bitmap
//! \param[in]  x                    x position of the pixel
//! \param[in]  y                    y position of the pixel
//! \param[out] pPixel               Pointer to a gfx_Color_t object to populate with the RGB color
//!
//! \note The prefered API to use instead of this function is gfx_bmp_GetPixel
//!       which will analyze the type of bitmap for which a pixel is being gotten
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_16BPP_565_dd(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                   uint16_t x, uint16_t y, gfx_Color_t *pPixel);

///////////////////////////////////////////////////////////////////////////////
//! \brief Sets a pixel in a BITMAP_TYPE_16BPP_565_DD bitmap
//!
//! This function sets the pixel at a given x,y to a given RGB color(converting it as best it can to match
//! the capabilities of the bitmap. This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_SetPixel())
//!
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pBitmap              A pointer to the bitmap
//! \param[in] x                 x position of the pixel
//! \param[in] y                 y position of the pixel
//! \param[in] uRGB                 Color value to place in the bitmap
//!
//! \note The prefered API to use instead of this function is gfx_bmp_PutPixel
//!       which will analyze the type of bitmap for which a pixel is being put
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_16BPP_565_dd(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                   uint16_t x, uint16_t y, gfx_Color_t uRGB);

///////////////////////////////////////////////////////////////////////////////
//! \brief Gets the size of the datablock for a BITMAP_TYPE_16BPP_565 bitmap
//!
//! \param[in] u16x     Pixels across
//! \param[in] u16y    Height in pixels
//! \return size of the data block, in bytes
//!
//! \note This function is called internally by graphics functions but is exposed
//!       in case the user would like to call it directly.
///////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_16BPP_565_dd(uint16_t u16x, uint16_t u16y);

///////////////////////////////////////////////////////////////////////////////
//! \brief This is the optimized version of BITMAP_TYPE_16BPP_565 to BITMAP_TYPE_16BPP_565 bitblt operation.
//!
//! This function copies a bitmap into a rectangle within another.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//!
//! \note      This code has been optimized for the ARM Thumb instruction set using the Green Hills Compiler with Osize
//!            Optimization setting.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_16BPP_565_dd(gfx_Color_t *pPalette,
                  gfx_Bmp_t *pDest,
                  gfx_Rect_t Rect,
                  gfx_Bmp_t *pSrc,
                  int SourceXoffset,
                  int SourceYoffset);

void gfx_bitblit_1BPP_Ideal_To_16BPP_565_dd(gfx_Color_t *pPalette,
                        gfx_Bmp_t *pDest,
                        gfx_Rect_t Rect,
                        gfx_Bmp_t *pSrc,
                        int SourceXoffset,
                        int SourceYoffset);

///////////////////////////////////////////////////////////////////////////////
//! \brief Draws a line, pre-clipped, in a given color to a given bitmap
//!
//! This function draws a line, pre-clipped, onto a 16bpp 565 bitmap
//! \todo introduce an assembly version of the horizontal line draw.
//! 
//! \param[in] pPalette     Not used by this function
//! \param[in] pDest        The gfx_Bmp_t to draw onto
//! \param[in] x0           x of point 0
//! \param[in] y0           y of point 0
//! \param[in] x1           x of point 1
//! \param[in] y1           y of point 1
//! \param[in] color        The color of the line
//!
//! \note The prefered API to use instead of this function is gfx_2d_DrawLine
//!       which will draw a line onto a device context. This function is exposed
//!       so that a line may be drawn directly onto a bitmap instead of a device
//!       context.  The caller should check all bounds to make sure the line
//!       will fit within the bitmap being drawn to.
///////////////////////////////////////////////////////////////////////////////
void gfx_DrawClippedLine_16BPP_565_dd(gfx_Color_t *pPalette,
                      gfx_Bmp_t *pDest,
                      int x0, int y0,
                      int x1, int y1,
                      gfx_Color_t color);

void gfx_alphablend_16BPP_565_dd(gfx_Color_t *pPalette,
                 gfx_Bmp_t *pDest,
                 gfx_Rect_t Rect,
                 gfx_Bmp_t *pSrc,
                 int SourceXoffset,
                 int SourceYoffset,
                 uint8_t alphaValue);

//function prototypes for BITMAP_TYPE_1BPP_IDEAL
////////////////////////////////////////////////////////////////////////////////
//! \brief Gets a pixel's color value from a BITMAP_TYPE_1BPP_IDEAL bitmap
//!
//! This function gets the pixel color at a given x,y converting it as best it can to match the ideal RGB
//! definition.  This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_GetPixel())
//!
//! \param[in]  pPalette  Pointer to the color palette.
//! \param[in]  pBitmap   Pointer to the bitmap
//! \param[in]  x         x position of the pixel
//! \param[in]  y         y position of the pixel
//! \param[out] pPixel    Pointer to a gfx_Color_t object to populate with the RGB color
//!
//! \note The prefered API to use instead of this function is gfx_bmp_GetPixel
//!       which will analyze the type of bitmap for which a pixel is being gotten
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
////////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_1BPP_Ideal(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                             uint16_t x, uint16_t y, gfx_Color_t *pPixel);

////////////////////////////////////////////////////////////////////////////////
//! \brief Sets a pixel in a BITMAP_TYPE_1BPP_IDEAL bitmap
//!
//! This function sets the pixel at a given x,y to a given RGB color(converting it as best it can to match
//! the capabilities of the bitmap. This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_SetPixel())
//!
//! \param[in] pPalette  Pointer to the color palette.
//! \param[in] pBitmap   Pointer to the bitmap
//! \param[in] x                    x position of the pixel
//! \param[in] y                    y position of the pixel
//! \param[in] uRGB                 Color value to place in the bitmap
//!
//! \note The prefered API to use instead of this function is gfx_bmp_PutPixel
//!       which will analyze the type of bitmap for which a pixel is being put
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_1BPP_Ideal(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                             uint16_t x, uint16_t y, gfx_Color_t uRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Calculates the data size required to support a bitmap of format type BITMAP_TYPE_1BPP_IDEAL
//!
//! \param[in] u16x  Width of the bitmap to calculate the data size.
//! \param[in] u16y Height of the bitmap to calculate the data size.
//!
//! \note This function is called internally by graphics functions but is exposed
//!       in case the user would like to call it directly.
////////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_1BPP_Ideal(uint16_t u16x, uint16_t u16y);

//function prototypes for BITMAP_TYPE_1BPP_VERTICAL
////////////////////////////////////////////////////////////////////////////////
//! \brief Gets a pixel's color value from a BITMAP_TYPE_1BPP_VERTICAL bitmap
//!
//! This function gets the pixel color at a given x,y converting it as best it can to match the ideal RGB
//! definition.  This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_GetPixel())
//!
//! \param[in]  pPalette  Pointer to the color palette.
//! \param[in]  pBitmap   Pointer to the bitmap
//! \param[in]  x         x position of the pixel
//! \param[in]  y         y position of the pixel
//! \param[out] pRGB      Pointer to a gfx_Color_t object to populate with the RGB color
//!
//! \note The prefered API to use instead of this function is gfx_bmp_GetPixel
//!       which will analyze the type of bitmap for which a pixel is being gotten
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
////////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_1BPP_Vertical(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap, 
                                uint16_t x, uint16_t y, gfx_Color_t *pRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Sets a pixel in a BITMAP_TYPE_1BPP_VERTICAL bitmap
//!
//! This function sets the pixel at a given x,y to a given RGB color(converting it as best it can to match
//! the capabilities of the bitmap. This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_SetPixel())
//!
//! \param[in] pPalette  Pointer to the color palette.
//! \param[in] pBitmap   Pointer to the bitmap
//! \param[in] x                    x position of the pixel
//! \param[in] y                    y position of the pixel
//! \param[in] cRGB                 Color value to place in the bitmap
//!
//! \note The prefered API to use instead of this function is gfx_bmp_PutPixel
//!       which will analyze the type of bitmap for which a pixel is being put
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_1BPP_Vertical(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap, 
                                uint16_t x, uint16_t y, gfx_Color_t cRGB);

///////////////////////////////////////////////////////////////////////////////
//! \brief Calculates the data size required to support a bitmap of format type BITMAP_TYPE_1BPP_VERTICAL
//!
//! \param[in] u16x Width of the bitmap to calculate the data size.
//! \param[in] u16y Height of the bitmap to calculate the data size.
//!
//! \note This function is called internally by graphics functions but is exposed
//!       in case the user would like to call it directly.
///////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_1BPP_Vertical(uint16_t u16x, uint16_t u16y);

//function prototypes for BITMAP_TYPE_18BPP_666
////////////////////////////////////////////////////////////////////////////////
//! \brief Gets a pixel's color value from a BITMAP_TYPE_18BPP_666 bitmap
//!
//! This function gets the pixel color at a given x,y converting it as best it can to match the ideal RGB
//! definition.  This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_GetPixel())
//!
//! \param[in]  pPalette Pointer to the active palette (unused by this function)
//! \param[in]  pBitmap  Pointer to the bitmap
//! \param[in]  x        x position of the pixel
//! \param[in]  y        y position of the pixel
//! \param[out] pRGB     Pointer to a gfx_Color_t object to populate with the RGB color
//!
//! \note The prefered API to use instead of this function is gfx_bmp_GetPixel
//!       which will analyze the type of bitmap for which a pixel is being gotten
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_18BPP_666(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                            uint16_t x, uint16_t y, gfx_Color_t *pRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Sets a pixel in a BITMAP_TYPE_18BPP_666 bitmap
//!
//! This function sets the pixel at a given x,y to a given RGB color(converting it as best it can to match
//! the capabilities of the bitmap. This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_SetPixel())
//!
//! \param[in] pPalette Pointer to the active palette (unused by this function)
//! \param[in] pBitmap  Pointer to the bitmap
//! \param[in] u16x     x position of the pixel
//! \param[in] u16y     y position of the pixel
//! \param[in] cRGB     Color value to place in the bitmap
//!
//! \note The prefered API to use instead of this function is gfx_bmp_PutPixel
//!       which will analyze the type of bitmap for which a pixel is being put
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_18BPP_666(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                            uint16_t u16x, uint16_t u16y, gfx_Color_t cRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Gets the size of the datablock for a 16BPP, 666 format bitmap
//!
//! \param[in] u16x  Pixels across
//! \param[in] u16y  Height in pixels
//!
//! \return size of the data block, in bytes
//!
//! \note This function is called internally by graphics functions but is exposed
//!       in case the user would like to call it directly.
///////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_18BPP_666(uint16_t u16x, uint16_t u16y);

////////////////////////////////////////////////////////////////////////////////
//! \brief  This function is the optimized version of BITMAP_TYPE_18BPP_666 to BITMAP_TYPE_18BPP_666 bitblt operation.        
//!
//! This function copies a bitmap into a rectangle within another.
//!
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap
//!                                 within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap
//!                                 within the rectangle.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_18BPP_666(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                           gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset);

////////////////////////////////////////////////////////////////////////////////
//! \brief Draws a line, pre-clipped, in a given color to a given bitmap
//!
//! This function draws a line, pre-clipped, onto a 16bpp 565 bitmap
//!
//! \param[in] pPalette     Not used by this function
//! \param[in] pDest        The gfx_Bmp_t to draw onto
//! \param[in] x0           x of point 0
//! \param[in] y0           y of point 0
//! \param[in] x1           x of point 1
//! \param[in] y1           y of point 1
//! \param[in] color        The color of the line
//!
//! \note The prefered API to use instead of this function is gfx_2d_DrawLine
//!       which will draw a line onto a device context.  This function is exposed
//!       so that a line may be drawn directly onto a bitmap instead of a device
//!       context.  The caller should check all bounds to make sure the line
//!       will fit within the bitmap being drawn to.
///////////////////////////////////////////////////////////////////////////////
void gfx_DrawClippedLine_18BPP_666(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, 
                                   int x0, int y0, int x1, int y1, gfx_Color_t color);


//function prototypes for BITMAP_TYPE_24BPP_888
////////////////////////////////////////////////////////////////////////////////
//! \brief Gets a pixel's color value from a BITMAP_TYPE_24BPP_888 bitmap
//!
//! This function gets the pixel color at a given x,y converting it as best it can to match the ideal RGB
//! definition.  This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_GetPixel())
//!
//! \param[in]  pPalette Pointer to the active palette (unused by this function)
//! \param[in]  pBitmap  Pointer to the bitmap
//! \param[in]  x        x position of the pixel
//! \param[in]  y        y position of the pixel
//! \param[out] pRGB     Pointer to a gfx_Color_t object to populate with the RGB color
//!
//! \note The prefered API to use instead of this function is gfx_bmp_GetPixel
//!       which will analyze the type of bitmap for which a pixel is being gotten
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_24BPP_888(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                            uint16_t x, uint16_t y, gfx_Color_t *pRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Sets a pixel in a BITMAP_TYPE_24BPP_888 bitmap
//!
//! This function sets the pixel at a given x,y to a given RGB color(converting it as best it can to match
//! the capabilities of the bitmap. This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_SetPixel())
//!
//! \param[in] pPalette Pointer to the active palette (unused by this function)
//! \param[in] pBitmap  Pointer to the bitmap
//! \param[in] u16x     x position of the pixel
//! \param[in] u16y     y position of the pixel
//! \param[in] cRGB     Color value to place in the bitmap
//!
//! \note The prefered API to use instead of this function is gfx_bmp_PutPixel
//!       which will analyze the type of bitmap for which a pixel is being put
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_24BPP_888(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                            uint16_t u16x, uint16_t u16y, gfx_Color_t cRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Gets the size of the datablock for a BITMAP_TYPE_24BPP_888 bitmap
//!
//! \param[in] u16x  Pixels across
//! \param[in] u16y  Height in pixels
//!
//! \return size of the data block, in bytes
//!
//! \note This function is called internally by graphics functions but is exposed
//!       in case the user would like to call it directly.
///////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_24BPP_888(uint16_t u16x, uint16_t u16y);

////////////////////////////////////////////////////////////////////////////////
//! \brief  This function is the optimized version of BITMAP_TYPE_24BPP_888 to BITMAP_TYPE_24BPP_888 bitblt operation.
//!
//! This function copies a bitmap into a rectangle within another.
//!
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap
//!                                 within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap
//!                                 within the rectangle.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_24BPP_888(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                           gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset);

//function prototypes for BITMAP_TYPE_32BPP_8888
////////////////////////////////////////////////////////////////////////////////
//! \brief Gets a pixel's color value from a BITMAP_TYPE_32BPP_8888 bitmap
//!
//! This function gets the pixel color at a given x,y converting it as best it can to match the ideal RGB
//! definition.  This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_GetPixel())
//!
//! \param[in]  pPalette Pointer to the active palette (unused by this function)
//! \param[in]  pBitmap  Pointer to the bitmap
//! \param[in]  x        x position of the pixel
//! \param[in]  y        y position of the pixel
//! \param[out] pRGB     Pointer to a gfx_Color_t object to populate with the RGB color
//!
//! \note The prefered API to use instead of this function is gfx_bmp_GetPixel
//!       which will analyze the type of bitmap for which a pixel is being gotten
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_32BPP_8888(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                 uint16_t x, uint16_t y, gfx_Color_t *pRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Sets a pixel in a BITMAP_TYPE_32BPP_8888 bitmap
//!
//! This function sets the pixel at a given x,y to a given RGB color(converting it as best it can to match
//! the capabilities of the bitmap. This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_SetPixel())
//!
//! \param[in] pPalette Pointer to the active palette (unused by this function)
//! \param[in] pBitmap  Pointer to the bitmap
//! \param[in] u16x     x position of the pixel
//! \param[in] u16y     y position of the pixel
//! \param[in] cRGB     Color value to place in the bitmap
//!
//! \note The prefered API to use instead of this function is gfx_bmp_PutPixel
//!       which will analyze the type of bitmap for which a pixel is being put
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_32BPP_8888(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                 uint16_t u16x, uint16_t u16y, gfx_Color_t cRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Gets the size of the datablock for a BITMAP_TYPE_32BPP_8888 bitmap
//!
//! \param[in] u16x  Pixels across
//! \param[in] u16y  Height in pixels
//!
//! \return size of the data block, in bytes
//!
//! \note This function is called internally by graphics functions but is exposed
//!       in case the user would like to call it directly.
///////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_32BPP_8888(uint16_t u16x, uint16_t u16y);

////////////////////////////////////////////////////////////////////////////////
//! \brief  This function is the optimized version of BITMAP_TYPE_32BPP_8888 to BITMAP_TYPE_32BPP_8888 bitblt operation.
//!
//! This function copies a bitmap into a rectangle within another.
//!
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap
//!                                 within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap
//!                                 within the rectangle.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_32BPP_8888(gfx_Color_t *pPalette,
                gfx_Bmp_t *pDest,
                gfx_Rect_t Rect,
                gfx_Bmp_t *pSrc,
                int SourceXoffset,
                int SourceYoffset);

///////////////////////////////////////////////////////////////////////////////
//! \brief This is the optimized version of BITMAP_TYPE_32BPP_888 to BITMAP_TYPE_16BPP_565 AlphaBlend operation.
//!
//! This function blends a bitmap into a rectangle within another bitmap.
//!
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//! \param[in] alphaValue           Global alpha value to apply to the entire source image, regardless of its per-pixel alpha channel values.
//!
//! \note      Using a global alphaValue and per-pixel alpha values can become somewhat confusing when trying to determine the
//!            the total alpha value to apply to a source-destination pixel.  This code uses the following rules to determine the
//!            the alpha value to use for a blend operation:
//!            
//!               Global alphaValue    |  Pixel alphaValue  | Result
//!            ---------------------------------------------------------------------------------------------------------------------------
//!             0xFF (opaque)          | 0xFF (opaque)      | Pixel is completely opaque.
//!             0xFF (opaque/disabled) | [0x01,0xFE]        | Alpha value is the pixel's alpha value.
//!             [0x01,0xFE]            | 0xFF (opaque)      | Alpha Value is the global alpha value.
//!             [0x01,0xFE]            | [0x01,0xFE]        | Alpha value is the multiplication of the global and pixel alpha values.
//!             0x00 (transparent)     | [0x00,0xFF]        | Entire source bitmap is transparent, so exit without performing an operation.
//!             [0x00,0xFF]            | 0x00 (transparent) | Pixel is completely transparent
//!
//! \note The prefered API to use instead of this function is gfx_bmp_AlphaBlendBitmap and gfx_bmp_AlphaBlendBitmapByAddress
//!       which will choose the appropriate blend function based on the types of the source and destination pair.
//!       This function is exposed so that a blend may be done directly onto a bitmap instead of a device
//!       context.  The caller should check all bounds to make sure the source bitmap
//!       will fit within the bitmap being blended onto.
///////////////////////////////////////////////////////////////////////////////
void gfx_alphablend_32BPP_888_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                              gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset, 
                              uint8_t alphaValue);

//function prototypes for BITMAP_TYPE_8BPP_PALETTE
////////////////////////////////////////////////////////////////////////////////
//! \brief Gets a pixel's color value from a BITMAP_TYPE_8BPP_PALETTE bitmap
//!
//! This function gets the pixel color at a given x,y converting.  It will obtain
//! this color from the palette passed in via the pPalette pointer.   The x,y
//! coordinate passed in is expected to be within the bitmap dimensions.
//! (That check is done by gfx_bmp_GetPixel())
//!
//! \param[in]  pPalette Pointer to the active palette (unused by this function)
//! \param[in]  pBitmap  Pointer to the bitmap
//! \param[in]  x        x position of the pixel
//! \param[in]  y        y position of the pixel
//! \param[out] pPixel   Pointer to a gfx_Color_t object to populate with the RGB color
//!
//! \note The prefered API to use instead of this function is gfx_bmp_GetPixel
//!       which will analyze the type of bitmap for which a pixel is being gotten
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_GetPixel_8BPP_Palette(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                             uint16_t x, uint16_t y, gfx_Color_t *pPixel);

////////////////////////////////////////////////////////////////////////////////
//! \brief Sets a pixel in a BITMAP_TYPE_8BPP_PALETTE bitmap
//!
//! This function sets the pixel at a given x,y to a given RGB color(converting it as best it can to match
//! the capabilities of the bitmap. This function expects X and Y to be within the bitmap width and height.
//! (That check is done by gfx_bmp_SetPixel())
//!
//! \param[in] pPalette Pointer to the active palette (unused by this function)
//! \param[in] pBitmap  Pointer to the bitmap
//! \param[in] x     x position of the pixel
//! \param[in] y     y position of the pixel
//! \param[in] uRGB     Color value to place in the bitmap
//!
//! \note Since the BITMAP_TYPE_8BPP_PALETTE bitmap type uses a color palette
//!       it may not be possible to set the pixel to the exact color passed
//!       in to this function.  Therefore an algorithm is used to choose the
//!       color from the palette that is the closest match to the color passed in.
//!       The closest color match (slight variation on the CIE94 color difference equation)
//!       treat each (R,G,B) tuple as a point in 3D space.
//!       It determines the distance from point 1 to point 2. 
//!       D=[(r1-r2)^2 + (g1-g2)^2 + (b1-b2)^2]^(1/2)
//!       The square root is not actually computed as it is unecessary for
//!       the comparison.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_PutPixel
//!       which will analyze the type of bitmap for which a pixel is being put
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_PutPixel_8BPP_Palette(gfx_Color_t *pPalette, gfx_Bmp_t *pBitmap,
                             uint16_t x, uint16_t y, gfx_Color_t uRGB);

////////////////////////////////////////////////////////////////////////////////
//! \brief Gets the size of the datablock for a BITMAP_TYPE_8BPP_PALETTE bitmap
//!
//! \param[in] u16x  Pixels across
//! \param[in] u16y  Height in pixels
//!
//! \return size of the data block, in bytes
//!
//! \note This function is called internally by graphics functions but is exposed
//!       in case the user would like to call it directly.
///////////////////////////////////////////////////////////////////////////////
uint32_t gfx_GetDataSize_8BPP_Palette(uint16_t u16x, uint16_t u16y);

////////////////////////////////////////////////////////////////////////////////
//! \brief This is the optimized version of BITMAP_TYPE_8BPP_PALETTE to BITMAP_TYPE_8BPP_PALETTE bitblt operation.
//!
//! This function copies a bitmap into a rectangle within another.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette             A pointer to the active palette (unused by this function)
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
////////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_8BPP_Palette(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                      gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset);

//Generic Graphics Functions
////////////////////////////////////////////////////////////////////////////////
//! \brief This function is the generic bitblt operation.
//! 
//! This function copies a rectangle from one bitmap to another.  It is not optimized for any particular format,
//! but will work for all formats supported by gfx_bmp_PutPixel and gfx_bmp_GetPixel.
//!
//! \param[in] pPalette      Pointer to the color palette
//! \param[in] pDest         Pointer to the destination bitmap
//! \param[in] pSrc          Pointer to the source bitmap
//! \param[in] Rect          Rectangle to draw within
//! \param[in] SourceXoffset Value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset Value to offset the Y coordinate of the source bitmap within the rectangle.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblt_Generic(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                        gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset);

////////////////////////////////////////////////////////////////////////////////
//! \brief Draws a line, pre-clipped, in a given color to a given bitmap.
//! 
//! This function draws a line, pre-clipped, onto any supported bitmap.
//! 
//! \param[in] pPalette  Pointer to the color palette.
//! \param[in] pDest     gfx_DeviceContext_t to operate on to check within.
//! \param[in] x0        x of point 0
//! \param[in] y0        y of point 0
//! \param[in] x1        x of point 1
//! \param[in] y1        y of point 1
//! \param[in] color     Color of the line
//!
//! \todo This function may be excess functionality than required.  The typical usage of line drawing
//!       in our system is horizontal or vertical lines, which are much simpler to clip.
//! \todo optimize:   the two branches (whether x or y is the incrementer) can be collapesed into one using
//!                   pointers to the original data.
//! 
//! \note The prefered API to use instead of this function is gfx_2d_DrawLine
//!       which will draw a line onto a device context.  This function is exposed
//!       so that a line may be drawn directly onto a bitmap instead of a device
//!       context.  The caller should check all bounds to make sure the line
//!       will fit within the bitmap being drawn to.
///////////////////////////////////////////////////////////////////////////////
void gfx_2d_DrawClippedLineGeneric(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, int x0,
                                   int y0, int x1, int y1, gfx_Color_t color);

////////////////////////////////////////////////////////////////////////////////
//! \brief This function is the generic AlphaBlend operation.
//! 
//! This function blends a rectangle from one bitmap onto another.  It is not optimized for any particular format,
//! but will work for all formats supported by gfx_bmp_PutPixel and gfx_bmp_GetPixel.
//!
//! \param[in] pPalette      Pointer to the color palette
//! \param[in] pDest         Pointer to the destination bitmap
//! \param[in] pSrc          Pointer to the source bitmap
//! \param[in] Rect          Rectangle to draw within
//! \param[in] SourceXoffset Value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset Value to offset the Y coordinate of the source bitmap within the rectangle.
//! \param[in] alphaValue    Value used as the alpha channel for the blend operation
//!
//! \note The prefered API to use instead of this function is gfx_bmp_AlphaBlendBitmap and gfx_bmp_AlphaBlendBitmapByAddress
//!       which will choose the appropriate blend function based on the types of the source and destination pair.
//!       This function is exposed so that a blend may be done directly onto a bitmap instead of a device
//!       context.  The caller should check all bounds to make sure the source bitmap
//!       will fit within the bitmap being blended onto.
///////////////////////////////////////////////////////////////////////////////
void gfx_alphablend_Generic(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                        gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset, uint8_t alphaValue);

////////////////////////////////////////////////////////////////////////////////
//! \brief This function is the generic StretchBlt operation.
//!
//! This function stretches a rectangle from one bitmap onto another.  It is not optimized for any particular format,
//! but will work for all formats supported by gfx_bmp_PutPixel and gfx_bmp_GetPixel.
//!
//! \param[in] *pPalette    Pointer to the color palette
//! \param[in] *pDest       Pointer to the destination bitmap
//! \param[in] Rect         Rectangle to draw within (not the same as the destination rectangle used for scale factor calculation)
//! \param[in] *dstRect     Rectangle to place the stetched bitmap into the destination (size used to compute stretch amount)
//! \param[in] *pSrc        Pointer to the source bitmap
//! \param[in] *srcRect     Pointer to a rectangle specifying the rectangle from the source to be stretched (size used to compute stretch amount)
//! \param[in] filterType   Type of stretching filter to be used: \ref gfx_StretchFilter_t
//!
//! \note The filters that can be used for the stretch operation are Nearest Neighbor,
//!       Bilinear Interpolation, and bicubic interpolation.  Currently, only the nearest
//!       neighbor algorithm is implemented.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_StretchBitmap and gfx_bmp_StretchBitmapByAddress
//!       which will choose the appropriate stretch function based on the types of the source and destination pair.
//!       This function is exposed so that a stretch may be done directly onto a bitmap instead of a device
//!       context.  The caller should check all bounds to make sure the source bitmap
//!       will fit within the bitmap being stretched into.
///////////////////////////////////////////////////////////////////////////////
void gfx_stretchblt_Generic(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect, 
                            gfx_Rect_t *dstRect, gfx_Bmp_t *pSrc, gfx_Rect_t *srcRect, gfx_StretchFilter_t filterType);


//Optimized Source-Destination Pair BitBlt Functions
////////////////////////////////////////////////////////////////////////////////
//! \brief Performs an optimized bit block transfer from a BITMAP_TYPE_1BPP_IDEAL source to a BITMAP_TYPE_16BPP_565 destination
//!
//! This function copies one 1 bpp bitmap into a rectangle of a 16 bpp bitmap.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette  Pointer to the color palette.
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//! 
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_1BPP_Ideal_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pDest,
                        gfx_Rect_t Rect, gfx_Bmp_t *pSrc,
                        int SourceXoffset, int SourceYoffset);

////////////////////////////////////////////////////////////////////////////////
//! \brief Performs an optimized bitblt from a BITMAP_TYPE_8BPP_PALETTE source to a BITMAP_TYPE_16BPP_565 destination
//!
//! This function copies one 1 bpp bitmap into a rectangle of a 16 bpp bitmap.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette  Pointer to the color palette.
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//!
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_8BPP_Palette_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, 
                                           gfx_Rect_t Rect, gfx_Bmp_t *pSrc, 
                                           int SourceXoffset, int SourceYoffset);

////////////////////////////////////////////////////////////////////////////////
//! \brief Performs an optimized bitblt from a BITMAP_TYPE_24BPP_888 source to a BITMAP_TYPE_16BPP_565 destination
//!
//! This function copies one 1 bpp bitmap into a rectangle of a 16 bpp bitmap.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette  Pointer to the color palette.
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//! 
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_24BPP_888_To_16BPP_565(gfx_Color_t *pPalette, gfx_Bmp_t *pDest, gfx_Rect_t Rect,
                           gfx_Bmp_t *pSrc, int SourceXoffset, int SourceYoffset);

////////////////////////////////////////////////////////////////////////////////
//! \brief Performs an optimized bitblt from a BITMAP_TYPE_32BPP_8888 source to a BITMAP_TYPE_16BPP_565 destination
//!
//! This function copies one 1 bpp bitmap into a rectangle of a 16 bpp bitmap.
//!
//! \note This function is an internal function and should not be called from the outside.
//! \param[in] pPalette  Pointer to the color palette.
//! \param[in] pDest                A pointer to the destination bitmap
//! \param[in] pSrc                 A pointer to the source bitmap
//! \param[in] Rect                 The rectangle to draw within
//! \param[in] SourceXoffset        The value to offset the X coordinate of the source bitmap within the rectangle.
//! \param[in] SourceYoffset        The value to offset the Y coordinate of the source bitmap within the rectangle.
//! 
//! \note The prefered API to use instead of this function is gfx_bmp_DrawBitmap and gfx_bmp_DrawBitmapByAddress
//!       which will analyze the type of bitmaps for which a BitBlt is being performed
//!       and will call this function automatically, however this function is
//!       exposed so the customer may call it directly if desired.
///////////////////////////////////////////////////////////////////////////////
void gfx_bitblit_32BPP_8888_To_16BPP_565(gfx_Color_t *pPalette,
                     gfx_Bmp_t *pDest,
                     gfx_Rect_t Rect,
                     gfx_Bmp_t *pSrc,
                     int SourceXoffset,
                     int SourceYoffset);

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
