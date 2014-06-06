/**
 * \file  CxDir.inl
 * \brief directory
 */


xNAMESPACE_BEGIN2(xlib, filesystem)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxDir::_isRoot_impl() const
{
    xCHECK_RET(dirPath() != CxConst::slash(), false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::_create_impl() const
{
    int_t iRv = ::mkdir(dirPath().c_str(), S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH);
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::_remove_impl() const
{
    int_t iRv = ::rmdir(dirPath().c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDir::_tryRemove_impl() const
{
    int_t iRv = ::rmdir(dirPath().c_str());
    xCHECK_RET(iRv == - 1, false);

    return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxDir::_current_impl()
{
    std::tstring_t sRv;
    std::tstring_t buff(xPATH_MAX + 1, 0);

    tchar_t *pszRv = ::getcwd(&buff[0], xPATH_MAX);
    xTEST_PTR(pszRv);
    xTEST_EQ(buff.c_str(), const_cast<ctchar_t *>( pszRv ));

    sRv.assign(pszRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::_setCurrent_impl(
    std::ctstring_t &a_dirPath
)
{
    std::tstring_t dirPath = CxPath(a_dirPath).slashAppend();

    int_t iRv = ::chdir(a_dirPath.c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxDir::_temp_impl()
{
    std::tstring_t sRv;

    std::ctstring_t envDirTemp = xT("TMPDIR");

    bool_t bRv = CxEnvironment::isExists(envDirTemp);
    if (bRv) {
        sRv = CxEnvironment::var(envDirTemp);
    } else {
        sRv = xDIR_TEMP;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
