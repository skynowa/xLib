/**
 * \file  CxString.cpp
 * \brief string utils
 */


#include <xLib/Common/CxString.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxArray.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
std::wstring
CxString::strToWStr(
    const std::string &a_csStr,
    const uint_t      &a_cuiCodePage
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_cuiCodePage);

    std::wstring wsRes;

#if   xOS_ENV_WIN
    int iSize = ::MultiByteToWideChar(a_cuiCodePage, 0UL, a_csStr.c_str(), - 1, NULL, 0);
    xTEST_LESS(0, iSize);

    wsRes.resize(iSize - 1);    // remove '\0'
    iSize = ::MultiByteToWideChar(a_cuiCodePage, 0UL, a_csStr.c_str(), - 1, static_cast<LPWSTR>(&wsRes.at(0)), iSize);
    xTEST_LESS(0, iSize);
#elif xOS_ENV_UNIX
    // TODO: strToWStr
    xNOT_IMPLEMENTED;
#endif

    return wsRes;
}
//---------------------------------------------------------------------------
/* static */
std::string
CxString::wstrToStr(
    const std::wstring &a_cwsStr,
    const uint_t       &a_cuiCodePage
)
{
    xTEST_NA(a_cwsStr);
    xTEST_NA(a_cuiCodePage);

    std::string asRes;

#if   xOS_ENV_WIN
    int iSize = ::WideCharToMultiByte(a_cuiCodePage, 0UL, a_cwsStr.c_str(), - 1, NULL, 0, NULL, NULL);
    xTEST_LESS(0, iSize);

    asRes.resize(iSize - 1);    // remove '\0'
    iSize = ::WideCharToMultiByte(a_cuiCodePage, 0UL, a_cwsStr.c_str(), - 1, static_cast<LPSTR>(&asRes.at(0)), iSize, NULL, NULL);
    xTEST_LESS(0, iSize);
#elif xOS_ENV_UNIX
    // TODO: (wstrToStr)
    xNOT_IMPLEMENTED;
#endif

    return asRes;
}
//---------------------------------------------------------------------------
/* static */
std::wstring
CxString::strToWStr(
    const std::string &a_csStdString,
    const std::locale &a_clocLocale /* = std::locale() */
)
{
    xTEST_NA(a_csStdString);
    xTEST_NA(a_clocLocale);

    std::wstring                swRv(a_csStdString.size(), std::wstring::value_type());

    std::string::const_iterator itBegin( a_csStdString.begin() );
    std::string::const_iterator itEnd  ( a_csStdString.end() );
    std::wstring::iterator      itToBegin( swRv.begin() );

    for ( ; itBegin != itEnd; ++ itBegin, ++ itToBegin) {
        *itToBegin = std::use_facet< std::ctype<wchar_t> >( a_clocLocale ).widen( *itBegin );
    }

    return swRv;
}
//---------------------------------------------------------------------------
/* static */
std::string
CxString::wstrToStr(
    const std::wstring &a_csStdWString,
    const std::locale  &a_clocLocale /* = std::locale() */
)
{
    xTEST_NA(a_csStdWString);
    xTEST_NA(a_clocLocale);

    typedef std::wstring::traits_type::state_type      state_type_t;
    typedef std::codecvt<wchar_t, char, state_type_t>  codecvt_t;

    std::string      asRv(a_csStdWString.size(), std::wstring::value_type());

    const codecvt_t &cvt       = std::use_facet<codecvt_t>( a_clocLocale );
    state_type_t     state     = state_type_t();

    const wchar_t   *itBegin   = &a_csStdWString.at(0);
    const wchar_t   *itEnd     = &a_csStdWString.at(0) + a_csStdWString.size();
    const wchar_t   *itNext    = NULL;

    char            *itToBegin = &asRv.at(0);
    char            *itToEnd   = &asRv.at(0) + asRv.size();
    char            *itToNext  = NULL;

    cvt.out(state, itBegin, itEnd, itNext, itToBegin, itToEnd, itToNext);

    return asRv;
}
//---------------------------------------------------------------------------
/* static */
std::string
CxString::convertCodePage(
    const std::string &a_csSource,
    const uint_t      &a_cuiCodePageSource,
    const uint_t      &a_cuiCodePageDest
)
{
    xTEST_NA(a_csSource);
    xTEST_NA(a_cuiCodePageSource);
    xTEST_NA(a_cuiCodePageDest);

//    xTEST_EQ(false, csSource.empty(), std::string());        //FIX: csStr    - n/a
//    // uiCodePageSource
//    // uiCodePageDest

    //CP_ACP(ANSI) <-> CP_UTF8(UTF-8)
    //1251  (WIN)  <-> 20866  (KOI-8r)

    return wstrToStr(strToWStr(a_csSource, a_cuiCodePageSource), a_cuiCodePageDest);
}
//---------------------------------------------------------------------------
/* static */
std::string
CxString::charToOemBuff(
    const std::tstring_t &a_csSrc
)
{
    xTEST_NA(a_csSrc);

    std::string asDst;

#if   xOS_ENV_WIN
    asDst.resize(a_csSrc.size());

    BOOL blRv = ::CharToOemBuff(a_csSrc.c_str(), &asDst.at(0), static_cast<DWORD>( asDst.size() ));
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    // TODO: charToOemBuff
    xNOT_IMPLEMENTED;
#endif

    return asDst;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::oemToCharBuff(
    const std::string &a_csSrc
)
{
    xTEST_NA(a_csSrc);

    std::tstring_t sDst;

#if   xOS_ENV_WIN
    sDst.resize(a_csSrc.size());

    BOOL blRv = ::OemToCharBuff(a_csSrc.c_str(), &sDst.at(0), static_cast<DWORD>( sDst.size() ));
    xTEST_DIFF(FALSE, blRv);
#elif xOS_ENV_UNIX
    // TODO: sOemToCharBuffoemToCharBuff
    xNOT_IMPLEMENTED;
#endif

    return sDst;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::boolToStr(
    const bool &a_cbBool
)
{
    xTEST_NA(a_cbBool);

    return (false == a_cbBool) ? xT("false") : xT("true");
}
//---------------------------------------------------------------------------
/* static */
bool
CxString::strToBool(
    const std::tstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    xCHECK_RET(false != compareNoCase(xT("true"),  a_csStr), true);
    xCHECK_RET(false != compareNoCase(xT("false"), a_csStr), false);

    return false;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::toLowerCase(
    const std::tstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    return toLowerCase(a_csStr, a_csStr.size());
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::toUpperCase(
    const std::tstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    return toUpperCase(a_csStr, a_csStr.size());
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::toLowerCase(
    const std::tstring_t &a_csStr,
    const size_t         &a_cuiLength
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_cuiLength);

    size_t uiLength = a_cuiLength;

    xCHECK_RET(true == a_csStr.empty(),   std::tstring_t());
    xCHECK_DO (a_csStr.size() < uiLength, uiLength = a_csStr.size());

    std::tstring_t sRv(a_csStr);

#if   xOS_ENV_WIN
    DWORD dwRv = ::CharLowerBuff(static_cast<LPTSTR>( &sRv[0] ), static_cast<DWORD>( uiLength ));
    xTEST_EQ(uiLength, static_cast<size_t>( dwRv ));
#elif xOS_ENV_UNIX
    std::transform(sRv.begin(), sRv.begin() + uiLength, sRv.begin(), CxChar::toLower);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::toUpperCase(
    const std::tstring_t &a_csStr,
    const size_t         &a_cuiLength
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_cuiLength);

    size_t uiLength = a_cuiLength;

    xCHECK_RET(true == a_csStr.empty(),   std::tstring_t());
    xCHECK_DO (a_csStr.size() < uiLength, uiLength = a_csStr.size());

    std::tstring_t sRv(a_csStr);

#if   xOS_ENV_WIN
    DWORD dwRv = ::CharUpperBuff(static_cast<LPTSTR>( &sRv[0] ), static_cast<DWORD>( uiLength ));
    xTEST_EQ(uiLength, static_cast<size_t>( dwRv ));
#elif xOS_ENV_UNIX
    std::transform(sRv.begin(), sRv.begin() + uiLength, sRv.begin(), CxChar::toUpper);
#endif

    return sRv;
}
//---------------------------------------------------------------------------

/****************************************************************************
*   actions
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::trimLeftChars(
    const std::tstring_t &a_csStr,
    const std::tstring_t &a_csChars
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_csChars);

    std::tstring_t sRv(a_csStr);

    return sRv.erase(0, sRv.find_first_not_of(a_csChars));
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::trimRightChars(
    const std::tstring_t &a_csStr,
    const std::tstring_t &a_csChars
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_csChars);

    std::tstring_t sRv(a_csStr);

    return sRv.erase(sRv.find_last_not_of(a_csChars) + 1);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::trimChars(
    const std::tstring_t &a_csStr,
    const std::tstring_t &a_csChars
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_csChars);

    std::tstring_t sRv(a_csStr);

    sRv = trimRightChars(sRv, a_csChars);
    sRv = trimLeftChars (sRv, a_csChars);

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::trimSpace(
    const std::tstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    return trimChars(a_csStr, CxConst::xWHITE_SPACES);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::removeEol(
    const std::tstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    return trimRightChars(a_csStr, CxConst::xEOL);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::replaceAll(
    const std::tstring_t &a_csStr,
    const std::tstring_t &a_csOldStr,
    const std::tstring_t &a_csNewStr
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_csOldStr);
    xTEST_NA(a_csNewStr);

    xCHECK_RET(true == a_csStr.empty(),    a_csStr);
    xCHECK_RET(true == a_csOldStr.empty(), a_csStr);

    std::tstring_t sRv(a_csStr);

    size_t uiPos = 0U;

    xFOREVER {
        uiPos = sRv.find(a_csOldStr, uiPos);
        xCHECK_DO(std::tstring_t::npos == uiPos, break);

        sRv.replace(uiPos, a_csOldStr.size(), a_csNewStr);

        uiPos += a_csNewStr.size();
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::replaceAll(
    const std::tstring_t &a_csStr,
    const tchar_t        &a_cchOldStr,
    const tchar_t        &a_cchNewStr
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_cchOldStr);
    xTEST_NA(a_cchNewStr);

    return replaceAll(a_csStr, std::tstring_t(1, a_cchOldStr), std::tstring_t(1, a_cchNewStr));
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::removeAll(
    const std::tstring_t &a_csStr,
    const std::tstring_t &a_csRemoveStr
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_csRemoveStr);

    return replaceAll(a_csStr, a_csRemoveStr, std::tstring_t());
}
//---------------------------------------------------------------------------
/* static */
void
CxString::split(
    const std::tstring_t &a_csStr,
    const std::tstring_t &a_csSep,
    std::vec_tstring_t   *a_pvsOut
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_csSep);
    xTEST_NA(a_pvsOut);

    xCHECK_DO(true == a_csStr.empty(), return);
    xCHECK_DO(true == a_csSep.empty(), return);
    xTEST_PTR(a_pvsOut);

    std::vec_tstring_t vsRes;
    size_t             uiPrevPos = 0U;     // start of string
    size_t             uiPos     = 0U;

    xFOREVER {
        uiPos = a_csStr.find(a_csSep, uiPrevPos);
        xCHECK_DO(std::tstring_t::npos == uiPos, break);

        vsRes.push_back(a_csStr.substr(uiPrevPos, uiPos - uiPrevPos));

        uiPrevPos = uiPos + a_csSep.size();
    }
    vsRes.push_back( a_csStr.substr(uiPrevPos, a_csStr.size() - uiPrevPos) );

    //out
    std::swap(*a_pvsOut, vsRes);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::join(
    const std::vec_tstring_t &a_cvsVec,
    const std::tstring_t     &a_csSep
)
{
    xTEST_NA(a_cvsVec);
    xTEST_NA(a_csSep);

    std::tstring_t sRv;

    xFOREACH_CONST(std::vec_tstring_t, it, a_cvsVec) {
        sRv.append(*it);

        xCHECK_DO(it < a_cvsVec.end() - 1, sRv.append(a_csSep));
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::join(
    const std::vec_tstring_t &a_cvsVec,
    const tchar_t            &a_cchSep
)
{
    xTEST_NA(a_cvsVec);
    xTEST_NA(a_cchSep);

    return join(a_cvsVec, std::tstring_t(1, a_cchSep));
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::cut(
    const std::tstring_t &a_csStr,
    const std::tstring_t &a_csLeftSep,
    const std::tstring_t &a_csRightSep
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_csLeftSep);
    xTEST_NA(a_csRightSep);

    size_t uiStartDelimPos = 0U;
    size_t uiStopDelimPos  = 0U;

    uiStartDelimPos = a_csStr.find(a_csLeftSep);
    xCHECK_RET(std::tstring_t::npos == uiStartDelimPos, std::tstring_t());
    uiStartDelimPos += a_csLeftSep.size();

    uiStopDelimPos  = a_csStr.rfind(a_csRightSep);
    xCHECK_RET(std::tstring_t::npos == uiStopDelimPos, std::tstring_t());

    xCHECK_RET(uiStartDelimPos      >= uiStopDelimPos, std::tstring_t());

    return a_csStr.substr(uiStartDelimPos, uiStopDelimPos - uiStartDelimPos);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::cut(
    const std::tstring_t &a_csStr,
    const size_t         &a_cuiStartPos /* = 0 */,
    const size_t         &a_cuiEndPos   /* = std::tstring_t:npos */
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_cuiStartPos);
    xTEST_NA(a_cuiEndPos);

    xCHECK_RET(true          == a_csStr.empty(), std::tstring_t());
    xCHECK_RET(a_cuiStartPos >  a_cuiEndPos,     std::tstring_t());

    size_t uiSize = ( (std::string::npos == a_cuiEndPos) ? (a_csStr.size()) : (a_cuiEndPos) ) - a_cuiStartPos /* + 1*/;

    return a_csStr.substr(a_cuiStartPos, uiSize);
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::format(
    const tchar_t *a_pcszFormat, ...
)
{
    xTEST_NA(a_pcszFormat);

    xCHECK_RET(NULL == a_pcszFormat, std::tstring_t());

    std::tstring_t sRv;

    va_list palArgs;
    xVA_START(palArgs, a_pcszFormat);

    sRv = formatV(a_pcszFormat, palArgs);

    xVA_END(palArgs);

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
#if 1

std::tstring_t
CxString::formatV(
    const tchar_t *a_pcszFormat,
    va_list        a_palArgs
)
{
    xTEST_NA(a_pcszFormat);
    xTEST_NA(a_palArgs);

    xCHECK_RET(NULL == a_pcszFormat, std::tstring_t());

    std::tstring_t sBuff(64, 0);
    int          iWrittenSize = - 1;

    xFOREVER {
        va_list _palArgs;
        xVA_COPY(_palArgs, a_palArgs);

        {
            iWrittenSize = ::xTVSNPRINTF(&sBuff.at(0), sBuff.size(), a_pcszFormat, _palArgs);
            xCHECK_DO(iWrittenSize > - 1 && static_cast<size_t>( iWrittenSize ) < sBuff.size(), break);

            sBuff.resize(sBuff.size() * 2);
        }

        xVA_END(_palArgs);
    }

    sBuff.resize(iWrittenSize);

    return sBuff;
}

#else

std::tstring_t
CxString::formatV(
    LPCTSTR a_pcszFormat,
    va_list a_palArgs
)
{
    xTEST_NA(a_pcszFormat);
    xTEST_NA(a_palArgs);

    xCHECK_RET(NULL == pcszFormat, std::tstring_t());

    std::tstring_t sBuff(64, 0);
    int            iWrittenSize = - 1;

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
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::minimize(
    const std::tstring_t &a_csStr,
    const size_t         &a_cuiMaxLen
)
{
    xTEST_NA(a_csStr);
    xTEST_NA(a_cuiMaxLen);

    xCHECK_RET(true == a_csStr.empty(), std::tstring_t());
    xCHECK_RET(0U   == a_cuiMaxLen,     std::tstring_t());

    std::tstring_t sRv;

    if (a_csStr.size() > a_cuiMaxLen) {
        if (a_cuiMaxLen < CxConst::x3DOT.size()) {
            sRv = a_csStr.substr(0, a_cuiMaxLen);
        } else {
            sRv = a_csStr.substr(0, a_cuiMaxLen - CxConst::x3DOT.size()) + CxConst::x3DOT;
        }
    } else {
        sRv = a_csStr;
    }

    return sRv;
}
//---------------------------------------------------------------------------

/****************************************************************************
*   compare
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
bool
CxString::compareNoCase(
    const std::tstring_t &a_csStr1,
    const std::tstring_t &a_csStr2
)
{
    xTEST_NA(a_csStr1);
    xTEST_NA(a_csStr2);

    xCHECK_RET(a_csStr1.size() != a_csStr2.size(), false);

#if   xOS_ENV_WIN
    int iRv = ::lstrcmpi(a_csStr1.c_str(), a_csStr2.c_str());
    // n/a
    xCHECK_RET(0 != iRv, false);
#elif xOS_ENV_UNIX
    struct SCompare {
        static bool
        bNoCase(const std::tstring_t::value_type &cchChar1, const std::tstring_t::value_type &cchChar2) {
            return CxChar::toUpper(cchChar1) == CxChar::toUpper(cchChar2);
        }
    };

    bool bRv = std::equal(a_csStr1.begin(), a_csStr1.end(), a_csStr2.begin(), SCompare::bNoCase);
    xCHECK_RET(false == bRv, false);
#endif

    return true;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    formating
*
*****************************************************************************/

//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::translitLatToRus(
    const std::tstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    xCHECK_RET(true == a_csStr.empty(), std::tstring_t());

    //translit table
    const std::tstring_t csDict[][2] = {
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

    std::tstring_t sRv(a_csStr);

    for (size_t i = 0; i < xARRAY_SIZE(csDict); ++ i) {
        sRv = replaceAll(sRv, csDict[i][0], csDict[i][1]);
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::formatBytes(
    const ulonglong_t &a_cullBytes
)
{
    xTEST_NA(a_cullBytes);

    std::tstring_t sRv = xT("<uknown>");

    const ulonglong_t cullTB   = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
    const ulonglong_t cullGB   = 1024ULL * 1024ULL * 1024ULL;
    const ulonglong_t cullMB   = 1024ULL * 1024ULL;
    const ulonglong_t cullKB   = 1024ULL;
    const ulonglong_t cullByte = 1ULL;

    if (     a_cullBytes / cullTB   > 0ULL) {
        sRv = format(xT("%.2f TB"),      static_cast<double>(a_cullBytes) / static_cast<double>(cullTB));
    }
    else if (a_cullBytes / cullGB   > 0ULL) {
        sRv = format(xT("%.2f GB"),      static_cast<double>(a_cullBytes) / static_cast<double>(cullGB));
    }
    else if (a_cullBytes / cullMB   > 0ULL) {
        sRv = format(xT("%.2f MB"),      static_cast<double>(a_cullBytes) / static_cast<double>(cullMB));
    }
    else if (a_cullBytes / cullKB   > 0ULL) {
        sRv = format(xT("%.2f KB"),      static_cast<double>(a_cullBytes) / static_cast<double>(cullKB));
    }
    else if (a_cullBytes / cullByte > 0ULL) {
        sRv = format(xT("%.2f Byte(s)"), static_cast<double>(a_cullBytes) / static_cast<double>(cullByte));
    }
    else {
        sRv = format(xT("%.2f Bit(s)"),  static_cast<double>(a_cullBytes));
    }

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::formatPercentage(
    const ulonglong_t &a_ullMaxValue,
    const ulonglong_t &a_ullCurrValue
)
{
    xTEST_NA(a_ullMaxValue);
    xTEST_NA(a_ullCurrValue);

    xCHECK_RET(0ULL == a_ullMaxValue, xT("0%"));    // devision by zero

    std::tstring_t sRv;

    sRv = cast( a_ullCurrValue * 100ULL / a_ullMaxValue );
    xCHECK_RET(true == sRv.empty(), xT("0%"));

    sRv.append(xT("%"));

    return sRv;
}
//--------------------------------------------------------------------------

/****************************************************************************
*    memory
*
*****************************************************************************/

//---------------------------------------------------------------------------
void *
CxString::memoryZeroSecure(
    void         *a_pvBuff,
    const size_t &a_cuiBuffSize
)
{
    xTEST_NA(a_pvBuff);
    xTEST_NA(a_cuiBuffSize);

    size_t uiBuffSize = a_cuiBuffSize;

    for (volatile uchar_t *a_vpvBuff = static_cast<volatile uchar_t *>( a_pvBuff );
         NULL != a_pvBuff && 0 != uiBuffSize;
         ++ a_vpvBuff, -- uiBuffSize)
    {
        *a_vpvBuff = 0;
    }

    return a_pvBuff;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    other
*
*****************************************************************************/

//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxString::createGuid() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
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
                guidId.Data4[2], guidId.Data4[3], guidId.Data4[4], guidId.Data4[5], guidId.Data4[6], guidId.Data4[7]
    );
    xTEST_EQ(false, sRv.empty());
#elif xOS_ENV_UNIX
    // TODO: (createGuid)
    // #include <uuid/uuid.h>
    xNOT_IMPLEMENTED;
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
bool
CxString::isRepeated(
    const std::tstring_t &a_csStr
)
{
    xTEST_NA(a_csStr);

    return ( std::tstring_t::npos == a_csStr.find_first_not_of(a_csStr.at(0)) );
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
