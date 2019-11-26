///////////////////////////////////////////////////////////////////////////////
// Copyright (c) Freescale Semiconductor. All rights reserved.
// 
// Freescale Semiconductor
// Proprietary & Confidential
// 
// This source code and the algorithms implemented therein constitute confidential
// information and may comprise trade secrets of Freescale Semiconductor or its
// associates, and any use thereof is subject to the terms and conditions of the
// Confidential Disclosure Agreement pursual to which this source code was
// originally received.
////////////////////////////////////////////////////////////////////////////////
//! \file ddi_media_errordefs.h
//! \brief Error definitions for all media components.
////////////////////////////////////////////////////////////////////////////////
#ifndef _DDI_MEDIA_ERRORDEFS_H
#define _DDI_MEDIA_ERRORDEFS_H

#include "..\..\drivers/ddi_errordefs.h"

//! \addtogroup ddi_media
//! @{

    //! \name Logical drive layer errors
    //!
    //! Errors returned from the logical drive layer for all media types.
    //@{
        //! \brief Generic LDL error.  [0xf0208000]
        #define ERROR_DDI_LDL_GENERAL                                    (ERROR_DDI_LDL_GROUP)

        //! \brief [0xf0208001]
        #define ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER                (ERROR_DDI_LDL_GROUP + 1)

        #define ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED                     (ERROR_DDI_LDL_GROUP + 2)
        #define ERROR_DDI_LDL_LDRIVE_HARDWARE_FAILURE                    (ERROR_DDI_LDL_GROUP + 3)
        #define ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_TYPE                  (ERROR_DDI_LDL_GROUP + 4)
        #define ERROR_DDI_LDL_LDRIVE_INVALID_INFO_TYPE                   (ERROR_DDI_LDL_GROUP + 5)
        #define ERROR_DDI_LDL_LDRIVE_SECTOR_OUT_OF_BOUNDS                (ERROR_DDI_LDL_GROUP + 6)
        #define ERROR_DDI_LDL_LDRIVE_WRITE_PROTECTED                     (ERROR_DDI_LDL_GROUP + 7)
        #define ERROR_DDI_LDL_LDRIVE_MUST_HAVE_MORE_THAN_ONE_SECTOR      (ERROR_DDI_LDL_GROUP + 9)
        #define ERROR_DDI_LDL_LDRIVE_WRITE_ABORT                         (ERROR_DDI_LDL_GROUP + 11)
        #define ERROR_DDI_LDL_LDRIVE_MEDIA_NOT_ALLOCATED                 (ERROR_DDI_LDL_GROUP + 12)
        #define ERROR_DDI_LDL_LDRIVE_LOW_LEVEL_MEDIA_FORMAT_REQUIRED     (ERROR_DDI_LDL_GROUP + 13)
        #define ERROR_DDI_LDL_LDRIVE_DRIVE_FULL                          (ERROR_DDI_LDL_GROUP + 14)
        #define ERROR_DDI_LDL_LDRIVE_NANDTHREADSAFEMUTEX_FAILED          (ERROR_DDI_LDL_GROUP + 15)
        #define ERROR_DDI_LDL_LMEDIA_HARDWARE_FAILURE                    (ERROR_DDI_LDL_GROUP + 16)
        #define ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER                (ERROR_DDI_LDL_GROUP + 17)
        #define ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED               (ERROR_DDI_LDL_GROUP + 18)
        #define ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_DISCOVERED                (ERROR_DDI_LDL_GROUP + 19)
        #define ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_INFO_TYPE             (ERROR_DDI_LDL_GROUP + 20)
        #define ERROR_DDI_LDL_LMEDIA_ALLOCATION_TOO_LARGE                (ERROR_DDI_LDL_GROUP + 21)
        #define ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_ERASED                    (ERROR_DDI_LDL_GROUP + 22)
        #define ERROR_DDI_LDL_LMEDIA_MEDIA_ERASED                        (ERROR_DDI_LDL_GROUP + 23)
        #define ERROR_DDI_LDL_LMEDIA_MEDIA_ALLOCATE_BOUNDS_EXCEEDED      (ERROR_DDI_LDL_GROUP + 24)
        #define ERROR_DDI_LDL_CALLBACK_REGISTER_FAILED                   (ERROR_DDI_LDL_GROUP + 25)
        #define ERROR_DDI_LDL_CALLBACK_DEREGISTER_FAILED                 (ERROR_DDI_LDL_GROUP + 26)

        //! \brief Indicates that the corrupted drive is not recoverable. [0xf000801b]
        #define ERROR_DDI_LDL_LDRIVE_DRIVE_NOT_RECOVERABLE               (ERROR_DDI_LDL_GROUP + 27)

        //! \brief Cannot set the sector size to the given value. [0xf000801c]
        #define ERROR_DDI_LDL_LDRIVE_INVALID_SECTOR_SIZE                 (ERROR_DDI_LDL_GROUP + 28)

        //! \brief Cannot do something because the drive is already initialized. [0xf000801d]
        #define ERROR_DDI_LDL_LDRIVE_ALREADY_INITIALIZED                 (ERROR_DDI_LDL_GROUP + 29)

        //! \brief There is no drive with the given tag value. [0xf000801e]
        #define ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_TAG                   (ERROR_DDI_LDL_GROUP + 30)
        
        //! \brief An LDL iterator has no more items to return. [0xf000801f]
        #define ERROR_DDI_LDL_ITERATOR_DONE                              (ERROR_DDI_LDL_GROUP + 31)
        
        //! \brief An LDL API is unimplemented by the underlying media driver. [0xf0008020]
        #define ERROR_DDI_LDL_UNIMPLEMENTED                              (ERROR_DDI_LDL_GROUP + 32)
        
    //@}

