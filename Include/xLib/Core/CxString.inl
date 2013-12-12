/**
 * \file  CxString.inl
 * \brief string utils
 */


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
#include <xLib/Log/CxTracer.h>
#include <xLib/Debug/CxStdDebug.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   casting
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
template<class T>
inline std::tstring_t
CxString::cast(
    const T &a_value
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
    const T &a_value,
    cint_t  &a_base
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
    std::ctstring_t &a_str
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
    std::ctstring_t &a_str,
    cint_t          &a_base
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
    std::cwstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::string asRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(asRv), SNarrow());

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::wstring
CxString::castW(
    std::cstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::wstring wsRv;

    std::transform(a_str.begin(), a_str.end(), std::back_inserter(wsRv), SWiden());

    return wsRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::wstring
CxString::strToWStr(
    std::cstring_t &a_str,
    cuint_t        &a_codePage
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    std::wstring wsRv;

#if xOS_ENV_WIN
    int_t size = ::MultiByteToWideChar(a_codePage, 0UL, a_str.c_str(), - 1, NULL, 0);
    xTEST_LESS(0, size);

    wsRv.resize(size - 1);    // remove '\0'
    size = ::MultiByteToWideChar(a_codePage, 0UL, a_str.c_str(), - 1,
        static_cast<LPWSTR>(&wsRv.at(0)), size);
    xTEST_LESS(0, size);
#else
    xUNUSED(a_str);
    xUNUSED(a_codePage);

    // TODO: strToWStr
    xNOT_IMPLEMENTED;
#endif

    return wsRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::wstrToStr(
    std::cwstring_t &a_str,
    cuint_t         &a_codePage
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    std::string asRv;

#if xOS_ENV_WIN
    int_t size = ::WideCharToMultiByte(a_codePage, 0UL, a_str.c_str(), - 1, NULL, 0, NULL, NULL);
    xTEST_LESS(0, size);

    asRv.resize(size - 1);    // remove '\0'
    size = ::WideCharToMultiByte(a_codePage, 0UL, a_str.c_str(), - 1,
        static_cast<LPSTR>(&asRv.at(0)), size, NULL, NULL);
    xTEST_LESS(0, size);
#else
    xUNUSED(a_str);
    xUNUSED(a_codePage);

    // TODO: (wstrToStr)
    xNOT_IMPLEMENTED;
#endif

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::wstring
CxString::strToWStr(
    std::cstring_t    &a_stdString,
    const std::locale &a_locale /* = std::locale() */
)
{
    xTEST_NA(a_stdString);
    xTEST_NA(a_locale);
    xSTD_VERIFY(std::has_facet<std::ctype<std::wstring::value_type> >(a_locale));

    xCHECK_RET(a_stdString.empty(),                                              std::wstring());
    xCHECK_RET(!std::has_facet<std::ctype<std::wstring::value_type> >(a_locale), std::wstring());

    std::wstring                swRv(a_stdString.size(), std::wstring::value_type());

    std::string::const_iterator itBegin   = a_stdString.begin();
    std::string::const_iterator itEnd     = a_stdString.end();
    std::wstring::iterator      itToBegin = swRv.begin();

    for ( ; itBegin != itEnd; ++ itBegin, ++ itToBegin) {
        *itToBegin = std::use_facet< std::ctype<wchar_t> >( a_locale ).widen(*itBegin);
    }

    return swRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::wstrToStr(
    std::cwstring_t   &a_stdWString,
    const std::locale &a_locale /* = std::locale() */
)
{
    xTEST_NA(a_stdWString);
    xTEST_NA(a_locale);
    xSTD_VERIFY(std::has_facet<std::ctype<wchar_t> >(a_locale));
    xSTD_VERIFY(std::has_facet<std::ctype<char> >(a_locale));

    xCHECK_RET(a_stdWString.empty(),                            std::string());
    xCHECK_RET(!std::has_facet<std::ctype<wchar_t> >(a_locale), std::string());
    xCHECK_RET(!std::has_facet<std::ctype<char> >(a_locale),    std::string());

    typedef std::wstring::traits_type::state_type     state_type_t;
    typedef std::codecvt<wchar_t, char, state_type_t> codecvt_t;

    std::string      asRv(a_stdWString.size(), std::wstring::value_type());

    const codecvt_t &codec     = std::use_facet<codecvt_t>( a_locale );
    state_type_t     state; xSTRUCT_ZERO(state);

    const wchar_t   *itBegin   = &a_stdWString.at(0);
    const wchar_t   *itEnd     = &a_stdWString.at(0) + a_stdWString.size();
    const wchar_t   *itNext    = NULL;

    char            *itToBegin = &asRv.at(0);
    char            *itToEnd   = &asRv.at(0) + asRv.size();
    char            *itToNext  = NULL;

    codec.out(state, itBegin, itEnd, itNext, itToBegin, itToEnd, itToNext);

    return asRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::convertCodePage(
    std::cstring_t &a_source,
    cuint_t        &a_codePageSource,
    cuint_t        &a_codePageDest
)
{
    xTEST_NA(a_source);
    xTEST_NA(a_codePageSource);
    xTEST_NA(a_codePageDest);

//    xTEST_EQ(false, source.empty(), std::string()); //FIX: str - n/a
//    // uiCodePageSource
//    // uiCodePageDest

    //CP_ACP(ANSI) <-> CP_UTF8(UTF-8)
    //1251  (WIN)  <-> 20866  (KOI-8r)

    return wstrToStr(strToWStr(a_source, a_codePageSource), a_codePageDest);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::string
CxString::charToOemBuff(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::string dest;

#if xOS_ENV_WIN
    dest.resize(a_str.size());

    BOOL blRv = ::CharToOemBuff(a_str.c_str(), &dest.at(0), static_cast<DWORD>( dest.size() ));
    xTEST_DIFF(FALSE, blRv);
#else
    xUNUSED(a_str);

    // TODO: charToOemBuff
    xNOT_IMPLEMENTED;
#endif

    return dest;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::oemToCharBuff(
    std::cstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::tstring_t dest;

#if xOS_ENV_WIN
    dest.resize(a_str.size());

    BOOL blRv = ::OemToCharBuff(a_str.c_str(), &dest.at(0), static_cast<DWORD>( dest.size() ));
    xTEST_DIFF(FALSE, blRv);
#else
    xUNUSED(a_str);

    // TODO: sOemToCharBuffoemToCharBuff
    xNOT_IMPLEMENTED;
#endif

    return dest;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::boolToStr(
    cbool_t &a_value
)
{
    xTEST_NA(a_value);

    return (!a_value) ? xT("false") : xT("true");
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxString::strToBool(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    xCHECK_RET(compareNoCase(xT("true"),  a_str), true);
    xCHECK_RET(compareNoCase(xT("false"), a_str), false);

    return false;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::toLowerCase(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return toLowerCase(a_str, a_str.size());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::toUpperCase(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return toUpperCase(a_str, a_str.size());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::toLowerCase(
    std::ctstring_t &a_str,
    std::csize_t    &a_length
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_length);

    size_t length = a_length;

    xCHECK_RET(a_str.empty(), std::tstring_t());
    xCHECK_DO (a_str.size() < length, length = a_str.size());

    std::tstring_t sRv(a_str);

#if xOS_ENV_WIN
    DWORD dwRv = ::CharLowerBuff(static_cast<LPTSTR>( &sRv[0] ),
                                 static_cast<DWORD>( length ));
    xTEST_EQ(length, static_cast<size_t>( dwRv ));
#else
    std::transform(sRv.begin(), sRv.begin() + length, sRv.begin(), CxChar::toLower);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::toUpperCase(
    std::ctstring_t &a_str,
    std::csize_t    &a_length
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_length);

    size_t length = a_length;

    xCHECK_RET(a_str.empty(), std::tstring_t());
    xCHECK_DO (a_str.size() < length, length = a_str.size());

    std::tstring_t sRv(a_str);

#if xOS_ENV_WIN
    DWORD dwRv = ::CharUpperBuff(static_cast<LPTSTR>( &sRv[0] ), static_cast<DWORD>( length ));
    xTEST_EQ(length, static_cast<size_t>( dwRv ));
#else
    std::transform(sRv.begin(), sRv.begin() + length, sRv.begin(), CxChar::toUpper);
#endif

    return sRv;
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
    std::ctstring_t &a_str,
    std::ctstring_t &a_chars
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
    std::ctstring_t &a_str,
    std::ctstring_t &a_chars
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
    std::ctstring_t &a_str,
    std::ctstring_t &a_chars
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
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return trimChars(a_str, CxConst::whiteSpaces());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::removeEol(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return trimRightChars(a_str, CxConst::eol());
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::replaceAll(
    std::ctstring_t &a_str,
    std::ctstring_t &a_strOld,
    std::ctstring_t &a_strNew
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_strOld);
    xTEST_NA(a_strNew);

    xCHECK_RET(a_str.empty(),    a_str);
    xCHECK_RET(a_strOld.empty(), a_str);

    std::tstring_t sRv(a_str);

    size_t pos = 0U;

    xFOREVER {
        pos = sRv.find(a_strOld, pos);
        xCHECK_DO(std::tstring_t::npos == pos, break);

        sRv.replace(pos, a_strOld.size(), a_strNew);

        pos += a_strNew.size();
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::replaceAll(
    std::ctstring_t &a_str,
    ctchar_t        &a_charOld,
    ctchar_t        &a_charNew
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
    std::ctstring_t &a_str,
    std::ctstring_t &a_removeStr
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
    std::ctstring_t    &a_str,
    std::ctstring_t    &a_sep,
    std::vec_tstring_t *a_rv
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sep);
    xTEST_NA(a_rv);

    xCHECK_DO(a_rv != NULL, a_rv->clear());

    xCHECK_DO(a_str.empty(), return);
    xCHECK_DO(a_sep.empty(), return);
    xTEST_PTR(a_rv);

    std::vec_tstring_t vsRv;
    size_t             posPrev = 0U;    // start of string
    size_t             pos     = 0U;

    xFOREVER {
        pos = a_str.find(a_sep, posPrev);
        xCHECK_DO(std::tstring_t::npos == pos, break);

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
    std::cvec_tstring_t &a_vec,
    std::ctstring_t     &a_sep
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
    std::cvec_tstring_t &a_vec,
    ctchar_t            &a_sep
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
    std::ctstring_t &a_str,
    std::ctstring_t &a_sepLeft,
    std::ctstring_t &a_sepRight
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sepLeft);
    xTEST_NA(a_sepRight);

    size_t startDelimPos = 0U;
    size_t stopDelimPos  = 0U;

    startDelimPos = a_str.find(a_sepLeft);
    xCHECK_RET(std::tstring_t::npos == startDelimPos, std::tstring_t());
    startDelimPos += a_sepLeft.size();

    stopDelimPos  = a_str.rfind(a_sepRight);
    xCHECK_RET(std::tstring_t::npos == stopDelimPos, std::tstring_t());

    xCHECK_RET(startDelimPos >= stopDelimPos, std::tstring_t());

    return a_str.substr(startDelimPos, stopDelimPos - startDelimPos);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::cut(
    std::ctstring_t &a_str,
    std::csize_t    &a_posBegin /* = 0 */,
    std::csize_t    &a_posEnd   /* = std::tstring_t:npos */
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_posBegin);
    xTEST_NA(a_posEnd);

    xCHECK_RET(true == a_str.empty(),  std::tstring_t());
    xCHECK_RET(a_posBegin >  a_posEnd, std::tstring_t());

    size_t size = std::string::npos;

    if (std::string::npos == a_posEnd) {
        size = a_str.size();
    } else {
        size = a_posEnd - a_posBegin /* + 1*/;
    }

    return a_str.substr(a_posBegin, size);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::format(
    ctchar_t *a_format, ...
)
{
    xTEST_NA(a_format);

    xCHECK_RET(NULL == a_format, std::tstring_t());

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
    ctchar_t *a_format,
    va_list   a_args
)
{
    xTEST_NA(a_format);
    xTEST_NA(a_args);

    xCHECK_RET(NULL == a_format, std::tstring_t());

    std::tstring_t buff(64, 0);
    int_t          writtenSize = - 1;

    xFOREVER {
        va_list _args;
        xVA_COPY(_args, a_args);

        {
            writtenSize = std::xTVSNPRINTF(&buff.at(0), buff.size(), a_format, _args);
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

    xCHECK_RET(NULL == a_format, std::tstring_t());

    std::tstring_t buff(64, 0);
    int_t          writtenSize = - 1;

    //--------------------------------------------------
    // calc size
    {
        va_list _args;
        xVA_COPY(_args, args);
        writtenSize = std::xTVSNPRINTF(&buff.at(0), buff.size(), a_format, _args);
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
    std::ctstring_t &a_str,
    std::csize_t    &a_maxLength
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_maxLength);

    xCHECK_RET(a_str.empty(),     std::tstring_t());
    xCHECK_RET(0U == a_maxLength, std::tstring_t());

    std::tstring_t sRv;

    if (a_str.size() > a_maxLength) {
        if (a_maxLength < CxConst::dot3().size()) {
            sRv = a_str.substr(0, a_maxLength);
        } else {
            sRv = a_str.substr(0, a_maxLength - CxConst::dot3().size()) + CxConst::dot3();
        }
    } else {
        sRv = a_str;
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*   compare
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxString::compareNoCase(
    std::ctstring_t &a_str1,
    std::ctstring_t &a_str2
)
{
    xTEST_NA(a_str1);
    xTEST_NA(a_str2);

    xCHECK_RET(a_str1.size() != a_str2.size(), false);

#if   xOS_ENV_WIN
    int_t iRv = ::lstrcmpi(a_str1.c_str(), a_str2.c_str());
    // n/a
    xCHECK_RET(0 != iRv, false);
#elif xOS_ENV_UNIX
    bool_t bRv = std::equal(a_str1.begin(), a_str1.end(), a_str2.begin(), SCompareNoCase());
    xCHECK_RET(!bRv, false);
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------

/**************************************************************************************************
*    formating
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::translitLatToRus(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    xCHECK_RET(a_str.empty(), std::tstring_t());

    // translit table
    std::ctstring_t dict[][2] = {
        {xT("Й"), xT("Y")},   {xT("Ц"), xT("C")},  {xT("У"), xT("U")},
        {xT("К"), xT("K")},   {xT("Е"), xT("E")},  {xT("Ё"), xT("E")},
        {xT("Н"), xT("N")},   {xT("Г"), xT("G")},  {xT("Ш"), xT("SH")},
        {xT("Щ"), xT("SH'")}, {xT("З"), xT("Z")},  {xT("Х"), xT("H")},
        {xT("Ъ"), xT("`")},   {xT("Ф"), xT("F")},  {xT("Ы"), xT("I")},
        {xT("В"), xT("V")},   {xT("А"), xT("A")},  {xT("П"), xT("P")},
        {xT("Р"), xT("R")},   {xT("О"), xT("O")},  {xT("Л"), xT("L")},
        {xT("Д"), xT("D")},   {xT("Ж"), xT("ZH")}, {xT("Э"), xT("E")},
        {xT("Я"), xT("YA")},  {xT("Ч"), xT("4")},  {xT("С"), xT("S")},
        {xT("М"), xT("M")},   {xT("И"), xT("I")},  {xT("Т"), xT("T")},
        {xT("Ь"), xT("'")},   {xT("Б"), xT("B")},  {xT("Ю"), xT("YU")},

        {xT("й"), xT("y")},   {xT("ц"), xT("c")},  {xT("у"), xT("u")},
        {xT("к"), xT("k")},   {xT("е"), xT("e")},  {xT("ё"), xT("e")},
        {xT("н"), xT("n")},   {xT("г"), xT("g")},  {xT("ш"), xT("sh")},
        {xT("щ"), xT("sh'")}, {xT("з"), xT("z")},  {xT("х"), xT("h")},
        {xT("ъ"), xT("`")},   {xT("ф"), xT("f")},  {xT("ы"), xT("i")},
        {xT("в"), xT("v")},   {xT("а"), xT("a")},  {xT("п"), xT("p")},
        {xT("р"), xT("r")},   {xT("о"), xT("o")},  {xT("л"), xT("l")},
        {xT("д"), xT("d")},   {xT("ж"), xT("zh")}, {xT("э"), xT("e")},
        {xT("я"), xT("ya")},  {xT("ч"), xT("4")},  {xT("с"), xT("s")},
        {xT("м"), xT("m")},   {xT("и"), xT("i")},  {xT("т"), xT("t")},
        {xT("ь"), xT("'")},   {xT("б"), xT("b")},  {xT("ю"), xT("yu")}
    };

    std::tstring_t sRv(a_str);

    for (size_t i = 0; i < xARRAY_SIZE(dict); ++ i) {
        sRv = replaceAll(sRv, dict[i][0], dict[i][1]);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::formatBytes(
    culonglong_t &a_bytes
)
{
    xTEST_NA(a_bytes);

    std::tstring_t sRv = xT("<uknown>");

    culonglong_t tb   = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
    culonglong_t gb   = 1024ULL * 1024ULL * 1024ULL;
    culonglong_t mb   = 1024ULL * 1024ULL;
    culonglong_t kb   = 1024ULL;
    culonglong_t byte = 1ULL;

    if (     a_bytes / tb > 0ULL) {
        sRv = format(xT("%.2f TB"),
                static_cast<double>(a_bytes) / static_cast<double>(tb));
    }
    else if (a_bytes / gb > 0ULL) {
        sRv = format(xT("%.2f GB"),
                static_cast<double>(a_bytes) / static_cast<double>(gb));
    }
    else if (a_bytes / mb > 0ULL) {
        sRv = format(xT("%.2f MB"),
                static_cast<double>(a_bytes) / static_cast<double>(mb));
    }
    else if (a_bytes / kb > 0ULL) {
        sRv = format(xT("%.2f KB"),
                static_cast<double>(a_bytes) / static_cast<double>(kb));
    }
    else if (a_bytes / byte > 0ULL) {
        sRv = format(xT("%.2f Byte(s)"),
                static_cast<double>(a_bytes) / static_cast<double>(byte));
    }
    else {
        sRv = format(xT("%.2f Bit(s)"),
                static_cast<double>(a_bytes));
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline std::tstring_t
CxString::formatPercentage(
    culonglong_t &a_maxValue,
    culonglong_t &a_currentValue
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
    void_t       *a_buff,
    std::csize_t &a_buffSize
)
{
    xTEST_NA(a_buff);
    xTEST_NA(a_buffSize);

    size_t buffSize = a_buffSize;

    for (volatile uchar_t *buff = static_cast<volatile uchar_t *>( a_buff );
         NULL != a_buff && 0 != buffSize;
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
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return ( std::tstring_t::npos == a_str.find_first_not_of(a_str.at(0)) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
