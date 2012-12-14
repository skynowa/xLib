/**
 * \file  CxVolume.cpp
 * \brief volume
 */


#include <xLib/Filesystem/CxVolume.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if   xOS_ENV_WIN
    #if !xCOMPILER_MINGW
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
    const std::tstring_t &a_csVolumePath
)
{
    xTEST_NA(csVolumePath);

#if   xOS_ENV_WIN
    bool bRv = CxDir(a_csVolumePath).bIsRoot();
    xCHECK_RET(false == bRv, false);
#elif xOS_ENV_UNIX
    xCHECK_RET(true                  == a_csVolumePath.empty(), false);
    xCHECK_RET(CxConst::xSLASH.at(0) != a_csVolumePath.at(0),   false);
#endif

    return true;
}
//--------------------------------------------------------------------------
/* static */
bool
CxVolume::bIsReady(
    const std::tstring_t &a_csVolumePath
)
{
    xTEST_EQ(false, a_csVolumePath.empty());

    bool           bRv        = false;
    std::tstring_t sVolumePath = CxPath(a_csVolumePath).sSlashAppend();
    std::tstring_t sOldDirPath;

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    UINT           uiOldErrorMode = 0U;

    uiOldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    // n/a

    sOldDirPath  = CxDir::sCurrent();
    // n/a

    bRv = !!::SetCurrentDirectory(sVolumePath.c_str());
    // n/a

    CxDir::vSetCurrent(sOldDirPath);

    (void)::SetErrorMode(uiOldErrorMode);
#elif xOS_ENV_UNIX
    sOldDirPath  = CxDir::sCurrent();
    // n/a

    int iRv = ::chdir(sVolumePath.c_str());
    // n/a
    bRv = (- 1 != iRv);

    CxDir::vSetCurrent(sOldDirPath);
#endif

    return bRv;
}
//--------------------------------------------------------------------------
/* static */
bool
CxVolume::bIsEmpty(
    const std::tstring_t &a_csVolumePath
)
{
    xTEST_EQ(false, a_csVolumePath.empty());

    return CxDir(a_csVolumePath).bIsEmpty(CxConst::xMASK_FILES_ALL);
}
//--------------------------------------------------------------------------
/* static */
void
CxVolume::vSpace(
    const std::tstring_t &a_csDirPath,      ///< directory path
    ulonglong_t          *a_pullAvailable,  ///< available space (for unprivileged users)
    ulonglong_t          *a_pullTotal,      ///< total space
    ulonglong_t          *a_pullFree        ///< free space
)
{
    // csDirPath     - n/a
    // pullAvailable - n/a
    // pullTotal     - n/a
    // pullFree      - n/a

    //--------------------------------------------------
    //if csDirPath parameter is empty, uses the root of the current volume
    std::tstring_t sDirPath;

    if (true == a_csDirPath.empty()) {
        sDirPath = CxPath::sExeDir();
    } else {
        sDirPath = a_csDirPath;
    }

    bool bRv = CxDir(sDirPath).bIsExists();
    xTEST_EQ(true, bRv);

#if   xOS_ENV_WIN
    ULARGE_INTEGER ullAvailable = {{0}};
    ULARGE_INTEGER ullTotal     = {{0}};
    ULARGE_INTEGER ullFree      = {{0}};

    BOOL blRes = ::GetDiskFreeSpaceEx(sDirPath.c_str(), &ullAvailable, &ullTotal, &ullFree);
    xTEST_DIFF(FALSE, blRes);

    CxUtils::ptrAssignT(a_pullAvailable, ullAvailable.QuadPart);
    CxUtils::ptrAssignT(a_pullTotal,     ullTotal.QuadPart);
    CxUtils::ptrAssignT(a_pullFree,      ullFree.QuadPart);
#elif xOS_ENV_UNIX
    struct xSTATVFS stfInfo = {0};

    int iRv = ::xSTATVFS(sDirPath.c_str(), &stfInfo);
    xTEST_DIFF(- 1, iRv);

    CxUtils::ptrAssignT(a_pullAvailable, static_cast<ulonglong_t>( stfInfo.f_bavail * stfInfo.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(a_pullTotal,     static_cast<ulonglong_t>( stfInfo.f_blocks * stfInfo.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(a_pullFree,      static_cast<ulonglong_t>( stfInfo.f_bfree  * stfInfo.xSTATVFS_F_FRSIZE ));
#endif
}
//---------------------------------------------------------------------------
/* static */
void
CxVolume::vMount(
    const std::tstring_t &a_csSourcePath, ///< source path
    const std::tstring_t &a_csDestPath    ///< destination path
)
{
    xTEST_EQ(false, a_csSourcePath.empty());
    xTEST_EQ(false, a_csDestPath.empty());

#if   xOS_ENV_WIN
    // TODO: CxVolume::bMount - is it correct?
    NETRESOURCE nrNetResource = {0};

    nrNetResource.dwScope       = RESOURCE_GLOBALNET;
    nrNetResource.dwType        = RESOURCETYPE_DISK;
    nrNetResource.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
    nrNetResource.dwUsage       = RESOURCEUSAGE_CONTAINER;
    nrNetResource.lpLocalName   = const_cast<tchar_t *>( a_csDestPath.c_str() );
    nrNetResource.lpRemoteName  = const_cast<tchar_t *>( a_csSourcePath.c_str() );
    nrNetResource.lpComment     = NULL;
    nrNetResource.lpProvider    = NULL;

    DWORD dwRes = ::WNetAddConnection2(&nrNetResource, NULL, NULL, CONNECT_UPDATE_PROFILE);
    xTEST_EQ(static_cast<DWORD>( NO_ERROR ), dwRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int iRv = ::mount(a_csSourcePath.c_str(), a_csDestPath.c_str(), NULL, MS_REMOUNT, NULL);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        int iRv = ::mount(a_csSourcePath.c_str(), a_csDestPath.c_str(), MNT_UPDATE, NULL);
        xTEST_DIFF(- 1, iRv);
    #endif
#endif
}
//--------------------------------------------------------------------------
/* static */
void
CxVolume::vUnMount(
    const std::tstring_t &a_csSourcePath, ///< source path
    const bool           &a_cbIsForce     ///< force unmount even if busy
)
{
    xTEST_EQ(false, a_csSourcePath.empty());
    // cbIsForce - n/a

#if   xOS_ENV_WIN
    // TODO: CxVolume::bUnMount - is it correct?
    DWORD dwRes = ::WNetCancelConnection2(a_csSourcePath.c_str(), CONNECT_UPDATE_PROFILE, a_cbIsForce);
    xTEST_EQ(static_cast<DWORD>( NO_ERROR ), dwRes);
#elif xOS_ENV_UNIX
    #ifdef MNT_DETACH
        #define xMNT_DETACH MNT_DETACH
    #else
        #define xMNT_DETACH MNT_FORCE
    #endif

    const int ciFlag = a_cbIsForce ? MNT_FORCE : xMNT_DETACH;

    #if   xOS_LINUX
        int iRv = ::umount2(a_csSourcePath.c_str(), ciFlag);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        int iRv = ::unmount(a_csSourcePath.c_str(), ciFlag);
        xTEST_DIFF(- 1, iRv);
    #endif
#endif
}
//--------------------------------------------------------------------------
/* static */
void
CxVolume::vPaths(
    std::vec_tstring_t *a_pvsVolumePaths
)
{
    xTEST_PTR(a_pvsVolumePaths);

    std::vec_tstring_t vsRes;

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    DWORD          dwRv = 0UL;

    dwRv = ::GetLogicalDriveStrings(0UL, NULL);
    xTEST_DIFF(0UL, dwRv);

    sRv.resize(dwRv);

    dwRv = ::GetLogicalDriveStrings(static_cast<DWORD>( sRv.size() ), &sRv.at(0));
    xTEST_DIFF(0UL, dwRv);

    for (const tchar_t *s = sRv.c_str(); 0 != *s; s += ::lstrlen(s) + 1) {
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
        xTEST_EQ(true, !! fsProcMounts.good());

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

    std::swap(*a_pvsVolumePaths, vsRes);
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxVolume::sLabel(
    const std::tstring_t &a_csVolumePath
)
{
    xTEST_EQ(false, a_csVolumePath.empty());

    std::tstring_t sRv;

    bool bRv = bIsReady(a_csVolumePath);
    xCHECK_RET(false == bRv, std::tstring_t());

#if   xOS_ENV_WIN
    tchar_t szVolumeName[MAX_PATH + 1] = {0};

    CxLastError::vReset();

    BOOL blRes = ::GetVolumeInformation(
                        CxPath(a_csVolumePath).sSlashAppend().c_str(),
                        &szVolumeName[0],
                        static_cast<DWORD>( xARRAY_SIZE(szVolumeName) ),
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        0
    );
    xTEST_DIFF(false, blRes && 0UL == CxLastError::ulGet());

    sRv.assign(szVolumeName);
#elif xOS_ENV_UNIX
    // REVIEW: just get the dir name ??
    if (CxConst::xUNIX_SLASH == a_csVolumePath) {
        sRv = CxConst::xUNIX_SLASH;
    } else {
        sRv = CxPath::sFileName(a_csVolumePath);
    }
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
CxVolume::ExType
CxVolume::dtType(
    const std::tstring_t &a_csVolumePath
)
{
    xTEST_EQ(false, a_csVolumePath.empty());

    ExType dtRes = dtUnknown;

#if   xOS_ENV_WIN
    dtRes = static_cast<ExType>( ::GetDriveType( CxPath(a_csVolumePath).sSlashAppend().c_str() ) );
    xTEST_NA(dtRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        FILE *pfFile = ::setmntent(xT("/etc/mtab"), xT("r"));
        xTEST_PTR(pfFile);

        xFOREVER {
            const mntent *pmteMountPoint = ::getmntent(pfFile);
            xCHECK_DO(NULL == pmteMountPoint, break);

            // printf("[name]: %s\n[path]: %s\n[type]: %s\n\n",
            //        pmteMountPoint->mnt_fsname, pmteMountPoint->mnt_dir, pmteMountPoint->mnt_type);

            bool bRv = CxString::bCompareNoCase(a_csVolumePath, std::tstring_t(pmteMountPoint->mnt_dir));
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