//! @}

//! \addtogroup media_buf_mgr
//! @{

    //! \name Media buffer manager errors
    //!
    //! Errors that the media buffer manager will return from its APIs.
    //@{
        //! General error. Not used. [0xf021f000]
        #define ERROR_DDI_MEDIABUFMGR_GENERAL                            (ERROR_DDI_MEDIABUFMGR_GROUP)

        //! There is no room to add another buffer to the buffer manager. [0xf021f001]
        #define ERROR_DDI_MEDIABUFMGR_NO_ROOM                            (ERROR_DDI_MEDIABUFMGR_GROUP + 1)

        //! The buffer passed into buffer_release() was not obtained from the buffer manager. [0xf021f002]
        #define ERROR_DDI_MEDIABUFMGR_INVALID_BUFFER                     (ERROR_DDI_MEDIABUFMGR_GROUP + 2)

        //! The buffer manager was unable to allocate a new temporary buffer for some reason. [0xf021f003]
        #define ERROR_DDI_MEDIABUFMGR_ALLOC_FAILED                       (ERROR_DDI_MEDIABUFMGR_GROUP + 3)
    //@}

//! @}

//! \addtogroup media_cache
//! @{

    //! \name Media cache errors
    //!
    //@{
        //! General error, not used. [0xf021e000]
        #define ERROR_DDI_MEDIA_CACHE_GENERAL                            (ERROR_DDI_MEDIA_CACHE_GROUP)

        //! The buffer passed to media_cache_init() is not useable for some reason. [0xf021e001]
        #define ERROR_DDI_MEDIA_CACHE_INVALID_BUFFER                     (ERROR_DDI_MEDIA_CACHE_GROUP + 1)

        //! Timed out while waiting for exclusive access to a cache entry. [0xf021e002]
        #define ERROR_DDI_MEDIA_CACHE_TIMEOUT                            (ERROR_DDI_MEDIA_CACHE_GROUP + 2)
    //@}

//! @}

//! \addtogroup ddi_nand
//! @{

    //! \name NAND driver errors
    //!
    //! Errors returned from the NAND driver through direct calls to it. Note that
    //! many of these errors are no longer reported and are here for historical
    //! information only. Also note that the NAND driver will return LDL errors from
    //! its functions that implement the logical drive and logical media interfaces.
    //@{
        //! \brief Unused general error. [0xf0220000]
        #define ERROR_DDI_NAND_GROUP_GENERAL                             (ERROR_DDI_NAND_GROUP)
        #define ERROR_DDI_NAND_LMEDIA_NO_REGIONS_IN_MEDIA                (ERROR_DDI_NAND_GROUP + 1)
        #define ERROR_DDI_NAND_LMEDIA_DRIVES_MAX_OUT                     (ERROR_DDI_NAND_GROUP + 2)
        #define ERROR_DDI_NAND_LMEDIA_MEDIA_WRITE_PROTECTED              (ERROR_DDI_NAND_GROUP + 3)
        #define ERROR_DDI_NAND_LMEDIA_BAD_BLOCKS_MAX_OUT                 (ERROR_DDI_NAND_GROUP + 4)
        #define ERROR_DDI_NAND_LMEDIA_NOT_ALLOCATED                      (ERROR_DDI_NAND_GROUP + 5)
        #define ERROR_DDI_NAND_CONFIG_BLOCK_NOT_FOUND                    (ERROR_DDI_NAND_GROUP + 6)
        #define ERROR_DDI_NAND_WRITE_PHYS_SECTOR_PROGRAM_FAILED          (ERROR_DDI_NAND_GROUP + 7)
        #define ERROR_DDI_NAND_MULTI_WRITE_SECTOR_FIFO_OVERFLOW          (ERROR_DDI_NAND_GROUP + 8)
        #define ERROR_DDI_NAND_MULTI_WRITE_SECTOR_FIFO_UNDERFLOW         (ERROR_DDI_NAND_GROUP + 9)
        #define ERROR_DDI_NAND_DATA_DRIVE_LOGICAL_SECTOR_OUT_OF_BOUNDS   (ERROR_DDI_NAND_GROUP + 10)
        #define ERROR_DDI_NAND_DATA_DRIVE_RBLOCK_NOT_FOUND               (ERROR_DDI_NAND_GROUP + 11)
        #define ERROR_DDI_NAND_DATA_DRIVE_NO_FREE_RBLOCKS                (ERROR_DDI_NAND_GROUP + 12)
        #define ERROR_DDI_NAND_DATA_DRIVE_USECTOR_LOOKUP_INTERNAL_1      (ERROR_DDI_NAND_GROUP + 13)
        #define ERROR_DDI_NAND_DATA_DRIVE_SECTOR_NOT_UPDATED             (ERROR_DDI_NAND_GROUP + 14)
        #define ERROR_DDI_NAND_DATA_DRIVE_CANT_RECYCLE_USECTOR_MAP       (ERROR_DDI_NAND_GROUP + 15)
        #define ERROR_DDI_NAND_DATA_DRIVE_UBLOCK_LBAS_INCONSISTENT       (ERROR_DDI_NAND_GROUP + 16)
        #define ERROR_DDI_NAND_DATA_DRIVE_UBLOCK_HSECTORIDX_OUT_OF_RANGE (ERROR_DDI_NAND_GROUP + 17)
        #define ERROR_DDI_NAND_DATA_DRIVE_CANT_RECYCLE_UBLOCK            (ERROR_DDI_NAND_GROUP + 18)
        #define ERROR_DDI_NAND_DATA_DRIVE_BBTABLE_FULL                   (ERROR_DDI_NAND_GROUP + 19)
        #define ERROR_DDI_NAND_DATA_DRIVE_UPDATE_NOT_OPEN                (ERROR_DDI_NAND_GROUP + 20)
        #define ERROR_DDI_NAND_DATA_DRIVE_CANT_GET_ERASED_UBLOCK         (ERROR_DDI_NAND_GROUP + 21)
        #define ERROR_DDI_NAND_DATA_DRIVE_NO_ERASED_UBLOCKS              (ERROR_DDI_NAND_GROUP + 22)
        #define ERROR_DDI_NAND_DATA_DRIVE_CANT_ERASE_FREE_UBLOCK         (ERROR_DDI_NAND_GROUP + 23)
        #define ERROR_DDI_NAND_DATA_DRIVE_KILLUSECTOR_INTERNAL_1         (ERROR_DDI_NAND_GROUP + 24)
        #define ERROR_DDI_NAND_DATA_DRIVE_KILLUSECTOR_INTERNAL_2         (ERROR_DDI_NAND_GROUP + 25)
        #define ERROR_DDI_NAND_DATA_DRIVE_RETURN_BLOCK_NOT_UPDATED       (ERROR_DDI_NAND_GROUP + 26)
        #define ERROR_DDI_NAND_DATA_DRIVE_UBLOCK_PROTECT_TABLE_FULL      (ERROR_DDI_NAND_GROUP + 27)
        #define ERROR_DDI_NAND_DATA_DRIVE_UBLOCK_ALREADY_PROTECTED       (ERROR_DDI_NAND_GROUP + 28)
        #define ERROR_DDI_NAND_DATA_DRIVE_UBLOCK_NOT_PROTECTED           (ERROR_DDI_NAND_GROUP + 29)
        #define ERROR_DDI_NAND_DATA_DRIVE_RECOVERUBLOCK_INTERNAL_1       (ERROR_DDI_NAND_GROUP + 30)
        #define ERROR_DDI_NAND_DATA_DRIVE_RECOVERUBLOCK_INTERNAL_2       (ERROR_DDI_NAND_GROUP + 31)
        #define ERROR_DDI_NAND_DATA_DRIVE_UBLOCK_NOT_IN_UTABLE           (ERROR_DDI_NAND_GROUP + 32)
        #define ERROR_DDI_NAND_DATA_DRIVE_CANT_ALLOCATE_USECTORS_MAPS    (ERROR_DDI_NAND_GROUP + 33)
        #define ERROR_DDI_NAND_DATA_DRIVE_CANT_INIT_DATA_REGIONS_LIST    (ERROR_DDI_NAND_GROUP + 34)
        #define ERROR_DDI_NAND_DATA_DRIVE_TOO_MANY_UBLOCKS_IN_CONFIG     (ERROR_DDI_NAND_GROUP + 35)
        #define ERROR_DDI_NAND_DATA_DRIVE_USECTOR_INDEX_IS_NOT_NEXT      (ERROR_DDI_NAND_GROUP + 36)
        #define ERROR_DDI_NAND_DATA_DRIVE_USECTOR_ALREADY_UPDATED        (ERROR_DDI_NAND_GROUP + 37)
        #define NAND_DATA_DRIVE_ERROR_BgGC_USECTOR_ERASE_TIMEDOUT        (ERROR_DDI_NAND_GROUP + 38)
        #define NAND_DATA_DRIVE_ERROR_BgGC_HSECTOR_COPY_TIMEDOUT         (ERROR_DDI_NAND_GROUP + 39)
        #define NAND_DATA_DRIVE_ERROR_BgGC_ALREADY_ENABLED               (ERROR_DDI_NAND_GROUP + 40)
        #define ERROR_DDI_NAND_DATA_DRIVE_BgGC_HSECTOR_ERASE_TIMEDOUT    (ERROR_DDI_NAND_GROUP + 41)
        #define ERROR_DDI_NAND_DATA_DRIVE_BgGC_SECTOR_NOT_UPDATED        (ERROR_DDI_NAND_GROUP + 42)
        #define ERROR_DDI_NAND_DATA_DRIVE_NO_STALE_UBLOCKS               (ERROR_DDI_NAND_GROUP + 43)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S0_FETCH_FAILED            (ERROR_DDI_NAND_GROUP + 44)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S1_FETCH_FAILED            (ERROR_DDI_NAND_GROUP + 45)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S2_1_FETCH_FAILED          (ERROR_DDI_NAND_GROUP + 46)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S2_2_FETCH_FAILED          (ERROR_DDI_NAND_GROUP + 47)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S3_1_FETCH_FAILED          (ERROR_DDI_NAND_GROUP + 48)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S3_2_FETCH_FAILED          (ERROR_DDI_NAND_GROUP + 49)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S4_1_FETCH_FAILED          (ERROR_DDI_NAND_GROUP + 50)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S4_2_FETCH_FAILED          (ERROR_DDI_NAND_GROUP + 51)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S5_FETCH_FAILED            (ERROR_DDI_NAND_GROUP + 52)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S0_ECC_TIMEOUT             (ERROR_DDI_NAND_GROUP + 53)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S2_ECC_TIMEOUT             (ERROR_DDI_NAND_GROUP + 54)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S3_ECC_TIMEOUT             (ERROR_DDI_NAND_GROUP + 55)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_S4_ECC_TIMEOUT             (ERROR_DDI_NAND_GROUP + 56)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_WRITE_FAILED               (ERROR_DDI_NAND_GROUP + 57)
        #define ERROR_DDI_NAND_DATA_DRIVE_CMW_RELEASE_FAILED             (ERROR_DDI_NAND_GROUP + 58)
        #define ERROR_DDI_NAND_DATA_DRIVE_INVALID_LOGICAL_SECTOR         (ERROR_DDI_NAND_GROUP + 59)
        #define ERROR_DDI_NAND_DATA_DRIVE_INVALID_RELATIVE_SECTOR        (ERROR_DDI_NAND_GROUP + 60)
        #define ERROR_DDI_NAND_DATA_DRIVE_EMPTY_UBLOCK                   (ERROR_DDI_NAND_GROUP + 61)
        #define ERROR_DDI_NAND_DATA_DRIVE_BAD_USECTOR_MAP                (ERROR_DDI_NAND_GROUP + 62)
        #define ERROR_DDI_NAND_DATA_DRIVE_TOO_MANY_BLOCK_RECOVERIES      (ERROR_DDI_NAND_GROUP + 63)
        #define ERROR_DDI_NAND_HAL_NANDTYPE_MISMATCH                     (ERROR_DDI_NAND_GROUP + 64)
        #define ERROR_DDI_NAND_HAL_LOOKUP_ID_FAILED                      (ERROR_DDI_NAND_GROUP + 65)
        #define ERROR_DDI_NAND_HAL_WRITE_PORT_CMD                        (ERROR_DDI_NAND_GROUP + 66)
        #define ERROR_DDI_NAND_HAL_WRITE_PORT_ADDR                       (ERROR_DDI_NAND_GROUP + 67)
        #define ERROR_DDI_NAND_HAL_WAIT_FOR_READY_PORT                   (ERROR_DDI_NAND_GROUP + 68)
        #define ERROR_DDI_NAND_HAL_LOCKPORT_TIMEOUT                      (ERROR_DDI_NAND_GROUP + 69)
        #define ERROR_DDI_NAND_HAL_LOCKNAND_TIMEOUT                      (ERROR_DDI_NAND_GROUP + 70)
        #define ERROR_DDI_NAND_HAL_WRITE_FAILED                          (ERROR_DDI_NAND_GROUP + 71)
        #define ERROR_DDI_NAND_HAL_READ_FAILED                           (ERROR_DDI_NAND_GROUP + 72)
        #define ERROR_DDI_NAND_HAL_SETNANDBUSY_FAILED                    (ERROR_DDI_NAND_GROUP + 73)
        #define ERROR_DDI_NAND_HAL_ASYNCWAIT_CALLBACK_ERR                (ERROR_DDI_NAND_GROUP + 74)
        #define ERROR_DDI_NAND_HAL_COMPUTE_ECC_RSHW_DISABLE              (ERROR_DDI_NAND_GROUP + 75)
        #define ERROR_DDI_NAND_HAL_COMPUTE_ECC_RSDEC_DISABLE             (ERROR_DDI_NAND_GROUP + 76)
        #define ERROR_DDI_NAND_HAL_COMPUTE_ECC_RSENC_DISABLE             (ERROR_DDI_NAND_GROUP + 77)
        #define ERROR_DDI_NAND_HAL_COMPUTE_ECC_NOT_DONE                  (ERROR_DDI_NAND_GROUP + 78)
        #define ERROR_DDI_NAND_HAL_LOCKECC_TIMEOUT                       (ERROR_DDI_NAND_GROUP + 79)
        #define ERROR_DDI_NAND_HAL_LOCKECC_LOCKED                        (ERROR_DDI_NAND_GROUP + 80)

        //! The following three error codes are, and must remain, in ascending numerical order of severity.
        #define ERROR_DDI_NAND_HAL_ECC_FIXED                             (ERROR_DDI_NAND_GROUP + 81)
        #define ERROR_DDI_NAND_HAL_ECC_FIXED_REWRITE_SECTOR              (ERROR_DDI_NAND_GROUP + 82)
        #define ERROR_DDI_NAND_HAL_ECC_FIX_FAILED                        (ERROR_DDI_NAND_GROUP + 83)

        #define ERROR_DDI_NAND_NANDINIT_FAILED                           (ERROR_DDI_NAND_GROUP + 84)
        #define ERROR_DDI_NAND_READ_ID_FAILED                            (ERROR_DDI_NAND_GROUP + 85)
        #define ERROR_DDI_NAND_SEARCH_FAILED                             (ERROR_DDI_NAND_GROUP + 86)
        #define ERROR_DDI_NAND_DMA_TIMEOUT                               (ERROR_DDI_NAND_GROUP + 87)
        #define ERROR_DDI_NAND_ERASE_FAILED                              (ERROR_DDI_NAND_GROUP + 88)
        #define ERROR_DDI_NAND_RESET_FAILED                              (ERROR_DDI_NAND_GROUP + 89)
        #define ERROR_DDI_NAND_PROGRAM_FAILED                            (ERROR_DDI_NAND_GROUP + 90)
        #define ERROR_DDI_NAND_DMA_BUSY                                  (ERROR_DDI_NAND_GROUP + 91)
        #define ERROR_DDI_NAND_NO_GPMI                                   (ERROR_DDI_NAND_GROUP + 92)
        #define ERROR_DDI_NAND_D_BAD_BLOCK_TABLE_BLOCK_NOT_FOUND         (ERROR_DDI_NAND_GROUP + 95)
        #define ERROR_DDI_NAND_CANT_ALLOCATE_DBBT_BLOCK                  (ERROR_DDI_NAND_GROUP + 96)
        #define ERROR_DDI_NAND_MEDIA_FINDING_NEXT_VALID_BLOCK            (ERROR_DDI_NAND_GROUP + 97)
        #define ERROR_DDI_NAND_MEDIA_CANT_ALLOCATE_BCB_BLOCK             (ERROR_DDI_NAND_GROUP + 98)
        #define ERROR_DDI_NAND_DRIVER_NO_BCB                             (ERROR_DDI_NAND_GROUP + 99)
        #define ERROR_DDI_NAND_BCB_SEARCH_FAILED                         (ERROR_DDI_NAND_GROUP + 100)
        #define ERROR_DDI_NAND_INVALID_BOOT_IMAGE_FORMAT                 (ERROR_DDI_NAND_GROUP + 101)
        #define ERROR_DDI_NAND_NO_MATCHING_SECTION                       (ERROR_DDI_NAND_GROUP + 102)

        //! General error
        #define ERROR_DDI_NAND_MAPPER_ERROR                              (ERROR_DDI_NAND_GROUP + 102)

        //! Mapper is not initialized yet
        #define ERROR_DDI_NAND_MAPPER_UNITIALIZED                        (ERROR_DDI_NAND_GROUP + 103)
        #define ERROR_DDI_NAND_MAPPER_INVALID_PHYADDR                    (ERROR_DDI_NAND_GROUP + 104)
        #define ERROR_DDI_NAND_MAPPER_INVALID_MAPTYPE                    (ERROR_DDI_NAND_GROUP + 105)
        #define ERROR_DDI_NAND_MAPPER_GET_BLOCK_FAILED                   (ERROR_DDI_NAND_GROUP + 106)
        #define ERROR_DDR_NAND_MAPPER_PHYMAP_MAPFULL                     (ERROR_DDI_NAND_GROUP + 107)
        #define ERROR_DDI_NAND_MAPPER_FIND_PHYMAP_BLOCK_FAILED           (ERROR_DDI_NAND_GROUP + 108)
        #define ERROR_DDI_NAND_MAPPER_FIND_LBAMAP_BLOCK_FAILED           (ERROR_DDI_NAND_GROUP + 109)

        //! Lba is out of range
        #define ERROR_DDI_NAND_MAPPER_LBA_OUTOFBOUND                     (ERROR_DDI_NAND_GROUP + 110)

        //! Logical page address is out of range
        #define ERROR_DDI_NAND_MAPPER_PAGE_OUTOFBOUND                    (ERROR_DDI_NAND_GROUP + 111)
        #define ERROR_DDI_NAND_MAPPER_MAKE_SPACE_FAILED                  (ERROR_DDI_NAND_GROUP + 112)
        #define ERROR_DDI_NAND_MAPPER_LBA_CORRUPTED                      (ERROR_DDI_NAND_GROUP + 113)
        #define ERROR_DDI_NAND_MAPPER_ZONE_MAP_CACHE_INIT_FAILED         (ERROR_DDI_NAND_GROUP + 114)
        #define ERROR_DDI_NAND_MAPPER_ZONE_MAP_INSUFFICIENT_NUM_FREE_BLOCKS (ERROR_DDI_NAND_GROUP + 115)
        #define ERROR_DDI_NAND_MAPPER_AUDIT_PHYMAP_FAIL                  (ERROR_DDI_NAND_GROUP + 116)
        #define ERROR_DDI_NAND_MAPPER_AUDIT_ZONEMAP_FAIL                 (ERROR_DDI_NAND_GROUP + 117)
        #define ERROR_DDI_NAND_DATA_DRIVE_SECTOR_OUT_OF_BOUNDS           (ERROR_DDI_NAND_GROUP + 118)

        //! Failed to find the correct status.
        #define ERROR_DDI_NAND_HAL_CHECK_STATUS_FAILED                   (ERROR_DDI_NAND_GROUP + 119)

        //! Cannot initiate another firmware refresh because one is already in progress.
        #define ERROR_DDI_NAND_FIRMWARE_REFRESH_BUSY                     (ERROR_DDI_NAND_GROUP + 120)

        //! The version of the config block found on the NAND does not match the one expected by the firmware.
        #define ERROR_DDI_NAND_CONFIG_BLOCK_VERSION_MISMATCH             (ERROR_DDI_NAND_GROUP + 121)

        //! Error codes from decoding software ecc encoded NCB block.
        #define ERROR_DDI_NAND_DRIVER_NCB_TRIPLE_RED_CHK_FAILED          (ERROR_DDI_NAND_GROUP + 122)
        #define ERROR_DDI_NAND_DRIVER_NCB_SYNDROME_TABLE_MISMATCH        (ERROR_DDI_NAND_GROUP + 123)
        #define ERROR_DDI_NAND_DRIVER_NCB_HAMMING_DOUBLE_ERROR           (ERROR_DDI_NAND_GROUP + 124)
        #define ERROR_DDI_NAND_DRIVER_NCB_MEM_ALLOC_FAILED               (ERROR_DDI_NAND_GROUP + 125)
    //@}

//! @}

#endif//_DDI_MEDIA_ERRORDEFS_H 



