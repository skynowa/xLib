/**
 * \file  CxString.inl
 * \brief string utils
 */


#include <xLib/Core/xUnits.h>
#include <xLib/Core/xFunctors.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxArray.h>
#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>
#include <xLib/Debug/xStdDebug.h>

#if   xENV_WIN
    #include "Platform/Win/CxString_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxString_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxString_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxString_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, core)

/*******************************************************************************
*   casting
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
CxString::cast(
    const T &a_value    ///< source value
)
{
    xTEST_NA(a_value);

    std::tstring_t sRv;

    try {
        std::tostringstream_t oss;

        oss.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        oss << a_value;

        sRv = oss.str();
    } catch (std::ctostringstream_t::failure &) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
CxString::cast(
    const T &a_value,   ///< source value
    cint_t  &a_base     ///< valid values: 8, 10, 16
)
{
    xTEST_NA(a_value);
    xTEST_NA(a_base);

    std::tstring_t sRv;

    try {
        std::tostringstream_t oss;

        oss.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
        oss << std::setbase(a_base) << std::uppercase << a_value;  // std::showbase

        sRv = oss.str();
    } catch (std::ctostringstream_t::failure &) {
        sRv.clear();
    } catch (...) {
        sRv.clear();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline T
CxString::cast(
    std::ctstring_t &a_str  ///< source string
)
{
    xTEST_NA(a_str);

    T ResT;

    try {
        std::tistringstream_t iss(a_str);

        iss.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        iss >> ResT;
    } catch (std::ctistringstream_t::failure &) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline T
CxString::cast(
    std::ctstring_t &a_str, ///< source string
    cint_t          &a_base ///< valid values: 8, 10, 16
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_base);

    T ResT;

    try {
        std::tistringstream_t iss(a_str);

        iss.exceptions(std::tistringstream_t::failbit | std::tistringstream_t::badbit);
        iss >> std::setbase(a_base) >> ResT;
    } catch (std::ctistringstream_t::failure &) {
        return T();
    } catch (...) {
        return T();
    }

    return ResT;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::castA(
    std::cwstring_t &a_str  ///< source string
)
{
    xTEST_NA(a_str);

    std::string asRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(asRv),
        functors::Narrow( std::locale() ));

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::wstring
CxString::castW(
    std::cstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    std::wstring wsRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(wsRv),
        functors::Widen( std::locale() ));

    return wsRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::castA(
    std::cwstring_t &a_str,     ///< source string
    cuint_t         &a_codePage ///< code page
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    return _castA_impl(a_str, a_codePage);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::wstring
CxString::castW(
    std::cstring_t &a_str,      ///< source string
    cuint_t        &a_codePage  ///< code page
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    return _castW_impl(a_str, a_codePage);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::castA(
    std::cwstring_t   &a_str,   ///< source string
    const std::locale &a_locale ///< locale
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_locale);
    _xVERIFY(std::has_facet<std::ctype<wchar_t> >(a_locale));
    _xVERIFY(std::has_facet<std::ctype<char> >(a_locale));

    xCHECK_RET(a_str.empty(),                                   std::string());
    xCHECK_RET(!std::has_facet<std::ctype<wchar_t> >(a_locale), std::string());
    xCHECK_RET(!std::has_facet<std::ctype<char> >(a_locale),    std::string());

    typedef std::wstring::traits_type::state_type     state_type_t;
    typedef std::codecvt<wchar_t, char, state_type_t> codecvt_t;

    std::string      asRv(a_str.size(), std::wstring::value_type());

    const codecvt_t &codec     = std::use_facet<codecvt_t>( a_locale );
    state_type_t     state; xSTRUCT_ZERO(state);

    const wchar_t   *itBegin   = &a_str.at(0);
    const wchar_t   *itEnd     = &a_str.at(0) + a_str.size();
    const wchar_t   *itNext    = xPTR_NULL;

    char            *itToBegin = &asRv.at(0);
    char            *itToEnd   = &asRv.at(0) + asRv.size();
    char            *itToNext  = xPTR_NULL;

    codec.out(state, itBegin, itEnd, itNext, itToBegin, itToEnd, itToNext);

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::wstring
CxString::castW(
    std::cstring_t    &a_str,   ///< source string
    const std::locale &a_locale ///< locale
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_locale);
    _xVERIFY(std::has_facet<std::ctype<std::wstring::value_type> >(a_locale));

    xCHECK_RET(a_str.empty(),                                                    std::wstring());
    xCHECK_RET(!std::has_facet<std::ctype<std::wstring::value_type> >(a_locale), std::wstring());

    std::wstring                swRv(a_str.size(), std::wstring::value_type());

    std::string::const_iterator itBegin   = a_str.begin();
    std::string::const_iterator itEnd     = a_str.end();
    std::wstring::iterator      itToBegin = swRv.begin();

    for ( ; itBegin != itEnd; ++ itBegin, ++ itToBegin) {
        *itToBegin = std::use_facet< std::ctype<wchar_t> >( a_locale ).widen(*itBegin);
    }

    return swRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::castCodePage(
    std::cstring_t &a_str,              ///< source string
    cuint_t        &a_codePageSource,   ///< source code page
    cuint_t        &a_codePageDest      ///< destination code page
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePageSource);
    xTEST_NA(a_codePageDest);

    return castA(castW(a_str, a_codePageSource), a_codePageDest);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::castToOem(
    std::ctstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    return _castToOem_impl(a_str);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::castFromOem(
    std::cstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    return _castFromOem_impl(a_str);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::castBool(
    cbool_t &a_value   ///< source string
)
{
    xTEST_NA(a_value);

    return (!a_value) ? xT("false") : xT("true");
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxString::castBool(
    std::ctstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    xCHECK_RET(CxStringCI::compare(xT("true"),  a_str), true);
    xCHECK_RET(CxStringCI::compare(xT("false"), a_str), false);

    return false;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::toLowerCase(
    std::ctstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    return toLowerCase(a_str, a_str.size());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::toUpperCase(
    std::ctstring_t &a_str   ///< source string
)
{
    xTEST_NA(a_str);

    return toUpperCase(a_str, a_str.size());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::toLowerCase(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t    &a_length   ///< string size
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_length);

    size_t length = a_length;

    xCHECK_RET(a_str.empty(), std::tstring_t());
    xCHECK_DO (a_str.size() < length, length = a_str.size());

    return _toLowerCase_impl(a_str, length);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::toUpperCase(
    std::ctstring_t &a_str,     ///< source string
    std::csize_t    &a_length   ///< string size
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_length);

    size_t length = a_length;

    xCHECK_RET(a_str.empty(), std::tstring_t());
    xCHECK_DO (a_str.size() < length, length = a_str.size());

    std::tstring_t sRv(a_str);

    return _toUpperCase_impl(a_str, length);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::trimLeftChars(
    std::ctstring_t &a_str,     ///< source string
    std::ctstring_t &a_chars    ///< chars for trim
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_chars);

    std::tstring_t sRv(a_str);

    return sRv.erase(0, sRv.find_first_not_of(a_chars));
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::trimRightChars(
    std::ctstring_t &a_str,    ///< source string
    std::ctstring_t &a_chars   ///< chars for trim
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_chars);

    std::tstring_t sRv(a_str);

    return sRv.erase(sRv.find_last_not_of(a_chars) + 1);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::trimChars(
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
inline std::tstring_t
CxString::trimSpace(
    std::ctstring_t &a_str    ///< source string
)
{
    xTEST_NA(a_str);

    return trimChars(a_str, CxConst::whiteSpaces());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::removeEol(
    std::ctstring_t &a_str    ///< source string
)
{
    xTEST_NA(a_str);

    return trimRightChars(a_str, CxConst::eol());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::replaceAll(
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
inline std::tstring_t
CxString::replaceAll(
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
inline std::tstring_t
CxString::removeAll(
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
inline void_t
CxString::split(
    std::ctstring_t    &a_str,  ///< source string
    std::ctstring_t    &a_sep,  ///< separator
    std::vec_tstring_t *a_rv    ///< [out] string vector
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sep);
    xTEST_NA(a_rv);

    xCHECK_DO(a_rv != xPTR_NULL, a_rv->clear());

    xCHECK_DO(a_str.empty(), return);
    xCHECK_DO(a_sep.empty(), return);
    xTEST_PTR(a_rv);

    std::vec_tstring_t vsRv;
    size_t             posPrev = 0U;    // start of string
    size_t             pos     = 0U;

    for ( ; ; ) {
        pos = a_str.find(a_sep, posPrev);
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
inline std::tstring_t
CxString::join(
    std::cvec_tstring_t &a_vec, ///< source string vector
    std::ctstring_t     &a_sep  ///< separator
)
{
    xTEST_NA(a_vec);
    xTEST_NA(a_sep);

    std::tstring_t sRv;

    xFOREACH_CONST(std::vec_tstring_t, it, a_vec) {
        sRv.append(*it);

        xCHECK_DO(it < a_vec.end() - 1, sRv.append(a_sep));
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::join(
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
inline std::tstring_t
CxString::cut(
    std::ctstring_t &a_str,     ///< source string
    std::ctstring_t &a_sepLeft, ///< left separator
    std::ctstring_t &a_sepRight ///< right separator
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sepLeft);
    xTEST_NA(a_sepRight);

    size_t startDelimPos = 0U;
    size_t stopDelimPos  = 0U;

    startDelimPos = a_str.find(a_sepLeft);
    xCHECK_RET(startDelimPos == std::tstring_t::npos, std::tstring_t());
    startDelimPos += a_sepLeft.size();

    stopDelimPos  = a_str.rfind(a_sepRight);
    xCHECK_RET(stopDelimPos == std::tstring_t::npos, std::tstring_t());

    xCHECK_RET(startDelimPos >= stopDelimPos, std::tstring_t());

    return a_str.substr(startDelimPos, stopDelimPos - startDelimPos);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::cut(
    std::ctstring_t &a_str,                                 ///< source string
    std::csize_t    &a_posBegin /* = 0 */,                  ///< begin position
    std::csize_t    &a_posEnd   /* = std::tstring_t:npos */ ///< end osition
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_posBegin);
    xTEST_NA(a_posEnd);

    xCHECK_RET(a_str.empty(),          std::tstring_t());
    xCHECK_RET(a_posBegin >  a_posEnd, std::tstring_t());

    size_t size = std::string::npos;

    if (a_posEnd == std::string::npos) {
        size = a_str.size();
    } else {
        size = a_posEnd - a_posBegin;
    }

    return a_str.substr(a_posBegin, size);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::format(
    ctchar_t *a_format, ...    ///< string format
)
{
    xTEST_NA(a_format);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    std::tstring_t sRv;

    va_list args;
    xVA_START(args, a_format);
    sRv = formatV(a_format, args);
    xVA_END(args);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
#if 1

inline std::tstring_t
CxString::formatV(
    ctchar_t *a_format,    ///< string format
    va_list   a_args       ///< arguments
)
{
    xTEST_NA(a_format);
    xTEST_NA(a_args);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    std::tstring_t buff(64, 0);
    int_t          writtenSize = - 1;

    for ( ; ; ) {
        va_list _args;
        xVA_COPY(_args, a_args);

        {
            writtenSize = xTVSNPRINTF(&buff.at(0), buff.size(), a_format, _args);
            xCHECK_DO(writtenSize > - 1 && static_cast<size_t>( writtenSize ) < buff.size(), break);

            buff.resize(buff.size() * 2);
        }

        xVA_END(_args);
    }

    buff.resize(writtenSize);

    return buff;
}

#else

inline std::tstring_t
CxString::formatV(
    LPCTSTR a_format,
    va_list a_args
)
{
    xTEST_NA(a_format);
    xTEST_NA(a_args);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    std::tstring_t buff(64, 0);
    int_t          writtenSize = - 1;

    //--------------------------------------------------
    // calc size
    {
        va_list _args;
        xVA_COPY(_args, args);
        writtenSize = xTVSNPRINTF(&buff.at(0), buff.size(), a_format, _args);
        xVA_END(_args);

        assert(- 1 < writtenSize);
        xCHECK_RET(0 >  writtenSize, std::tstring_t());
        xCHECK_RET(0 == writtenSize, buff);
    }

    //--------------------------------------------------
    // format
    if (buff.size() <= static_cast<size_t>( writtenSize )) {
        buff.resize(writtenSize + 1);

        va_list _args;
        xVA_COPY(_args, args);
        writtenSize = std::xTVSNPRINTF(&buff.at(0), buff.size(), a_format, _args);
        xVA_END(_args);

        assert(- 1 <  writtenSize);
        assert(buff.size() == static_cast<size_t>( writtenSize ) + 1);
        xCHECK_RET(0 >  writtenSize,                                      std::tstring_t());
        xCHECK_RET(buff.size() != static_cast<size_t>( writtenSize ) + 1, std::tstring_t());
    }

    buff.resize(writtenSize);

    return buff;
}

#endif
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::minimize(
    std::ctstring_t &a_str,         ///< source string
    std::csize_t    &a_maxLength    ///< string maximum size
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_maxLength);

    xCHECK_RET(a_str.empty(),     std::tstring_t());
    xCHECK_RET(a_maxLength == 0U, std::tstring_t());

    std::tstring_t sRv;

    if (a_str.size() > a_maxLength) {
        if (a_maxLength < CxConst::dot3().size()) {
            sRv = a_str.substr(0U, a_maxLength);
        } else {
            sRv = a_str.substr(0U, a_maxLength - CxConst::dot3().size()) + CxConst::dot3();
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
inline std::tstring_t
CxString::formatBytes(
    culonglong_t &a_bytes    ///< bytes
)
{
    xTEST_NA(a_bytes);

    std::tstring_t sRv = CxConst::strUnknown();

    culonglong_t eb   = xEB(1);
    culonglong_t pb   = xPB(1);
    culonglong_t tb   = xTB(1);
    culonglong_t gb   = xGB(1);
    culonglong_t mb   = xMB(1);
    culonglong_t kb   = xKB(1);
    culonglong_t byte = xBYTES(1);


    if (     a_bytes / eb > 0ULL) {
        sRv = format(xT("%.2f EB"), static_cast<double>(a_bytes) / static_cast<double>(eb));
    }
    else if (a_bytes / pb > 0ULL) {
        sRv = format(xT("%.2f PB"), static_cast<double>(a_bytes) / static_cast<double>(pb));
    }
    else if (a_bytes / tb > 0ULL) {
        sRv = format(xT("%.2f TB"), static_cast<double>(a_bytes) / static_cast<double>(tb));
    }
    else if (a_bytes / gb > 0ULL) {
        sRv = format(xT("%.2f GB"), static_cast<double>(a_bytes) / static_cast<double>(gb));
    }
    else if (a_bytes / mb > 0ULL) {
        sRv = format(xT("%.2f MB"), static_cast<double>(a_bytes) / static_cast<double>(mb));
    }
    else if (a_bytes / kb > 0ULL) {
        sRv = format(xT("%.2f KB"), static_cast<double>(a_bytes) / static_cast<double>(kb));
    }
    else if (a_bytes / byte > 0ULL) {
        sRv = format(xT("%.2f Byte(s)"), static_cast<double>(a_bytes) / static_cast<double>(byte));
    }
    else {
        sRv = format(xT("%.2f Bit(s)"), static_cast<double>(a_bytes));
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::formatPercentage(
    culonglong_t &a_maxValue,       ///< maximum value
    culonglong_t &a_currentValue    ///< current value
)
{
    xTEST_NA(a_maxValue);
    xTEST_NA(a_currentValue);

    xCHECK_RET(0ULL == a_maxValue, xT("0%")); // devision by zero

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
inline void_t *
CxString::memoryZeroSecure(
    void_t       *a_buff,       ///< buffer
    std::csize_t &a_buffSize    ///< buffer size (bytes)
)
{
    xTEST_NA(a_buff);
    xTEST_NA(a_buffSize);

    size_t buffSize = a_buffSize;

    for (volatile uchar_t *buff = static_cast<volatile uchar_t *>( a_buff );
         a_buff != xPTR_NULL && 0 != buffSize;
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
inline bool_t
CxString::isRepeated(
    std::ctstring_t &a_str    ///< source string
)
{
    xTEST_NA(a_str);

    return ( std::tstring_t::npos == a_str.find_first_not_of(a_str.at(0)) );
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
inline std::size_t
CxStringCI::find(
    std::ctstring_t   &a_str,                           ///< source string
    std::ctstring_t   &a_target,                        ///< target string
    std::csize_t      &a_pos    /* = 0 */,              ///< start position
    const std::locale &a_locale /* = std::locale() */   ///< locale
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_target);
    xTEST_NA(a_pos);

    xCHECK_RET(a_str.empty() && a_target.empty() && a_pos == 0U, 0U);
    xCHECK_RET(a_target.empty(),                                 0U);

    std::tstring_t::const_iterator cit;

    cit = std::search(a_str.begin() + a_pos, a_str.end(), a_target.begin(), a_target.end(),
        functors::CompareCI(a_locale));
    xCHECK_RET(cit != a_str.end(), cit - a_str.begin());

    return std::tstring_t::npos;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxStringCI::compare(
    std::ctstring_t   &a_str1,                          ///< source string
    std::ctstring_t   &a_str2,                          ///< target string
    const std::locale &a_locale /* = std::locale() */   ///< locale
)
{
    xTEST_NA(a_str1);
    xTEST_NA(a_str2);

    xCHECK_RET(a_str1.size() != a_str2.size(), false);

    return _compare_impl(a_str1, a_str2, a_locale);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
