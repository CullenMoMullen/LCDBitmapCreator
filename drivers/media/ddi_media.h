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
//! \addtogroup ddi_media
//! @{
//! \file ddi_media.h
//! \brief Contains public interface for the Logical Drive Layer.
////////////////////////////////////////////////////////////////////////////////
#ifndef _DDI_MEDIA_H
#define _DDI_MEDIA_H

#include <types.h>
#include "ddi_media_errordefs.h"
#include "drive_tags.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

//! \brief Maximum number of entries in the media allocation table.
#define MAX_MEDIA_TABLE_ENTRIES                 8

//! \brief Maximum number of media supported at once.
#define MAX_LOGICAL_MEDIA                       2

//! \brief Maximum number of drives supported at once.
//!
//! The current set of drives is as follows:
//! - Internal data
//! - External data
//! - Hidden 1
//! - Hidden 2
//! - System primary
//! - System secondary
//! - System master
//!
//! With a few extra slots added for safety, the maximum is set to 10.
#define MAX_LOGICAL_DRIVES                      8

//! \brief Constant to be passed to erase functions.
#define DDI_MAGIC_NUMBER                        0xADEADE

//! \name Write types
//!
//! These values are passed to the read and write functions to give a hint as to
//! the sequence of I/O operations that is being performed.
//@{
#define WRITE_TYPE_RANDOM    0
#define WRITE_TYPE_SEQ_FIRST 1
#define WRITE_TYPE_SEQ_NEXT  2
#define WRITE_TYPE_NOREADBACK  3
//@}

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////

//! Abstract reference for a logical drive. This value should be unique for each drive.
typedef uint8_t DriveTag_t;

//! \brief TBD
//! \todo [PUBS] Add definition(s)...Low
typedef enum {
    //! \brief TBD
    kMediaStateUnknown,
    //! \brief TBD
    kMediaStateErased,
    //! \brief TBD
    kMediaStateAllocated
} kMediaState_t;

//! \brief This initialization state type can be used to signify if media or drive 
//! or FS init has been attempted yet and whether it succeeded.
//! Note: See related SCSI_MEDIA_STATE (logical drive state) & its state machine 
//!       spec in scsi.h. and see g_eMtpExternalStoreState.
typedef enum {    
    eInitPending = 0, // Default state indicates that init attempt hasn't completed yet, so can wait on it.
    eInitFailed,               
    eInitSucceeded,   // Initialized. 
    eInitTerminated   // After a shutdown, the state of entity initialization is terminated.
} InitializationState_t; 

//! \brief An enumeration of physical storage media types supported by STMP3xxx SDK5
typedef enum {
    //! \brief NAND flash is typically the primary storage media
    kMediaTypeNand,
    //! \brief MultiMedia Card (MMC) or Secure Digital (SD) card may be removable.
    kMediaTypeMMC,
    //! \brief Hard Disk Drive (HDD) spinning random access R/W storge media
    kMediaTypeHDD,
    //! \brief RAM based virtual disk for mounting an FS in fast access RAM (if extra available).
    kMediaTypeRAM,
    //! \brief Toshiba LBA-NAND device.
    kMediaTypeLbaNand
} PhysicalMediaType_t;

//! \brief TBD
//! \todo [PUBS] Add definition(s)...Medium
enum _logical_media_info
{
    //! \brief TBD
    kMediaInfoNumberOfDrives = 0,
    //! \brief TBD
    kMediaInfoSizeInBytes = 1,
    //! \brief TBD
    kMediaInfoAllocationUnitSizeInBytes = 2,
    //! \brief TBD
    kMediaInfoIsInitialized = 3,
    //! \brief TBD
    kMediaInfoMediaState = 4,
    //! \brief TBD
    kMediaInfoIsWriteProtected = 5,
    //! \brief TBD
    kMediaInfoPhysicalMediaType = 6,
    //! \brief TBD
    kMediaInfoSizeOfSerialNumberInBytes = 7,
    //! \brief TBD
    kMediaInfoSerialNumber = 8,
    //! \brief TBD
    kMediaInfoIsSystemMedia = 9,
    //! \brief TBD
    kMediaInfoIsMediaPresent = 10,

