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

#if xENV_BSD
    // TODO: CxVolume::fileSystem()
    xNOT_IMPLEMENTED
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxVolume::_mount_impl(
    std::ctstring_t &a_destPath    ///< destination path
) const
{
#if xENV_BSD
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

#if xENV_BSD
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
CxVolume::_paths_impl(
    std::vec_tstring_t *a_volumePaths    ///< volume paths
)
{
    std::vec_tstring_t vsRv;

#if xENV_BSD
    // TODO: CxVolume::paths()
#endif

    // out
    a_volumePaths->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
