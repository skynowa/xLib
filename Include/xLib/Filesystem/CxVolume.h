/**
 * \file  CxVolume.h
 * \brief volume
 */


#ifndef xLib_Filesystem_CxVolumeH
#define xLib_Filesystem_CxVolumeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxVolume :
    private CxNonCopyable
    /// volume
{
    public:
        static bool  bIsReady             (const std::tstring_t &csVolumePath);
            ///< is ready
        static bool  bIsEmpty             (const std::tstring_t &csVolumePath);
            ///< is empty
        static bool  bGetFreeSpace        (const std::tstring_t &csDirPath, ulonglong_t *pullAvailable, ulonglong_t *pullTotal, ulonglong_t *pullFree);
            ///< get free space
        static bool  bMount               (const std::tstring_t &csSourcePath, const std::tstring_t &csDestPath);
            ///< mount
        static bool  bUnMount             (const std::tstring_t &csSourcePath, const bool cbIsForce);
            ///< unmount

    #if   xOS_ENV_WIN
        enum EType
            /// filesystem type
        {
            dtUnknown   = DRIVE_UNKNOWN,
            dtNoRoot    = DRIVE_NO_ROOT_DIR,
            dtRemovable = DRIVE_REMOVABLE,
            dtFixed     = DRIVE_FIXED,
            dtRemote    = DRIVE_REMOTE,
            dtCdRom     = DRIVE_CDROM,
            dtRam       = DRIVE_RAMDISK
        };

        static EType dtGetType          (const std::tstring_t &csDrivePath);
        static bool  bGetLogicalDrives  (std::vector<std::tstring_t> *pvsDrives);
        static bool  bIsValidDriveLetter(const tchar_t cchDriveLetter);
    #endif

    private:
                     CxVolume           ();
            ///< constructor
        virtual     ~CxVolume           ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxVolumeH
