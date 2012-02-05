/**
 * \file  CxVolume.cpp
 * \brief volume
 */


#include <xLib/Filesystem/CxVolume.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if xOS_ENV_WIN
    #if !xCOMPILER_MINGW32
        #pragma comment(lib, "mpr.lib")
    #endif
#elif xOS_ENV_UNIX
    #include <sys/mount.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//--------------------------------------------------------------------------
/*static*/
bool
CxVolume::bIsReady(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumePath.empty(), false);

    bool           bRes        = false;
    std::tstring_t sVolumePath = CxPath::sSlashAppend(csVolumePath);
    std::tstring_t sOldDirPath;

#if xOS_ENV_WIN
    std::tstring_t sRes;
    UINT           uiOldErrorMode = 0U;

    uiOldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    /*DEBUG*/// n/a

    sOldDirPath  = CxDir::sGetCurrent();
    /*DEBUG*/// n/a

    bRes = !!::SetCurrentDirectory(sVolumePath.c_str());
    /*DEBUG*/// n/a

    (void)CxDir::bSetCurrent(sOldDirPath);

    (void)::SetErrorMode(uiOldErrorMode);
#elif xOS_ENV_UNIX
    sOldDirPath  = CxDir::sGetCurrent();
    /*DEBUG*/// n/a

    int iRes = ::chdir(sVolumePath.c_str());
    /*DEBUG*/// n/a
    bRes = (- 1 != iRes);

    (void)CxDir::bSetCurrent(sOldDirPath);
