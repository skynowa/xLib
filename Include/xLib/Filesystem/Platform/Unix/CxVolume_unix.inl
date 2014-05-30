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

xNAMESPACE_END2(xlib, filesystem)
