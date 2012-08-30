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
    #include <sys/param.h>
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
CxVolume::bIsValid(
    const std::tstring_t &csVolumePath
)
{
    xDEBUG_VAR_NA(csVolumePath);

#if   xOS_ENV_WIN
    bool bRv = CxDir::bIsRoot(csVolumePath);
    xCHECK_RET(false == bRv, false);
#elif xOS_ENV_UNIX
    xCHECK_RET(true                  == csVolumePath.empty(), false);
    xCHECK_RET(CxConst::xSLASH.at(0) != csVolumePath.at(0),   false);
#endif

    return true;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxVolume::bIsReady(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumePath.empty(), false);

    bool           bRv        = false;
    std::tstring_t sVolumePath = CxPath::sSlashAppend(csVolumePath);
    std::tstring_t sOldDirPath;

#if xOS_ENV_WIN
    std::tstring_t sRv;
    UINT           uiOldErrorMode = 0U;

    uiOldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    /*DEBUG*/// n/a

    sOldDirPath  = CxDir::sGetCurrent();
    /*DEBUG*/// n/a

    bRv = !!::SetCurrentDirectory(sVolumePath.c_str());
    /*DEBUG*/// n/a

    (void)CxDir::bSetCurrent(sOldDirPath);

    (void)::SetErrorMode(uiOldErrorMode);
#elif xOS_ENV_UNIX
    sOldDirPath  = CxDir::sGetCurrent();
    /*DEBUG*/// n/a

    int iRv = ::chdir(sVolumePath.c_str());
    /*DEBUG*/// n/a
    bRv = (- 1 != iRv);

    (void)CxDir::bSetCurrent(sOldDirPath);
#endif

    return bRv;
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
CxVolume::bGetSpace(
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

    bool bRv = CxDir::bIsExists(_sDirPath);
    xCHECK_RET(false == bRv, false);

#if   xOS_ENV_WIN
    ULARGE_INTEGER ullAvailable = {{0}};
    ULARGE_INTEGER ullTotal     = {{0}};
    ULARGE_INTEGER ullFree      = {{0}};

    BOOL blRes = ::GetDiskFreeSpaceEx(_sDirPath.c_str(), &ullAvailable, &ullTotal, &ullFree);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    xPTR_ASSIGN(pullAvailable, ullAvailable.QuadPart);
    xPTR_ASSIGN(pullTotal,     ullTotal.QuadPart);
    xPTR_ASSIGN(pullFree,      ullFree.QuadPart);
#elif xOS_ENV_UNIX
    struct xSTATVFS stfInfo = {0};

    int iRv = ::xSTATVFS(_sDirPath.c_str(), &stfInfo);
    /*DEBUG*/xASSERT_MSG_RET(- 1 != iRv, _sDirPath, false);

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
    // TODO: CxVolume::bMount - is it correct?
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
    #if   xOS_LINUX
        int iRv = ::mount(csSourcePath.c_str(), csDestPath.c_str(), NULL, MS_REMOUNT, NULL);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, false);
    #elif xOS_FREEBSD
        int iRv = ::mount(csSourcePath.c_str(), csDestPath.c_str(), MNT_UPDATE, NULL);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, false);
    #endif
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
    // TODO: CxVolume::bUnMount - is it correct?
    DWORD dwRes = ::WNetCancelConnection2(csSourcePath.c_str(), CONNECT_UPDATE_PROFILE, cbIsForce);
    /*DEBUG*/xASSERT_RET(NO_ERROR == dwRes, false);
#elif xOS_ENV_UNIX
    #ifdef MNT_DETACH
        #define xMNT_DETACH MNT_DETACH
    #else
        #define xMNT_DETACH MNT_FORCE
    #endif

    const int ciFlag = cbIsForce ? MNT_FORCE : xMNT_DETACH;

    #if   xOS_LINUX
        int iRv = ::umount2(csSourcePath.c_str(), ciFlag);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, false);
    #elif xOS_FREEBSD
        int iRv = ::unmount(csSourcePath.c_str(), ciFlag);
        /*DEBUG*/xASSERT_RET(- 1 != iRv, false);
    #endif
