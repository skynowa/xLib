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
Volume::Type
Volume::_type_impl() const
{
    return Type::Fixed;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Volume::_label_impl() const
{
    std::tstring_t sRv;

    // REVIEW: just get the dir name ??
    if (path() == Const::unixSlash()) {
        sRv = Const::unixSlash();
    } else {
        sRv = Path( path() ).fileName();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
bool_t
Volume::_isValid_impl() const
{
    xCHECK_RET(path().empty(),                       false);
    xCHECK_RET(path().at(0) != Const::slash().at(0), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
bool_t
Volume::_isReady_impl() const
{
    bool_t         bRv {};
    std::tstring_t volumeDirPath = Path( path() ).slashAppend().str();
    std::tstring_t dirPathOld;

    dirPathOld = Dir::current().str();
    xTEST_NA(dirPathOld);

    int_t iRv = ::chdir(xT2A(volumeDirPath).c_str());
    xTEST_NA(iRv);
    bRv = (iRv != - 1);

    Dir::setCurrent(dirPathOld);

    return bRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

#if 1
	// Fs
	#include <sys/param.h>
	#include <sys/mount.h>
#endif
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Volume::_space_impl(
    std::ctstring_t &a_dirPath,          ///< directory path
    ulonglong_t*    &a_totalBytes,       ///< total space
    ulonglong_t*    &a_availableBytes,   ///< available space (for unprivileged users)
    ulonglong_t*    &a_freeBytes         ///< free space
)
{
    struct xSTATVFS info {};

    int_t iRv = xSTATVFS(xT2A(a_dirPath).c_str(), &info);
    xTEST_DIFF(iRv, - 1);

    Utils::ptrAssignT(a_totalBytes,
    	static_cast<ulonglong_t>( info.f_blocks * static_cast<ulonglong_t>(info.f_bsize) ));
    Utils::ptrAssignT(a_availableBytes,
    	static_cast<ulonglong_t>( info.f_bavail * static_cast<ulonglong_t>(info.f_bsize) ));
    Utils::ptrAssignT(a_freeBytes,
    	static_cast<ulonglong_t>( info.f_bfree  * static_cast<ulonglong_t>(info.f_bsize) ));
}
//-------------------------------------------------------------------------------------------------

} // namespace
