/**
 * \file  Dir.inl
 * \brief directory
 */


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Dir::_isRoot_impl() const
{
    xCHECK_RET(dirPath() != Const::slash(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_create_impl() const
{
    int_t iRv = ::mkdir(xT2A(dirPath()).c_str(), ACCESSPERMS);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
Dir::_remove_impl() const
{
    int_t iRv = ::rmdir(xT2A(dirPath()).c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
bool_t
Dir::_tryRemove_impl() const
{
    int_t iRv = ::rmdir(xT2A(dirPath()).c_str());
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
    std::string asRv;
    std::string buff(xPATH_MAX + 1, 0);

    const char *pszRv = ::getcwd(&buff[0], xPATH_MAX);
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
    std::tstring_t dirPath = Path(a_dirPath).slashAppend();

    int_t iRv = ::chdir(xT2A(a_dirPath).c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Dir::_temp_impl()
{
    std::tstring_t sRv;

    std::ctstring_t envDirTemp = xT("TMPDIR");

    bool_t bRv = Environment::isExists(envDirTemp);
    if (bRv) {
        sRv = Environment::var(envDirTemp);
    } else {
        sRv = xDIR_TEMP;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
