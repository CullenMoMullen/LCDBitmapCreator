////////////////////////////////////////////////////////////////////////////////
//! \addtogroup cmp_gfx
//! @{
//
// Copyright (c) 2019 Cullen Logan
//
//! \file    gfx_rsrcfont.h
//! \brief   Contains structures and defines for resource-based bitmap font.
//! \version 1.0
//! \date    19-August2005
////////////////////////////////////////////////////////////////////////////////
#ifndef __GFX_RSRCFONT_H
#define __GFX_RSRCFONT_H

#include "os/os_resource_api.h"
#include "os/threadx/tx_api.h"
#include "components/lru/lru.h"

//! \brief Value used to indicate that character spacing for a font is proportional.
#define GFX_RSRC_FONT_PROPORTIONAL 0

//! \brief Structure to hold the private data for the font.
typedef struct _gfx_RsrcFontData
{
    //! \brief Base Resource for the Font bitmaps in the resource file.
    os_resource_ResourceId_t m_uResource;
    //! \brief The line height for a font.  Max height of all glyphs.
    uint8_t             m_LineHeight;
    //! \brief Width for a character.  A zero denotes a proportional font.
    uint8_t             m_CharWidth;
    //! \brief Pointer to an array of handles for caching purposes.
    util_lru_Cache_t   *m_pCache;
    //! \brief Glyph to use as a replacement for an unsupported glyph
    uint16_t            m_u16UnknownGlyph;
    //! \brief Mutex to protect the data
    TX_MUTEX            m_CacheMutex;
} gfx_RsrcFontData_t;

////////////////////////////////////////////////////////////////////////////////
//! \brief Initializes a gfx_Font_t structure
//!
//! \param[in] pFont        font to initialize
//! \param[in] pRsrcFontData    pointer to a font specific data.
//!
//! \todo This function neeeds to be grown to do more than set up the Glyph function pointer.
//!       It needs to make some decision on the Glyph function pointer, or set some properties to
//!       base the font on.   (Resource table number, or...?)
////////////////////////////////////////////////////////////////////////////////
void gfx_rsrcfont_Initialize(gfx_Font_t *pFont, gfx_RsrcFontData_t *pRsrcFontData);


#endif
////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
