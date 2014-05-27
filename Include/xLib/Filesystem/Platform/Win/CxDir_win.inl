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
    xCHECK_RET(3 != dirPath().size(), false);

    bool_t bRv1 = CxChar::isAlpha(dirPath().at(0));
    bool_t bRv2 = (dirPath().at(1) == CxConst::colon().at(0));
    bool_t bRv3 = (dirPath().at(2) == CxConst::winSlash().at(0) ||
                   dirPath().at(2) == CxConst::unixSlash().at(0));

    xCHECK_RET(!bRv1 || !bRv2 || !bRv3, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::_create_impl() const
{
    BOOL blRv = ::CreateDirectory(dirPath().c_str(), xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::_remove_impl() const
{
    BOOL blRv = ::RemoveDirectory(dirPath().c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
CxDir::_tryRemove_impl() const
{
    BOOL blRv = ::RemoveDirectory(dirPath().c_str());
    xCHECK_RET(blRv == FALSE, false);

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

    DWORD ulRv = ::GetCurrentDirectory(static_cast<DWORD>( xPATH_MAX ), &buff[0]);
    xTEST_DIFF(ulRv, 0UL);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(buff, 0, ulRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxDir::_setCurrent_impl(
    std::ctstring_t &a_dirPath
)
{
    std::tstring_t dirPath = CxPath(a_dirPath).slashAppend();

    BOOL blRv = ::SetCurrentDirectory(dirPath.c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxDir::_temp_impl()
{
    std::tstring_t sRv;

    std::tstring_t buff(xPATH_MAX + 1, 0);

    DWORD ulRv = ::GetTempPath(static_cast<DWORD>( xPATH_MAX ), &buff[0]);
    xTEST_DIFF(ulRv, 0UL);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(buff, 0, ulRv);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, filesystem)