    // The Updater app requests these and udpater scsi commands get them.
    // Commands below are only allowed for media type nand initially.
    // Other media need stub functions before MediaGetInfo() to avoid error reply. MMC has stubs
    //! \brief Media Info page size in bytes (page terminology may only be valid for nand media type).
    kMediaInfoPageSizeInBytes = 11,   //
    //! \brief Media Info Mfg Id for Nand case: Mfg Id byte (1st byte of n byte readId nand HW cmd response)
    kMediaInfoMediaMfgId = 12, // eg: 0xEC for samsung.
    //! \brief Media Info Id details Nand Flash case returns all bytes from nand HW readId command.
    kMediaInfoIdDetails = 13,
    kMediaInfoNumChipEnables = 14,   // num CE discovered at driver init time (up to build option max supported num CE)
    
    //! \brief Whether the media is removable.
    //!
    //! The value is a \a bool.
    kMediaInfoIsRemovable = 15,
    
    //! \brief Driver-specific reference value.
    kMediaInfoOpaqueDriverData = 16
};

//! \brief List of drive info selectors.
//!
//! These selectors are passed to DriveGetInfo() and DriveSetInfo() to read and write
//! certain fields per drive. Not all selectors apply to every drive type or media type,
//! and only a few selectors are mutable with DriveSetInfo().
enum _logical_drive_info
{
    //! \brief Nominal sector size in bytes for this drive.
    //!
    //! This sector size is the "nominal" sector size. It may be different (i.e., smaller)
    //! from the native sector size that is determined by the underlying media. Use this value
    //! if you are using the media cache to read and write.
    //!
    //! This selector's data is a uint32_t value. It can be overridden by a call to
    //! DriveSetInfo(). The new value must be a power of two between 512 and the value of
    //! the #kDriveInfoNativeSectorSizeInBytes selector. However, the sector size can only
    //! be set \i before the given drive is initialized.
    //!
    //! \retval SUCCESS
    //! \retval ERROR_DDI_LDL_LDRIVE_INVALID_SECTOR_SIZE
    //! \retval ERROR_DDI_LDL_LDRIVE_ALREADY_INITIALIZED
    kDriveInfoSectorSizeInBytes = 0,
    
    //! \brief TBD
    kDriveInfoEraseSizeInBytes = 1,
    //! \brief TBD
    kDriveInfoSizeInBytes = 2,
    //! \brief TBD
    kDriveInfoSizeInMegaBytes = 3,
    
    //! \brief Number of nominal sectors that the drive occupies.
    //!
    //! The data for this selector is a single uint32_t value that is read-only.
    kDriveInfoSizeInSectors = 4,
    
    //! \brief TBD
    kDriveInfoType = 5,
    //! \brief TBD
    kDriveInfoTag = 6,
    //! \brief TBD
    kDriveInfoComponentVersion = 7,
    //! \brief TBD
    kDriveInfoProjectVersion = 8,
    //! \brief TBD
    kDriveInfoIsWriteProtected = 9,
    //! \brief TBD
    kDriveInfoSizeOfSerialNumberInBytes = 10,
    //! \brief TBD
    kDriveInfoSerialNumber = 11,
    //! \brief TBD
    kDriveInfoMediaPresent = 12,
    //! \brief TBD
    kDriveInfoMediaChange = 13,
    //! \brief TBD
    kDriveInfoSizeOfRawSerialNumberInBytes = 15,
    //! \brief TBD
    kDriveInfoRawSerialNumber = 16,

    //! \brief Selector for the number of non-sequential sector maps the drive uses.
    //!
    //! The parameter is a single uint32_t value that is the count of NSS maps for
    //! the given drive. DriveGetInfo() with this selector will just return the current
    //! count of maps. The array of maps is shared between all data-type drives.
    //! DriveSetInfo() allows you to change the number
    //! of maps to the value passed in. All previous maps will be
    //! flushed immediately and memory for the maps reallocated.
    //!
    //! \retval SUCCESS
    //! \retval ERROR_DDI_NAND_DATA_DRIVE_CANT_ALLOCATE_USECTORS_MAPS
    //!
    //! \note This selector only applies to data drives. System drives will return an error.
    kDriveInfoNSSMCount = 19,
    
