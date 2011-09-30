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
        static BOOL         bIsReady                         (const std::tstring &csVolumePath);
        	///< is ready
        static BOOL         bIsEmpty                         (const std::tstring &csVolumePath);
        	///< is empty
        static BOOL         bGetFreeSpace                    (const std::tstring &csDirPath, ULONGLONG *pullAvailable, ULONGLONG *pullTotal, ULONGLONG *pullFree);
        	///< get free space
        static BOOL         bMount                           (const std::tstring &csSourcePath, const std::tstring &csDestPath);
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

        static BOOL         bDefineDosDevice                 (ULONG ulFlags, const std::tstring &csDeviceName, const std::tstring &csTargetPath);
        static BOOL         bDeleteVolumeMountPoint          (const std::tstring &csVolumeMountPoint);
        static HANDLE       hFindFirstVolume                 (std::tstring *psVolumeName);
        static HANDLE       hFindFirstVolumeMountPoint       (const std::tstring &csRootPathName, std::tstring *psVolumeMountPoint);
        static std::tstring sFindNextVolume                  (HANDLE hFindVolume);
        static BOOL         bFindNextVolumeMountPoint        (HANDLE hFindVolumeMountPoint, std::tstring *psVolumeMountPoint);
        static BOOL         bFindVolumeClose                 (HANDLE hFindVolume);
        static BOOL         bFindVolumeMountPointClose       (HANDLE hFindVolumeMountPoint);
        static EType        dtGetType                        (const std::tstring &csDrivePath);
        static BOOL         bGetLogicalDrives                (std::vector<std::tstring> *pvsDrives);
        static BOOL         bGetLogicalDrives                (std::vector<std::tstring> *pvsDrives, const EType cdtDriveType);
        static std::tstring sGetLogicalStrings               ();
        static BOOL         bGetInfo                         (const std::tstring &csDrivePath,
                                                              std::tstring       *psVolumeName,
                                                              ULONG              *pulVolumeSerialNumber,
                                                              ULONG              *pulMaximumComponentLength,
                                                              ULONG              *pulFileSystemFlags,
                                                              std::tstring       *psFileSystemName);
        static std::tstring sGetVolumeNameForVolumeMountPoint(const std::tstring &csVolumeMountPoint);
        static std::tstring sGetVolumePathName               (const std::tstring &csFileName);
        static std::tstring sGetVolumePathNamesForVolumeName (const std::tstring &csVolumeName);
        static std::tstring sQueryDosDevice                  (const std::tstring &csDeviceName);
        static BOOL         bSetVolumeLabel                  (const std::tstring &csRootPathName, const std::tstring &cslpVolumeName);
        static BOOL         bSetVolumeMountPoint             (const std::tstring &csVolumeMountPoint, const std::tstring &csVolumeName);
        static BOOL         bIsValidDriveLetter              (TCHAR szDriveLetter);
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
