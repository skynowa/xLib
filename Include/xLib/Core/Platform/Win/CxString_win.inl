/**
 * \file  CxString.inl
 * \brief string utils
 */


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::_castA_impl(
    std::cwstring_t &a_str,     ///< source string
    cuint_t         &a_codePage ///< code page
)
{
    std::string asRv;

    int_t size = ::WideCharToMultiByte(a_codePage, 0UL, a_str.c_str(), - 1, xPTR_NULL, 0, xPTR_NULL, xPTR_NULL);
    xTEST_LESS(0, size);

    asRv.resize(size - 1);    // remove '\0'
    size = ::WideCharToMultiByte(a_codePage, 0UL, a_str.c_str(), - 1,
        static_cast<LPSTR>(&asRv.at(0)), size, xPTR_NULL, xPTR_NULL);
    xTEST_LESS(0, size);

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::wstring
CxString::_castW_impl(
    std::cstring_t &a_str,      ///< source string
    cuint_t        &a_codePage  ///< code page
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    std::wstring wsRv;

    int_t size = ::MultiByteToWideChar(a_codePage, 0UL, a_str.c_str(), - 1, xPTR_NULL, 0);
    xTEST_LESS(0, size);

    wsRv.resize(size - 1);    // remove '\0'
    size = ::MultiByteToWideChar(a_codePage, 0UL, a_str.c_str(), - 1,
        static_cast<LPWSTR>(&wsRv.at(0)), size);
    xTEST_LESS(0, size);

    return wsRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::_castToOem_impl(
    std::ctstring_t &a_str   ///< source string
)
{
    std::string dest;

    dest.resize(a_str.size());

    BOOL blRv = ::CharToOemBuff(a_str.c_str(), &dest.at(0), static_cast<DWORD>( dest.size() ));
    xTEST_DIFF(blRv, FALSE);

    return dest;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::_castFromOem_impl(
    std::cstring_t &a_str   ///< source string
)
{
    std::tstring_t dest;

    dest.resize(a_str.size());

    BOOL blRv = ::OemToCharBuff(a_str.c_str(), &dest.at(0), static_cast<DWORD>( dest.size() ));
    xTEST_DIFF(blRv, FALSE);

    return dest;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::_toLowerCase_impl(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t    &a_length   ///< string size
)
{
    std::tstring_t sRv(a_str);

    DWORD dwRv = ::CharLowerBuff(static_cast<LPTSTR>( &sRv[0] ), static_cast<DWORD>( a_length ));
    xTEST_EQ(a_length, static_cast<size_t>( dwRv ));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::_toUpperCase_impl(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t    &a_length   ///< string size
)
{
    std::tstring_t sRv(a_str);

    DWORD dwRv = ::CharUpperBuff(static_cast<LPTSTR>( &sRv[0] ), static_cast<DWORD>( a_length ));
    xTEST_EQ(a_length, static_cast<size_t>( dwRv ));

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*   search, compare
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxStringCI::_compare_impl(
    std::ctstring_t   &a_str1,                          ///< source string
    std::ctstring_t   &a_str2,                          ///< target string
    const std::locale &a_locale /* = std::locale() */   ///< locale
)
{
    int_t iRv = ::lstrcmpi(a_str1.c_str(), a_str2.c_str());
    xCHECK_RET(0 != iRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
