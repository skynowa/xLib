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
    public CxNonCopyable
    /// volume
{
    public:
        static bool         bIsReady                         (const std::tstring_t &csVolumePath);
            ///< is ready
        static bool         bIsEmpty                         (const std::tstring_t &csVolumePath);
            ///< is empty
        static bool         bGetFreeSpace                    (const std::tstring_t &csDirPath, ulonglong_t *pullAvailable, ulonglong_t *pullTotal, ulonglong_t *pullFree);
            ///< get free space
        static bool         bMount                           (const std::tstring_t &csSourcePath, const std::tstring_t &csDestPath);
            ///< mount

    #if xOS_ENV_WIN
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

        static bool         bDefineDosDevice                 (ulong_t ulFlags, const std::tstring_t &csDeviceName, const std::tstring_t &csTargetPath);
        static bool         bDeleteVolumeMountPoint          (const std::tstring_t &csVolumeMountPoint);
        static HANDLE       hFindFirstVolume                 (std::tstring_t *psVolumeName);
        static HANDLE       hFindFirstVolumeMountPoint       (const std::tstring_t &csRootPathName, std::tstring_t *psVolumeMountPoint);
        static std::tstring_t sFindNextVolume                  (HANDLE hFindVolume);
        static bool         bFindNextVolumeMountPoint        (HANDLE hFindVolumeMountPoint, std::tstring_t *psVolumeMountPoint);
        static bool         bFindVolumeClose                 (HANDLE hFindVolume);
        static bool         bFindVolumeMountPointClose       (HANDLE hFindVolumeMountPoint);
        static EType        dtGetType                        (const std::tstring_t &csDrivePath);
        static bool         bGetLogicalDrives                (std::vector<std::tstring_t> *pvsDrives);
        static bool         bGetLogicalDrives                (std::vector<std::tstring_t> *pvsDrives, const EType cdtDriveType);
        static std::tstring_t sGetLogicalStrings               ();
        static bool         bGetInfo                         (const std::tstring_t &csDrivePath,
                                                              std::tstring_t       *psVolumeName,
                                                              ulong_t              *pulVolumeSerialNumber,
                                                              ulong_t              *pulMaximumComponentLength,
                                                              ulong_t              *pulFileSystemFlags,
                                                              std::tstring_t       *psFileSystemName);
        static std::tstring_t sGetVolumeNameForVolumeMountPoint(const std::tstring_t &csVolumeMountPoint);
        static std::tstring_t sGetVolumePathName               (const std::tstring_t &csFileName);
        static std::tstring_t sGetVolumePathNamesForVolumeName (const std::tstring_t &csVolumeName);
        static std::tstring_t sQueryDosDevice                  (const std::tstring_t &csDeviceName);
        static bool         bSetVolumeLabel                  (const std::tstring_t &csRootPathName, const std::tstring_t &cslpVolumeName);
        static bool         bSetVolumeMountPoint             (const std::tstring_t &csVolumeMountPoint, const std::tstring_t &csVolumeName);
        static bool         bIsValidDriveLetter              (tchar_t szDriveLetter);
    #elif xOS_ENV_UNIX

    #endif

    private:
                            CxVolume                         ();
            ///< constructor
        virtual            ~CxVolume                         ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxVolumeH
