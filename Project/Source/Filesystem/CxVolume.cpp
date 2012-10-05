/**
 * \file  CxVolume.cpp
 * \brief volume
 */


#include <xLib/Filesystem/CxVolume.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if   xOS_ENV_WIN
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
/* static */
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
/* static */
bool
CxVolume::bIsReady(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xTEST_EQ(false, csVolumePath.empty());

    bool           bRv        = false;
    std::tstring_t sVolumePath = CxPath::sSlashAppend(csVolumePath);
    std::tstring_t sOldDirPath;

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    UINT           uiOldErrorMode = 0U;

    uiOldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    /*DEBUG*/// n/a

    sOldDirPath  = CxDir::sGetCurrent();
    /*DEBUG*/// n/a

    bRv = !!::SetCurrentDirectory(sVolumePath.c_str());
    /*DEBUG*/// n/a

    CxDir::vSetCurrent(sOldDirPath);

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
/* static */
bool
CxVolume::bIsEmpty(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xTEST_EQ(false, csVolumePath.empty());

    return CxDir::bIsEmpty(csVolumePath, CxConst::xMASK_FILES_ALL);
}
//--------------------------------------------------------------------------
/* static */
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
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);

    CxUtils::ptrAssignT(pullAvailable, ullAvailable.QuadPart);
    CxUtils::ptrAssignT(pullTotal,     ullTotal.QuadPart);
    CxUtils::ptrAssignT(pullFree,      ullFree.QuadPart);
#elif xOS_ENV_UNIX
    struct xSTATVFS stfInfo = {0};

    int iRv = ::xSTATVFS(_sDirPath.c_str(), &stfInfo);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);

    CxUtils::ptrAssignT(pullAvailable, static_cast<ulonglong_t>( stfInfo.f_bavail * stfInfo.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(pullTotal,     static_cast<ulonglong_t>( stfInfo.f_blocks * stfInfo.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(pullFree,      static_cast<ulonglong_t>( stfInfo.f_bfree  * stfInfo.xSTATVFS_F_FRSIZE ));
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxVolume::bMount(
    const std::tstring_t &csSourcePath, ///< source path
    const std::tstring_t &csDestPath    ///< destination path
)
{
    /*DEBUG*/xTEST_EQ(false, csSourcePath.empty());
    /*DEBUG*/xTEST_EQ(false, csDestPath.empty());

#if   xOS_ENV_WIN
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
    /*DEBUG*/xTEST_EQ(static_cast<DWORD>( NO_ERROR ), dwRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int iRv = ::mount(csSourcePath.c_str(), csDestPath.c_str(), NULL, MS_REMOUNT, NULL);
        /*DEBUG*/xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        int iRv = ::mount(csSourcePath.c_str(), csDestPath.c_str(), MNT_UPDATE, NULL);
        /*DEBUG*/xTEST_DIFF(- 1, iRv);
    #endif
#endif

    return true;
}
//--------------------------------------------------------------------------
/* static */
bool
CxVolume::bUnMount(
    const std::tstring_t &csSourcePath, ///< source path
    const bool            cbIsForce     ///< force unmount even if busy
)
{
    /*DEBUG*/xTEST_EQ(false, csSourcePath.empty());
    /*DEBUG*/// cbIsForce - n/a

#if   xOS_ENV_WIN
    // TODO: CxVolume::bUnMount - is it correct?
    DWORD dwRes = ::WNetCancelConnection2(csSourcePath.c_str(), CONNECT_UPDATE_PROFILE, cbIsForce);
    /*DEBUG*/xTEST_EQ(static_cast<DWORD>( NO_ERROR ), dwRes);
#elif xOS_ENV_UNIX
    #ifdef MNT_DETACH
        #define xMNT_DETACH MNT_DETACH
    #else
        #define xMNT_DETACH MNT_FORCE
    #endif

    const int ciFlag = cbIsForce ? MNT_FORCE : xMNT_DETACH;

    #if   xOS_LINUX
        int iRv = ::umount2(csSourcePath.c_str(), ciFlag);
        /*DEBUG*/xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        int iRv = ::unmount(csSourcePath.c_str(), ciFlag);
        /*DEBUG*/xTEST_DIFF(- 1, iRv);
    #endif
#endif

    return true;
}
//--------------------------------------------------------------------------
/* static */
bool
CxVolume::bGetPaths(
    std::vec_tstring_t *pvsVolumePaths
)
{
    /*DEBUG*/xTEST_PTR(pvsVolumePaths);

    std::vec_tstring_t vsRes;

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    DWORD          ulRv = 0UL;

    ulRv = ::GetLogicalDriveStrings(0UL, NULL);
    /*DEBUG*/xTEST_DIFF(0UL, ulRv);

    sRv.resize(ulRv);

    ulRv = ::GetLogicalDriveStrings(sRv.size(), &sRv.at(0));
    /*DEBUG*/xTEST_DIFF(0UL, ulRv);

    for (const tchar_t *s = &sRv.at(0); 0 != *s; s += _tcslen(s) + sizeof(xT('\0'))) {
        vsRes.push_back(s);
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct _SMounts {
            std::tstring_t m_sDevice;
            std::tstring_t m_sDestination;
            std::tstring_t m_sFsType;
            std::tstring_t m_sOptions;
            int            m_iDump;
            int            m_iPass;
        };

        std::tifstream_t fsProcMounts(xT("/proc/mounts"));
        /*DEBUG*/xTEST_EQ(true, !! fsProcMounts.good());

        for ( ; !fsProcMounts.eof(); ) {
            _SMounts mntMounts;

            fsProcMounts >> mntMounts.m_sDevice  >> mntMounts.m_sDestination >> mntMounts.m_sFsType >>
                            mntMounts.m_sOptions >> mntMounts.m_iDump        >> mntMounts.m_iPass;
            xCHECK_DO(true == mntMounts.m_sDevice.empty(), continue);

            vsRes.push_back(mntMounts.m_sDestination);
        }
    #elif xOS_FREEBSD
        // TODO: CxVolume::bGetPaths
    #endif
#endif

    std::swap(*pvsVolumePaths, vsRes);

    return true;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxVolume::sGetLabel(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xTEST_EQ(false, csVolumePath.empty());

    std::tstring_t sRv;

    bool bRv = bIsReady(csVolumePath);
    xCHECK_RET(false == bRv, std::tstring_t());

#if   xOS_ENV_WIN
    tchar_t szVolumeName[MAX_PATH + 1] = {0};

    CxLastError::vReset();

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
    /*DEBUG*/xTEST_DIFF(false, blRes && 0UL == CxLastError::ulGet());

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
/* static */
CxVolume::ExType
CxVolume::dtGetType(
    const std::tstring_t &csVolumePath
)
{
    /*DEBUG*/xTEST_EQ(false, csVolumePath.empty());

    ExType dtRes = dtUnknown;

#if   xOS_ENV_WIN
    dtRes = static_cast<ExType>( ::GetDriveType(CxPath::sSlashAppend(csVolumePath).c_str()) );
    xDEBUG_VAR_NA(dtRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        FILE *pfFile = ::setmntent(xT("/etc/mtab"), xT("r"));
        xTEST_PTR(pfFile);

        for ( ; ; ) {
            const mntent *pmteMountPoint = ::getmntent(pfFile);
            xCHECK_DO(NULL == pmteMountPoint, break);

            // printf("[name]: %s\n[path]: %s\n[type]: %s\n\n",
            //        pmteMountPoint->mnt_fsname, pmteMountPoint->mnt_dir, pmteMountPoint->mnt_type);

            bool bRv = CxString::bCompareNoCase(csVolumePath, std::tstring_t(pmteMountPoint->mnt_dir));
            xCHECK_DO(false == bRv, continue);

            // TODO: CxVolume::dtGetType
            dtRes = (NULL == pmteMountPoint->mnt_type) ? dtUnknown : dtOther;

            break;
        }

        int iRv = ::endmntent(pfFile);
        xTEST_EQ(1, iRv);
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
/* virtual */
CxVolume::~CxVolume() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
