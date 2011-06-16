/****************************************************************************
* Class name:  CxDrive
* Description: drive
* File name:   CxDrive.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:25:22
*
*****************************************************************************/


#ifndef xLib_Filesystem_Win_CxDriveH
#define xLib_Filesystem_Win_CxDriveH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxDrive :
    public CxNonCopyable
{
    public:
        enum EType {
            dtUnknown   = DRIVE_UNKNOWN,
            dtNoRoot    = DRIVE_NO_ROOT_DIR,
            dtRemovable = DRIVE_REMOVABLE,
            dtFixed     = DRIVE_FIXED,
            dtRemote    = DRIVE_REMOTE,
            dtCdRom     = DRIVE_CDROM,
            dtRam       = DRIVE_RAMDISK
        };

        //static BOOL    bIsExists   (const tString &csDirPath);
        static BOOL    bIsReady                         (const tString &csDrivePath);
        static BOOL    bIsEmpty                         (const tString &csDrivePath);
        static BOOL    bGetFreeSpace                    (const tString &csDirPath, ULONGLONG *pullFreeBytesAvailable, ULONGLONG *pullTotalBytes, ULONGLONG *pullTotalFreeBytes);
        static BOOL    bDefineDosDevice                 (ULONG ulFlags, const tString &csDeviceName, const tString &csTargetPath);
        static BOOL    bDeleteVolumeMountPoint          (const tString &csVolumeMountPoint);
        static HANDLE  hFindFirstVolume                 (tString *psVolumeName);
        static HANDLE  hFindFirstVolumeMountPoint       (const tString &csRootPathName, tString *psVolumeMountPoint);
        static tString sFindNextVolume                  (HANDLE hFindVolume);
        static BOOL    bFindNextVolumeMountPoint        (HANDLE hFindVolumeMountPoint, tString *psVolumeMountPoint);
        static BOOL    bFindVolumeClose                 (HANDLE hFindVolume);
        static BOOL    bFindVolumeMountPointClose       (HANDLE hFindVolumeMountPoint);
        static EType   dtGetType                        (const tString &csDrivePath);
        static BOOL    bGetLogicalDrives                (std::vector<tString> *pvsDrives);
        static BOOL    bGetLogicalDrives                (std::vector<tString> *pvsDrives, const EType cdtDriveType);
        static tString sGetLogicalStrings               ();
        static BOOL    bGetInfo                         (const tString &csDrivePath,
                                                         tString       *psVolumeName,
                                                         ULONG         *pulVolumeSerialNumber,
                                                         ULONG         *pulMaximumComponentLength,
                                                         ULONG         *pulFileSystemFlags,
                                                         tString       *psFileSystemName);
        static tString sGetVolumeNameForVolumeMountPoint(const tString &csVolumeMountPoint);
        static tString sGetVolumePathName               (const tString &csFileName);
        static tString sGetVolumePathNamesForVolumeName (const tString &csVolumeName);
        static tString sQueryDosDevice                  (const tString &csDeviceName);
        static BOOL    bSetVolumeLabel                  (const tString &csRootPathName, const tString &cslpVolumeName);
        static BOOL    bSetVolumeMountPoint             (const tString &csVolumeMountPoint, const tString &csVolumeName);
        static BOOL    bIsValidDriveLetter              (TCHAR szDriveLetter);


    private:
                       CxDrive                          ();
        virtual       ~CxDrive                          ();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_Win_CxDriveH