    //! \brief Sector size in bytes that the underlying media has given this drive. 
    //!
    //! The data for this selector is a single uint32_t value that is read-only.
    //!
    //! Use the native sector size when working with DriveReadSector(), DriveWriteSector(),
    //! MediaRead(), and MediaWrite().
    kDriveInfoNativeSectorSizeInBytes = 20,
    
    //! \brief Number of native sectors consumed by this drive.
    //!
    //! The data for this selector is a single uint32_t value that is read-only.
    kDriveInfoSizeInNativeSectors = 21,
    
    //! \brief Driver-specific reference value.
    kDriveInfoOpaqueDriverData = 22,
    
    //! \brief Offset to beginning of this partition from the first sector of its parent drive.
    kDriveInfoSectorOffsetInParent = 23
};


// Data drive ID
#define    DATA_DRIVE_ID_INTERNAL        0
#define    DATA_DRIVE_ID_EXTERNAL        1

//! \brief Logical Drive Types include data drives, hidden data drives, and system drives.
//! \todo [PUBS] Add definition(s)...Medium
typedef enum {
    //! \brief TBD
    kDriveTypeData = 0,
    //! \brief TBD
    kDriveTypeSystem = 1,
    //! \brief TBD
    kDriveTypeHidden = 2,
    //! \brief TBD
    kDriveTypeUnknown = 3
} LogicalDriveType_t;

//! \brief TBD
//! \todo [PUBS] Add definition(s)...Medium
typedef struct {
    //! \brief TBD - In reference to the entire system
    uint32_t u32DriveNumber;
    //! \brief TBD
    LogicalDriveType_t Type;
    //! \brief TBD
    uint32_t u32Tag;
    //! \brief TBD
    uint64_t u64SizeInBytes;
    //! \brief TBD
    bool bRequired;
} MediaAllocationTableEntry_t;

//! \brief TBD
//! \todo [PUBS] Add definition(s)...Medium
typedef struct {
    //! \brief TBD
    uint32_t u32NumEntries;
    //! \brief TBD
    MediaAllocationTableEntry_t Entry[MAX_MEDIA_TABLE_ENTRIES];
} MediaAllocationTable_t;


//! \brief TBD
//! \todo [PUBS] Add definition(s)...Medium
typedef union {
    struct {
        //! \brief TBD
        uint8_t MinorL;
        //! \brief TBD
        uint8_t MinorH;
        //! \brief TBD
        uint8_t MiddleL;
        //! \brief TBD
        uint8_t MiddleH;
        //! \brief TBD
        uint8_t MajorL;
        //! \brief TBD
        uint8_t MajorH;
    } partialVersion;

    //! \brief TBD
    uint64_t   Version;
} SystemVersion_t;

//! Possible states for a logical drive.
typedef enum {
    kDriveNotPresent,
    kDriveUninitialized,
    kDriveFailedInitialization,
    kDriveReady
} DriveState_t;

//! An opaque type for a drive iterator.
typedef struct OpaqueDriveIterator * DriveIterator_t;

///////////////////////////////////////////////////////////////////////////////
// External references
///////////////////////////////////////////////////////////////////////////////

extern bool                 g_bFrameworkExternalDriveOrFsInit;
extern InitializationState_t g_eFrameworkExternalMediaInit;
extern const int g_MinDataDriveSize;
extern const int g_MinDataDriveSize;

#define IsExternalDriveInit()           false
#define IsExternalMediaPresentAndInit() false
#define IsExternalMediaInitPending()    false

