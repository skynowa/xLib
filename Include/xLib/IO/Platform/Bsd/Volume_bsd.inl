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

    // TODO: Volume::_fileSystem_impl()
    xNOT_IMPLEMENTED

    return sRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Volume::_mount_impl(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    int_t iRv = ::mount(path().c_str(), a_destPath.c_str(), MNT_UPDATE, xPTR_NULL);
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

    int_t iRv = ::unmount(path().c_str(), flag);
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

    // TODO: Volume::_paths_impl()
    xNOT_IMPLEMENTED

    // out
    a_volumePaths->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
