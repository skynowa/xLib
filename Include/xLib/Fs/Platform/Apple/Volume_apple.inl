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

    // TODO: [skynowa] Volume::_fileSystem_impl()
    xTRACE_NOT_IMPLEMENTED

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Volume::_mount_impl(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
    // TODO: [skynowa] Volume::_mount_impl()
    xTRACE_NOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
void_t
Volume::_unMount_impl(
    cbool_t a_isForce     ///< force unmount even if busy
) const
{
    // TODO: [skynowa] Volume::_unMount_impl()
    xTRACE_NOT_IMPLEMENTED
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
    // TODO: [skynowa] Volume::_paths_impl()
    xTRACE_NOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------

} // namespace