#endif

    return bRes;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxVolume::bIsEmpty(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumePath.empty(), false);

    return CxDir::bIsEmpty(csVolumePath, CxConst::xMASK_FILES_ALL);
}
//--------------------------------------------------------------------------
/*static*/
bool
CxVolume::bGetFreeSpace(
    const std::tstring_t &csDirPath,
    ulonglong_t          *pullAvailable,   ///< for unprivileged users
    ulonglong_t          *pullTotal,
    ulonglong_t          *pullFree
)
{
    /*DEBUG*/// csDirPath     - n/a
    /*DEBUG*/// pullAvailable - n/a
    /*DEBUG*/// pullTotal     - n/a
    /*DEBUG*/// pullFree      - n/a

    //--------------------------------------------------
    //if csDirPath parameter is empty, uses the root of the current volume
    std::tstring_t _sDirPath;

    if (true == csDirPath.empty()) {
        _sDirPath = CxPath::sGetExeDir();
    } else {
        _sDirPath = csDirPath;
    }

#if xOS_ENV_WIN
    ULARGE_INTEGER ullAvailable = {{0}};
    ULARGE_INTEGER ullTotal     = {{0}};
    ULARGE_INTEGER ullFree      = {{0}};

    BOOL blRes = ::GetDiskFreeSpaceEx(_sDirPath.c_str(), &ullAvailable, &ullTotal, &ullFree);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    xPTR_ASSIGN(pullAvailable, ullAvailable.QuadPart);
    xPTR_ASSIGN(pullTotal,     ullTotal.QuadPart);
    xPTR_ASSIGN(pullFree,      ullFree.QuadPart);
#elif xOS_ENV_UNIX
    #if xOS_FREEBSD
        #define xSTATVFS          statvfs
        #define xSTATVFS_F_FRSIZE f_frsize
    #else
        #define xSTATVFS          statfs64
        #define xSTATVFS_F_FRSIZE f_bsize
    #endif

    struct xSTATVFS stfInfo = {0};

    int iRes = ::xSTATVFS(_sDirPath.c_str(), &stfInfo);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRes, _sDirPath, false);

    xPTR_ASSIGN(pullAvailable, stfInfo.f_bavail * stfInfo.xSTATVFS_F_FRSIZE);
    xPTR_ASSIGN(pullTotal,     stfInfo.f_blocks * stfInfo.xSTATVFS_F_FRSIZE);
    xPTR_ASSIGN(pullFree,      stfInfo.f_bfree  * stfInfo.xSTATVFS_F_FRSIZE);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxVolume::bMount(
    const std::tstring_t &csSourcePath, ///< source path
    const std::tstring_t &csDestPath    ///< destination path
)
{
    /*DEBUG*/xASSERT_RET(false == csSourcePath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csDestPath.empty(),   false);

#if xOS_ENV_WIN
    NETRESOURCE nrNetResource = {0};

    nrNetResource.dwScope       = RESOURCE_GLOBALNET;
    nrNetResource.dwType        = RESOURCETYPE_DISK;
    nrNetResource.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
    nrNetResource.dwUsage       = RESOURCEUSAGE_CONTAINER;
    nrNetResource.lpLocalName   = const_cast<tchar_t *>( csDestPath.c_str() );
    nrNetResource.lpRemoteName  = const_cast<tchar_t *>( csSourcePath.c_str() );
    nrNetResource.lpComment     = NULL;
    nrNetResource.lpProvider    = NULL;

    DWORD dwRes = ::WNetAddConnection2(&nrNetResource, NULL, NULL, CONNECT_UPDATE_PROFILE);
    /*DEBUG*/xASSERT_RET(NO_ERROR == dwRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::mount(csSourcePath.c_str(), csDestPath.c_str(), NULL, MS_REMOUNT, NULL);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxVolume::bUnMount(
    const std::tstring_t &csSourcePath, ///< source path
    const bool            cbIsForce     ///< force unmount even if busy
)
{
    /*DEBUG*/xASSERT_RET(false == csSourcePath.empty(), false);
    /*DEBUG*/// cbIsForce - n/a

#if xOS_ENV_WIN
    DWORD dwRes = ::WNetCancelConnection2(csSourcePath.c_str(), CONNECT_UPDATE_PROFILE, cbIsForce);
    /*DEBUG*/xASSERT_RET(NO_ERROR == dwRes, false);
#elif xOS_ENV_UNIX
    #ifndef MNT_DETACH
        #define MNT_DETACH MNT_FORCE
    #endif

    const int ciFlag = cbIsForce ? MNT_FORCE : MNT_DETACH;

    int iRes = ::umount2(csSourcePath.c_str(), ciFlag);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//--------------------------------------------------------------------------
//Defines, redefines, or deletes MS-DOS device names
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bDefineDosDevice(
    ulong_t               ulFlags,
    const std::tstring_t &csDeviceName,
    const std::tstring_t &csTargetPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDeviceName.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csTargetPath.empty(), false);

    BOOL blRes = ::DefineDosDevice(ulFlags, csDeviceName.c_str(), csTargetPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Deletes a drive letter or mounted folder
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bDeleteVolumeMountPoint(
    const std::tstring_t &csVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), false);

    BOOL blRes = ::DeleteVolumeMountPoint(csVolumeMountPoint.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves the name of a volume on a computer
/*static*/
#if xOS_ENV_WIN
HANDLE
CxVolume::hFindFirstVolume(
    std::tstring_t *psVolumeName
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
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves the name of a mounted folder on the specified volume
/*static*/
#if xOS_ENV_WIN
HANDLE
CxVolume::hFindFirstVolumeMountPoint(
    const std::tstring_t &csRootPathName,
    std::tstring_t       *psVolumeMountPoint
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
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Continues a volume search started by a call to the FindFirstVolume function
/*static*/
#if xOS_ENV_WIN
std::tstring_t
CxVolume::sFindNextVolume(
    HANDLE hFindVolume
)
{
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolume, std::tstring_t());

    const ulong_t culBuffSize                   = MAX_PATH;
    tchar_t       szVolumeName[culBuffSize + 1] = {0};

    BOOL blRes = ::FindNextVolume(hFindVolume, &szVolumeName[0], culBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, std::tstring_t());

    return std::tstring_t(szVolumeName);
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Continues a mounted folder search started by a call to the FindFirstVolumeMountPoint function
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bFindNextVolumeMountPoint(
    HANDLE hFindVolumeMountPoint,
    std::tstring_t *psVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolumeMountPoint, false);
    /*DEBUG*/xASSERT_RET(NULL != psVolumeMountPoint,                    false);

    psVolumeMountPoint->clear();
    psVolumeMountPoint->resize(xPATH_MAX);

    BOOL blRes = ::FindNextVolumeMountPoint(hFindVolumeMountPoint, &(*psVolumeMountPoint)[0], psVolumeMountPoint->size());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Closes the specified volume search handle
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bFindVolumeClose(
    HANDLE hFindVolume
)
{
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolume, false);

    BOOL blRes = ::FindVolumeClose(hFindVolume);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Closes the specified mounted folder search handle
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bFindVolumeMountPointClose(
    HANDLE hFindVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hFindVolumeMountPoint, false);

    BOOL blRes = ::FindVolumeMountPointClose(hFindVolumeMountPoint);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//get type
/*static*/
#if xOS_ENV_WIN
CxVolume::EType
CxVolume::dtGetType(
    const std::tstring_t &csDrivePath
)
{
    /*DEBUG*/xASSERT_RET(false == csDrivePath.empty(), dtUnknown);

    return static_cast<EType>( ::GetDriveType(CxPath::sSlashAppend(csDrivePath).c_str()) );
    /*DEBUG*/// n/a
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//get logical drives
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bGetLogicalDrives(
    std::vector<std::tstring_t> *pvsDrives
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsDrives, false);

    ulong_t ulDrives = 0;        //bGetLogicalDrives +++++++++

    ulDrives = ::GetLogicalDrives();
    /*DEBUG*/xASSERT_RET(0 != ulDrives, false);

    pvsDrives->clear();
    for (int i = 0; i < 26; ++ i) {
        if (1 == ((ulDrives >> i) & 0x00000001)) {
            std::tstring_t sDrivePath;

            sDrivePath.push_back(static_cast<tchar_t>(65 + i));
            sDrivePath.append(CxConst::xDRIVE_SEP);

            pvsDrives->push_back(sDrivePath);
        }
    }

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//TODO:  bGetLogicalDrives (get logical drives by type)
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bGetLogicalDrives(
    std::vector<std::tstring_t> *pvsDrives,
    const EType           cdtDriveType
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsDrives, false);

    std::vector<std::tstring_t> vsRes;

#if xOS_ENV_WIN
    ulong_t                ulDrives = 0;

    ulDrives = ::GetLogicalDrives();
    /*DEBUG*/xASSERT_RET(0 != ulDrives, false);

    for (int i = 0; i < 26; ++ i) {
        if (1 == ((ulDrives >> i) & 0x00000001)) {
            std::tstring_t sDrivePath;

            sDrivePath.push_back(static_cast<tchar_t>(65 + i));
            sDrivePath.append(CxConst::xDRIVE_SEP);

            xCHECK_DO(cdtDriveType != dtGetType(sDrivePath), continue);

            vsRes.push_back(sDrivePath);
        }
    }
#elif xOS_ENV_UNIX
    bool bRes = CxDir::bFindDirs(xT("/"), CxConst::xMASK_ALL, false, &vsRes);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    //TODO: filter by cdtDriveType
#endif

    //out
    std::swap(vsRes, *pvsDrives);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Fills a buffer with strings that specify valid drives in the xTSYSTEM
/*static*/  //FIXME
#if xOS_ENV_WIN
std::tstring_t
CxVolume::sGetLogicalStrings() {
    std::tstring_t sRes;
    ulong_t   ulRes = 0;

    ulRes = ::GetLogicalDriveStrings(0, NULL);
    /*DEBUG*/xASSERT_RET(0 != ulRes, std::tstring_t());

    sRes.resize(ulRes);

    ulRes = ::GetLogicalDriveStrings(sRes.size(), &sRes[0]);
    /*DEBUG*/xASSERT_RET(0 != ulRes, std::tstring_t());

    return sRes;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//get info
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bGetInfo(
    const std::tstring_t &csDrivePath,
    std::tstring_t       *psVolumeName,
    ulong_t         *pulVolumeSerialNumber,
    ulong_t         *pulMaximumComponentLength,
    ulong_t         *pulFileSystemFlags,
    std::tstring_t       *psFileSystemName
)
{
    /*DEBUG*/xASSERT_RET(false == csDrivePath.empty(), false);
    /*DEBUG*/// psVolumeName              - n/a
    /*DEBUG*/// pulVolumeSerialNumber     - n/a
    /*DEBUG*/// pulMaximumComponentLength - n/a
    /*DEBUG*/// pulFileSystemFlags        - n/a
    /*DEBUG*/// psFileSystemName          - n/a

    if (NULL != psVolumeName) {
        (*psVolumeName).clear();
        (*psVolumeName).resize(xPATH_MAX + 1);
    }

    if (NULL != psFileSystemName) {
        (*psFileSystemName).clear();
        (*psFileSystemName).resize(xPATH_MAX + 1);
    }

    //
    /*bool WINAPI GetVolumeInformationA(
     *                     LPCSTR,
     *                     LPSTR,
     *                     DWORD,
     *                     PDWORD,
     *                     PDWORD,
     *                     PDWORD,
     *                     LPSTR,
     *                     DWORD);
     */
    BOOL blRes = ::GetVolumeInformation(
                        CxPath::sSlashAppend(csDrivePath).c_str(),
                        (NULL == psVolumeName)     ? NULL :  &(*psVolumeName).at(0),
                        (NULL == psVolumeName)     ? 0    :   (*psVolumeName).size(),
                        pulVolumeSerialNumber,
                        pulMaximumComponentLength,
                        pulFileSystemFlags,
                        (NULL == psFileSystemName) ? NULL : &(*psFileSystemName).at(0),
                        (NULL == psFileSystemName) ? 0    :  (*psFileSystemName).size()
    );
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves a volume GUID path for the volume that is associated with the specified volume mount point (drive letter, volume GUID path, or mounted folder
/*static*/
#if xOS_ENV_WIN
std::tstring_t
CxVolume::sGetVolumeNameForVolumeMountPoint(
    const std::tstring_t &csVolumeMountPoint
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), std::tstring_t());

    tchar_t szRes[50 + 1] = {0};

    BOOL blRes = ::GetVolumeNameForVolumeMountPoint(CxPath::sSlashAppend(csVolumeMountPoint).c_str(), &szRes[0], xPATH_MAX);
    /*DEBUG*/////xASSERT_RET(true == bRes, std::tstring_t());
    xCHECK_RET(FALSE == blRes, std::tstring_t());

    return std::tstring_t(szRes);
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves the volume mount point where the specified path is mounted
/*static*/
#if xOS_ENV_WIN
std::tstring_t
CxVolume::sGetVolumePathName(
    const std::tstring_t &csFileName
)
{
    /*DEBUG*/xASSERT_RET(false == csFileName.empty(), std::tstring_t());

    const ulong_t culBuffSize                        = MAX_PATH;
    tchar_t       szVolumePathName[culBuffSize + 1] = {0};

    BOOL blRes = ::GetVolumePathName(csFileName.c_str(), &szVolumePathName[0], culBuffSize);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, std::tstring_t());

    return std::tstring_t(szVolumePathName);
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves a list of drive letters and volume GUID paths for the specified volume
/*static*/
#if xOS_ENV_WIN
std::tstring_t
CxVolume::sGetVolumePathNamesForVolumeName(
    const std::tstring_t &csVolumeName
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumeName.empty(), std::tstring_t());

//    bool        bRes                           = false;
    const ulong_t culBuffSize                    = xPATH_MAX;
    std::tstring_t     sVolumePathNames(culBuffSize, 0);
    ulong_t       ulReturnLength                 = 0;
//    ulong_t       ulLastError                    = 0;

//    bRes        = ::GetVolumePathNamesForVolumeName(csVolumeName.c_str(), &sVolumePathNames[0], culBuffSize, &ulReturnLength);
//    ulLastError = ::GetLastError();
//    if (false == bRes && ERROR_MORE_DATA == ulLastError) {
//        sVolumePathNames.resize(ulReturnLength);
//        bRes        = ::GetVolumePathNamesForVolumeName(csVolumeName.c_str(), &sVolumePathNames[0], culBuffSize, &ulReturnLength);
//        ulLastError = ::GetLastError();
//    }
//    /*DEBUG*/xASSERT_RET(true == bRes && ulLastError != ERROR_MORE_DATA, std::tstring_t());

    return std::tstring_t(sVolumePathNames, ulReturnLength);
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Retrieves information about MS-DOS device names
/*static*/
#if xOS_ENV_WIN
std::tstring_t
CxVolume::sQueryDosDevice(
    const std::tstring_t &csDeviceName
)
{
    /*DEBUG*/xASSERT_RET(false == csDeviceName.empty(), std::tstring_t());

    ulong_t       ulRes                     = 0;
    const ulong_t culMax                    = MAX_PATH;
    tchar_t        szTargetPath[culMax + 1] = {0};
    ulong_t       ulLastError               = 0;

    ulRes       = ::QueryDosDevice(csDeviceName.c_str(), &szTargetPath[0], culMax);
    ulLastError = ::GetLastError();
    /*DEBUG*/xASSERT_RET(0 != ulRes && ERROR_INSUFFICIENT_BUFFER != ulLastError, std::tstring_t());

    return std::tstring_t(szTargetPath, ulRes);
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Sets the label of a file xTSYSTEM volume
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bSetVolumeLabel(
    const std::tstring_t &csRootPathName,
    const std::tstring_t &cslpVolumeName
)
{
    /*DEBUG*/xASSERT_RET(false == csRootPathName.empty(), false);
    /*DEBUG*/xASSERT_RET(false == cslpVolumeName.empty(), false);

    BOOL blRes = ::SetVolumeLabel(csRootPathName.c_str(), cslpVolumeName.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//Associates a volume with a drive letter or a directory on another volume
/*static*/
#if xOS_ENV_WIN
bool
CxVolume::bSetVolumeMountPoint(
    const std::tstring_t &csVolumeMountPoint,
    const std::tstring_t &csVolumeName
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumeMountPoint.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csVolumeName.empty(),       false);

    BOOL blRes = ::SetVolumeMountPoint(csVolumeMountPoint.c_str(), csVolumeName.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    return true;
}
#elif xOS_ENV_UNIX
    //TODO: xOS_ENV_UNIX
#endif
//--------------------------------------------------------------------------
//TODO: bIsValidDriveLetter
#if xOS_ENV_WIN
/*static*/
bool
CxVolume::bIsValidDriveLetter(
    tchar_t szDriveLetter
)
{
    /*DEBUG*/// szDriveLetter - n/a

    return (xT('a') <= szDriveLetter && szDriveLetter <= xT('z'))  ||
           (xT('A') <= szDriveLetter && szDriveLetter <= xT('Z'));
}
#elif xOS_ENV_UNIX
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

xNAMESPACE_END(NxLib)
