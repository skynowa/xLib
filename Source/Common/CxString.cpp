/**
 * \file  CxString.cpp
 * \brief string utils
 */


#include <xLib/Common/CxString.h>


#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxArray.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sBoolToStr(
    const bool cbBool
)
{
    /*DEBUG*/// bBool - n/a

    return (false == cbBool) ? xT("false") : xT("true");
}
//---------------------------------------------------------------------------
/*static*/
bool
CxString::bStrToBool(
    const std::tstring_t &csStr
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(false != bCompareNoCase(xT("true"),  csStr), true);
    xCHECK_RET(false != bCompareNoCase(xT("false"), csStr), false);

    return false;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sTrimLeftChars(
    const std::tstring_t &csStr,
    const std::tstring_t &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::tstring_t sRes(csStr);

    return sRes.erase(0, sRes.find_first_not_of(csChars));
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sTrimRightChars(
    const std::tstring_t &csStr,
    const std::tstring_t &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::tstring_t sRes(csStr);

    return sRes.erase(sRes.find_last_not_of(csChars) + 1);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sTrimChars(
    const std::tstring_t &csStr,
    const std::tstring_t &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::tstring_t sRes(csStr);

    sRes = sTrimRightChars(sRes, csChars);
    sRes = sTrimLeftChars (sRes, csChars);

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sTrimSpace(
    const std::tstring_t &csStr
)
{
    /*DEBUG*/// csStr - n/a

    return sTrimChars(csStr, CxConst::xWHITE_SPACES);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sRemoveEol(
    const std::tstring_t &csStr
)
{
    /*DEBUG*/// csStr - n/a

    return sTrimRightChars(csStr, CxConst::xEOL);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sReplaceAll(
    const std::tstring_t &csStr,
    const std::tstring_t &csOldStr,
    const std::tstring_t &csNewStr
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// csOldStr - n/a
    /*DEBUG*/// csNewStr - n/a

    xCHECK_RET(true == csStr.empty(),    csStr);
    xCHECK_RET(true == csOldStr.empty(), csStr);

    std::tstring_t sRes(csStr);

    size_t uiPos = 0;

    for ( ; ; ) {
        uiPos = sRes.find(csOldStr, uiPos);
        xCHECK_DO(std::tstring_t::npos == uiPos, break);

        sRes.replace(uiPos, csOldStr.size(), csNewStr);

        uiPos += csNewStr.size();
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sReplaceAll(
    const std::tstring_t &csStr,
    const tchar_t         cchOldStr,
    const tchar_t         cchNewStr
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// cchOldStr - n/a
    /*DEBUG*/// cchNewStr - n/a

    return sReplaceAll(csStr, std::tstring_t(1, cchOldStr), std::tstring_t(1, cchNewStr));
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sRemoveAll(
    const std::tstring_t &csStr,
    const std::tstring_t &csRemoveStr
)
{
    /*DEBUG*/// csStr      - n/a
    /*DEBUG*/// csRemoveStr - n/a

    return sReplaceAll(csStr, csRemoveStr, std::tstring_t());
}
//---------------------------------------------------------------------------
/*static*/
bool
CxString::bSplit(
    const std::tstring_t        &csStr,
    const std::tstring_t        &csSep,
    std::vector<std::tstring_t> *pvsOut
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// csSep    - n/a
    /*DEBUG*/// pvsOut - n/a

    xCHECK_RET(true == csStr.empty(), true);
    xCHECK_RET(true == csSep.empty(), true);
    xCHECK_RET(NULL == pvsOut,        false);

    std::vector<std::tstring_t> vsRes;
    size_t                    uiPrevPos = 0;     //start of string
    size_t                    uiPos     = 0;

    for ( ; ; ) {
        uiPos = csStr.find(csSep, uiPrevPos);
        xCHECK_DO(std::tstring_t::npos == uiPos, break);

        vsRes.push_back(csStr.substr(uiPrevPos, uiPos - uiPrevPos));

        uiPrevPos = uiPos + csSep.size();
    }
    vsRes.push_back( csStr.substr(uiPrevPos, csStr.size() - uiPrevPos) );

    //out
    std::swap(*pvsOut, vsRes);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sJoin(
    const std::vector<std::tstring_t> &cvsVec,
    const std::tstring_t              &csSep
)
{
    /*DEBUG*/// cvsVec - n/a
    /*DEBUG*/// csSep    - n/a

    std::tstring_t sRes;

    for (std::vector<std::tstring_t>::const_iterator it = cvsVec.begin(); it != cvsVec.end(); ++ it) {
        sRes.append(*it);

        xCHECK_DO(it < cvsVec.end() - 1, sRes.append(csSep));
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sJoin(
    const std::vector<std::tstring_t> &cvsVec,
    const tchar_t                      cchSep
)
{
    /*DEBUG*/// cvsVec - n/a
    /*DEBUG*/// csSep    - n/a

    return sJoin(cvsVec, std::tstring_t(1, cchSep));
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sCut(
    const std::tstring_t &csStr,
    const std::tstring_t &csLeftSep,
    const std::tstring_t &csRightSep
)
{
    /*DEBUG*/// csStr      - n/a
    /*DEBUG*/// csLeftSep  - n/a
    /*DEBUG*/// csRightSep - n/a

    size_t uiStartDelimPos = 0;
    size_t uiStopDelimPos  = 0;

    uiStartDelimPos = csStr.find(csLeftSep);
    xCHECK_RET(std::tstring_t::npos == uiStartDelimPos, std::tstring_t());
    uiStartDelimPos += csLeftSep.size();

    uiStopDelimPos  = csStr.rfind(csRightSep);
    xCHECK_RET(std::tstring_t::npos == uiStopDelimPos, std::tstring_t());

    xCHECK_RET(uiStartDelimPos     >= uiStopDelimPos, std::tstring_t());

    return csStr.substr(uiStartDelimPos, uiStopDelimPos - uiStartDelimPos);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sCut(
    const std::tstring_t &csStr,
    const size_t        cuiStartPos /*= 0*/,
    const size_t        cuiEndPos   /*= std::tstring_t:npos*/
)
{
    xCHECK_RET(true        == csStr.empty(), std::tstring_t());
    xCHECK_RET(cuiStartPos >  cuiEndPos,     std::tstring_t());

    size_t uiSize = ( (std::string::npos == cuiEndPos) ? (csStr.size()) : (cuiEndPos) ) - cuiStartPos/* + 1*/;

    return csStr.substr(cuiStartPos, uiSize);
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sToLowerCase(
    const std::tstring_t &csStr
)
{
    /*DEBUG*/// n/a

    return sToLowerCase(csStr, csStr.size());
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sToUpperCase(
    const std::tstring_t &csStr
)
{
    /*DEBUG*/// n/a

    return sToUpperCase(csStr, csStr.size());
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sToLowerCase(
    const std::tstring_t &csStr,
    size_t              uiLength
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csStr.empty(), std::tstring_t());
    xCHECK_DO (csStr.size() < uiLength, uiLength = csStr.size());

    std::tstring_t sRes(csStr);

#if xOS_ENV_WIN
    ulong_t ulRes = ::CharLowerBuff(static_cast<LPTSTR>( &sRes[0] ), uiLength);
    /*DEBUG*/xASSERT_RET(uiLength == ulRes, std::tstring_t());
#elif xOS_ENV_UNIX
    std::transform(sRes.begin(), sRes.begin() + uiLength, sRes.begin(), CxChar::chToLower);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sToUpperCase(
    const std::tstring_t &csStr,
    size_t              uiLength
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csStr.empty(), std::tstring_t());
    xCHECK_DO (csStr.size() < uiLength, uiLength = csStr.size());

    std::tstring_t sRes(csStr);

#if xOS_ENV_WIN
    ulong_t ulRes = ::CharUpperBuff(static_cast<LPTSTR>( &sRes[0] ), uiLength);
    /*DEBUG*/xASSERT_RET(uiLength == ulRes, std::tstring_t());
#elif xOS_ENV_UNIX
    std::transform(sRes.begin(), sRes.begin() + uiLength, sRes.begin(), CxChar::chToUpper);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxString::bCompareNoCase(
    const std::tstring_t &csStr1,
    const std::tstring_t &csStr2
)
{
    /*DEBUG*/// csStr1 - n/a
    /*DEBUG*/// csStr2 - n/a
    xCHECK_RET(csStr1.size() != csStr2.size(), false);

#if xOS_ENV_WIN
    int iRes = - 1;

    iRes = ::lstrcmpi(csStr1.c_str(), csStr2.c_str());
    /*DEBUG*/// n/a
    xCHECK_RET(0 != iRes, false);
#elif xOS_ENV_UNIX
    struct SCompare {
        static bool
        bNoCase(const std::tstring_t::value_type &cchChar1, const std::tstring_t::value_type &cchChar2) {
            return CxChar::chToUpper(cchChar1) == CxChar::chToUpper(cchChar2);
        }
    };

    bool bRes = std::equal(csStr1.begin(), csStr1.end(), csStr2.begin(), SCompare::bNoCase);
    xCHECK_RET(false == bRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    memory
*
*****************************************************************************/

//---------------------------------------------------------------------------
void *
CxString::pvMemoryZeroSecure(
    void   *pvBuff,
    size_t  uiBuffSize
)
{
    /*DEBUG*/// pvBuff     - n/a
    /*DEBUG*/// uiBuffSize - n/a

    for (volatile char *vpvBuff = static_cast<volatile char *>( pvBuff );
         NULL != pvBuff && 0 != uiBuffSize;
         ++ vpvBuff, -- uiBuffSize)
    {
        *vpvBuff = 0;
    }

    return pvBuff;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    other
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sFormat(
    const tchar_t *pcszFormat, ...
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == pcszFormat, std::tstring_t());

    std::tstring_t sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszFormat);

    sRes = sFormatV(pcszFormat, palArgs);

    xVA_END(palArgs);

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
#if 1
    std::tstring_t
    CxString::sFormatV(
        const tchar_t *pcszFormat,
        va_list      palArgs
    )
    {
        /*DEBUG*/// n/a
        xCHECK_RET(NULL == pcszFormat, std::tstring_t());

        std::tstring_t sBuff(64, 0);
        int          iWrittenSize = - 1;

        for ( ; ; ) {
            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);

            {
                iWrittenSize = ::xTVSNPRINTF(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
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
    CxString::sFormatV(
        LPCTSTR pcszFormat,
        va_list palArgs
    )
    {
        /*DEBUG*/// n/a
        xCHECK_RET(NULL == pcszFormat, std::tstring_t());

        std::tstring_t sBuff(64, 0);
        int          iWrittenSize = - 1;

        //--------------------------------------------------
        //calc size
        {
            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);
            iWrittenSize = ::xTVSNPRINTF(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
            xVA_END(_palArgs);

            /*DEBUG*/assert(- 1 < iWrittenSize);
            xCHECK_RET(0 >  iWrittenSize, std::tstring_t());
            xCHECK_RET(0 == iWrittenSize, sBuff);
        }

        //--------------------------------------------------
        //format
        if (sBuff.size() <= static_cast<size_t>( iWrittenSize )) {
            sBuff.resize(iWrittenSize + 1);

            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);
            iWrittenSize = std::xTVSNPRINTF(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
            xVA_END(_palArgs);

            /*DEBUG*/assert(- 1          <  iWrittenSize);
            /*DEBUG*/assert(sBuff.size() == static_cast<size_t>( iWrittenSize ) + 1);
            xCHECK_RET(0             >  iWrittenSize,                           std::tstring_t());
            xCHECK_RET(sBuff.size() != static_cast<size_t>( iWrittenSize ) + 1, std::tstring_t());
        }

        sBuff.resize(iWrittenSize);

        return sBuff;
    }
#endif
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sMinimize(
    const std::tstring_t &csStr,
    const size_t        cuiMaxLen
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csStr.empty(), std::tstring_t());
    xCHECK_RET(0    == cuiMaxLen,     std::tstring_t());

    std::tstring_t sRes;

    if (csStr.size() > cuiMaxLen) {
        if (cuiMaxLen < CxConst::x3DOT.size()) {
            sRes = csStr.substr(0, cuiMaxLen);
        } else {
            sRes = csStr.substr(0, cuiMaxLen - CxConst::x3DOT.size()) + CxConst::x3DOT;
        }
    } else {
        sRes = csStr;
    }

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sCreateGuid() {
    /*DEBUG*/// n/a

    std::tstring_t sRes;

#if xOS_ENV_WIN
    GUID    guidId = {0};
    HRESULT hrGuid = S_FALSE;

    hrGuid = CoCreateGuid(&guidId);
    /*DEBUG*/xASSERT_RET(SUCCEEDED(hrGuid), std::tstring_t());

    sRes = sFormat(
                xT("%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"),
                guidId.Data1,
                guidId.Data2,
                guidId.Data3,
                guidId.Data4[0], guidId.Data4[1],
                guidId.Data4[2], guidId.Data4[3], guidId.Data4[4], guidId.Data4[5], guidId.Data4[6], guidId.Data4[7]
    );
    /*DEBUG*/xASSERT_RET(false == sRes.empty(), std::tstring_t());
#elif xOS_ENV_UNIX
    //TODO: (sCreateGuid)
    //#include <uuid/uuid.h>
    xNOT_IMPLEMENTED_RET(std::tstring_t());
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
bool 
CxString::bIsRepeated(
    const std::tstring_t &csStr
)
{
    /*DEBUG*/// n/a

    return ( std::tstring_t::npos == csStr.find_first_not_of(csStr.at(0)) );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    coders
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sTranslitLatToRus(
    const std::tstring_t &csStr
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csStr.empty(), std::tstring_t());

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

    std::tstring_t sRes(csStr);

    for (size_t i = 0; i < xARRAY_SIZE(csDict); ++ i) {
        sRes = sReplaceAll(sRes, csDict[i][0], csDict[i][1]);
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sFormatBytes(
    const double cdBytes
)
{
    /*DEBUG*/// dBytes - n/a

    std::tstring_t sRes = xT("Uknown");

    const ulonglong_t cullTB   = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
    const ulonglong_t cullGB   = 1024ULL * 1024ULL * 1024ULL;
    const ulonglong_t cullMB   = 1024ULL * 1024ULL;
    const ulonglong_t cullKB   = 1024ULL;
    const ulonglong_t cullByte = 1ULL;

    if (     static_cast<ulonglong_t>(cdBytes) / cullTB   > 0ULL) {
        sRes = sFormat(xT("%.2f TB"),      cdBytes / static_cast<double>(cullTB));
    }
    else if (static_cast<ulonglong_t>(cdBytes) / cullGB   > 0ULL) {
        sRes = sFormat(xT("%.2f GB"),      cdBytes / static_cast<double>(cullGB));
    }
    else if (static_cast<ulonglong_t>(cdBytes) / cullMB   > 0ULL) {
        sRes = sFormat(xT("%.2f MB"),      cdBytes / static_cast<double>(cullMB));
    }
    else if (static_cast<ulonglong_t>(cdBytes) / cullKB   > 0ULL) {
        sRes = sFormat(xT("%.2f KB"),      cdBytes / static_cast<double>(cullKB));
    }
    else if (static_cast<ulonglong_t>(cdBytes) / cullByte > 0ULL) {
        sRes = sFormat(xT("%.2f Byte(s)"), cdBytes / static_cast<double>(cullByte));
    }
    else {
        sRes = sFormat(xT("%.2f Bit(s)"),  cdBytes);
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sFormatBytes(
    const ulonglong_t cullBytes
)
{
    /*DEBUG*/// ulBytes - n/a

    std::tstring_t sRes = xT("<uknown>");

    const ulonglong_t cullTB   = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
    const ulonglong_t cullGB   = 1024ULL * 1024ULL * 1024ULL;
    const ulonglong_t cullMB   = 1024ULL * 1024ULL;
    const ulonglong_t cullKB   = 1024ULL;
    const ulonglong_t cullByte = 1ULL;

    if (     cullBytes / cullTB   > 0ULL) {
        sRes = sFormat(xT("%.2f TB"),      static_cast<double>(cullBytes) / static_cast<double>(cullTB));
    }
    else if (cullBytes / cullGB   > 0ULL) {
        sRes = sFormat(xT("%.2f GB"),      static_cast<double>(cullBytes) / static_cast<double>(cullGB));
    }
    else if (cullBytes / cullMB   > 0ULL) {
        sRes = sFormat(xT("%.2f MB"),      static_cast<double>(cullBytes) / static_cast<double>(cullMB));
    }
    else if (cullBytes / cullKB   > 0ULL) {
        sRes = sFormat(xT("%.2f KB"),      static_cast<double>(cullBytes) / static_cast<double>(cullKB));
    }
    else if (cullBytes / cullByte > 0ULL) {
        sRes = sFormat(xT("%.2f Byte(s)"), static_cast<double>(cullBytes) / static_cast<double>(cullByte));
    }
    else {
        sRes = sFormat(xT("%.2f Bit(s)"),  static_cast<double>(cullBytes));
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sFormatPercentage(
    ulonglong_t ullMaxValue,
    ulonglong_t ullCurrValue
)
{
    /*DEBUG*/// ullMaxValue  - n/a
    /*DEBUG*/// ullCurrValue - n/a
    xCHECK_RET(0 == ullMaxValue, xT("0%"));    //devision by zero

    std::tstring_t sRes;

    sRes = lexical_cast( ullCurrValue * 100ULL / ullMaxValue );
    xCHECK_RET(true == sRes.empty(), xT("0%"));

    return sRes.append(xT("%"));
}
//---------------------------------------------------------------------------
/*static*/
std::wstring
CxString::sStrToWStr(
    const std::string &csStr,
    const uint_t         cuiCodePage
)
{
    /*DEBUG*/// csStr - n/a
    /*DEBUG*/// uiCodePage - n/a

    std::wstring wsRes;

#if xOS_ENV_WIN
    int iSize = ::MultiByteToWideChar(cuiCodePage, 0, csStr.c_str(), - 1, NULL, 0);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::wstring());

    wsRes.resize(iSize - 1);    //Р±РµР· '\0'
    iSize = ::MultiByteToWideChar(cuiCodePage, 0, csStr.c_str(), - 1, static_cast<LPWSTR>(&wsRes.at(0)), iSize);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::wstring());
#elif xOS_ENV_UNIX
    //TODO: (sStrToWStr)
    xNOT_IMPLEMENTED_RET(std::wstring());
#endif

    return wsRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string
CxString::sWStrToStr(
    const std::wstring &cwsStr,
    const uint_t          cuiCodePage
)
{
    /*DEBUG*/// cwsStr - n/a
    /*DEBUG*/// uiCodePage - n/a

    std::string asRes;

#if xOS_ENV_WIN
    int iSize = ::WideCharToMultiByte(cuiCodePage, 0, cwsStr.c_str(), - 1, NULL, 0, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::string());

    asRes.resize(iSize - 1);    //Р±РµР· '\0'
    iSize = ::WideCharToMultiByte(cuiCodePage, 0, cwsStr.c_str(), - 1, static_cast<LPSTR>(&asRes.at(0)), iSize, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::string());
#elif xOS_ENV_UNIX
    //TODO: (sWStrToStr)
    xNOT_IMPLEMENTED_RET(std::string());
#endif

    return asRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string
CxString::sConvertCodePage(
    const std::string &csSource,
    const uint_t         cuiCodePageSource,
    const uint_t         cuiCodePageDest
)
{
//    /*DEBUG*/xASSERT_RET(false == csSource.empty(), std::string());        //FIX: csStr    - n/a
//    /*DEBUG*/// uiCodePageSource
//    /*DEBUG*/// uiCodePageDest

    //CP_ACP(ANSI) <-> CP_UTF8(UTF-8)
    //1251  (WIN)  <-> 20866  (KOI-8r)

    return sWStrToStr(sStrToWStr(csSource, cuiCodePageSource), cuiCodePageDest);
}
//---------------------------------------------------------------------------
/*static*/
std::string
CxString::asCharToOemBuff(
    const std::tstring_t &csSrc
)
{
    std::string asDst;

#if xOS_ENV_WIN
    asDst.resize(csSrc.size());

    BOOL bRes = ::CharToOemBuff(csSrc.c_str(), &asDst.at(0), asDst.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::string());
#elif xOS_ENV_UNIX
    //TODO: asCharToOemBuff
    xNOT_IMPLEMENTED_RET(std::string());
#endif

    return asDst;
}
//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxString::sOemToCharBuff(
    const std::string &csSrc
)
{
    std::tstring_t sDst;

#if xOS_ENV_WIN
    sDst.resize(csSrc.size());

    BOOL bRes = ::OemToCharBuff(csSrc.c_str(), &sDst.at(0), sDst.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::tstring_t());
#elif xOS_ENV_UNIX
    //TODO: sOemToCharBuff
    xNOT_IMPLEMENTED_RET(std::tstring_t());
#endif

    return sDst;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    other
*
*****************************************************************************/

xNAMESPACE_END(NxLib)
