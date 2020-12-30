/**
 * \file  Volume.inl
 * \brief volume
 */


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Volume::_fileSystem_impl() const
{
    std::tstring_t sRv;

#if cmHAVE_GETMNTENT_R
    FILE *file = ::setmntent("/etc/mtab", "r");
    xTEST_PTR(file);

    for ( ; ; ) {
        mntent mnt {};
        constexpr int_t buffLen       {4096 + 1};
        char            buff[buffLen] {};

        const mntent *mountPoint = ::getmntent_r(file, &mnt, buff, buffLen);
        xCHECK_DO(mountPoint == nullptr, break);

        bool_t bRv = StringCI::compare(path(), xA2T(mountPoint->mnt_dir));
        xCHECK_DO(!bRv, continue);

        sRv = (mountPoint->mnt_type == nullptr) ? Const::strEmpty() : xA2T(mountPoint->mnt_type);

        break;
    }

    int_t iRv = ::endmntent(file);  file = nullptr;
    xTEST_EQ(iRv, 1);
#else
    // ANDROID: ::setmntent, ::endmntent
    #if xTODO_ANDROID
        FILE *file = ::setmntent("/etc/mnttab", "r");
        xTEST_PTR(file);

        for ( ; ; ) {
            const mntent *mountPoint = ::getmntent(file);
            xCHECK_DO(mountPoint == nullptr, break);

            bool_t bRv = StringCI::compare(path(), mountPoint->mnt_dir);
            xCHECK_DO(!bRv, continue);

            sRv = (mountPoint->mnt_type == nullptr) ? Const::strEmpty() : mountPoint->mnt_type;

            break;
        }

        int_t iRv = ::endmntent(file);  file = nullptr;
        xTEST_EQ(iRv, 1);
    #endif
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Volume::_mount_impl(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    int_t iRv = ::mount(xT2A(path()).c_str(), xT2A(a_destPath).c_str(), nullptr, MS_REMOUNT, nullptr);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
Volume::_unMount_impl(
    cbool_t a_isForce     ///< force unmount even if busy
) const
{
	cint_t mntDetach =
	#if defined(MNT_DETACH)
		MNT_DETACH;
	#else
		MNT_FORCE;
	#endif

    cint_t flag = a_isForce ? MNT_FORCE : mntDetach;

    int_t iRv = ::umount2(xT2A(path()).c_str(), flag);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
void_t
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
        int_t          dump {};
        int_t          pass {};
    };

    std::tifstream_t procMounts(xT("/proc/mounts"));
    xTEST(procMounts.good());

    for ( ; !procMounts.eof(); ) {
        _Mounts mounts;
        procMounts
			>> mounts.device  >> mounts.destination >> mounts.fsType
			>> mounts.options >> mounts.dump        >> mounts.pass;
        xCHECK_DO(mounts.device.empty(), continue);

        vsRv.push_back(mounts.destination);
    }

    // out
    a_volumePaths->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------

} // namespace
