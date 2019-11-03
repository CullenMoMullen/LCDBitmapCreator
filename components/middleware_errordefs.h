#ifndef _MIDDLEWARE_ERRORDEFS_H
#define _MIDDLEWARE_ERRORDEFS_H

#include "errordefs.h"
#include "middleware_subgroups.h"
//commented out codes are ones that are not being used at all right now.

#define ERROR_ASI_GROUP                  (ERROR_MASK|ASI_GROUP)
#define ERROR_FG_GROUP                   (ERROR_MASK|FILTERGRAPH_GROUP)
#define ERROR_PQI_GROUP                  (ERROR_MASK|PQI_GROUP)
#define ERROR_PQM_GROUP                  (ERROR_MASK|PQM_GROUP)
#define ERROR_CMI_GROUP                  (ERROR_MASK|CMI_GROUP)
#define ERROR_IMG_GROUP                  (ERROR_MASK|IMG_GROUP)
#define ERROR_MIXER_GROUP                (ERROR_MASK|MIXER_GROUP)
#define ERROR_RDS_GROUP                  (ERROR_MASK|RDS_GROUP)
#define ERROR_LRU_GROUP                  (ERROR_MASK|LRU_GROUP)
#define ERROR_PRESENTATION_GROUP         (ERROR_MASK|PRESENTATION_GROUP)
#define ERROR_UIM_GROUP                  (ERROR_MASK|UIM_GROUP)
#define ERROR_UTIL_SM_GROUP              (ERROR_MASK|UTIL_SM_GROUP)
#define ERROR_IMG_DEC_GROUP              (ERROR_MASK|IMG_DEC_GROUP)
#define ERROR_TSS_GROUP                  (ERROR_MASK|TSS_GROUP)
#define ERROR_USER_CLOCK_ALARM_GROUP     (ERROR_MASK|USER_CLOCK_ALARM_GROUP)
#define ERROR_USER_CLOCK_STOPWATCH_GROUP (ERROR_MASK|USER_CLOCK_STOPWATCH_GROUP)
#define ERROR_IMG_IDFFI_GROUP            (ERROR_MASK|IMG_IDFFI_GROUP)
#define ERROR_SETTINGS_GROUP             (ERROR_MASK|SETTINGS_GROUP)
#define ERROR_FW_UPDATE_GROUP            (ERROR_MASK|FW_UPDATE_GROUP)
#define ERROR_RUNTIME_GROUP              (ERROR_MASK|RUNTIME_GROUP)
#define ERROR_BEEP_GROUP                 (ERROR_MASK|BEEP_GROUP)


#endif//_MIDDLEWARE_ERRORDEFS_H


