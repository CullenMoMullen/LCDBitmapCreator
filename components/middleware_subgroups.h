////////////////////////////////////////////////////////////////////////////////
//! \addtogroup cmp
//! @{
//
// Copyright(C) 2019 Cullen Logan 
//
//! \file middleware_subgroups.h
//! \brief Defines the Middleware component subgroups.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MIDDLEWARE_SUBGROUPS_H
#define _MIDDLEWARE_SUBGROUPS_H

////////////////////////////////////////////////////////////////////////////////
// Includes and external references
////////////////////////////////////////////////////////////////////////////////
#include "../groups.h"



////////////////////////////////////////////////////////////////////////////////
// Definitions (global defines and typedefs)
////////////////////////////////////////////////////////////////////////////////

// Note: Middleware subgroup codes can range from "MIDDLEWARE_GROUP" to "MIDDLEWARE_GROUP+0x000FFFFF"

#define ASI_GROUP                  (MIDDLEWARE_GROUP|0x00000000)
#define PQI_GROUP                  (MIDDLEWARE_GROUP|0x00001000)
#define PQM_GROUP                  (PQI_GROUP)
#define CMI_GROUP                  (MIDDLEWARE_GROUP|0x00002000)
#define IMG_GROUP                  (MIDDLEWARE_GROUP|0x00003000)
#define MIXER_GROUP                (MIDDLEWARE_GROUP|0x00004000)
#define RDS_GROUP                  (MIDDLEWARE_GROUP|0x00005000)
#define LRU_GROUP                  (MIDDLEWARE_GROUP|0x00006000)
#define PRESENTATION_GROUP         (MIDDLEWARE_GROUP|0x00007000)
#define UIM_GROUP                  (MIDDLEWARE_GROUP|0x00008000)
#define UTIL_SM_GROUP              (MIDDLEWARE_GROUP|0x00009000)
#define IMG_DEC_GROUP              (MIDDLEWARE_GROUP|0x0000a000)
#define TSS_GROUP                  (MIDDLEWARE_GROUP|0x0000b000)
#define USER_CLOCK_ALARM_GROUP     (MIDDLEWARE_GROUP|0x0000c000)
#define USER_CLOCK_STOPWATCH_GROUP (MIDDLEWARE_GROUP|0x0000d000)
#define IMG_IDFFI_GROUP            (MIDDLEWARE_GROUP|0x0000e000)
#define FILTERGRAPH_GROUP          (MIDDLEWARE_GROUP|0x0000f000)
#define BTN_XLAT_GROUP             (MIDDLEWARE_GROUP|0x00010000)
#define CODEC_GROUP                (MIDDLEWARE_GROUP|0x00011000)
#define EFFECTS_GROUP              (MIDDLEWARE_GROUP|0x00012000)
#define GFX_GROUP                  (MIDDLEWARE_GROUP|0x00013000)
#define LYRICS_GROUP               (MIDDLEWARE_GROUP|0x00014000)
#define SRC_GROUP                  (MIDDLEWARE_GROUP|0x00015000)
#define STORE_GROUP                (MIDDLEWARE_GROUP|0x00016000)
#define USER_CLOCK_GROUP           (MIDDLEWARE_GROUP|0x00017000)
#define BT_GROUP                   (MIDDLEWARE_GROUP|0x00018000)
#define BT_STACK_GROUP             (MIDDLEWARE_GROUP|0x00019000)
#define BT_OBEX_GROUP              (MIDDLEWARE_GROUP|0x0001A000)
#define HOSTINTERFACE_GROUP        (MIDDLEWARE_GROUP|0x0001B000)
#define PROFILE_GROUP	           (MIDDLEWARE_GROUP|0x0001C000)
#define SETTINGS_GROUP             (MIDDLEWARE_GROUP|0x0001D000)
#define FW_UPDATE_GROUP            (MIDDLEWARE_GROUP|0x0001E000)
#define RUNTIME_GROUP              (MIDDLEWARE_GROUP|0x0001F000)
#define SPECTRUM_ANALYZER_GROUP    (MIDDLEWARE_GROUP|0X00020000)
#define BEEP_GROUP                 (MIDDLEWARE_GROUP|0X00021000)


#endif //_MIDDLEWARE_SUBGROUPS_H

////////////////////////////////////////////////////////////////////////////////
//! End of file
////////////////////////////////////////////////////////////////////////////////
//! @}