#endif

    return true;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxVolume::bGetPaths(
    std::vector<std::tstring_t> *pvsVolumePaths
)
{
    /*DEBUG*/xASSERT_RET(NULL != pvsVolumePaths, false);

    std::vector<std::tstring_t> vsRes;

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    DWORD          ulRv = 0UL;

    ulRv = ::GetLogicalDriveStrings(0UL, NULL);
    /*DEBUG*/xASSERT_RET(0UL != ulRv, false);

    sRv.resize(ulRv);

    ulRv = ::GetLogicalDriveStrings(sRv.size(), &sRv.at(0));
    /*DEBUG*/xASSERT_RET(0UL != ulRv, false);

    for (const tchar_t *s = &sRv.at(0); 0 != *s; s += _tcslen(s) + sizeof(xT('\0'))) {
        vsRes.push_back(s);
    }
#elif xOS_ENV_UNIX
    struct _SMounts {
        std::tstring_t m_sDevice;
        std::tstring_t m_sDestination;
        std::tstring_t m_sFsType;
        std::tstring_t m_sOptions;
        int            m_iDump;
        int            m_iPass;
    };

    std::tifstream_t fsProcMounts(xT("/proc/mounts"));

    for ( ; !fsProcMounts.eof(); ) {
        _SMounts mntMounts;

        fsProcMounts >> mntMounts.m_sDevice  >> mntMounts.m_sDestination >> mntMounts.m_sFsType >>
                        mntMounts.m_sOptions >> mntMounts.m_iDump        >> mntMounts.m_iPass;
        xCHECK_DO(true == mntMounts.m_sDevice.empty(), continue);

        vsRes.push_back(mntMounts.m_sDestination);
    }
#endif

    std::swap(*pvsVolumePaths, vsRes);

    return true;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxVolume::sGetLabel(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumePath.empty(), std::tstring_t());

    std::tstring_t sRv;

    bool bRv = bIsReady(csVolumePath);
    xCHECK_RET(false == bRv, std::tstring_t());

#if   xOS_ENV_WIN
    tchar_t szVolumeName[MAX_PATH + 1] = {0};

    CxLastError::bReset();

    BOOL blRes = ::GetVolumeInformation(
                        CxPath::sSlashAppend(csVolumePath).c_str(),
                        &szVolumeName[0],
                        xARRAY_SIZE(szVolumeName),
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        0
    );
    /*DEBUG*/xASSERT_RET(FALSE != blRes && 0UL == CxLastError::ulGet(), std::tstring_t());

    sRv.assign(szVolumeName);
#elif xOS_ENV_UNIX
    // REVIEW: just get the dir name ??
    if (CxConst::xUNIX_SLASH == csVolumePath) {
        sRv = CxConst::xUNIX_SLASH;
    } else {
        sRv = CxPath::sGetFileName(csVolumePath);
    }
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxVolume::bSetLabel(
    const std::tstring_t &csVolumePath,
    const std::tstring_t &csVolumeName
)
{
    /*DEBUG*/
    /*DEBUG*/

    bool bRv = bIsReady(csVolumePath);
    xCHECK_RET(false == bRv, false);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetVolumeLabel(csVolumePath.c_str(), csVolumeName.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        // TODO: CxVolume::bSetLabel
    #elif xOS_FREEBSD
        // TODO: CxVolume::bSetLabel
    #endif
#endif

    return true;
}
//--------------------------------------------------------------------------
/*static*/
CxVolume::EType
CxVolume::dtGetType(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xASSERT_RET(false == csVolumePath.empty(), dtUnknown);

    EType dtRes = dtUnknown;

#if   xOS_ENV_WIN
    dtRes = static_cast<EType>( ::GetDriveType(CxPath::sSlashAppend(csVolumePath).c_str()) );
    xDEBUG_VAR_NA(dtRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        FILE *pfFile = ::setmntent(xT("/etc/mtab"), xT("r"));
        xASSERT_RET(NULL != pfFile, dtUnknown);

        for ( ; ; ) {
            const mntent *pmteMountPoint = ::getmntent(pfFile);
            xCHECK_DO(NULL == pmteMountPoint, break);

             printf("[name]: %s\n[path]: %s\n[type]: %s\n\n",
                    pmteMountPoint->mnt_fsname, pmteMountPoint->mnt_dir, pmteMountPoint->mnt_type);

            bool bRv = CxString::bCompareNoCase(csVolumePath, std::tstring_t(pmteMountPoint->mnt_dir));
            xCHECK_DO(false == bRv, continue);

            // TODO: CxVolume::dtGetType
            dtRes = (NULL == pmteMountPoint->mnt_type) ? dtUnknown : dtOther;

            break;
        }

        int iRv = ::endmntent(pfFile);
        xASSERT_RET(1 == iRv, dtUnknown);
    #elif xOS_FREEBSD
        // TODO: CxVolume::dtGetType
    #endif
#endif

    return dtRes;
}
//--------------------------------------------------------------------------


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
