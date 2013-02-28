/**
 * \file  CxVolume.h
 * \brief volume
 */


#ifndef xLib_Filesystem_CxVolumeH
#define xLib_Filesystem_CxVolumeH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxVolume :
    private CxNonCopyable
    /// volume
{
public:
    enum ExType
        /// file system type
    {
        #if   xOS_ENV_WIN
            dtUnknown   = DRIVE_UNKNOWN,
            dtNoRoot    = DRIVE_NO_ROOT_DIR,
            dtRemovable = DRIVE_REMOVABLE,
            dtFixed     = DRIVE_FIXED,
            dtRemote    = DRIVE_REMOTE,
            dtCdRom     = DRIVE_CDROM,
            dtRam       = DRIVE_RAMDISK
        #elif xOS_ENV_UNIX
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

    explicit               CxVolume  (std::ctstring_t &csVolumePath);
        ///< constructor
    virtual               ~CxVolume  ();
        ///< destructor

    std::ctstring_t & volumePath() const xWARN_UNUSED_RV;
        ///< volume path
    ExType                 type      () const xWARN_UNUSED_RV;
        ///< drive type
    std::tstring_t         label     () const xWARN_UNUSED_RV;
        ///< get label
    bool_t                   isValid   () const xWARN_UNUSED_RV;
        ///< is valid path
    bool_t                   isReady   () const xWARN_UNUSED_RV;
        ///< is ready
    bool_t                   isEmpty   () const xWARN_UNUSED_RV;
        ///< is empty
    void                   mount     (std::ctstring_t &csDestPath) const;
        ///< mount
    void                   unMount   (cbool_t &cbIsForce) const;
        ///< unmount

    // static
    static void            space     (std::ctstring_t &csDirPath,
                                      ulonglong_t *pullAvailable,
                                      ulonglong_t *pullTotal,
                                      ulonglong_t *pullFree);
        ///< get free space
    static void            paths     (std::vec_tstring_t *pvsVolumePaths);
        ///< get paths

private:
    std::ctstring_t   _m_csVolumePath;  ///< volume path
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Filesystem_CxVolumeH
