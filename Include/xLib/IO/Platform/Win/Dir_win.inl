/**
 * \file  Dir.inl
 * \brief directory
 */


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
Dir::_isRoot_impl() const
{
    xCHECK_RET(3 != dirPath().size(), false);

    bool_t bRv1 = Char::isAlpha(dirPath().at(0));
    bool_t bRv2 = (dirPath().at(1) == Const::colon().at(0));
    bool_t bRv3 = (dirPath().at(2) == Const::winSlash().at(0) ||
                   dirPath().at(2) == Const::unixSlash().at(0));

    xCHECK_RET(!bRv1 || !bRv2 || !bRv3, false);

    return true;
}
//-------------------------------------------------------------------------------------------------
inline void_t
Dir::_create_impl() const
{
    BOOL blRv = ::CreateDirectory(dirPath().c_str(), xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
Dir::_remove_impl() const
{
    BOOL blRv = ::RemoveDirectory(dirPath().c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline bool_t
Dir::_tryRemove_impl() const
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
Dir::_current_impl()
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
Dir::_setCurrent_impl(
    std::ctstring_t &a_dirPath
)
{
    std::tstring_t dirPath = Path(a_dirPath).slashAppend();

    BOOL blRv = ::SetCurrentDirectory(dirPath.c_str());
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
Dir::_temp_impl()
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

xNAMESPACE_END2(xlib, io)
