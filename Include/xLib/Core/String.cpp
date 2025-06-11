/**
 * \file  String.cpp
 * \brief string utils
 */


#include "String.h"

#include <xLib/Core/Units.h>
#include <xLib/Core/Functors.h>
#include <xLib/Core/Utils.h>
#include <xLib/Core/Const.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/LogStream.h>

#if   xENV_WIN
    #include "Platform/Win/String_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/String_unix.inl"
#endif


namespace xl::core
{

/**************************************************************************************************
*   casting
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::string
String::castA(
    std::cwstring_t &a_str  ///< source string
)
{
    xTEST_NA(a_str);

    std::string asRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(asRv), Narrow( std::locale() ));

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::wstring
String::castW(
    std::cstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    std::wstring wsRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(wsRv), Widen( std::locale() ));

    return wsRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::string
String::castA(
    std::cwstring_t &a_str,     ///< source string
    cuint_t          a_codePage ///< code page
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    return _castA_impl(a_str, a_codePage);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::wstring
String::castW(
    std::cstring_t &a_str,      ///< source string
    cuint_t         a_codePage  ///< code page
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    return _castW_impl(a_str, a_codePage);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::string
String::castA(
    std::cwstring_t   &a_str,   ///< source string
    const std::locale &a_locale ///< locale
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_locale);
    xSTD_VERIFY(std::has_facet<std::ctype<wchar_t> >(a_locale));
    xSTD_VERIFY(std::has_facet<std::ctype<char> >(a_locale));

    xCHECK_RET(a_str.empty(),                                   std::string());
    xCHECK_RET(!std::has_facet<std::ctype<wchar_t> >(a_locale), std::string());
    xCHECK_RET(!std::has_facet<std::ctype<char> >(a_locale),    std::string());

    using state_type_t = std::wstring::traits_type::state_type;
    using codecvt_t    = std::codecvt<wchar_t, char, state_type_t>;

    std::string      asRv(a_str.size(), std::wstring::value_type());

    const codecvt_t &codec     = std::use_facet<codecvt_t>( a_locale );
    state_type_t     state {};

    cptr_cwchar_t    itBegin   = &a_str.at(0);
    cptr_cwchar_t    itEnd     = &a_str.at(0) + a_str.size();
    const wchar_t   *itNext    = nullptr;

    char            *itToBegin = &asRv.at(0);
    char            *itToEnd   = &asRv.at(0) + asRv.size();
    char            *itToNext  = nullptr;

    codec.out(state, itBegin, itEnd, itNext, itToBegin, itToEnd, itToNext);

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::wstring
String::castW(
    std::cstring_t    &a_str,   ///< source string
    const std::locale &a_locale ///< locale
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_locale);
    xSTD_VERIFY(std::has_facet<std::ctype<std::wstring::value_type>>(a_locale));

    xCHECK_RET(a_str.empty(),                                                   std::wstring());
    xCHECK_RET(!std::has_facet<std::ctype<std::wstring::value_type>>(a_locale), std::wstring());

    std::wstring swRv(a_str.size(), std::wstring::value_type());

    auto itBegin   = a_str.cbegin();
    auto itEnd     = a_str.cend();
    auto itToBegin = swRv.begin();

    for ( ; itBegin != itEnd; ++ itBegin, ++ itToBegin) {
        *itToBegin = std::use_facet<std::ctype<wchar_t>>( a_locale ).widen(*itBegin);
    }

    return swRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::string
String::castCodePage(
    std::cstring_t &a_str,              ///< source string
    cuint_t         a_codePageSource,   ///< source code page
    cuint_t         a_codePageDest      ///< destination code page
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePageSource);
    xTEST_NA(a_codePageDest);

    return castA(castW(a_str, a_codePageSource), a_codePageDest);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::string
String::castToOem(
    std::ctstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    return _castToOem_impl(a_str);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::castFromOem(
    std::cstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    return _castFromOem_impl(a_str);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::castBool(
    cbool_t a_value   ///< source string
)
{
    xTEST_NA(a_value);

    return (!a_value) ? xT("false") : xT("true");
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
String::castBool(
    std::ctstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    xCHECK_RET(StringCI::compare(xT("true"),  a_str), true);
    xCHECK_RET(StringCI::compare(xT("false"), a_str), false);

    return false;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::toLowerCase(
    std::ctstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    return toLowerCase(a_str, a_str.size());
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::toUpperCase(
    std::ctstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    return toUpperCase(a_str, a_str.size());
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::toLowerCase(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t     a_length   ///< string size
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_length);

    size_t length = a_length;

    xCHECK_RET(a_str.empty(),         std::tstring_t());
    xCHECK_DO (a_str.size() < length, length = a_str.size());

    return _toLowerCase_impl(a_str, length);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::toUpperCase(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t     a_length   ///< string size
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_length);

    size_t length = a_length;

    xCHECK_RET(a_str.empty(),         std::tstring_t());
    xCHECK_DO (a_str.size() < length, length = a_str.size());

    return _toUpperCase_impl(a_str, length);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::trimLeftChars(
    std::ctstring_t &a_str,     ///< source string
    std::ctstring_t &a_chars    ///< chars for trim
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_chars);

    std::tstring_t sRv(a_str);

    const std::tstring_t::size_type pos = sRv.find_first_not_of(a_chars);
    if (pos == std::tstring_t::npos) {
        sRv.erase();
        return sRv;
    }

    sRv.erase(0, pos);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::trimRightChars(
    std::ctstring_t &a_str,    ///< source string
    std::ctstring_t &a_chars   ///< chars for trim
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_chars);

    std::tstring_t sRv(a_str);

    const std::tstring_t::size_type pos = sRv.find_last_not_of(a_chars);
    if (pos == std::tstring_t::npos) {
        sRv.erase();
        return sRv;
    }

    sRv.erase(pos + 1);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::trimChars(
    std::ctstring_t &a_str,    ///< source string
    std::ctstring_t &a_chars   ///< chars for trim
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_chars);

    std::tstring_t sRv(a_str);

    sRv = trimRightChars(sRv, a_chars);
    sRv = trimLeftChars (sRv, a_chars);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::trimSpace(
    std::ctstring_t &a_str    ///< source string
)
{
    xTEST_NA(a_str);

    return trimChars(a_str, Const::whiteSpaces());
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::removeEol(
    std::ctstring_t &a_str    ///< source string
)
{
    xTEST_NA(a_str);

    return trimRightChars(a_str, Const::eol());
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::quoted(
    std::ctstring_t &a_str,                         ///< source string
    ctchar_t         a_delimiter /* = xT('\"') */,  ///< delimiter
    ctchar_t         a_escape    /* = xT('\\') */   ///< escape
)
{
    std::tstring_t sRv;

    sRv = a_delimiter;

    for (const auto &it : a_str) {
        if (it == a_delimiter ||
            it == a_escape)
        {
            sRv += a_escape;
        }

        sRv += it;
    }

    sRv += a_delimiter;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::replaceAll(
    std::ctstring_t &a_str,     ///< source string
    std::ctstring_t &a_strOld,  ///< old string
    std::ctstring_t &a_strNew   ///< new string
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_strOld);
    xTEST_NA(a_strNew);

    xCHECK_RET(a_str.empty(),    a_str);
    xCHECK_RET(a_strOld.empty(), a_str);

    std::tstring_t sRv(a_str);

    size_t pos = 0U;

    for ( ; ; ) {
        pos = sRv.find(a_strOld, pos);
        xCHECK_DO(pos == std::tstring_t::npos, break);

        sRv.replace(pos, a_strOld.size(), a_strNew);

        pos += a_strNew.size();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::replaceAll(
    std::ctstring_t &a_str,     ///< source string
    ctchar_t        &a_charOld, ///< old char
    ctchar_t        &a_charNew  ///< new char
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_charOld);
    xTEST_NA(a_charNew);

    return replaceAll(a_str, std::tstring_t(1, a_charOld), std::tstring_t(1, a_charNew));
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::removeAll(
    std::ctstring_t &a_str,         ///< source string
    std::ctstring_t &a_removeStr    ///< string for remove
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_removeStr);

    return replaceAll(a_str, a_removeStr, std::tstring_t());
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
String::split(
    std::ctstring_t    &a_str,  ///< source string
    std::ctstring_t    &a_sep,  ///< separator
    std::vec_tstring_t *a_rv    ///< [out] string vector
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sep);
    xTEST_NA(a_rv);

    xCHECK_DO(a_rv != nullptr, a_rv->clear());

    xCHECK_DO(a_str.empty(), return);
    xCHECK_DO(a_sep.empty(), return);
    xTEST_PTR(a_rv);

    std::vec_tstring_t vsRv;
    std::size_t        posPrev = 0U;    // start of string

    for ( ; ; ) {
        std::csize_t pos = a_str.find(a_sep, posPrev);
        xCHECK_DO(pos == std::tstring_t::npos, break);

        vsRv.push_back(a_str.substr(posPrev, pos - posPrev));

        posPrev = pos + a_sep.size();
    }

    vsRv.push_back( a_str.substr(posPrev, a_str.size() - posPrev) );

    // out
    a_rv->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::join(
    std::cvec_tstring_t &a_vec, ///< source string vector
    std::ctstring_t     &a_sep  ///< separator
)
{
    xTEST_NA(a_vec);
    xTEST_NA(a_sep);

    std::tstring_t sRv;

    for (auto it = a_vec.cbegin(); it != a_vec.cend();  ++ it) {
        sRv.append(*it);

        xCHECK_DO(it < a_vec.end() - 1, sRv.append(a_sep));
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::join(
    std::cvec_tstring_t &a_vec, ///< source string vector
    ctchar_t            &a_sep  ///< separator
)
{
    xTEST_NA(a_vec);
    xTEST_NA(a_sep);

    return join(a_vec, std::ctstring_t(1, a_sep));
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::cut(
    std::ctstring_t &a_str,      ///< source string
    std::ctstring_t &a_sepLeft, ///< left separator
    std::ctstring_t &a_sepRight ///< right separator
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sepLeft);
    xTEST_NA(a_sepRight);

    size_t delimPosStart = a_str.find(a_sepLeft);
    xCHECK_RET(delimPosStart == std::tstring_t::npos, std::tstring_t());

    delimPosStart += a_sepLeft.size();

    size_t delimPosStop = a_str.find(a_sepRight, delimPosStart);
    xCHECK_RET(delimPosStop == std::tstring_t::npos, std::tstring_t());
    xCHECK_RET(delimPosStart >= delimPosStop,        std::tstring_t());

    return a_str.substr(delimPosStart, delimPosStop - delimPosStart);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::rcut(
    std::ctstring_t &a_str,     ///< source string
    std::ctstring_t &a_sepLeft, ///< left separator
    std::ctstring_t &a_sepRight ///< right separator
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sepLeft);
    xTEST_NA(a_sepRight);

    size_t delimPosStart = a_str.find(a_sepLeft);
    xCHECK_RET(delimPosStart == std::tstring_t::npos, std::tstring_t());

    delimPosStart += a_sepLeft.size();

    size_t delimPosStop  = a_str.rfind(a_sepRight);
    xCHECK_RET(delimPosStop == std::tstring_t::npos, std::tstring_t());
    xCHECK_RET(delimPosStart >= delimPosStop,        std::tstring_t());

    return a_str.substr(delimPosStart, delimPosStop - delimPosStart);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::cut(
    std::ctstring_t &a_str,                                  ///< source string
    std::csize_t     a_posBegin,                             ///< begin position
    std::csize_t     a_posEnd   /* = std::tstring_t::npos */ ///< end position
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_posBegin);
    xTEST_NA(a_posEnd);

    xCHECK_RET(a_str.empty(),         std::tstring_t());
    xCHECK_RET(a_posBegin > a_posEnd, std::tstring_t());

    size_t size = std::tstring_t::npos;

    if (a_posEnd == std::tstring_t::npos) {
        size = a_posEnd;
    } else {
        size = a_posEnd - a_posBegin;
    }

    return a_str.substr(a_posBegin, size);
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::minimize(
    std::ctstring_t &a_str,         ///< source string
    std::csize_t     a_maxLength    ///< string maximum size
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_maxLength);

    xCHECK_RET(a_str.empty(),     std::tstring_t());
    xCHECK_RET(a_maxLength == 0U, std::tstring_t());

    std::tstring_t sRv;

    if (a_str.size() > a_maxLength) {
        if (a_maxLength < Const::dot3().size()) {
            sRv = a_str.substr(0U, a_maxLength);
        } else {
            sRv = a_str.substr(0U, a_maxLength - Const::dot3().size()) + Const::dot3();
        }
    } else {
        sRv = a_str;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    formating
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::formatBytes(
    culonglong_t &a_bytes    ///< bytes
)
{
    xTEST_NA(a_bytes);

    std::tstring_t sRv = Const::strUnknown();

    culonglong_t eb   = xEB(1);
    culonglong_t pb   = xPB(1);
    culonglong_t tb   = xTB(1);
    culonglong_t gb   = xGB(1);
    culonglong_t mb   = xMB(1);
    culonglong_t kb   = xKB(1);
    culonglong_t byte = xBYTES(1);


    if (     a_bytes / eb > 0ULL) {
        sRv = FormatC::str(xT("%.2f EB"), static_cast<double>(a_bytes) / static_cast<double>(eb));
    }
    else if (a_bytes / pb > 0ULL) {
        sRv = FormatC::str(xT("%.2f PB"), static_cast<double>(a_bytes) / static_cast<double>(pb));
    }
    else if (a_bytes / tb > 0ULL) {
        sRv = FormatC::str(xT("%.2f TB"), static_cast<double>(a_bytes) / static_cast<double>(tb));
    }
    else if (a_bytes / gb > 0ULL) {
        sRv = FormatC::str(xT("%.2f GB"), static_cast<double>(a_bytes) / static_cast<double>(gb));
    }
    else if (a_bytes / mb > 0ULL) {
        sRv = FormatC::str(xT("%.2f MB"), static_cast<double>(a_bytes) / static_cast<double>(mb));
    }
    else if (a_bytes / kb > 0ULL) {
        sRv = FormatC::str(xT("%.2f KB"), static_cast<double>(a_bytes) / static_cast<double>(kb));
    }
    else if (a_bytes / byte > 0ULL) {
        sRv = FormatC::str(xT("%.2f Byte(s)"), static_cast<double>(a_bytes) / static_cast<double>(byte));
    }
    else {
        sRv = FormatC::str(xT("%.2f Bit(s)"), static_cast<double>(a_bytes));
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
String::formatPercentage(
    culonglong_t &a_maxValue,       ///< maximum value
    culonglong_t &a_currentValue    ///< current value
)
{
    xTEST_NA(a_maxValue);
    xTEST_NA(a_currentValue);

    xCHECK_RET(a_maxValue == 0ULL, xT("0%")); // devision by zero

    std::tstring_t sRv;

    sRv = cast( a_currentValue * 100ULL / a_maxValue );
    xCHECK_RET(sRv.empty(), xT("0%"));

    sRv.append(xT("%"));

    return sRv;
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    memory
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t *
String::memoryZeroSecure(
    void_t       *a_buff,       ///< buffer
    std::csize_t  a_buffSize    ///< buffer size (bytes)
)
{
    xTEST_NA(a_buff);
    xTEST_NA(a_buffSize);

    size_t buffSize = a_buffSize;

    for (volatile uchar_t *buff = static_cast<volatile uchar_t *>( a_buff );
         a_buff != nullptr && 0 != buffSize;
         ++ buff, -- buffSize)
    {
        *buff = 0;
    }

    return a_buff;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    other
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
bool_t
String::isRepeated(
    std::ctstring_t &a_str    ///< source string
)
{
    xTEST_NA(a_str);

    return ( std::tstring_t::npos == a_str.find_first_not_of(a_str.at(0)) );
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
std::size_t
StringCI::find(
    std::ctstring_t &a_str,                      ///< source string
    std::ctstring_t &a_target,                   ///< target string
    std::csize_t     a_pos    /* = 0 */,         ///< start position
    const xTLOCALE  &a_locale /* = xTLOCALE() */ ///< locale
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_target);
    xTEST_NA(a_pos);

    xCHECK_RET(a_str.empty() && a_target.empty() && a_pos == 0U, 0U);
    xCHECK_RET(a_target.empty(),                                 0U);

    auto cit = std::search(
        a_str.cbegin() + static_cast<std::ssize_t>(a_pos), a_str.cend(),
        a_target.cbegin(), a_target.cend(), CompareCI(a_locale));
    xCHECK_RET(cit != a_str.cend(), static_cast<std::size_t >(cit - a_str.cbegin()));

    return std::tstring_t::npos;
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
StringCI::contains(
    std::ctstring_t &a_str,                      ///< source string
    std::ctstring_t &a_target,                   ///< target string
    std::csize_t     a_pos    /* = 0 */,         ///< start position
    const xTLOCALE  &a_locale /* = xTLOCALE() */ ///< locale
)
{
    return (find(a_str, a_target, a_pos, a_locale) != std::tstring_t::npos);
}
//-------------------------------------------------------------------------------------------------
/* static */
bool_t
StringCI::compare(
    std::ctstring_t &a_str1,                     ///< source string
    std::ctstring_t &a_str2,                     ///< target string
    const xTLOCALE  &a_locale /* = xTLOCALE() */ ///< locale
)
{
    xTEST_NA(a_str1);
    xTEST_NA(a_str2);

    xCHECK_RET(a_str1.size() != a_str2.size(), false);

    return _compare_impl(a_str1, a_str2, a_locale);
}
//-------------------------------------------------------------------------------------------------

} // namespace
