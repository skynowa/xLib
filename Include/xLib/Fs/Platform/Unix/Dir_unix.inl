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
    xCHECK_RET(_dirPath != Const::slash(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_create_impl() const
{
    int_t iRv = ::mkdir(xT2A(_dirPath).c_str(), ACCESSPERMS);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_createSymlink_impl(
	std::ctstring_t &a_dirPathTo
) const
{
	int_t iRv {};

	iRv = ::symlink(_dirPath.c_str(), a_dirPathTo.c_str());
	xTEST_EQ(iRv, 0);
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_remove_impl() const
{
    int_t iRv = ::rmdir(xT2A(_dirPath).c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
bool_t
Dir::_tryRemove_impl() const
{
    int_t iRv = ::rmdir(xT2A(_dirPath).c_str());
    xCHECK_RET(iRv == - 1, false);

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
	std::csize_t _maxSize = maxSize();

    std::string asRv;
    std::string buff(_maxSize + 1, 0);

    const char *pszRv = ::getcwd(&buff[0], _maxSize);
    xTEST_PTR(pszRv);
    xTEST_EQ(pszRv, buff.c_str());

    asRv.assign(pszRv);

    return xA2T(asRv);
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_setCurrent_impl(
    std::ctstring_t &a_dirPath
)
{
    std::tstring_t dirPath = Path(a_dirPath).slashAppend().str();

    int_t iRv = ::chdir(xT2A(dirPath).c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Dir::_temp_impl()
{
    std::ctstring_t envDirTemp = xT("TMPDIR");

    Environment env(envDirTemp);

    return env.isExists() ? env.var() : _dirTmp();
}
//-------------------------------------------------------------------------------------------------

} // namespace
