/**
 * \file  String.inl
 * \brief string utils
 */


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::string
String::_castA_impl(
    std::cwstring_t &a_str,     ///< source string
    cuint_t         &a_codePage ///< code page
)
{
    std::string asRv;

    xUNUSED(a_str);
    xUNUSED(a_codePage);

    // TODO: String::castA() - Unix
    xNOT_IMPLEMENTED

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::wstring
String::_castW_impl(
    std::cstring_t &a_str,      ///< source string
    cuint_t        &a_codePage  ///< code page
)
{
    std::wstring wsRv;

    xUNUSED(a_str);
    xUNUSED(a_codePage);

    // TODO: String::castW() - Unix
    xNOT_IMPLEMENTED

    return wsRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::string
String::_castToOem_impl(
    std::ctstring_t &a_str   ///< source string
)
{
    std::string dest;

    xUNUSED(a_str);

    // TODO: String::castToOem()
    xNOT_IMPLEMENTED

    return dest;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
String::_castFromOem_impl(
    std::cstring_t &a_str   ///< source string
)
{
    std::tstring_t dest;

    xUNUSED(a_str);

    // TODO: String::castFromOem()
    xNOT_IMPLEMENTED

    return dest;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
String::_toLowerCase_impl(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t    &a_length   ///< string size
)
{
    std::tstring_t sRv(a_str);

    std::transform(sRv.begin(), sRv.begin() +  static_cast< ::ssize_t >(a_length), sRv.begin(), ToLower( xTLOCALE() ));

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
String::_toUpperCase_impl(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t    &a_length   ///< string size
)
{
    std::tstring_t sRv(a_str);

    std::transform(sRv.begin(), sRv.begin() + static_cast< ::ssize_t >(a_length), sRv.begin(), ToUpper( xTLOCALE() ));

    return sRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)


xNAMESPACE_BEGIN2(xl, core)

/**************************************************************************************************
*   search, compare
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE bool_t
StringCI::_compare_impl(
    std::ctstring_t &a_str1,                    ///< source string
    std::ctstring_t &a_str2,                    ///< target string
    const xTLOCALE   &a_locale /* = xTLOCALE() */ ///< locale
)
{
    bool_t bRv = std::equal(a_str1.begin(), a_str1.end(), a_str2.begin(), CompareCI(a_locale));
    xCHECK_RET(!bRv, false);

    return true;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