///////////////////////////////////////////////////////////////////////////////
// Prototypes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////////
//! \brief      Initializes the logical data drive on the selected device.
//!
//! \fntype     Non-Reentrant
//!
//! Determines the sector location of the logical data drive on the selected
//! device. Reads the media's master boot record (MBR) from sector 0, and
//! saves the starting sector for partition 0, which is the data drive.
//!
//! \param[in]  driveNumber     Logical Drive Number
//!
//! \retval SUCCESS     Initialization completed.
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
//! \retval ERROR_OS_FILESYSTEM_FILESYSTEM_NOT_FOUND
//! \retval ERROR_DDI_MEDIABUFMGR_ALLOC_FAILED 
//! \retval Error code from DriveReadSector
//! \retval ERROR_OS_FILESYSTEM_MAX_DEVICES_EXCEEDED
//! \retval ERROR_ROM_ATA_nnn
//!
//! \note   This function blocks until the initialization is completed.
//! \todo [PUBS] Revise documentation to be valid for all selected device variations.
////////////////////////////////////////////////////////////////////////////////
RtStatus_t FSDataDriveInit(DriveTag_t tag);

unsigned MediaGetCount(void);
RtStatus_t MediaGetInfoSize(unsigned mediaNumber, uint32_t selector, uint32_t * propertySize);
RtStatus_t MediaSetInfo(unsigned mediaNumber, uint32_t selector, const void * value);

///////////////////////////////////////////////////////////////////////////////
//! \brief TBD
//!
//! \fntype Function
//!
//! \param[in] u32LogMediaNumber Logical media number
//!
//! \return Status of the call.
//! \retval TBD
//!
//! \todo [PUBS] Add definition(s)...High
//!
//! \internal
//! \see To view the function definition, see ddi_ldl_init.c.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaInit(uint32_t u32LogMediaNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief TBD
//!
//! \fntype Function
//!
//! \param[in] u32LogMediaNumber Logical media number
//! \param[in] pMediaTable       Pointer to Media Table structure
//!
//! \return Status of the call.
//! \retval TBD
//!
//! \todo [PUBS] Add definition(s)...High
//!
//! \internal
//! \see To view the function definition, see ddi_ldl_init.c.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaAllocate(uint32_t u32LogMediaNumber, MediaAllocationTable_t * pMediaTable);

///////////////////////////////////////////////////////////////////////////////
//! \brief TBD
//!
//! \fntype Function
//!
//! \param[in] u32LogMediaNumber Logical media number
//!
//! \return Status of the call.
//! \retval TBD
//!
//! \todo [PUBS] Add definition(s)...High
//!
//! \internal
//! \see To view the function definition, see ddi_ldl_util.c.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaDiscoverAllocation(uint32_t u32LogMediaNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief TBD
//!
//! \fntype Function
//!
//! \param[in] u32LogMediaNumber   Logical media number
//! \param[in] pMediaTable         Media table to populate
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
//!
//! \todo [PUBS] Add definition(s)...High
//!
//! \internal
//! \see To view the function definition, see ddi_ldl_util.c.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaGetMediaTable(uint32_t u32LogMediaNumber, MediaAllocationTable_t ** pMediaTable);

///////////////////////////////////////////////////////////////////////////////
//! \brief For the requested logical media number, get the info Type requested into *pInfo.
//!        Type must be one of those supported by the media driver
//!        as defined for example in NANDMediaGetInfo and MmcMediaGetInfo.
//!
//! \fntype Function
//!
//! \param[in] u32LogMediaNumber Logical media number
//! \param[in] Type              Logical media type
//! \param[in] pInfo             Receives media information
//!
//! \return Status of the call.
//! \retval TBD
//!
//! \todo [PUBS] Add definition(s)...High
//!
//! \internal
//! \see To view the function definition, see ddi_ldl_util.c.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaGetInfo(uint32_t u32LogMediaNumber, uint32_t Type, void * pInfo);

