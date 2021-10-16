/**
 * \file  Dir.inl
 * \brief directory
 */


namespace xl::fs
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Dir::_isRoot_impl() const
{
    xCHECK_RET(3 != _dirPath.size(), false);

    bool_t bRv1 = Char(_dirPath.at(0)).isAlpha();
    bool_t bRv2 = (_dirPath.at(1) == Const::colon().at(0));
    bool_t bRv3 = (_dirPath.at(2) == Const::winSlash().at(0) ||
                   _dirPath.at(2) == Const::unixSlash().at(0));

    xCHECK_RET(!bRv1 || !bRv2 || !bRv3, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_create_impl() const
{
    BOOL blRv = ::CreateDirectory(_dirPath.c_str(), nullptr);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_createSymlink_impl(
	std::ctstring_t &a_dirPathTo
) const
{
	BOOL bRv {};

	DWORD flags {SYMBOLIC_LINK_FLAG_DIRECTORY};
	bRv = ::CreateSymbolicLink(_dirPath.c_str(), a_dirPathTo.c_str(), flags);
	xTEST_DIFF(bRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_remove_impl() const
{
    BOOL blRv = ::RemoveDirectory(_dirPath.c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
bool_t
Dir::_tryRemove_impl() const
{
    BOOL blRv = ::RemoveDirectory(_dirPath.c_str());
    xCHECK_RET(blRv == FALSE, false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Dir::_current_impl()
{
    std::tstring_t sRv;

	std::csize_t   _maxSize = Path::maxSize();
    std::tstring_t buff(_maxSize + 1, 0);

    DWORD ulRv = ::GetCurrentDirectory(static_cast<DWORD>(_maxSize), &buff[0]);
    xTEST_DIFF(ulRv, 0UL);
    xTEST_LESS(ulRv, static_cast<ulong_t>(_maxSize));

    sRv.assign(buff, 0, ulRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_setCurrent_impl(
    std::ctstring_t &a_dirPath
)
{
    std::tstring_t dirPath = Path(a_dirPath).slashAppend().str();

    BOOL blRv = ::SetCurrentDirectory(dirPath.c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Dir::_temp_impl()
{
    std::tstring_t sRv;

    std::csize_t   _maxSize = Path::maxSize();
    std::tstring_t buff(_maxSize + 1, 0);

    DWORD ulRv = ::GetTempPath(static_cast<DWORD>(_maxSize), &buff[0]);
    xTEST_DIFF(ulRv, 0UL);
    xTEST_LESS(ulRv, static_cast<ulong_t>(_maxSize));

    sRv.assign(buff, 0, ulRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
