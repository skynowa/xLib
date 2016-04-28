/**
 * \file  Volume.inl
 * \brief volume
 */


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Volume::_fileSystem_impl() const
{
    std::tstring_t sRv;

#if xHAVE_GETMNTENT_R
    FILE *file = ::setmntent("/etc/mtab", "r");
    xTEST_PTR(file);

    for ( ; ; ) {
        mntent mnt;  xSTRUCT_ZERO(mnt);
        cint_t buffLen       = 4096 + 1;
        char   buff[buffLen] = {0};

        const mntent *mountPoint = ::getmntent_r(file, &mnt, buff, buffLen);
        xCHECK_DO(mountPoint == xPTR_NULL, break);

        bool_t bRv = StringCI::compare(path(), mountPoint->mnt_dir);
        xCHECK_DO(!bRv, continue);

        sRv = (mountPoint->mnt_type == xPTR_NULL) ? Const::strEmpty() : mountPoint->mnt_type;

        break;
    }

    int_t iRv = ::endmntent(file);  file = xPTR_NULL;
    xTEST_EQ(iRv, 1);
#else
    // ANDROID: ::setmntent, ::endmntent
    #if xTODO_ANDROID
        FILE *file = ::setmntent("/etc/mnttab", "r");
        xTEST_PTR(file);

        for ( ; ; ) {
            const mntent *mountPoint = ::getmntent(file);
            xCHECK_DO(mountPoint == xPTR_NULL, break);

            bool_t bRv = StringCI::compare(path(), mountPoint->mnt_dir);
            xCHECK_DO(!bRv, continue);

            sRv = (mountPoint->mnt_type == xPTR_NULL) ? Const::strEmpty() : mountPoint->mnt_type;

            break;
        }

        int_t iRv = ::endmntent(file);  file = xPTR_NULL;
        xTEST_EQ(iRv, 1);
    #endif
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Volume::_mount_impl(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    int_t iRv = ::mount(path().c_str(), a_destPath.c_str(), xPTR_NULL, MS_REMOUNT, xPTR_NULL);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Volume::_unMount_impl(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
#if defined(MNT_DETACH)
    cint_t mntDetach = MNT_DETACH;
#else
    cint_t mntDetach = MNT_FORCE;
#endif

    cint_t flag = a_isForce ? MNT_FORCE : mntDetach;

    int_t iRv = ::umount2(path().c_str(), flag);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE void_t
Volume::_paths_impl(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    std::vec_tstring_t vsRv;

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

    // out
    a_volumePaths->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