///////////////////////////////////////////////////////////////////////////////
//! \brief Erase all allowed portions of the media except hidden areas if requested.
//!
//! \fntype Function
//!
//! \param[in] u32LogMediaNumber Logical drive number
//! \param[in] u32MagicNumber    TBD
//! \param[in] u8NoEraseHidden   Flag to indicate hidden data drive should
//!                              not be erased.
//!
//! \return Status of the call.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
//! \reval  Others status codes from media specific Erase API
//!
//! \note Globals read: g_wNumMedia, g_Media for Erase API and media descriptor.                           
//!
//! \todo [PUBS] Add definition(s)...High
//!
//! \internal
//! \see To view the function definition, see ddi_ldl_write.c.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaErase(uint32_t u32LogMediaNumber, uint32_t u32MagicNumber, uint8_t u8NoEraseHidden);

////////////////////////////////////////////////////////////////////////////////
//! \brief If the media number is valid and was init, calls media's shutdown API.
//!
//! \param[in] wLogMediaNumber     Logical Media Number such as that of NAND or MMC
//!
//! \return Status of call RtStatus_t
//! \retval SUCCESS If no error has occurred.
//! \retval Status code from media's shutdown API. 
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER.
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED.
//!
//! \note  Globals read: g_Media for media init bool, media's descriptor & shutdown API
//! \see To view the function definition, see ddi_ldl_write.c
////////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaShutdown(uint32_t u32LogMediaNumber);

////////////////////////////////////////////////////////////////////////////////
//! \brief If the media number is valid and was init, calls media's flush drives API.
//!
//! \param[in] wLogMediaNumber     Logical Media Number such as that of NAND or MMC
//!
//! \return Status of call RtStatus_t
//! \retval SUCCESS If no error has occurred.
//! \retval Status code from media's flush drives API. 
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER.
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED.
//!
//! \note  Globals read: g_Media for media init bool, media's descriptor & flush drives API
//! \see To view the function definition, see ddi_ldl_util.c
////////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaFlushDrives(uint32_t u32LogMediaNumber);

///////////////////////////////////////////////////////////////////////////////
//! \brief LDL API to set bootable firmware to primary or secondary firmware.
//!
//! \fntype Function
//!
//! \param[in] u32LogMediaNumber Logical drive number
//! \param[in] u32DriveTag       Drive tag, can be either DRIVE_TAG_BOOTMANAGER_S
//!                              or DRIVE_TAG_BOOTMANAGER2_S
//!
//! \return Status of the call.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LMEDIA_INVALID_MEDIA_NUMBER
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
//! \reval  Others status codes from media specific Erase API
//!
//!
//! \internal
//! \see To view the function definition, see ddi_ldl_util.c.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t MediaSetBootDrive(uint32_t u32LogMediaNumber, DriveTag_t u32DriveTag);

unsigned DriveGetCount(void);
RtStatus_t DriveCreateIterator(DriveIterator_t * iter);
RtStatus_t DriveIteratorNext(DriveIterator_t iter, DriveTag_t * tag);
void DriveIteratorDispose(DriveIterator_t iter);
DriveState_t DriveGetState(DriveTag_t tag);
RtStatus_t DriveInitAll(void);
RtStatus_t DriveGetInfoSize(DriveTag_t tag, uint32_t selector, uint32_t * propertySize);

///////////////////////////////////////////////////////////////////////////////
//! \brief Initializes the specified drive.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//!
//! \return Status of the call.
//! \retval TBD
//!
///////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveInit(DriveTag_t tag);

///////////////////////////////////////////////////////////////////////////////
//! \brief For the requested logical drive, get the info Type into *pInfo.
//!
//! The Type must be supported by the media driver implementation such as  
//! NANDDataDriveGetInfo or ddi_mmc_DataDriveGetInfo.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] Type              Type of information to write to *pInfo
//! \param[out] pInfo            Buffer to fill with requested information
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveGetInfo(DriveTag_t tag, uint32_t Type, void * pInfo);

