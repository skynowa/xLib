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
        static bool           bIsValid (const std::tstring_t &csVolumePath);
            ///< is valid path
        static bool           bIsReady (const std::tstring_t &csVolumePath);
            ///< is ready
        static bool           bIsEmpty (const std::tstring_t &csVolumePath);
            ///< is empty
        static bool           bGetSpace(const std::tstring_t &csDirPath, ulonglong_t *pullAvailable, ulonglong_t *pullTotal, ulonglong_t *pullFree);
            ///< get free space
        static bool           bMount   (const std::tstring_t &csSourcePath, const std::tstring_t &csDestPath);
            ///< mount
        static bool           bUnMount (const std::tstring_t &csSourcePath, const bool cbIsForce);
            ///< unmount
        static bool           bGetPaths(std::vector<std::tstring_t> *pvsVolumePaths);
            ///< get paths
        static std::tstring_t sGetLabel(const std::tstring_t &csVolumePath);
            ///< get label
        static bool           bSetLabel(const std::tstring_t &csVolumePath, const std::tstring_t &csVolumeName);
            ///< set label

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

        static EType          dtGetType(const std::tstring_t &csVolumePath);
        static bool           bGetInfo (const std::tstring_t &csVolumePath,
                                        std::tstring_t       *psVolumeName,
                                        ulong_t              *pulVolumeSerialNumber,
                                        ulong_t              *pulMaximumComponentLength,
                                        ulong_t              *pulFileSystemFlags,
                                        std::tstring_t       *psFileSystemName);
    #endif

    private:
                              CxVolume ();
            ///< constructor
        virtual              ~CxVolume ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxVolumeH
