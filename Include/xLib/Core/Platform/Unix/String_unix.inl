/**
 * \file  String.inl
 * \brief string utils
 */


namespace xl::core
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::string
String::_castA_impl(
    std::cwstring_t &a_str,     ///< source string
    cuint_t          a_codePage ///< code page
)
{
    std::string asRv;

    xUNUSED(a_str);
    xUNUSED(a_codePage);

    // TODO: [skynowa] String::castA() - Unix
    xTRACE_NOT_IMPLEMENTED

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::wstring
String::_castW_impl(
    std::cstring_t &a_str,      ///< source string
    cuint_t         a_codePage  ///< code page
)
{
    std::wstring wsRv;

    xUNUSED(a_str);
    xUNUSED(a_codePage);

    // TODO: [skynowa] String::castW() - Unix
    xTRACE_NOT_IMPLEMENTED

    return wsRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::string
String::_castToOem_impl(
    std::ctstring_t &a_str   ///< source string
)
{
    std::string dest;

    xUNUSED(a_str);

    // TODO: [skynowa] String::castToOem()
    xTRACE_NOT_IMPLEMENTED

    return dest;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::_castFromOem_impl(
    std::cstring_t &a_str   ///< source string
)
{
    std::tstring_t dest;

    xUNUSED(a_str);

    // TODO: [skynowa] String::castFromOem()
    xTRACE_NOT_IMPLEMENTED

    return dest;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::_toLowerCase_impl(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t     a_length   ///< string size
)
{
    std::tstring_t sRv(a_str);

    std::transform(sRv.begin(), sRv.begin() +  static_cast<::ssize_t>(a_length), sRv.begin(), ToLower( xTLOCALE() ));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::_toUpperCase_impl(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t     a_length   ///< string size
)
{
    std::tstring_t sRv(a_str);

    std::transform(sRv.begin(), sRv.begin() + static_cast<::ssize_t>(a_length), sRv.begin(), ToUpper( xTLOCALE() ));

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace


namespace xl::core
{

/**************************************************************************************************
*   search, compare
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
StringCI::_compare_impl(
    std::ctstring_t &a_str1,                    ///< source string
    std::ctstring_t &a_str2,                    ///< target string
    const xTLOCALE   &a_locale /* = xTLOCALE() */ ///< locale
)
{
    bool_t bRv = std::equal(a_str1.cbegin(), a_str1.cend(), a_str2.cbegin(), CompareCI(a_locale));
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

} // namespace
