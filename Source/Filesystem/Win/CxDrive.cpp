/****************************************************************************
* Class name:  CxDrive
* Description: drive
* File name:   CxDrive.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:25:22
*
*****************************************************************************/


#include <xLib/Filesystem/Win/CxDrive.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//--------------------------------------------------------------------------
//DONE:  bIsReady (���������� ���������� �����)
/*static*/
BOOL
CxDrive::bIsReady(const tString &csDrivePath) {
    /*DEBUG*/xASSERT_RET(false == csDrivePath.empty(), FALSE);

    BOOL    bRes           = FALSE;
    UINT    uiOldErrorMode = 0;
    tString sOldDirectory;

    uiOldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS /*SEM_NOOPENFILEERRORBOX*/);
    sOldDirectory  = CxDir::sGetCurrent();

    //-------------------------------------
    //�������� ����� �� ��������� ����
    ULONG ulRes = ::SetCurrentDirectory(CxPath::sSlashAppend(csDrivePath).c_str());
    if (0 == ulRes) {  // 0 - error
        bRes = FALSE;
    } else {
        bRes = TRUE;
    }

    CxDir::bSetCurrent(sOldDirectory);
    ::SetErrorMode(uiOldErrorMode);

    return bRes;
}
//--------------------------------------------------------------------------
//DONE:  bIsEmpty (���� �� ����)
/*static*/
BOOL
CxDrive::bIsEmpty(const tString &csDrivePath) {
    /*DEBUG*/xASSERT_RET(false == csDrivePath.empty(), FALSE);

    BOOL            bRes       = TRUE;
    HANDLE          hFile      = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA stFindData = {0};

    hFile = ::FindFirstFile((CxPath::sSlashAppend(csDrivePath) + CxConst::xMASK_FILES_ALL).c_str(), &stFindData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, TRUE);

    bRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, TRUE);

    return FALSE;
}
//--------------------------------------------------------------------------
//DONE:  bDefineDosDevice (Defines, redefines, or deletes MS-DOS device names.)
/*static*/
BOOL
CxDrive::bDefineDosDevice(ULONG ulFlags, const tString &csDeviceName, const tString &csTargetPath) {
    /*DEBUG*/xASSERT_RET(false == csDeviceName.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csTargetPath.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::DefineDosDevice(ulFlags, csDeviceName.c_str(), csTargetPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  bDeleteVolumeMountPoint (Deletes a drive letter or mounted folder.)
/*static*/
BOOL
CxDrive::bDeleteVolumeMountPoint(const tString &csVolumeMountPoint) {
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::DeleteVolumeMountPoint(csVolumeMountPoint.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  hFindFirstVolume (Retrieves the name of a volume on a computer)
/*static*/
HANDLE
CxDrive::hFindFirstVolume(tString *psVolumeName) {
    /*DEBUG*/xASSERT_RET(NULL != psVolumeName, INVALID_HANDLE_VALUE);

    HANDLE hRes = INVALID_HANDLE_VALUE;

    psVolumeName->clear();
    psVolumeName->resize(MAX_PATH);

    hRes = ::FindFirstVolume(&(*psVolumeName)[0], psVolumeName->size());
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hRes, INVALID_HANDLE_VALUE);

    return hRes;
}
//--------------------------------------------------------------------------
//DONE:  hFindFirstVolumeMountPoint (Retrieves the name of a mounted folder on the specified volume)
/*static*/
HANDLE
CxDrive::hFindFirstVolumeMountPoint(const tString &csRootPathName, tString *psVolumeMountPoint) {
    /*DEBUG*/xASSERT_RET(false == csRootPathName.empty(), INVALID_HANDLE_VALUE);
    /*DEBUG*/xASSERT_RET(NULL != psVolumeMountPoint,      INVALID_HANDLE_VALUE);

    HANDLE hRes = INVALID_HANDLE_VALUE;

    (*psVolumeMountPoint).clear();
    (*psVolumeMountPoint).resize(MAX_PATH);

    hRes = ::FindFirstVolumeMountPoint(const_cast<LPTSTR>( csRootPathName.c_str() ), &(*psVolumeMountPoint).at(0), (*psVolumeMountPoint).size());
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hRes, INVALID_HANDLE_VALUE);

    return hRes;
}
//--------------------------------------------------------------------------
//DONE:  sFindNextVolume (Continues a volume search started by a call to the FindFirstVolume function.)
/*static*/
tString
CxDrive::sFindNextVolume(HANDLE hFindVolume) {
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolume, tString());

    BOOL        bRes                          = FALSE;
    const ULONG culBuffSize                   = MAX_PATH;
    TCHAR       szVolumeName[culBuffSize + 1] = {0};

    bRes = ::FindNextVolume(hFindVolume, &szVolumeName[0], culBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, tString());

    return tString(szVolumeName);
}
//--------------------------------------------------------------------------
//DONE:  bFindNextVolumeMountPoint (Continues a mounted folder search started by a call to the FindFirstVolumeMountPoint function)
/*static*/
BOOL
CxDrive::bFindNextVolumeMountPoint(HANDLE hFindVolumeMountPoint, tString *psVolumeMountPoint) {
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolumeMountPoint, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != psVolumeMountPoint,                    FALSE);

    BOOL bRes = FALSE;

    psVolumeMountPoint->clear();
    psVolumeMountPoint->resize(MAX_PATH);

    bRes = ::FindNextVolumeMountPoint(hFindVolumeMountPoint, &(*psVolumeMountPoint)[0], psVolumeMountPoint->size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  bFindVolumeClose (Closes the specified volume search handle)
/*static*/
BOOL
CxDrive::bFindVolumeClose(HANDLE hFindVolume) {
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolume, FALSE);

    BOOL bRes = FALSE;

    bRes = ::FindVolumeClose(hFindVolume);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  bFindVolumeMountPointClose (Closes the specified mounted folder search handle)
/*static*/
BOOL
CxDrive::bFindVolumeMountPointClose(HANDLE hFindVolumeMountPoint) {
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolumeMountPoint, FALSE);

    BOOL bRes = FALSE;

    bRes = ::FindVolumeMountPointClose(hFindVolumeMountPoint);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  bGetFreeSpace (���������� � ������� �����)
/*static*/
BOOL
CxDrive::bGetFreeSpace(const tString &csDirPath, ULONGLONG *pullFreeBytesAvailable, ULONGLONG *pullTotalBytes, ULONGLONG *pullTotalFreeBytes) {
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), FALSE);

    BOOL bRes = FALSE;

    ULARGE_INTEGER ullFreeBytesAvailable = {{0}};
    ULARGE_INTEGER ullTotalBytes         = {{0}};
    ULARGE_INTEGER ullTotalFreeBytes     = {{0}};

    bRes = ::GetDiskFreeSpaceEx(csDirPath.c_str(), &ullFreeBytesAvailable, &ullTotalBytes, &ullTotalFreeBytes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    if (NULL != pullFreeBytesAvailable) {
        *pullFreeBytesAvailable = ullFreeBytesAvailable.QuadPart;
    }

    if (NULL != pullTotalBytes) {
        *pullTotalBytes         = ullTotalBytes.QuadPart;
    }

    if (NULL != pullTotalFreeBytes) {
        *pullTotalFreeBytes     = ullTotalFreeBytes.QuadPart;
    }

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  dtGetType (��� �����)
/*static*/
CxDrive::EType
CxDrive::dtGetType(const tString &csDrivePath) {
    /*DEBUG*/xASSERT_RET(false == csDrivePath.empty(), dtUnknown);

    return static_cast<EType>( ::GetDriveType(CxPath::sSlashAppend(csDrivePath).c_str()) );
    /*DEBUG*/// n/a
}
//--------------------------------------------------------------------------
//DONE:  bGetLogicalDrives (������ ���� ��������� ������)
/*static*/
BOOL
CxDrive::bGetLogicalDrives(std::vector<tString> *pvsDrives) {
    /*DEBUG*/xASSERT_RET(NULL != pvecsDrives, FALSE);

    ULONG ulDrives = 0;        //bGetLogicalDrives +++++++++

    ulDrives = ::GetLogicalDrives();
    /*DEBUG*/xASSERT_RET(0 != ulDrives, FALSE);

    pvsDrives->clear();
    for (INT i = 0; i < 26; ++ i) {
        if (1 == ((ulDrives >> i) & 0x00000001)) {
            tString sDrivePath;

            sDrivePath.push_back(static_cast<TCHAR>(65 + i));
            sDrivePath.append(CxConst::xDRIVE_SEP);

            pvsDrives->push_back(sDrivePath);
        }
    }

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO:  bGetLogicalDrives (������ ���� ��������� ������ �� ����)
/*static*/
BOOL
CxDrive::bGetLogicalDrives(
    std::vector<tString> *pvsDrives,
    const EType           cdtDriveType
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsDrives, FALSE);

    BOOL                 bRes = FALSE;
    std::vector<tString> vsRes;

#if defined(xOS_WIN)
    ULONG                ulDrives = 0;

    ulDrives = ::GetLogicalDrives();
    /*DEBUG*/xASSERT_RET(0 != ulDrives, FALSE);

    for (INT i = 0; i < 26; ++ i) {
        if (1 == ((ulDrives >> i) & 0x00000001)) {
            tString sDrivePath;

            sDrivePath.push_back(static_cast<TCHAR>(65 + i));
            sDrivePath.append(CxConst::xDRIVE_SEP);

            xCHECK_DO(cdtDriveType != CxDrive::dtGetType(sDrivePath), continue);

            vsRes.push_back(sDrivePath);
        }
    }
#elif defined(xOS_LINUX)
    bRes = CxDir::bFindDirs(xT("/"), CxConst::xMASK_ALL, FALSE, &vsRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //TODO: filter by cdtDriveType
#endif

    //out
    std::swap(vsRes, *pvsDrives);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  sGetLogicalStrings (Fills a buffer with strings that specify valid drives in the _tsystem.)
/*static*/  //FIXME
tString
CxDrive::sGetLogicalStrings() {
    tString sRes;
    ULONG   ulRes = 0;

    ulRes = ::GetLogicalDriveStrings(0, NULL);
    /*DEBUG*/xASSERT_RET(0 != ulRes, tString());

    sRes.resize(ulRes);

    ulRes = ::GetLogicalDriveStrings(sRes.size(), &sRes[0]);
    /*DEBUG*/xASSERT_RET(0 != ulRes, tString());

    return sRes;
}
//--------------------------------------------------------------------------
//DONE:  bGetInfo (���������� � �����)
/*static*/
BOOL
CxDrive::bGetInfo(const tString &csDrivePath,
                       tString       *psVolumeName,
                       ULONG         *pulVolumeSerialNumber,
                       ULONG         *pulMaximumComponentLength,
                       ULONG         *pulFileSystemFlags,
                       tString       *psFileSystemName)
{
    /*DEBUG*/xASSERT_RET(false == csDrivePath.empty(), FALSE);
    /*DEBUG*/// psVolumeName              - n/a
    /*DEBUG*/// pulVolumeSerialNumber     - n/a
    /*DEBUG*/// pulMaximumComponentLength - n/a
    /*DEBUG*/// pulFileSystemFlags        - n/a
    /*DEBUG*/// psFileSystemName          - n/a

    BOOL bRes = FALSE;

    if (NULL != psVolumeName) {
        (*psVolumeName).clear();
        (*psVolumeName).resize(MAX_PATH + 1);
    }

    if (NULL != psFileSystemName) {
        (*psFileSystemName).clear();
        (*psFileSystemName).resize(MAX_PATH + 1);
    }

    //
    /*BOOL WINAPI GetVolumeInformationA(
     *                     LPCSTR,
     *                     LPSTR,
     *                     DWORD,
     *                     PDWORD,
     *                     PDWORD,
     *                     PDWORD,
     *                     LPSTR,
     *                     DWORD);
     */
    bRes = ::GetVolumeInformation(
                        CxPath::sSlashAppend(csDrivePath).c_str(),
                        (NULL == psVolumeName)     ? NULL :  &(*psVolumeName).at(0),
                        (NULL == psVolumeName)     ? 0    :   (*psVolumeName).size(),
                        pulVolumeSerialNumber,
                        pulMaximumComponentLength,
                        pulFileSystemFlags,
                        (NULL == psFileSystemName) ? NULL : &(*psFileSystemName).at(0),
                        (NULL == psFileSystemName) ? 0    :  (*psFileSystemName).size()
    );
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  sGetVolumeNameForVolumeMountPoint (Retrieves a volume GUID path for the volume that is associated with the specified volume mount point (drive letter, volume GUID path, or mounted folder)
/*static*/
tString
CxDrive::sGetVolumeNameForVolumeMountPoint(const tString &csVolumeMountPoint) {
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), tString());

    TCHAR szRes[50 + 1] = {0};
    BOOL  bRes          = FALSE;

    bRes = ::GetVolumeNameForVolumeMountPoint(CxPath::sSlashAppend(csVolumeMountPoint).c_str(), &szRes[0], MAX_PATH);
    /*DEBUG*/////xASSERT_RET(FALSE != bRes, tString());
    xCHECK_RET(FALSE == bRes, tString());

    return tString(szRes);
}
//--------------------------------------------------------------------------
//DONE:  sGetVolumePathName (Retrieves the volume mount point where the specified path is mounted.)
/*static*/
tString
CxDrive::sGetVolumePathName(const tString &csFileName) {
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), tString());

    BOOL        bRes                               = FALSE;
    const ULONG culBuffSize                        = MAX_PATH;
    TCHAR        szVolumePathName[culBuffSize + 1] = {0};

    bRes = ::GetVolumePathName(csFileName.c_str(), &szVolumePathName[0], culBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, tString());

    return tString(szVolumePathName);
}
//--------------------------------------------------------------------------
//DONE:  sGetVolumePathNamesForVolumeName (Retrieves a list of drive letters and volume GUID paths for the specified volume.)
/*static*/
tString
CxDrive::sGetVolumePathNamesForVolumeName(const tString &csVolumeName) {
    /*DEBUG*/xASSERT_RET(false == csVolumeName.empty(), tString());

//    BOOL        bRes                           = FALSE;
    const ULONG culBuffSize                    = MAX_PATH;
    tString     sVolumePathNames(culBuffSize, 0);
    ULONG       ulReturnLength                 = 0;
//    ULONG       ulLastError                    = 0;

//    bRes        = ::GetVolumePathNamesForVolumeName(csVolumeName.c_str(), &sVolumePathNames[0], culBuffSize, &ulReturnLength);
//    ulLastError = ::GetLastError();
//    if (FALSE == bRes && ERROR_MORE_DATA == ulLastError) {
//        sVolumePathNames.resize(ulReturnLength);
//        bRes        = ::GetVolumePathNamesForVolumeName(csVolumeName.c_str(), &sVolumePathNames[0], culBuffSize, &ulReturnLength);
//        ulLastError = ::GetLastError();
//    }
//    /*DEBUG*/xASSERT_RET(FALSE != bRes && ulLastError != ERROR_MORE_DATA, tString());

    return tString(sVolumePathNames, ulReturnLength);
}
//--------------------------------------------------------------------------
//DONE:  sQueryDosDevice (Retrieves information about MS-DOS device names)
/*static*/
tString
CxDrive::sQueryDosDevice(const tString &csDeviceName) {
    /*DEBUG*/xASSERT_RET(false == csDeviceName.empty(), tString());

    ULONG       ulRes                     = 0;
    const ULONG culMax                    = MAX_PATH;
    TCHAR        szTargetPath[culMax + 1] = {0};
    ULONG       ulLastError               = 0;

    ulRes       = ::QueryDosDevice(csDeviceName.c_str(), &szTargetPath[0], culMax);
    ulLastError = ::GetLastError();
    /*DEBUG*/xASSERT_RET(0 != ulRes && ERROR_INSUFFICIENT_BUFFER != ulLastError, tString());

    return tString(szTargetPath, ulRes);
}
//--------------------------------------------------------------------------
//DONE:  bSetVolumeLabel (Sets the label of a file _tsystem volume.)
/*static*/
BOOL
CxDrive::bSetVolumeLabel(const tString &csRootPathName, const tString &cslpVolumeName) {
    /*DEBUG*/xASSERT_RET(false == csRootPathName.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == cslpVolumeName.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::SetVolumeLabel(csRootPathName.c_str(), cslpVolumeName.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//DONE:  bSetVolumeMountPoint (Associates a volume with a drive letter or a directory on another volume.)
/*static*/
BOOL
CxDrive::bSetVolumeMountPoint(const tString &csVolumeMountPoint, const tString &csVolumeName) {
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csVolumeName.empty(),       FALSE);

    BOOL bRes = FALSE;

    bRes = ::SetVolumeMountPoint(csVolumeMountPoint.c_str(), csVolumeName.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: bIsValidDriveLetter ()
/*static*/
BOOL
CxDrive::bIsValidDriveLetter(TCHAR szDriveLetter) {
    /*DEBUG*/// szDriveLetter - n/a

    return (xT('a') <= szDriveLetter && szDriveLetter <= xT('z'))
            ||
           (xT('A') <= szDriveLetter && szDriveLetter <= xT('Z'));
}
//---------------------------------------------------------------------------



/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE:
CxDrive::CxDrive() {
    //code
}
//---------------------------------------------------------------------------
//DONE:
CxDrive::~CxDrive() {
    //code
}
//---------------------------------------------------------------------------