///////////////////////////////////////////////////////////////////////////////
//! \brief For the requested logical drive, set the *pInfo of Type specified. 
//!
//! Type must be supported by the media driver implementation such as  
//! NANDDataDriveSetInfo or ddi_mmc_DataDriveSetInfo.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] Type              Type of information to set
//! \param[in] pInfo             Buffer to copy the information from
//!
//! \return Status of the call.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_INFO_TYPE
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
//!
//! \todo [PUBS] Add definition(s)...High
//!
//! \internal
//! \see To view the function definition, see ddi_ldl_util.c.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveSetInfo(DriveTag_t tag, uint32_t Type, const void * pInfo);

///////////////////////////////////////////////////////////////////////////////
//! \brief Read a sector from the indicated drive.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] u32SectorNumber    Sector to read; 0-based.
//! \param[in] pSectorData        Pointer to buffer to fill with sector data.
//!
//! \return Status of the call.
///////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveReadSector(DriveTag_t tag, uint32_t u32SectorNumber, SECTOR_BUFFER * pSectorData);

///////////////////////////////////////////////////////////////////////////////
//! \brief Virtual Memory Interface entry point for loading a sector to RAM.
//!
//! NOTHING other than the VMI component is allowed to call this function. The
//! code path for this function is guaranteed to not require paging.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] u32SectorNumber    Sector to read; 0-based.
//! \param[in] pSectorData        Pointer to buffer to fill with sector data.
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER
//! \retval ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED
///////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveReadSectorForVMI(DriveTag_t tag, uint32_t u32SectorNumber, SECTOR_BUFFER * pSectorData);

///////////////////////////////////////////////////////////////////////////////
//! \brief Writes a sector of a logical drive.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//! \param[in] u32SectorNumber   Sector to write; 0-based.
//! \param[in] pSectorData       Pointer to buffer of sector data to write.
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER
//! \retval ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED
//! \retval Others possible from drive type's WriteSector API
///////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveWriteSector(DriveTag_t tag, uint32_t u32SectorNumber, const SECTOR_BUFFER * pSectorData);

///////////////////////////////////////////////////////////////////////////////
//! \brief Erase the logical drive if the drive num is valid and already init.
//!
//! \param[in] u32LogDriveNumber Logical drive number
//! \param[in] u32MagicNumber    Currently unused.
//!
//! \return Status of the call.
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER
//! \retval ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED
//! \retval Others possible from drive type's erase API
///////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveErase(DriveTag_t tag, uint32_t u32MagicNumber);

////////////////////////////////////////////////////////////////////////////////
//! \brief Flush the logical drive number's contents from RAM to physical media.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//!
//! \retval SUCCESS 
//! \retval ERROR_DDI_LDL_LDRIVE_INVALID_DRIVE_NUMBER 
//! \retval ERROR_DDI_LDL_LDRIVE_NOT_INITIALIZED         NAND: this or above.
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED   Possible for SD or MMC. 
//! \retval MMC_DATA_DRIVE_ERROR_WRITE_SECTOR_FAIL       Possible for SD or MMC.
//! \retval ERROR_DDI_LDL_LDRIVE_HARDWARE_FAILURE        Possible for SD or MMC.
////////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveFlush(DriveTag_t tag);

////////////////////////////////////////////////////////////////////////////////
//! \brief DriveFlush and if allowed shutdown the logical data drive.
//!
//! \param[in] tag Unique tag for the drive to operate on.
//!
//! \return RtStatus or an error the drive's flush or shutdown API.
//! \retval SUCCESS
//! \retval ERROR_DDI_LDL_LMEDIA_MEDIA_NOT_INITIALIZED
////////////////////////////////////////////////////////////////////////////////
RtStatus_t DriveShutdown(DriveTag_t tag);

void ddi_ldl_ResetCounter(void);
void ddi_ldl_DecrementCounter(uint32_t decrement_value);
int32_t ddi_ldl_GetCounter(void);
void ddi_ldl_SetCounterResetValue(int32_t NewResetValue);
void ddi_ldl_InitMediaCounter(void (*pFuncPointer)());

#ifdef __cplusplus
} // extern "C"

