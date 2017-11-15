/**
 * \file  Volume.inl
 * \brief volume
 */


xNAMESPACE_BEGIN2(xl, fs)

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
    // TODO: Volume::_mount_impl()
    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Volume::_unMount_impl(
    cbool_t &a_isForce     ///< force unmount even if busy
) const
{
    // TODO: Volume::_unMount_impl()
    xNOT_IMPLEMENTED
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
    // TODO: Volume::_paths_impl()
    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
