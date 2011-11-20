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
        static bool         bIsReady                         (const std::tstring &csVolumePath);
            ///< is ready
        static bool         bIsEmpty                         (const std::tstring &csVolumePath);
            ///< is empty
        static bool         bGetFreeSpace                    (const std::tstring &csDirPath, ULONGLONG *pullAvailable, ULONGLONG *pullTotal, ULONGLONG *pullFree);
            ///< get free space
        static bool         bMount                           (const std::tstring &csSourcePath, const std::tstring &csDestPath);
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

        static bool         bDefineDosDevice                 (ULONG ulFlags, const std::tstring &csDeviceName, const std::tstring &csTargetPath);
        static bool         bDeleteVolumeMountPoint          (const std::tstring &csVolumeMountPoint);
        static HANDLE       hFindFirstVolume                 (std::tstring *psVolumeName);
        static HANDLE       hFindFirstVolumeMountPoint       (const std::tstring &csRootPathName, std::tstring *psVolumeMountPoint);
        static std::tstring sFindNextVolume                  (HANDLE hFindVolume);
        static bool         bFindNextVolumeMountPoint        (HANDLE hFindVolumeMountPoint, std::tstring *psVolumeMountPoint);
        static bool         bFindVolumeClose                 (HANDLE hFindVolume);
        static bool         bFindVolumeMountPointClose       (HANDLE hFindVolumeMountPoint);
        static EType        dtGetType                        (const std::tstring &csDrivePath);
        static bool         bGetLogicalDrives                (std::vector<std::tstring> *pvsDrives);
        static bool         bGetLogicalDrives                (std::vector<std::tstring> *pvsDrives, const EType cdtDriveType);
        static std::tstring sGetLogicalStrings               ();
        static bool         bGetInfo                         (const std::tstring &csDrivePath,
                                                              std::tstring       *psVolumeName,
                                                              ULONG              *pulVolumeSerialNumber,
                                                              ULONG              *pulMaximumComponentLength,
                                                              ULONG              *pulFileSystemFlags,
                                                              std::tstring       *psFileSystemName);
        static std::tstring sGetVolumeNameForVolumeMountPoint(const std::tstring &csVolumeMountPoint);
        static std::tstring sGetVolumePathName               (const std::tstring &csFileName);
        static std::tstring sGetVolumePathNamesForVolumeName (const std::tstring &csVolumeName);
        static std::tstring sQueryDosDevice                  (const std::tstring &csDeviceName);
        static bool         bSetVolumeLabel                  (const std::tstring &csRootPathName, const std::tstring &cslpVolumeName);
        static bool         bSetVolumeMountPoint             (const std::tstring &csVolumeMountPoint, const std::tstring &csVolumeName);
        static bool         bIsValidDriveLetter              (tchar szDriveLetter);
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
