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
        static void           vSpace   (const std::tstring_t &csDirPath, ulonglong_t *pullAvailable, ulonglong_t *pullTotal, ulonglong_t *pullFree);
            ///< get free space
        static void           vMount   (const std::tstring_t &csSourcePath, const std::tstring_t &csDestPath);
            ///< mount
        static void           vUnMount (const std::tstring_t &csSourcePath, const bool &cbIsForce);
            ///< unmount
        static void           vPaths   (std::vec_tstring_t *pvsVolumePaths);
            ///< get paths
        static std::tstring_t sLabel   (const std::tstring_t &csVolumePath);
            ///< get label

        enum ExType
            /// filesystem type
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

        static ExType         dtType   (const std::tstring_t &csVolumePath);

    private:
                              CxVolume ();
            ///< constructor
        virtual              ~CxVolume ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxVolumeH
