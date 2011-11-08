/**
 * \file  CxVolume.cpp
 * \brief volume
 */


#include <xLib/Filesystem/CxVolume.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if defined(xOS_ENV_WIN)

#elif defined(xOS_ENV_UNIX)
    #include <sys/mount.h>
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/
BOOL
CxVolume::bIsReady(
    const std::string_t &csVolumePath
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumePath.empty(), FALSE);

    BOOL         bRes        = FALSE;
    std::string_t sVolumePath = CxPath::sSlashAppend(csVolumePath);
    std::string_t sOldDirPath;

#if defined(xOS_ENV_WIN)
    std::string_t sRes;
    UINT         uiOldErrorMode = 0;

    uiOldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    /*DEBUG*/// n/a

    sOldDirPath  = CxDir::sGetCurrent();
    /*DEBUG*/// n/a

    bRes = ::SetCurrentDirectory(sVolumePath.c_str());
    /*DEBUG*/// n/a

    CxDir::bSetCurrent(sOldDirPath);
    /*DEBUG*/// n/a

    ::SetErrorMode(uiOldErrorMode);
    /*DEBUG*/// n/a
#elif defined(xOS_ENV_UNIX)
    sOldDirPath  = CxDir::sGetCurrent();
    /*DEBUG*/// n/a

    INT iRes = chdir(sVolumePath.c_str());
    /*DEBUG*/// n/a
    bRes = xAS_BOOL(- 1 != iRes);

    CxDir::bSetCurrent(sOldDirPath);
    /*DEBUG*/// n/a
#endif

    return bRes;
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxVolume::bIsEmpty(
    const std::string_t &csVolumePath
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumePath.empty(), FALSE);

    return CxDir::bIsEmpty(csVolumePath, CxConst::xMASK_FILES_ALL);
}
//--------------------------------------------------------------------------
/*static*/
BOOL
CxVolume::bGetFreeSpace(
    const std::string_t &csDirPath,
    ULONGLONG          *pullAvailable,   ///< for unprivileged users
    ULONGLONG          *pullTotal,
    ULONGLONG          *pullFree
)
{
    /*DEBUG*/// csDirPath     - n/a
    /*DEBUG*/// pullAvailable - n/a
    /*DEBUG*/// pullTotal     - n/a
    /*DEBUG*/// pullFree      - n/a

    //--------------------------------------------------
    //if csDirPath parameter is empty, uses the root of the current volume
    std::string_t _sDirPath;

    if (true == csDirPath.empty()) {
        _sDirPath = CxPath::sGetExeDir();
    } else {
        _sDirPath = csDirPath;
    }

#if defined(xOS_ENV_WIN)
    ULARGE_INTEGER ullAvailable = {{0}};
    ULARGE_INTEGER ullTotal     = {{0}};
    ULARGE_INTEGER ullFree      = {{0}};

    BOOL bRes = ::GetDiskFreeSpaceEx(_sDirPath.c_str(), &ullAvailable, &ullTotal, &ullFree);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    xPTR_ASSIGN(pullAvailable, ullAvailable.QuadPart);
    xPTR_ASSIGN(pullTotal,     ullTotal.QuadPart);
    xPTR_ASSIGN(pullFree,      ullFree.QuadPart);
#elif defined(xOS_ENV_UNIX)
    #if defined(xOS_FREEBSD)
        #define xSTATVFS          statvfs
        #define xSTATVFS_F_FRSIZE f_frsize
    #else
        #define xSTATVFS          statfs64
        #define xSTATVFS_F_FRSIZE f_bsize
    #endif

    struct xSTATVFS stfInfo = {0};

    INT iRes = xSTATVFS(_sDirPath.c_str(), &stfInfo);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRes, _sDirPath, FALSE);

    xPTR_ASSIGN(pullAvailable, stfInfo.f_bavail * stfInfo.xSTATVFS_F_FRSIZE);
    xPTR_ASSIGN(pullTotal,     stfInfo.f_blocks * stfInfo.xSTATVFS_F_FRSIZE);
    xPTR_ASSIGN(pullFree,      stfInfo.f_bfree  * stfInfo.xSTATVFS_F_FRSIZE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bMount
/*static*/
BOOL
CxVolume::bMount(
    const std::string_t &csSourcePath,
    const std::string_t &csDestPath
)
{
    /*DEBUG*/xASSERT_RET(false == csSourcePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csDestPath.empty(),   FALSE);

#if defined(xOS_ENV_WIN)
    //TODO: bMount
    #if xTODO
        DWORD WNetAddConnection2(
          __in  LPNETRESOURCE lpNetResource,
          __in  LPCTSTR lpPassword,
          __in  LPCTSTR lpUsername,
          __in  DWORD dwFlags
        );
    #endif
#elif defined(xOS_ENV_UNIX)
    //TODO: bMount

    #if xTODO
        const std::string_t  csFilesytemType;
        const ULONG         culMountFlags = 0UL;
        const VOID         *pcvData       = NULL;

        INT iRes = mount(csSourcePath.c_str(), csDestPath.c_str(), csFilesytemType.c_str(), culMountFlags, pcvData);
        /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
    #endif

#endif

    return TRUE;
}
//--------------------------------------------------------------------------
//Defines, redefines, or deletes MS-DOS device names
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bDefineDosDevice(
    ULONG               ulFlags,
    const std::string_t &csDeviceName,
    const std::string_t &csTargetPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDeviceName.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csTargetPath.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::DefineDosDevice(ulFlags, csDeviceName.c_str(), csTargetPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Deletes a drive letter or mounted folder
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bDeleteVolumeMountPoint(
    const std::string_t &csVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::DeleteVolumeMountPoint(csVolumeMountPoint.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves the name of a volume on a computer
/*static*/
#if defined(xOS_ENV_WIN)
HANDLE
CxVolume::hFindFirstVolume(
    std::string_t *psVolumeName
)
{
    /*DEBUG*/xASSERT_RET(NULL != psVolumeName, INVALID_HANDLE_VALUE);

    HANDLE hRes = INVALID_HANDLE_VALUE;

    psVolumeName->clear();
    psVolumeName->resize(xPATH_MAX);

    hRes = ::FindFirstVolume(&(*psVolumeName)[0], psVolumeName->size());
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hRes, INVALID_HANDLE_VALUE);

    return hRes;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves the name of a mounted folder on the specified volume
/*static*/
#if defined(xOS_ENV_WIN)
HANDLE
CxVolume::hFindFirstVolumeMountPoint(
    const std::string_t &csRootPathName,
    std::string_t       *psVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(false == csRootPathName.empty(), INVALID_HANDLE_VALUE);
    /*DEBUG*/xASSERT_RET(NULL != psVolumeMountPoint,      INVALID_HANDLE_VALUE);

    HANDLE hRes = INVALID_HANDLE_VALUE;

    (*psVolumeMountPoint).clear();
    (*psVolumeMountPoint).resize(xPATH_MAX);

    hRes = ::FindFirstVolumeMountPoint(const_cast<LPTSTR>( csRootPathName.c_str() ), &(*psVolumeMountPoint).at(0), (*psVolumeMountPoint).size());
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hRes, INVALID_HANDLE_VALUE);

    return hRes;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Continues a volume search started by a call to the FindFirstVolume function
/*static*/
#if defined(xOS_ENV_WIN)
std::string_t
CxVolume::sFindNextVolume(
    HANDLE hFindVolume
)
{
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolume, std::string_t());

    BOOL        bRes                          = FALSE;
    const ULONG culBuffSize                   = MAX_PATH;
    char_t       szVolumeName[culBuffSize + 1] = {0};

    bRes = ::FindNextVolume(hFindVolume, &szVolumeName[0], culBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::string_t());

    return std::string_t(szVolumeName);
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Continues a mounted folder search started by a call to the FindFirstVolumeMountPoint function
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bFindNextVolumeMountPoint(
    HANDLE hFindVolumeMountPoint,
    std::string_t *psVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolumeMountPoint, FALSE);
    /*DEBUG*/xASSERT_RET(NULL != psVolumeMountPoint,                    FALSE);

    BOOL bRes = FALSE;

    psVolumeMountPoint->clear();
    psVolumeMountPoint->resize(xPATH_MAX);

    bRes = ::FindNextVolumeMountPoint(hFindVolumeMountPoint, &(*psVolumeMountPoint)[0], psVolumeMountPoint->size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Closes the specified volume search handle
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bFindVolumeClose(
    HANDLE hFindVolume
)
{
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolume, FALSE);

    BOOL bRes = FALSE;

    bRes = ::FindVolumeClose(hFindVolume);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Closes the specified mounted folder search handle
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bFindVolumeMountPointClose(
    HANDLE hFindVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolumeMountPoint, FALSE);

    BOOL bRes = FALSE;

    bRes = ::FindVolumeMountPointClose(hFindVolumeMountPoint);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//get type
/*static*/
#if defined(xOS_ENV_WIN)
CxVolume::EType
CxVolume::dtGetType(
    const std::string_t &csDrivePath
)
{
    /*DEBUG*/xASSERT_RET(false == csDrivePath.empty(), dtUnknown);

    return static_cast<EType>( ::GetDriveType(CxPath::sSlashAppend(csDrivePath).c_str()) );
    /*DEBUG*/// n/a
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//get logical drives
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bGetLogicalDrives(
    std::vector<std::string_t> *pvsDrives
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsDrives, FALSE);

    ULONG ulDrives = 0;        //bGetLogicalDrives +++++++++

    ulDrives = ::GetLogicalDrives();
    /*DEBUG*/xASSERT_RET(0 != ulDrives, FALSE);

    pvsDrives->clear();
    for (INT i = 0; i < 26; ++ i) {
        if (1 == ((ulDrives >> i) & 0x00000001)) {
            std::string_t sDrivePath;

            sDrivePath.push_back(static_cast<char_t>(65 + i));
            sDrivePath.append(CxConst::xDRIVE_SEP);

            pvsDrives->push_back(sDrivePath);
        }
    }

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//TODO:  bGetLogicalDrives (get logical drives by type)
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bGetLogicalDrives(
    std::vector<std::string_t> *pvsDrives,
    const EType           cdtDriveType
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsDrives, FALSE);

    std::vector<std::string_t> vsRes;

#if defined(xOS_ENV_WIN)
    ULONG                ulDrives = 0;

    ulDrives = ::GetLogicalDrives();
    /*DEBUG*/xASSERT_RET(0 != ulDrives, FALSE);

    for (INT i = 0; i < 26; ++ i) {
        if (1 == ((ulDrives >> i) & 0x00000001)) {
            std::string_t sDrivePath;

            sDrivePath.push_back(static_cast<char_t>(65 + i));
            sDrivePath.append(CxConst::xDRIVE_SEP);

            xCHECK_DO(cdtDriveType != dtGetType(sDrivePath), continue);

            vsRes.push_back(sDrivePath);
        }
    }
#elif defined(xOS_ENV_UNIX)
    BOOL bRes = CxDir::bFindDirs(xT("/"), CxConst::xMASK_ALL, FALSE, &vsRes);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    //TODO: filter by cdtDriveType
#endif

    //out
    std::swap(vsRes, *pvsDrives);

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Fills a buffer with strings that specify valid drives in the xTSYSTEM
/*static*/  //FIXME
#if defined(xOS_ENV_WIN)
std::string_t
CxVolume::sGetLogicalStrings() {
    std::string_t sRes;
    ULONG   ulRes = 0;

    ulRes = ::GetLogicalDriveStrings(0, NULL);
    /*DEBUG*/xASSERT_RET(0 != ulRes, std::string_t());

    sRes.resize(ulRes);

    ulRes = ::GetLogicalDriveStrings(sRes.size(), &sRes[0]);
    /*DEBUG*/xASSERT_RET(0 != ulRes, std::string_t());

    return sRes;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//get info
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bGetInfo(
    const std::string_t &csDrivePath,
    std::string_t       *psVolumeName,
    ULONG         *pulVolumeSerialNumber,
    ULONG         *pulMaximumComponentLength,
    ULONG         *pulFileSystemFlags,
    std::string_t       *psFileSystemName
)
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
        (*psVolumeName).resize(xPATH_MAX + 1);
    }

    if (NULL != psFileSystemName) {
        (*psFileSystemName).clear();
        (*psFileSystemName).resize(xPATH_MAX + 1);
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
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves a volume GUID path for the volume that is associated with the specified volume mount point (drive letter, volume GUID path, or mounted folder
/*static*/
#if defined(xOS_ENV_WIN)
std::string_t
CxVolume::sGetVolumeNameForVolumeMountPoint(
    const std::string_t &csVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), std::string_t());

    char_t szRes[50 + 1] = {0};
    BOOL  bRes          = FALSE;

    bRes = ::GetVolumeNameForVolumeMountPoint(CxPath::sSlashAppend(csVolumeMountPoint).c_str(), &szRes[0], xPATH_MAX);
    /*DEBUG*/////xASSERT_RET(FALSE != bRes, std::string_t());
    xCHECK_RET(FALSE == bRes, std::string_t());

    return std::string_t(szRes);
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves the volume mount point where the specified path is mounted
/*static*/
#if defined(xOS_ENV_WIN)
std::string_t
CxVolume::sGetVolumePathName(
    const std::string_t &csFileName
)
{
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), std::string_t());

    BOOL        bRes                               = FALSE;
    const ULONG culBuffSize                        = MAX_PATH;
    char_t        szVolumePathName[culBuffSize + 1] = {0};

    bRes = ::GetVolumePathName(csFileName.c_str(), &szVolumePathName[0], culBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::string_t());

    return std::string_t(szVolumePathName);
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves a list of drive letters and volume GUID paths for the specified volume
/*static*/
#if defined(xOS_ENV_WIN)
std::string_t
CxVolume::sGetVolumePathNamesForVolumeName(
    const std::string_t &csVolumeName
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumeName.empty(), std::string_t());

//    BOOL        bRes                           = FALSE;
    const ULONG culBuffSize                    = xPATH_MAX;
    std::string_t     sVolumePathNames(culBuffSize, 0);
    ULONG       ulReturnLength                 = 0;
//    ULONG       ulLastError                    = 0;

//    bRes        = ::GetVolumePathNamesForVolumeName(csVolumeName.c_str(), &sVolumePathNames[0], culBuffSize, &ulReturnLength);
//    ulLastError = ::GetLastError();
//    if (FALSE == bRes && ERROR_MORE_DATA == ulLastError) {
//        sVolumePathNames.resize(ulReturnLength);
//        bRes        = ::GetVolumePathNamesForVolumeName(csVolumeName.c_str(), &sVolumePathNames[0], culBuffSize, &ulReturnLength);
//        ulLastError = ::GetLastError();
//    }
//    /*DEBUG*/xASSERT_RET(FALSE != bRes && ulLastError != ERROR_MORE_DATA, std::string_t());

    return std::string_t(sVolumePathNames, ulReturnLength);
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves information about MS-DOS device names
/*static*/
#if defined(xOS_ENV_WIN)
std::string_t
CxVolume::sQueryDosDevice(
    const std::string_t &csDeviceName
)
{
    /*DEBUG*/xASSERT_RET(false == csDeviceName.empty(), std::string_t());

    ULONG       ulRes                     = 0;
    const ULONG culMax                    = MAX_PATH;
    char_t        szTargetPath[culMax + 1] = {0};
    ULONG       ulLastError               = 0;

    ulRes       = ::QueryDosDevice(csDeviceName.c_str(), &szTargetPath[0], culMax);
    ulLastError = ::GetLastError();
    /*DEBUG*/xASSERT_RET(0 != ulRes && ERROR_INSUFFICIENT_BUFFER != ulLastError, std::string_t());

    return std::string_t(szTargetPath, ulRes);
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Sets the label of a file xTSYSTEM volume
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bSetVolumeLabel(
    const std::string_t &csRootPathName,
    const std::string_t &cslpVolumeName
)
{
    /*DEBUG*/xASSERT_RET(false == csRootPathName.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == cslpVolumeName.empty(), FALSE);

    BOOL bRes = FALSE;

    bRes = ::SetVolumeLabel(csRootPathName.c_str(), cslpVolumeName.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Associates a volume with a drive letter or a directory on another volume
/*static*/
#if defined(xOS_ENV_WIN)
BOOL
CxVolume::bSetVolumeMountPoint(
    const std::string_t &csVolumeMountPoint,
    const std::string_t &csVolumeName
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(false == csVolumeName.empty(),       FALSE);

    BOOL bRes = FALSE;

    bRes = ::SetVolumeMountPoint(csVolumeMountPoint.c_str(), csVolumeName.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//TODO: bIsValidDriveLetter
#if defined(xOS_ENV_WIN)
/*static*/
BOOL
CxVolume::bIsValidDriveLetter(
    char_t szDriveLetter
)
{
    /*DEBUG*/// szDriveLetter - n/a

    return (xT('a') <= szDriveLetter && szDriveLetter <= xT('z'))  ||
           (xT('A') <= szDriveLetter && szDriveLetter <= xT('Z'));
}
#elif defined(xOS_ENV_UNIX)
    //TODO: xOS_ENV_UNIX
#endif
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxVolume::CxVolume() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxVolume::~CxVolume() {

}
//---------------------------------------------------------------------------
