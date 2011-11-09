/**
 * \file  CxVolume.h
 * \brief volume
 */


#ifndef xLib_Filesystem_CxVolumeH
#define xLib_Filesystem_CxVolumeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxVolume :
    public CxNonCopyable
    /// volume
{
    public:
        static BOOL         bIsReady                         (const std::string_t &csVolumePath);
            ///< is ready
        static BOOL         bIsEmpty                         (const std::string_t &csVolumePath);
            ///< is empty
        static BOOL         bGetFreeSpace                    (const std::string_t &csDirPath, ULONGLONG *pullAvailable, ULONGLONG *pullTotal, ULONGLONG *pullFree);
            ///< get free space
        static BOOL         bMount                           (const std::string_t &csSourcePath, const std::string_t &csDestPath);
            ///< mount

    #if defined(xOS_ENV_WIN)
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

        static BOOL         bDefineDosDevice                 (ULONG ulFlags, const std::string_t &csDeviceName, const std::string_t &csTargetPath);
        static BOOL         bDeleteVolumeMountPoint          (const std::string_t &csVolumeMountPoint);
        static HANDLE       hFindFirstVolume                 (std::string_t *psVolumeName);
        static HANDLE       hFindFirstVolumeMountPoint       (const std::string_t &csRootPathName, std::string_t *psVolumeMountPoint);
        static std::string_t sFindNextVolume                  (HANDLE hFindVolume);
        static BOOL         bFindNextVolumeMountPoint        (HANDLE hFindVolumeMountPoint, std::string_t *psVolumeMountPoint);
        static BOOL         bFindVolumeClose                 (HANDLE hFindVolume);
        static BOOL         bFindVolumeMountPointClose       (HANDLE hFindVolumeMountPoint);
        static EType        dtGetType                        (const std::string_t &csDrivePath);
        static BOOL         bGetLogicalDrives                (std::vector<std::string_t> *pvsDrives);
        static BOOL         bGetLogicalDrives                (std::vector<std::string_t> *pvsDrives, const EType cdtDriveType);
        static std::string_t sGetLogicalStrings               ();
        static BOOL         bGetInfo                         (const std::string_t &csDrivePath,
                                                              std::string_t       *psVolumeName,
                                                              ULONG              *pulVolumeSerialNumber,
                                                              ULONG              *pulMaximumComponentLength,
                                                              ULONG              *pulFileSystemFlags,
                                                              std::string_t       *psFileSystemName);
        static std::string_t sGetVolumeNameForVolumeMountPoint(const std::string_t &csVolumeMountPoint);
        static std::string_t sGetVolumePathName               (const std::string_t &csFileName);
        static std::string_t sGetVolumePathNamesForVolumeName (const std::string_t &csVolumeName);
        static std::string_t sQueryDosDevice                  (const std::string_t &csDeviceName);
        static BOOL         bSetVolumeLabel                  (const std::string_t &csRootPathName, const std::string_t &cslpVolumeName);
        static BOOL         bSetVolumeMountPoint             (const std::string_t &csVolumeMountPoint, const std::string_t &csVolumeName);
        static BOOL         bIsValidDriveLetter              (char_t szDriveLetter);
    #elif defined(xOS_ENV_UNIX)

    #endif

    private:
                            CxVolume                         ();
            ///< constructor
        virtual            ~CxVolume                         ();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxVolumeH
