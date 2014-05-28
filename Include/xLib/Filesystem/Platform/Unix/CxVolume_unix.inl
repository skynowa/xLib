/**
 * \file  CxVolume.inl
 * \brief volume
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxVolume::_fileSystem_impl() const
{
    std::tstring_t sRv;

#if   xOS_LINUX
    FILE *file = ::setmntent("/etc/mtab", "r");
    xTEST_PTR(file);

    for ( ; ; ) {
        mntent mnt;  xSTRUCT_ZERO(mnt);
        cint_t buffLen       = 4096 + 1;
        char   buff[buffLen] = {0};

        const mntent *mountPoint = ::getmntent_r(file, &mnt, buff, buffLen);
        xCHECK_DO(mountPoint == xPTR_NULL, break);

        bool_t bRv = CxStringCI::compare(path(), mountPoint->mnt_dir);
        xCHECK_DO(!bRv, continue);

        sRv = (mountPoint->mnt_type == xPTR_NULL) ? CxConst::strEmpty() : mountPoint->mnt_type;

        break;
    }

    int_t iRv = ::endmntent(file);  file = xPTR_NULL;
    xTEST_EQ(iRv, 1);
#elif xOS_FREEBSD
    // TODO: CxVolume::fileSystem()
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxVolume::_label_impl() const
{
    std::tstring_t sRv;

    // REVIEW: just get the dir name ??
    if (path() == CxConst::unixSlash()) {
        sRv = CxConst::unixSlash();
    } else {
        sRv = CxPath( path() ).fileName();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::_isValid_impl() const
{
    xCHECK_RET(path().empty(),                         false);
    xCHECK_RET(path().at(0) != CxConst::slash().at(0), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxVolume::_isReady_impl() const
{
    bool_t         bRv           = false;
    std::tstring_t volumeDirPath = CxPath( path() ).slashAppend();
    std::tstring_t oldDirPath;

    oldDirPath = CxDir::current();
    xTEST_NA(oldDirPath);

    int_t iRv = ::chdir(volumeDirPath.c_str());
    xTEST_NA(iRv);
    bRv = (iRv != - 1);

    CxDir::setCurrent(oldDirPath);

    return bRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::_mount_impl(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
#if   xOS_LINUX
    int_t iRv = ::mount(path().c_str(), a_destPath.c_str(), xPTR_NULL, MS_REMOUNT, xPTR_NULL);
    xTEST_DIFF(iRv, - 1);
#elif xOS_FREEBSD
    int_t iRv = ::mount(path().c_str(), a_destPath.c_str(), MNT_UPDATE, xPTR_NULL);
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::_unMount_impl(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
#ifdef MNT_DETACH
    #define xMNT_DETACH MNT_DETACH
#else
    #define xMNT_DETACH MNT_FORCE
#endif

    cint_t flag = a_isForce ? MNT_FORCE : xMNT_DETACH;

#if   xOS_LINUX
    int_t iRv = ::umount2(path().c_str(), flag);
    xTEST_DIFF(iRv, - 1);
#elif xOS_FREEBSD
    int_t iRv = ::unmount(path().c_str(), flag);
    xTEST_DIFF(iRv, - 1);
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxVolume::_space_impl(
    std::ctstring_t &a_dirPath,     ///< directory path
    ulonglong_t     *a_available,   ///< available space (for unprivileged users)
    ulonglong_t     *a_total,       ///< total space
    ulonglong_t     *a_free         ///< free space
)
{
    struct xSTATVFS info;   xSTRUCT_ZERO(info);

    int_t iRv = ::xSTATVFS(a_dirPath.c_str(), &info);
    xTEST_DIFF(iRv, - 1);

    CxUtils::ptrAssignT(a_available, static_cast<ulonglong_t>( info.f_bavail * info.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(a_total,     static_cast<ulonglong_t>( info.f_blocks * info.xSTATVFS_F_FRSIZE ));
    CxUtils::ptrAssignT(a_free,      static_cast<ulonglong_t>( info.f_bfree  * info.xSTATVFS_F_FRSIZE ));
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxVolume::_paths_impl(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    std::vec_tstring_t vsRv;

#if   xOS_LINUX
    struct _Mounts
    {
        std::tstring_t device;
        std::tstring_t destination;
        std::tstring_t fsType;
        std::tstring_t options;
        int_t          dump;
        int_t          pass;
    };

    std::tifstream_t procMounts(xT("/proc/mounts"));
    xTEST_EQ(procMounts.good(), true);

    for ( ; !procMounts.eof(); ) {
        _Mounts mounts;

        procMounts >> mounts.device  >> mounts.destination >> mounts.fsType >>
                      mounts.options >> mounts.dump        >> mounts.pass;
        xCHECK_DO(mounts.device.empty(), continue);

        vsRv.push_back(mounts.destination);
    }
#elif xOS_FREEBSD
    // TODO: CxVolume::paths()
#endif

    // out
    a_volumePaths->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
