/**
 * \file  CxVolume.h
 * \brief volume
 */


#pragma once

#ifndef xLib_CxVolumeH
#define xLib_CxVolumeH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxVolume :
    public CxNonCopyable
    /// volume
{
public:
    enum ExType
        /// file system type
    {
        #if xOS_ENV_WIN
            dtUnknown   = DRIVE_UNKNOWN,
            dtNoRoot    = DRIVE_NO_ROOT_DIR,
            dtRemovable = DRIVE_REMOVABLE,
            dtFixed     = DRIVE_FIXED,
            dtRemote    = DRIVE_REMOTE,
            dtCdRom     = DRIVE_CDROM,
            dtRam       = DRIVE_RAMDISK
        #else
            dtUnknown   = 0,
            dtNoRoot    = 1,
            dtRemovable = 2,
            dtFixed     = 3,
            dtRemote    = 4,
            dtCdRom     = 5,
            dtRam       = 6,
            dtOther     = 7    // TODO: CxVolume::dtGetType
        #endif
    };

    explicit          CxVolume(std::ctstring_t &volumePath);
        ///< constructor
    virtual          ~CxVolume() {}
        ///< destructor

    std::ctstring_t & volumePath() const xWARN_UNUSED_RV;
        ///< volume path
    ExType            type() const xWARN_UNUSED_RV;
        ///< drive type
    std::tstring_t    label() const xWARN_UNUSED_RV;
        ///< get label
    bool_t            isValid() const xWARN_UNUSED_RV;
        ///< is valid path
    bool_t            isReady() const xWARN_UNUSED_RV;
        ///< is ready
    bool_t            isEmpty() const xWARN_UNUSED_RV;
        ///< is empty
    void_t            mount(std::ctstring_t &destPath) const;
        ///< mount
    void_t            unMount(cbool_t &isForce) const;
        ///< unmount

    // static
    static void_t     space(std::ctstring_t &dirPath, ulonglong_t *available, ulonglong_t *total,
                          ulonglong_t *free);
        ///< get free space
    static void_t     paths(std::vec_tstring_t *volumePaths);
        ///< get paths

private:
    std::ctstring_t   _volumePath;  ///< volume path
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Filesystem/CxVolume.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxVolumeH
