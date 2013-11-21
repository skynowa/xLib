/**
 * \file  CxVolume.cpp
 * \brief volume
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>

#if xOS_ENV_WIN
    #if !xCOMPILER_MINGW
        #pragma comment(lib, "mpr.lib")
    #endif
#else
    #include <sys/param.h>
    #include <sys/mount.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxVolume::CxVolume(
    std::ctstring_t &a_volumePath
) :
    _volumePath(a_volumePath)
{
    xTEST_EQ(false, _volumePath.empty());
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxVolume::volumePath() const
{
    xTEST_EQ(false, _volumePath.empty());

    return _volumePath;
}
//-------------------------------------------------------------------------------------------------
inline CxVolume::ExType
CxVolume::type() const
{
    ExType dtRv = dtUnknown;

#if   xOS_ENV_WIN
    dtRv = static_cast<ExType>( ::GetDriveType( CxPath(volumePath()).slashAppend().c_str() ) );
    xTEST_NA(dtRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        FILE *file = ::setmntent(xT("/etc/mtab"), xT("r"));
        xTEST_PTR(file);

        xFOREVER {
            const mntent *mountPoint = ::getmntent(file);
            xCHECK_DO(NULL == mountPoint, break);

            // printf("[name]: %s\n[path]: %s\n[type]: %s\n\n",
            //        mountPoint->mnt_fsname, mountPoint->mnt_dir, mountPoint->mnt_type);

            bool_t bRv = CxString::compareNoCase(volumePath(), std::tstring_t(mountPoint->mnt_dir));
            xCHECK_DO(!bRv, continue);

            // TODO: CxVolume::dtGetType
            dtRv = (NULL == mountPoint->mnt_type) ? dtUnknown : dtOther;

            break;
        }

        int_t iRv = ::endmntent(file);
        xTEST_EQ(1, iRv);
    #elif xOS_FREEBSD
        // TODO: CxVolume::dtGetType
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    return dtRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxVolume::label() const
{
    std::tstring_t sRv;

    bool_t bRv = isReady();
    xCHECK_RET(!bRv, std::tstring_t());

#if xOS_ENV_WIN
    tchar_t volumeName[MAX_PATH + 1] = {0};

    CxLastError::reset();

    BOOL blRv = ::GetVolumeInformation(CxPath( volumePath() ).slashAppend().c_str(), &volumeName[0],
        static_cast<DWORD>( xARRAY_SIZE(volumeName) ), NULL, NULL, NULL, NULL, 0);
    xTEST_DIFF(false, blRv && 0UL == CxLastError::get());

    sRv.assign(volumeName);
#else
    // REVIEW: just get the dir name ??
    if (CxConst::unixSlash() == volumePath()) {
        sRv = CxConst::unixSlash();
    } else {
        sRv = CxPath( volumePath() ).fileName();
    }
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::isValid() const
{
#if xOS_ENV_WIN
    bool_t bRv = CxDir( volumePath() ).isRoot();
    xCHECK_RET(!bRv, false);
#else
    xCHECK_RET(true                   == volumePath().empty(), false);
    xCHECK_RET(CxConst::slash().at(0) != volumePath().at(0),   false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::isReady() const
{
    bool_t         bRv           = false;
    std::tstring_t volumeDirPath = CxPath( volumePath() ).slashAppend();
    std::tstring_t oldDirPath;

#if xOS_ENV_WIN
    std::tstring_t sRv;
    UINT           oldErrorMode = 0U;

    oldErrorMode = ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT |
        SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
    xTEST_NA(oldErrorMode);

    oldDirPath  = CxDir::current();
    xTEST_NA(oldDirPath);

    bRv = !!::SetCurrentDirectory(volumeDirPath.c_str());
    xTEST_NA(bRv);

    CxDir::setCurrent(oldDirPath);

    (void_t)::SetErrorMode(oldErrorMode);
#else
    oldDirPath = CxDir::current();
    xTEST_NA(oldDirPath);

    int_t iRv = ::chdir(volumeDirPath.c_str());
    xTEST_NA(iRv);
    bRv = (- 1 != iRv);

    CxDir::setCurrent(oldDirPath);
#endif

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::isEmpty() const
{
    return CxDir( volumePath() ).isEmpty(CxConst::maskAll());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::mount(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    xTEST_EQ(false, a_destPath.empty());

#if   xOS_ENV_WIN
    // TODO: CxVolume::bMount - is it correct?
    NETRESOURCE netResource = {0};

    netResource.dwScope       = RESOURCE_GLOBALNET;
    netResource.dwType        = RESOURCETYPE_DISK;
    netResource.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
    netResource.dwUsage       = RESOURCEUSAGE_CONTAINER;
    netResource.lpLocalName   = const_cast<tchar_t *>( a_destPath.c_str() );
    netResource.lpRemoteName  = const_cast<tchar_t *>( volumePath().c_str() );
    netResource.lpComment     = NULL;
    netResource.lpProvider    = NULL;

    DWORD dwRv = ::WNetAddConnection2(&netResource, NULL, NULL, CONNECT_UPDATE_PROFILE);
    xTEST_EQ(static_cast<DWORD>( NO_ERROR ), dwRv);
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        int_t iRv = ::mount(volumePath().c_str(), a_destPath.c_str(), NULL, MS_REMOUNT, NULL);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        int_t iRv = ::mount(volumePath().c_str(), a_destPath.c_str(), MNT_UPDATE, NULL);
        xTEST_DIFF(- 1, iRv);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::unMount(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
    xTEST_NA(a_isForce);

#if   xOS_ENV_WIN
    // TODO: CxVolume::unMount - is it correct?
    DWORD dwRv = ::WNetCancelConnection2(volumePath().c_str(), CONNECT_UPDATE_PROFILE, a_isForce);
    xTEST_EQ(static_cast<DWORD>( NO_ERROR ), dwRv);
#elif xOS_ENV_UNIX
    #ifdef MNT_DETACH
        #define xMNT_DETACH MNT_DETACH
    #else
        #define xMNT_DETACH MNT_FORCE
    #endif

    cint_t flag = a_isForce ? MNT_FORCE : xMNT_DETACH;

    #if   xOS_LINUX
        int_t iRv = ::umount2(volumePath().c_str(), flag);
        xTEST_DIFF(- 1, iRv);
    #elif xOS_FREEBSD
        int_t iRv = ::unmount(volumePath().c_str(), flag);
        xTEST_DIFF(- 1, iRv);
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::isSpaceEnough(
    culonglong_t &a_needBytes ///< need space in bytes
) const
{
    xTEST_NA(a_needBytes);

    ulonglong_t totalFreeBytes = 0ULL;
    space(_volumePath, NULL, NULL, &totalFreeBytes);

    xCHECK_RET(a_needBytes > totalFreeBytes, false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxVolume::space(
    std::ctstring_t &a_dirPath,     ///< directory path
    ulonglong_t     *a_available,   ///< available space (for unprivileged users)
    ulonglong_t     *a_total,       ///< total space
    ulonglong_t     *a_free         ///< free space
)
{
    xTEST_NA(a_dirPath);
    xTEST_NA(a_available);
    xTEST_NA(a_total);
    xTEST_NA(a_free);

    //--------------------------------------------------
    // if a_dirPath parameter is empty, uses the root of the current volume
    std::tstring_t dirPath;

    if (a_dirPath.empty()) {
        dirPath = CxPath::exeDir();
    } else {
        dirPath = a_dirPath;
    }

    bool_t bRv = CxDir(dirPath).isExists();
    xTEST_EQ(true, bRv);

#if xOS_ENV_WIN
    ULARGE_INTEGER available = {{0}};
    ULARGE_INTEGER total     = {{0}};
    ULARGE_INTEGER free      = {{0}};

    BOOL blRv = ::GetDiskFreeSpaceEx(dirPath.c_str(), &available, &total, &free);
    xTEST_DIFF(FALSE, blRv);

    CxUtils::ptrAssignT(a_available, available.QuadPart);
    CxUtils::ptrAssignT(a_total,     total.QuadPart);
    CxUtils::ptrAssignT(a_free,      free.QuadPart);
#else
    struct xSTATVFS info;   xSTRUCT_ZERO(info);

    int_t iRv = ::xSTATVFS(dirPath.c_str(), &info);
    xTEST_DIFF(- 1, iRv);

    CxUtils::ptrAssignT(a_available, static_cast<ulonglong_t>( info.f_bavail * info.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(a_total,     static_cast<ulonglong_t>( info.f_blocks * info.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(a_free,      static_cast<ulonglong_t>( info.f_bfree  * info.xSTATVFS_F_FRSIZE ));
#endif
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxVolume::paths(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    xTEST_PTR(a_volumePaths);

    std::vec_tstring_t vsRv;

#if   xOS_ENV_WIN
    std::tstring_t sRv;
    DWORD          dwRv = 0UL;

    dwRv = ::GetLogicalDriveStrings(0UL, NULL);
    xTEST_DIFF(0UL, dwRv);

    sRv.resize(dwRv);

    dwRv = ::GetLogicalDriveStrings(static_cast<DWORD>( sRv.size() ), &sRv.at(0));
    xTEST_DIFF(0UL, dwRv);

    for (ctchar_t *s = sRv.c_str(); 0 != *s; s += ::lstrlen(s) + 1) {
        vsRv.push_back(s);
    }
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        struct _SMounts
        {
            std::tstring_t device;
            std::tstring_t destination;
            std::tstring_t fsType;
            std::tstring_t options;
            int_t          dump;
            int_t          pass;
        };

        std::tifstream_t procMounts(xT("/proc/mounts"));
        xTEST_EQ(true, procMounts.good());

        for ( ; !procMounts.eof(); ) {
            _SMounts mounts;

            procMounts >> mounts.device  >> mounts.destination >> mounts.fsType >>
                          mounts.options >> mounts.dump        >> mounts.pass;
            xCHECK_DO(mounts.device.empty(), continue);

            vsRv.push_back(mounts.destination);
        }
    #elif xOS_FREEBSD
        // TODO: CxVolume::paths()
    #endif
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    // out
    a_volumePaths->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
