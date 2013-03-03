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

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxVolume::CxVolume(
    std::ctstring_t &csVolumePath
) :
    _m_csVolumePath(csVolumePath)
{
    xTEST_EQ(false, _m_csVolumePath.empty());
}
//------------------------------------------------------------------------------
/* virtual */
CxVolume::~CxVolume() {

}
//------------------------------------------------------------------------------
std::ctstring_t &
CxVolume::volumePath() const {
    xTEST_EQ(false, _m_csVolumePath.empty());

    return _m_csVolumePath;
}
//--------------------------------------------------------------------------
CxVolume::ExType
CxVolume::type() const {
    ExType dtRes = dtUnknown;

#if   xOS_ENV_WIN
    dtRes = static_cast<ExType>( ::GetDriveType( CxPath(volumePath()).slashAppend().c_str() ) );
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

            bool_t bRv = CxString::compareNoCase(volumePath(), std::tstring_t(pmteMountPoint->mnt_dir));
            xCHECK_DO(!bRv, continue);

            // TODO: CxVolume::dtGetType
            dtRes = (NULL == pmteMountPoint->mnt_type) ? dtUnknown : dtOther;

            break;
        }

        int_t iRv = ::endmntent(pfFile);
        xTEST_EQ(1, iRv);
    #elif xOS_FREEBSD
        // TODO: CxVolume::dtGetType
    #endif
#endif

    return dtRes;
}
//--------------------------------------------------------------------------
std::tstring_t
CxVolume::label() const {
    std::tstring_t sRv;

    bool_t bRv = isReady();
    xCHECK_RET(!bRv, std::tstring_t());

#if   xOS_ENV_WIN
    tchar_t szVolumeName[MAX_PATH + 1] = {0};

    CxLastError::reset();

    BOOL blRes = ::GetVolumeInformation(
                        CxPath( volumePath() ).slashAppend().c_str(),
                        &szVolumeName[0],
                        static_cast<DWORD>( xARRAY_SIZE(szVolumeName) ),
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        0
    );
    xTEST_DIFF(false, blRes && 0UL == CxLastError::get());

    sRv.assign(szVolumeName);
#elif xOS_ENV_UNIX
    // REVIEW: just get the dir name ??
    if (CxConst::xUNIX_SLASH == volumePath()) {
        sRv = CxConst::xUNIX_SLASH;
    } else {
        sRv = CxPath( volumePath() ).fileName();
    }
#endif

    return sRv;
}
//--------------------------------------------------------------------------
bool_t
CxVolume::isValid() const {
#if   xOS_ENV_WIN
    bool_t bRv = CxDir( volumePath() ).isRoot();
    xCHECK_RET(!bRv, false);
#elif xOS_ENV_UNIX
    xCHECK_RET(true                  == volumePath().empty(), false);
    xCHECK_RET(CxConst::xSLASH.at(0) != volumePath().at(0),   false);
#endif

    return true;
}
//--------------------------------------------------------------------------
bool_t
CxVolume::isReady() const {
    bool_t         bRv          = false;
    std::tstring_t _sVolumePath = CxPath( volumePath() ).slashAppend();
    std::tstring_t sOldDirPath;

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    UINT           uiOldErrorMode = 0U;

    uiOldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    xTEST_NA(uiOldErrorMode);

    sOldDirPath  = CxDir::current();
    xTEST_NA(sOldDirPath);

    bRv = !!::SetCurrentDirectory(_sVolumePath.c_str());
    xTEST_NA(bRv);

    CxDir::setCurrent(sOldDirPath);

    (void_t)::SetErrorMode(uiOldErrorMode);
#elif xOS_ENV_UNIX
    sOldDirPath  = CxDir::current();
    xTEST_NA(sOldDirPath);

    int_t iRv = ::chdir(_sVolumePath.c_str());
    xTEST_NA(iRv);
    bRv = (- 1 != iRv);

    CxDir::setCurrent(sOldDirPath);
#endif

    return bRv;
}
//--------------------------------------------------------------------------
bool_t
CxVolume::isEmpty() const {
    return CxDir( volumePath() ).isEmpty(CxConst::xMASK_ALL);
}
//------------------------------------------------------------------------------
void_t
CxVolume::mount(
    std::ctstring_t &a_csDestPath    ///< destination path
) const
{
    xTEST_EQ(false, a_csDestPath.empty());

#if   xOS_ENV_WIN
    // TODO: CxVolume::bMount - is it correct?
    NETRESOURCE nrNetResource = {0};

    nrNetResource.dwScope       = RESOURCE_GLOBALNET;
    nrNetResource.dwType        = RESOURCETYPE_DISK;
    nrNetResource.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
    nrNetResource.dwUsage       = RESOURCEUSAGE_CONTAINER;
    nrNetResource.lpLocalName   = const_cast<tchar_t *>( a_csDestPath.c_str() );
    nrNetResource.lpRemoteName  = const_cast<tchar_t *>( volumePath().c_str() );
    nrNetResource.lpComment     = NULL;
    nrNetResource.lpProvider    = NULL;

    DWORD dwRes = ::WNetAddConnection2(&nrNetResource, NULL, NULL, CONNECT_UPDATE_PROFILE);
    xTEST_EQ(static_cast<DWORD>( NO_ERROR ), dwRes);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t iRv = ::mount(volumePath().c_str(), a_csDestPath.c_str(), NULL, MS_REMOUNT, NULL);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        int_t iRv = ::mount(volumePath().c_str(), a_csDestPath.c_str(), MNT_UPDATE, NULL);
        xTEST_DIFF(- 1, iRv);
    #endif
#endif
}
//--------------------------------------------------------------------------
void_t
CxVolume::unMount(
    cbool_t &a_cbIsForce     ///< force unmount even if busy
) const
{
    xTEST_NA(a_cbIsForce);

#if   xOS_ENV_WIN
    // TODO: CxVolume::bUnMount - is it correct?
    DWORD dwRes = ::WNetCancelConnection2(volumePath().c_str(), CONNECT_UPDATE_PROFILE, a_cbIsForce);
    xTEST_EQ(static_cast<DWORD>( NO_ERROR ), dwRes);
#elif xOS_ENV_UNIX
    #ifdef MNT_DETACH
        #define xMNT_DETACH MNT_DETACH
    #else
        #define xMNT_DETACH MNT_FORCE
    #endif

    cint_t ciFlag = a_cbIsForce ? MNT_FORCE : xMNT_DETACH;

    #if   xOS_LINUX
        int_t iRv = ::umount2(volumePath().c_str(), ciFlag);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        int_t iRv = ::unmount(volumePath().c_str(), ciFlag);
        xTEST_DIFF(- 1, iRv);
    #endif
#endif
}
//--------------------------------------------------------------------------


/*******************************************************************************
*    public, static
*
*******************************************************************************/

//--------------------------------------------------------------------------
/* static */
void_t
CxVolume::space(
    std::ctstring_t &a_csDirPath,      ///< directory path
    ulonglong_t     *a_pullAvailable,  ///< available space (for unprivileged users)
    ulonglong_t     *a_pullTotal,      ///< total space
    ulonglong_t     *a_pullFree        ///< free space
)
{
    xTEST_NA(a_csDirPath);
    xTEST_NA(a_pullAvailable);
    xTEST_NA(a_pullTotal);
    xTEST_NA(a_pullFree);

    //--------------------------------------------------
    //if csDirPath parameter is empty, uses the root of the current volume
    std::tstring_t sDirPath;

    if (a_csDirPath.empty()) {
        sDirPath = CxPath::exeDir();
    } else {
        sDirPath = a_csDirPath;
    }

    bool_t bRv = CxDir(sDirPath).isExists();
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

    int_t iRv = ::xSTATVFS(sDirPath.c_str(), &stfInfo);
    xTEST_DIFF(- 1, iRv);

    CxUtils::ptrAssignT(a_pullAvailable, static_cast<ulonglong_t>( stfInfo.f_bavail * stfInfo.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(a_pullTotal,     static_cast<ulonglong_t>( stfInfo.f_blocks * stfInfo.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(a_pullFree,      static_cast<ulonglong_t>( stfInfo.f_bfree  * stfInfo.xSTATVFS_F_FRSIZE ));
#endif
}
//--------------------------------------------------------------------------
/* static */
void_t
CxVolume::paths(
    std::vec_tstring_t *a_pvsVolumePaths    ///< volume paths
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

    for (ctchar_t *s = sRv.c_str(); 0 != *s; s += ::lstrlen(s) + 1) {
        vsRes.push_back(s);
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct _SMounts {
            std::tstring_t m_sDevice;
            std::tstring_t m_sDestination;
            std::tstring_t m_sFsType;
            std::tstring_t m_sOptions;
            int_t            m_iDump;
            int_t            m_iPass;
        };

        std::tifstream_t fsProcMounts(xT("/proc/mounts"));
        xTEST_EQ(true, !! fsProcMounts.good());

        for ( ; !fsProcMounts.eof(); ) {
            _SMounts mntMounts;

            fsProcMounts >> mntMounts.m_sDevice  >> mntMounts.m_sDestination >> mntMounts.m_sFsType >>
                            mntMounts.m_sOptions >> mntMounts.m_iDump        >> mntMounts.m_iPass;
            xCHECK_DO(mntMounts.m_sDevice.empty(), continue);

            vsRes.push_back(mntMounts.m_sDestination);
        }
    #elif xOS_FREEBSD
        // TODO: CxVolume::paths
    #endif
#endif

    // out
    std::swap(*a_pvsVolumePaths, vsRes);
}
//--------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
