/****************************************************************************
* Class name:  CxDrive
* Description: drive
* File name:   CxDrive.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:25:22
*
*****************************************************************************/


#ifndef xLib_Fso_CxDriveH
#define xLib_Fso_CxDriveH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxDrive : public CxNonCopyable {
	public:
		//���� ������
		typedef enum {
			dtUnknown   = DRIVE_UNKNOWN,		//The drive type cannot be determined
			dtNoRoot    = DRIVE_NO_ROOT_DIR,	//The root path is invalid
			dtRemovable = DRIVE_REMOVABLE,		//The drive has removable media
			dtFixed     = DRIVE_FIXED,			//The drive has fixed media
			dtRemote    = DRIVE_REMOTE,			//The drive is a remote (network) drive
			dtCdRom     = DRIVE_CDROM,			//The drive is a CD-ROM drive
			dtRam       = DRIVE_RAMDISK 		//The drive is a RAM disk
		} EType;	

		//static BOOL    bIsExists   (const tString &csDirPath);
	    static BOOL    bIsReady					        (const tString &csDrivePath); 
	    static BOOL    bIsEmpty					        (const tString &csDrivePath); 
		static BOOL    bGetFreeSpace			        (const tString &csDirPath, ULONGLONG *pullFreeBytesAvailable, ULONGLONG *pullTotalBytes, ULONGLONG *pullTotalFreeBytes); 
		static BOOL    bDefineDosDevice			        (ULONG ulFlags, const tString &csDeviceName, const tString &csTargetPath);	
		static BOOL    bDeleteVolumeMountPoint          (const tString &csVolumeMountPoint);
		static HANDLE  hFindFirstVolume                 (tString *psVolumeName);
		static HANDLE  hFindFirstVolumeMountPoint       (const tString &csRootPathName, tString *psVolumeMountPoint);
		static tString sFindNextVolume			        (HANDLE hFindVolume);
		static BOOL    bFindNextVolumeMountPoint        (HANDLE hFindVolumeMountPoint, tString *psVolumeMountPoint);
		static BOOL    bFindVolumeClose		            (HANDLE hFindVolume);
		static BOOL    bFindVolumeMountPointClose       (HANDLE hFindVolumeMountPoint);
		static EType   dtGetType				        (const tString &csDrivePath);
		static BOOL    bGetLogicalDrives                (std::vector<tString> *vecsDrives);
		static BOOL    bGetLogicalDrives                (std::vector<tString> *vecsDrives, EType dtDriveType);
		static tString sGetLogicalStrings               ();
		static BOOL    bGetInfo     			        (const tString &csDrivePath,
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
					   CxDrive					        ();
					  ~CxDrive					        ();
};
//---------------------------------------------------------------------------
#endif	//xLib_Fso_CxDriveH
