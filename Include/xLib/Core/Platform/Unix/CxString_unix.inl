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

    xUNUSED(a_str);
    xUNUSED(a_codePage);

    // TODO: CxString::castA() - Unix
    xNOT_IMPLEMENTED;

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
    std::wstring wsRv;

    xUNUSED(a_str);
    xUNUSED(a_codePage);

    // TODO: CxString::castW() - Unix
    xNOT_IMPLEMENTED;

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

    xUNUSED(a_str);

    // TODO: CxString::castToOem()
    xNOT_IMPLEMENTED;

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

    xUNUSED(a_str);

    // TODO: CxString::castFromOem()
    xNOT_IMPLEMENTED;

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

    std::transform(sRv.begin(), sRv.begin() + a_length, sRv.begin(), functors::ToLower( std::locale() ));

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

    std::transform(sRv.begin(), sRv.begin() + a_length, sRv.begin(), functors::ToUpper( std::locale() ));

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
    bool_t bRv = std::equal(a_str1.begin(), a_str1.end(), a_str2.begin(),
        functors::CompareCI(a_locale));
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