//! \brief Convenient template form of DriveGetInfo().
template <typename T> inline T DriveGetInfoTyped(DriveTag_t drive, uint32_t propertyName)
{
    T value;
    DriveGetInfo(drive, propertyName, (void *)&value);
    return value;
}

//! \brief Convenient template form of DriveGetInfo().
template <typename T> inline T DriveGetInfoTyped(DriveTag_t drive, uint32_t propertyName, RtStatus_t & status)
{
    T value;
    status = DriveGetInfo(drive, propertyName, (void *)&value);
    return value;
}

//! \brief Convenient template form of DriveSetInfo().
//! \note This function is named differently than DriveSetInfo() because the GHS C++ compiler
//!     wants to create an instatiation loop if they're named the same. Maybe this is because
//!     the base function uses C linkage?
template <typename T> inline RtStatus_t DriveSetInfoTyped(DriveTag_t drive, uint32_t propertyName, T value)
{
    return DriveSetInfo(drive, propertyName, (const void *)&value);
}

/*!
 * \brief Wrapper class for a logical drive.
 *
 * This class simply provides a simplified C++ interface to all of the LDL drive APIs. An instance
 * is associated with a particular drive tag via construction or assignment.
 */
class LogicalDrive
{
public:
    inline LogicalDrive(DriveTag_t tag) : m_tag(tag) {}
    inline LogicalDrive(const LogicalDrive & other) : m_tag(other.m_tag) {}
    
    inline LogicalDrive & operator = (const LogicalDrive & other) { m_tag = other.m_tag; return *this; }
    
    inline RtStatus_t init() { return DriveInit(m_tag); }
    inline RtStatus_t shutdown() { return DriveShutdown(m_tag); }
    
    inline DriveTag_t getTag() const { return m_tag; }
    
//    DriveStatus_t getStatus() const;
    
    inline RtStatus_t readSector(uint32_t sector, SECTOR_BUFFER * buffer) { return DriveReadSector(m_tag, sector, buffer); }
    inline RtStatus_t readSectorForVMI(uint32_t sector, SECTOR_BUFFER * buffer) { return DriveReadSectorForVMI(m_tag, sector, buffer); }
    inline RtStatus_t writeSector(uint32_t sector, const SECTOR_BUFFER * buffer) { return DriveWriteSector(m_tag, sector, buffer); }
    
    inline RtStatus_t flush() { return DriveFlush(m_tag); }
    
    inline RtStatus_t erase(uint32_t magicWord) { return DriveErase(m_tag, magicWord); }
    
    inline RtStatus_t getInfo(uint32_t selector, void * value) { return DriveGetInfo(m_tag, selector, value); }
    inline RtStatus_t setInfo(uint32_t selector, const void * value) { return DriveSetInfo(m_tag, selector, value); }

    template <typename T> inline T getInfo(uint32_t selector) const
    {
        T value;
        DriveGetInfo(m_tag, selector, (void *)&value);
        return value;
    }

    template <typename T> inline T getInfo(uint32_t selector, RtStatus_t & status) const
    {
        T value;
        status = DriveGetInfo(m_tag, selector, (void *)&value);
        return value;
    }
    
    template <typename T> inline RtStatus_t setInfo(uint32_t selector, T value)
    {
        return DriveSetInfo(m_tag, selector, (const void *)&value);
    }
    
    //! \name Accessors for common properties
    //@{
    inline uint32_t getSectorSize() const { return getInfo<uint32_t>(kDriveInfoSectorSizeInBytes); }
    inline uint32_t getSizeInSectors() const { return getInfo<uint32_t>(kDriveInfoSizeInSectors); }
    inline uint64_t getSizeInBytes() const { return getInfo<uint64_t>(kDriveInfoSizeInBytes); }
//    inline kDriveType_t getType() const { return getInfo<kDriveType_t>(kDriveInfoType); }
    inline bool isWriteProtected() const { return getInfo<bool>(kDriveInfoIsWriteProtected); }
    //@}
    
protected:
    DriveTag_t m_tag;   //!< The drive's unique tag value.
};

#endif // __cplusplus

#endif // _DDI_MEDIA_H
//! @}
