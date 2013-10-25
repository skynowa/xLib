/**
 * \file  CxString.cpp
 * \brief string utils
 */


#include <xLib/Core/CxString.h>


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Core/xFunctors.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTracer.h>
#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxChar.h>
#include <xLib/Core/CxArray.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::wstring
CxString::strToWStr(
    std::cstring_t &a_str,
    cuint_t        &a_codePage
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    std::wstring wsRes;

#if xOS_ENV_WIN
    int_t iSize = ::MultiByteToWideChar(a_codePage, 0UL, a_str.c_str(), - 1,
                                      NULL, 0);
    xTEST_LESS(0, iSize);

    wsRes.resize(iSize - 1);    // remove '\0'
    iSize = ::MultiByteToWideChar(a_codePage, 0UL, a_str.c_str(), - 1,
                                  static_cast<LPWSTR>(&wsRes.at(0)), iSize);
    xTEST_LESS(0, iSize);
#else
    // TODO: strToWStr
    xNOT_IMPLEMENTED;
#endif

    return wsRes;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::string
CxString::wstrToStr(
    std::cwstring_t &a_str,
    cuint_t         &a_codePage
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_codePage);

    std::string asRes;

#if xOS_ENV_WIN
    int_t iSize = ::WideCharToMultiByte(a_codePage, 0UL, a_str.c_str(), - 1,
                                      NULL, 0, NULL, NULL);
    xTEST_LESS(0, iSize);

    asRes.resize(iSize - 1);    // remove '\0'
    iSize = ::WideCharToMultiByte(a_codePage, 0UL, a_str.c_str(), - 1,
                                  static_cast<LPSTR>(&asRes.at(0)), iSize, NULL,
                                  NULL);
    xTEST_LESS(0, iSize);
#else
    // TODO: (wstrToStr)
    xNOT_IMPLEMENTED;
#endif

    return asRes;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::wstring
CxString::strToWStr(
    std::cstring_t    &a_stdString,
    const std::locale &a_locale /* = std::locale() */
)
{
    xTEST_NA(a_stdString);
    xTEST_NA(a_locale);

    std::wstring                swRv(a_stdString.size(), std::wstring::value_type());

    std::string::const_iterator itBegin( a_stdString.begin() );
    std::string::const_iterator itEnd  ( a_stdString.end() );
    std::wstring::iterator      itToBegin( swRv.begin() );

    for ( ; itBegin != itEnd; ++ itBegin, ++ itToBegin) {
        *itToBegin = std::use_facet< std::ctype<wchar_t> >( a_locale )
                        .widen( *itBegin );
    }

    return swRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::string
CxString::wstrToStr(
    std::cwstring_t   &a_stdWString,
    const std::locale &a_locale /* = std::locale() */
)
{
    xTEST_NA(a_stdWString);
    xTEST_NA(a_locale);

    typedef std::wstring::traits_type::state_type      state_type_t;
    typedef std::codecvt<wchar_t, char, state_type_t>  codecvt_t;

    std::string      asRv(a_stdWString.size(), std::wstring::value_type());

    const codecvt_t &cvt       = std::use_facet<codecvt_t>( a_locale );
    state_type_t     state     = state_type_t();

    const wchar_t   *itBegin   = &a_stdWString.at(0);
    const wchar_t   *itEnd     = &a_stdWString.at(0) + a_stdWString.size();
    const wchar_t   *itNext    = NULL;

    char            *itToBegin = &asRv.at(0);
    char            *itToEnd   = &asRv.at(0) + asRv.size();
    char            *itToNext  = NULL;

    cvt.out(state, itBegin, itEnd, itNext, itToBegin, itToEnd, itToNext);

    return asRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::string
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::string
CxString::charToOemBuff(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::string asDst;

#if xOS_ENV_WIN
    asDst.resize(a_str.size());

    BOOL blRv = ::CharToOemBuff(a_str.c_str(), &asDst.at(0),
                                static_cast<DWORD>( asDst.size() ));
    xTEST_DIFF(FALSE, blRv);
#else
    // TODO: charToOemBuff
    xNOT_IMPLEMENTED;
#endif

    return asDst;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::oemToCharBuff(
    std::cstring_t &a_str
)
{
    xTEST_NA(a_str);

    std::tstring_t sDst;

#if xOS_ENV_WIN
    sDst.resize(a_str.size());

    BOOL blRv = ::OemToCharBuff(a_str.c_str(), &sDst.at(0),
                                static_cast<DWORD>( sDst.size() ));
    xTEST_DIFF(FALSE, blRv);
#else
    // TODO: sOemToCharBuffoemToCharBuff
    xNOT_IMPLEMENTED;
#endif

    return sDst;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::boolToStr(
    cbool_t &a_value
)
{
    xTEST_NA(a_value);

    return (!a_value) ? xT("false") : xT("true");
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxString::strToBool(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    xCHECK_RET(compareNoCase(xT("true"),  a_str), true);
    xCHECK_RET(compareNoCase(xT("false"), a_str), false);

    return false;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::toLowerCase(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return toLowerCase(a_str, a_str.size());
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::toUpperCase(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return toUpperCase(a_str, a_str.size());
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::toLowerCase(
    std::ctstring_t &a_str,
    std::csize_t    &a_length
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_length);

    size_t uiLength = a_length;

    xCHECK_RET(a_str.empty(),   std::tstring_t());
    xCHECK_DO (a_str.size() < uiLength, uiLength = a_str.size());

    std::tstring_t sRv(a_str);

#if xOS_ENV_WIN
    DWORD dwRv = ::CharLowerBuff(static_cast<LPTSTR>( &sRv[0] ),
                                 static_cast<DWORD>( uiLength ));
    xTEST_EQ(uiLength, static_cast<size_t>( dwRv ));
#else
    std::transform(sRv.begin(), sRv.begin() + uiLength, sRv.begin(), CxChar::toLower);
#endif

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::toUpperCase(
    std::ctstring_t &a_str,
    std::csize_t    &a_length
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_length);

    size_t uiLength = a_length;

    xCHECK_RET(a_str.empty(),   std::tstring_t());
    xCHECK_DO (a_str.size() < uiLength, uiLength = a_str.size());

    std::tstring_t sRv(a_str);

#if xOS_ENV_WIN
    DWORD dwRv = ::CharUpperBuff(static_cast<LPTSTR>( &sRv[0] ),
                                 static_cast<DWORD>( uiLength ));
    xTEST_EQ(uiLength, static_cast<size_t>( dwRv ));
#else
    std::transform(sRv.begin(), sRv.begin() + uiLength, sRv.begin(), CxChar::toUpper);
#endif

    return sRv;
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   actions
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::trimSpace(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return trimChars(a_str, CxConst::xWHITE_SPACES());
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::removeEol(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return trimRightChars(a_str, CxConst::xEOL());
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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

    size_t uiPos = 0U;

    xFOREVER {
        uiPos = sRv.find(a_strOld, uiPos);
        xCHECK_DO(std::tstring_t::npos == uiPos, break);

        sRv.replace(uiPos, a_strOld.size(), a_strNew);

        uiPos += a_strNew.size();
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::removeAll(
    std::ctstring_t &a_str,
    std::ctstring_t &a_removeStr
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_removeStr);

    return replaceAll(a_str, a_removeStr, std::tstring_t());
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxString::split(
    std::ctstring_t    &a_str,
    std::ctstring_t    &a_sep,
    std::vec_tstring_t *a_rv
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sep);
    xTEST_NA(a_rv);

    xCHECK_DO(a_str.empty(), return);
    xCHECK_DO(a_sep.empty(), return);
    xTEST_PTR(a_rv);

    std::vec_tstring_t vsRes;
    size_t             uiPrevPos = 0U;     // start of string
    size_t             uiPos     = 0U;

    xFOREVER {
        uiPos = a_str.find(a_sep, uiPrevPos);
        xCHECK_DO(std::tstring_t::npos == uiPos, break);

        vsRes.push_back(a_str.substr(uiPrevPos, uiPos - uiPrevPos));

        uiPrevPos = uiPos + a_sep.size();
    }
    vsRes.push_back( a_str.substr(uiPrevPos, a_str.size() - uiPrevPos) );

    //out
    std::swap(*a_rv, vsRes);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::join(
    std::cvec_tstring_t &a_vec,
    ctchar_t            &a_sep
)
{
    xTEST_NA(a_vec);
    xTEST_NA(a_sep);

    return join(a_vec, std::ctstring_t(1, a_sep));
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::cut(
    std::ctstring_t &a_str,
    std::ctstring_t &a_sepLeft,
    std::ctstring_t &a_sepRight
)
{
    xTEST_NA(a_str);
    xTEST_NA(a_sepLeft);
    xTEST_NA(a_sepRight);

    size_t uiStartDelimPos = 0U;
    size_t uiStopDelimPos  = 0U;

    uiStartDelimPos = a_str.find(a_sepLeft);
    xCHECK_RET(std::tstring_t::npos == uiStartDelimPos, std::tstring_t());
    uiStartDelimPos += a_sepLeft.size();

    uiStopDelimPos  = a_str.rfind(a_sepRight);
    xCHECK_RET(std::tstring_t::npos == uiStopDelimPos, std::tstring_t());

    xCHECK_RET(uiStartDelimPos      >= uiStopDelimPos, std::tstring_t());

    return a_str.substr(uiStartDelimPos, uiStopDelimPos - uiStartDelimPos);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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

    size_t uiSize = std::string::npos;

    if (std::string::npos == a_posEnd) {
        uiSize = a_str.size();
    } else {
        uiSize = a_posEnd - a_posBegin /* + 1*/;
    }

    return a_str.substr(a_posBegin, uiSize);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::format(
    ctchar_t *a_format, ...
)
{
    xTEST_NA(a_format);

    xCHECK_RET(NULL == a_format, std::tstring_t());

    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, a_format);

    sRv = formatV(a_format, palArgs);

    xVA_END(palArgs);

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
#if 1

xINLINE_HO std::tstring_t
CxString::formatV(
    ctchar_t *a_format,
    va_list   a_args
)
{
    xTEST_NA(a_format);
    xTEST_NA(a_args);

    xCHECK_RET(NULL == a_format, std::tstring_t());

    std::tstring_t sBuff(64, 0);
    int_t          iWrittenSize = - 1;

    xFOREVER {
        va_list _palArgs;
        xVA_COPY(_palArgs, a_args);

        {
            iWrittenSize = ::xTVSNPRINTF(&sBuff.at(0), sBuff.size(), a_format, _palArgs);
            xCHECK_DO(iWrittenSize > - 1 && static_cast<size_t>( iWrittenSize ) < sBuff.size(), break);

            sBuff.resize(sBuff.size() * 2);
        }

        xVA_END(_palArgs);
    }

    sBuff.resize(iWrittenSize);

    return sBuff;
}

#else

xINLINE_HO std::tstring_t
CxString::formatV(
    LPCTSTR a_format,
    va_list a_args
)
{
    xTEST_NA(a_format);
    xTEST_NA(a_args);

    xCHECK_RET(NULL == pcszFormat, std::tstring_t());

    std::tstring_t sBuff(64, 0);
    int_t            iWrittenSize = - 1;

    //--------------------------------------------------
    // calc size
    {
        va_list _palArgs;
        xVA_COPY(_palArgs, palArgs);
        iWrittenSize = ::xTVSNPRINTF(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
        xVA_END(_palArgs);

        assert(- 1 < iWrittenSize);
        xCHECK_RET(0 >  iWrittenSize, std::tstring_t());
        xCHECK_RET(0 == iWrittenSize, sBuff);
    }

    //--------------------------------------------------
    // format
    if (sBuff.size() <= static_cast<size_t>( iWrittenSize )) {
        sBuff.resize(iWrittenSize + 1);

        va_list _palArgs;
        xVA_COPY(_palArgs, palArgs);
        iWrittenSize = std::xTVSNPRINTF(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
        xVA_END(_palArgs);

        assert(- 1          <  iWrittenSize);
        assert(sBuff.size() == static_cast<size_t>( iWrittenSize ) + 1);
        xCHECK_RET(0             >  iWrittenSize,                           std::tstring_t());
        xCHECK_RET(sBuff.size() != static_cast<size_t>( iWrittenSize ) + 1, std::tstring_t());
    }

    sBuff.resize(iWrittenSize);

    return sBuff;
}

#endif
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
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
        if (a_maxLength < CxConst::x3DOT().size()) {
            sRv = a_str.substr(0, a_maxLength);
        } else {
            sRv = a_str.substr(0, a_maxLength - CxConst::x3DOT().size()) +
                                 CxConst::x3DOT();
        }
    } else {
        sRv = a_str;
    }

    return sRv;
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   compare
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
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
//------------------------------------------------------------------------------

/*******************************************************************************
*    formating
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::translitLatToRus(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    xCHECK_RET(a_str.empty(), std::tstring_t());

    // translit table
    std::ctstring_t csDict[][2] = {
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

    for (size_t i = 0; i < xARRAY_SIZE(csDict); ++ i) {
        sRv = replaceAll(sRv, csDict[i][0], csDict[i][1]);
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::formatBytes(
    culonglong_t &a_bytes
)
{
    xTEST_NA(a_bytes);

    std::tstring_t sRv = xT("<uknown>");

    culonglong_t cullTB   = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
    culonglong_t cullGB   = 1024ULL * 1024ULL * 1024ULL;
    culonglong_t cullMB   = 1024ULL * 1024ULL;
    culonglong_t cullKB   = 1024ULL;
    culonglong_t cullByte = 1ULL;

    if (     a_bytes / cullTB > 0ULL) {
        sRv = format(xT("%.2f TB"),
                static_cast<double>(a_bytes) / static_cast<double>(cullTB));
    }
    else if (a_bytes / cullGB > 0ULL) {
        sRv = format(xT("%.2f GB"),
                static_cast<double>(a_bytes) / static_cast<double>(cullGB));
    }
    else if (a_bytes / cullMB > 0ULL) {
        sRv = format(xT("%.2f MB"),
                static_cast<double>(a_bytes) / static_cast<double>(cullMB));
    }
    else if (a_bytes / cullKB > 0ULL) {
        sRv = format(xT("%.2f KB"),
                static_cast<double>(a_bytes) / static_cast<double>(cullKB));
    }
    else if (a_bytes / cullByte > 0ULL) {
        sRv = format(xT("%.2f Byte(s)"),
                static_cast<double>(a_bytes) / static_cast<double>(cullByte));
    }
    else {
        sRv = format(xT("%.2f Bit(s)"),
                static_cast<double>(a_bytes));
    }

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::formatPercentage(
    culonglong_t &a_maxValue,
    culonglong_t &a_currValue
)
{
    xTEST_NA(a_maxValue);
    xTEST_NA(a_currValue);

    xCHECK_RET(0ULL == a_maxValue, xT("0%")); // devision by zero

    std::tstring_t sRv;

    sRv = cast( a_currValue * 100ULL / a_maxValue );
    xCHECK_RET(sRv.empty(), xT("0%"));

    sRv.append(xT("%"));

    return sRv;
}
//--------------------------------------------------------------------------

/*******************************************************************************
*    memory
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO void_t *
CxString::memoryZeroSecure(
    void_t       *a_buff,
    std::csize_t &a_buffSize
)
{
    xTEST_NA(a_buff);
    xTEST_NA(a_buffSize);

    size_t uiBuffSize = a_buffSize;

    for (volatile uchar_t *buff = static_cast<volatile uchar_t *>( a_buff );
         NULL != a_buff && 0 != uiBuffSize;
         ++ buff, -- uiBuffSize)
    {
        *buff = 0;
    }

    return a_buff;
}
//------------------------------------------------------------------------------

/*******************************************************************************
*    other
*
*******************************************************************************/

//--------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxString::createGuid()
{
    std::tstring_t sRv;

#if xOS_ENV_WIN
    GUID    guidId = {0};
    HRESULT hrGuid = S_FALSE;

    hrGuid = ::CoCreateGuid(&guidId);
    xTEST_EQ(true, SUCCEEDED(hrGuid));

    sRv = format(
            xT("%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"),
            guidId.Data1,
            guidId.Data2,
            guidId.Data3,
            guidId.Data4[0], guidId.Data4[1],
            guidId.Data4[2], guidId.Data4[3],
            guidId.Data4[4], guidId.Data4[5],
            guidId.Data4[6], guidId.Data4[7]
    );
    xTEST_EQ(false, sRv.empty());
#else
    // TODO: createGuid
    // #include <uuid/uuid.h>
    xNOT_IMPLEMENTED;
#endif

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO bool_t
CxString::isRepeated(
    std::ctstring_t &a_str
)
{
    xTEST_NA(a_str);

    return ( std::tstring_t::npos == a_str.find_first_not_of(a_str.at(0)) );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
