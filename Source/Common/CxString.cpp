/**
 * \file  CxString.cpp
 * \brief string utils
 */


#include <xLib/Common/CxString.h>


#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxArray.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sBoolToStr(
    const BOOL cbBool
)
{
    /*DEBUG*/// bBool - n/a

    return (FALSE == cbBool) ? xT("FALSE") : xT("TRUE");
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxString::bStrToBool(
    const std::string_t &csStr
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(FALSE != bCompareNoCase(xT("TRUE"),  csStr), TRUE);
    xCHECK_RET(FALSE != bCompareNoCase(xT("FALSE"), csStr), FALSE);

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sTrimLeftChars(
    const std::string_t &csStr,
    const std::string_t &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::string_t sRes;
    sRes.assign(csStr);

    return sRes.erase(0, sRes.find_first_not_of(csChars));
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sTrimRightChars(
    const std::string_t &csStr,
    const std::string_t &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::string_t sRes;
    sRes.assign(csStr);

    return sRes.erase(sRes.find_last_not_of(csChars) + 1);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sTrimChars(
    const std::string_t &csStr,
    const std::string_t &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::string_t sRes;
    sRes.assign(csStr);

    sRes.assign( sTrimRightChars(sRes, csChars) );
    sRes.assign( sTrimLeftChars (sRes, csChars) );

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sTrimSpace(
    const std::string_t &csStr
)
{
    /*DEBUG*/// csStr - n/a

    return sTrimChars(csStr, CxConst::xWHITE_SPACES);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sRemoveEol(
    const std::string_t &csStr
)
{
    /*DEBUG*/// csStr - n/a

    return sTrimRightChars(csStr, CxConst::xEOL);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sReplaceAll(
    const std::string_t &csStr,
    const std::string_t &csOldStr,
    const std::string_t &csNewStr
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// csOldStr - n/a
    /*DEBUG*/// csNewStr - n/a

    xCHECK_RET(true == csStr.empty(),    csStr);
    xCHECK_RET(true == csOldStr.empty(), csStr);

    std::string_t sRes;
    sRes.assign(csStr);

    size_t uiPos = 0;

    for ( ; ; ) {
        uiPos = sRes.find(csOldStr, uiPos);
        xCHECK_DO(std::string_t::npos == uiPos, break);

        sRes.replace(uiPos, csOldStr.size(), csNewStr);

        uiPos += csNewStr.size();
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sReplaceAll(
    const std::string_t &csStr,
    const TCHAR         cchOldStr,
    const TCHAR         cchNewStr
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// cchOldStr - n/a
    /*DEBUG*/// cchNewStr - n/a

    return sReplaceAll(csStr, std::string_t(1, cchOldStr), std::string_t(1, cchNewStr));
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sRemoveAll(
    const std::string_t &csStr,
    const std::string_t &csRemoveStr
)
{
    /*DEBUG*/// csStr      - n/a
    /*DEBUG*/// csRemoveStr - n/a

    return sReplaceAll(csStr, csRemoveStr, std::string_t());
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxString::bSplit(
    const std::string_t        &csStr,
    const std::string_t        &csSep,
    std::vector<std::string_t> *pvsOut
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// csSep    - n/a
    /*DEBUG*/// pvsOut - n/a

    xCHECK_RET(true == csStr.empty(), TRUE);
    xCHECK_RET(true == csSep.empty(), TRUE);
    xCHECK_RET(NULL == pvsOut,        FALSE);

    std::vector<std::string_t> vsRes;
    size_t                    uiPrevPos = 0;     //start of string
    size_t                    uiPos     = 0;

    for ( ; ; ) {
        uiPos = csStr.find(csSep, uiPrevPos);
        xCHECK_DO(std::string_t::npos == uiPos, break);

        vsRes.push_back(csStr.substr(uiPrevPos, uiPos - uiPrevPos));

        uiPrevPos = uiPos + csSep.size();
    }
    vsRes.push_back( csStr.substr(uiPrevPos, csStr.size() - uiPrevPos) );

    //out
    std::swap(*pvsOut, vsRes);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sJoin(
    const std::vector<std::string_t> &cvsVec,
    const std::string_t              &csSep
)
{
    /*DEBUG*/// cvsVec - n/a
    /*DEBUG*/// csSep    - n/a

    std::string_t sRes;

    for (std::vector<std::string_t>::const_iterator it = cvsVec.begin(); it != cvsVec.end(); ++ it) {
        sRes.append(*it);

        xCHECK_DO(it < cvsVec.end() - 1, sRes.append(csSep));
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sJoin(
    const std::vector<std::string_t> &cvsVec,
    const TCHAR                      cchSep
)
{
    /*DEBUG*/// cvsVec - n/a
    /*DEBUG*/// csSep    - n/a

    return sJoin(cvsVec, std::string_t(1, cchSep));
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sCut(
    const std::string_t &csStr,
    const std::string_t &csLeftSep,
    const std::string_t &csRightSep
)
{
    /*DEBUG*/// csStr      - n/a
    /*DEBUG*/// csLeftSep  - n/a
    /*DEBUG*/// csRightSep - n/a

    size_t uiStartDelimPos = 0;
    size_t uiStopDelimPos  = 0;

    uiStartDelimPos = csStr.find(csLeftSep);
    xCHECK_RET(std::string_t::npos == uiStartDelimPos, std::string_t());
    uiStartDelimPos += csLeftSep.size();

    uiStopDelimPos  = csStr.rfind(csRightSep);
    xCHECK_RET(std::string_t::npos == uiStopDelimPos, std::string_t());

    xCHECK_RET(uiStartDelimPos >= uiStopDelimPos, std::string_t());

    return csStr.substr(uiStartDelimPos, uiStopDelimPos - uiStartDelimPos);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sCut(
    const std::string_t &csStr,
    const size_t        cuiStartPos /*= 0*/,
    const size_t        cuiEndPos   /*= std::string_t:npos*/
)
{
    xCHECK_RET(true        == csStr.empty(), std::string_t());
    xCHECK_RET(cuiStartPos >  cuiEndPos,     std::string_t());

    size_t uiSize = ( (std::string::npos == cuiEndPos) ? (csStr.size()) : (cuiEndPos) ) - cuiStartPos/* + 1*/;

    return csStr.substr(cuiStartPos, uiSize);
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sToLowerCase(
    const std::string_t &csStr
)
{
    /*DEBUG*/// n/a

    return sToLowerCase(csStr, csStr.size());
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sToUpperCase(
    const std::string_t &csStr
)
{
    /*DEBUG*/// n/a

    return sToUpperCase(csStr, csStr.size());
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sToLowerCase(
    const std::string_t &csStr,
    size_t              uiLength
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csStr.empty(), std::string_t());
    xCHECK_DO (csStr.size() < uiLength, uiLength = csStr.size());

    std::string_t sRes;
    sRes.assign(csStr);

#if defined(xOS_ENV_WIN)
    ULONG ulRes = ::CharLowerBuff(static_cast<LPTSTR>( &sRes[0] ), uiLength);
    /*DEBUG*/xASSERT_RET(uiLength == ulRes, std::string_t());
#elif defined(xOS_ENV_UNIX)
    std::transform(sRes.begin(), sRes.begin() + uiLength, sRes.begin(), CxChar::chToLower);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sToUpperCase(
    const std::string_t &csStr,
    size_t              uiLength
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csStr.empty(), std::string_t());
    xCHECK_DO (csStr.size() < uiLength, uiLength = csStr.size());

    std::string_t sRes;
    sRes.assign(csStr);

#if defined(xOS_ENV_WIN)
    ULONG ulRes = ::CharUpperBuff(static_cast<LPTSTR>( &sRes[0] ), uiLength);
    /*DEBUG*/xASSERT_RET(uiLength == ulRes, std::string_t());
#elif defined(xOS_ENV_UNIX)
    std::transform(sRes.begin(), sRes.begin() + uiLength, sRes.begin(), CxChar::chToUpper);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxString::bCompareNoCase(
    const std::string_t &csStr1,
    const std::string_t &csStr2
)
{
    /*DEBUG*/// csStr1 - n/a
    /*DEBUG*/// csStr2 - n/a
    xCHECK_RET(csStr1.size() != csStr2.size(), FALSE);

#if defined(xOS_ENV_WIN)
    INT iRes = - 1;

    iRes = ::lstrcmpi(csStr1.c_str(), csStr2.c_str());
    /*DEBUG*/// n/a
    xCHECK_RET(0 != iRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    struct SCompare {
        static bool
        bNoCase(const std::string_t::value_type &cchChar1, const std::string_t::value_type &cchChar2) {
            return CxChar::chToUpper(cchChar1) == CxChar::chToUpper(cchChar2);
        }
    };

    bool bRes = std::equal(csStr1.begin(), csStr1.end(), csStr2.begin(), SCompare::bNoCase);
    xCHECK_RET(false == bRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    memory
*
*****************************************************************************/

//---------------------------------------------------------------------------
VOID *
CxString::pvMemoryZeroSecure(
    VOID   *pvBuff,
    size_t  uiBuffSize
)
{
    /*DEBUG*/// pvBuff     - n/a
    /*DEBUG*/// uiBuffSize - n/a

    for (volatile CHAR *vpvBuff = static_cast<volatile CHAR *>( pvBuff );
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
std::string_t
CxString::sFormat(
    const TCHAR *pcszFormat, ...
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == pcszFormat, std::string_t());

    std::string_t sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszFormat);

    sRes = sFormatV(pcszFormat, palArgs);

    xVA_END(palArgs);

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
#if 1
    std::string_t
    CxString::sFormatV(
        const TCHAR *pcszFormat,
        va_list      palArgs
    )
    {
        /*DEBUG*/// n/a
        xCHECK_RET(NULL == pcszFormat, std::string_t());

        std::string_t sBuff(64, 0);
        INT          iWrittenSize = - 1;

        for ( ; ; ) {
            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);

            {
                iWrittenSize = xTVSNPRINTF(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
                xCHECK_DO(iWrittenSize > - 1 && static_cast<size_t>( iWrittenSize ) < sBuff.size(), break);

                sBuff.resize(sBuff.size() * 2);
            }

            xVA_END(_palArgs);
        }

        sBuff.resize(iWrittenSize);

        return sBuff;
    }
#else
    std::string_t
    CxString::sFormatV(
        LPCTSTR pcszFormat,
        va_list palArgs
    )
    {
        /*DEBUG*/// n/a
        xCHECK_RET(NULL == pcszFormat, std::string_t());

        std::string_t sBuff(64, 0);
        INT          iWrittenSize = - 1;

        //--------------------------------------------------
        //calc size
        {
            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);
            iWrittenSize = xTVSNPRINTF(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
            xVA_END(_palArgs);

            /*DEBUG*/assert(- 1 < iWrittenSize);
            xCHECK_RET(0 >  iWrittenSize, std::string_t());
            xCHECK_RET(0 == iWrittenSize, sBuff);
        }

        //--------------------------------------------------
        //format
        if (sBuff.size() <= static_cast<size_t>( iWrittenSize )) {
            sBuff.resize(iWrittenSize + 1);

            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);
            iWrittenSize = xTVSNPRINTF(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
            xVA_END(_palArgs);

            /*DEBUG*/assert(- 1          <  iWrittenSize);
            /*DEBUG*/assert(sBuff.size() == static_cast<size_t>( iWrittenSize ) + 1);
            xCHECK_RET(0             >  iWrittenSize,                           std::string_t());
            xCHECK_RET(sBuff.size() != static_cast<size_t>( iWrittenSize ) + 1, std::string_t());
        }

        sBuff.resize(iWrittenSize);

        return sBuff;
    }
#endif
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sMinimize(
    const std::string_t &csStr,
    const size_t        cuiMaxLen
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csStr.empty(), std::string_t());
    xCHECK_RET(0    == cuiMaxLen,     std::string_t());

    std::string_t sRes;

    if (csStr.size() > cuiMaxLen) {
        if (cuiMaxLen < CxConst::x3DOT.size()) {
            sRes = csStr.substr(0, cuiMaxLen);
        } else {
            sRes = csStr.substr(0, cuiMaxLen - CxConst::x3DOT.size()) + CxConst::x3DOT;
        }
    } else {
        sRes.assign(csStr);
    }

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sCreateGuid() {
    /*DEBUG*/// n/a

    std::string_t sRes;

#if defined(xOS_ENV_WIN)
    GUID    guidId = {0};
    HRESULT hrGuid = S_FALSE;

    hrGuid = CoCreateGuid(&guidId);
    /*DEBUG*/xASSERT_RET(SUCCEEDED(hrGuid), std::string_t());

    sRes = sFormat(
                xT("%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"),
                guidId.Data1,
                guidId.Data2,
                guidId.Data3,
                guidId.Data4[0], guidId.Data4[1],
                guidId.Data4[2], guidId.Data4[3], guidId.Data4[4], guidId.Data4[5], guidId.Data4[6], guidId.Data4[7]
    );
    /*DEBUG*/xASSERT_RET(false == sRes.empty(), std::string_t());
#elif defined(xOS_ENV_UNIX)
    //TODO: (sCreateGuid)
    //#include <uuid/uuid.h>
    xNOT_IMPLEMENTED_RET(std::string_t());
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL CxString::bIsRepeated(
    const std::string_t &csStr
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( std::string_t::npos == csStr.find_first_not_of(csStr.at(0)) );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    coders
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sTranslitLatToRus(
    const std::string_t &csStr
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csStr.empty(), std::string_t());

    //translit table
    const std::string_t csDict[][2] = {
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

    std::string_t sRes;
    sRes.assign(csStr);

    for (size_t i = 0; i < xARRAY_SIZE(csDict); ++ i) {
        sRes.assign( sReplaceAll(sRes, csDict[i][0], csDict[i][1]) );
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sFormatBytes(
    const DOUBLE cdBytes
)
{
    /*DEBUG*/// dBytes - n/a

    std::string_t sRes = xT("Uknown");

    const ULONGLONG cullTB   = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
    const ULONGLONG cullGB   = 1024ULL * 1024ULL * 1024ULL;
    const ULONGLONG cullMB   = 1024ULL * 1024ULL;
    const ULONGLONG cullKB   = 1024ULL;
    const ULONGLONG cullByte = 1ULL;

    if (     static_cast<ULONGLONG>(cdBytes) / cullTB   > 0ULL) {
        sRes = sFormat(xT("%.2f TB"),      cdBytes / static_cast<DOUBLE>(cullTB));
    }
    else if (static_cast<ULONGLONG>(cdBytes) / cullGB   > 0ULL) {
        sRes = sFormat(xT("%.2f GB"),      cdBytes / static_cast<DOUBLE>(cullGB));
    }
    else if (static_cast<ULONGLONG>(cdBytes) / cullMB   > 0ULL) {
        sRes = sFormat(xT("%.2f MB"),      cdBytes / static_cast<DOUBLE>(cullMB));
    }
    else if (static_cast<ULONGLONG>(cdBytes) / cullKB   > 0ULL) {
        sRes = sFormat(xT("%.2f KB"),      cdBytes / static_cast<DOUBLE>(cullKB));
    }
    else if (static_cast<ULONGLONG>(cdBytes) / cullByte > 0ULL) {
        sRes = sFormat(xT("%.2f Byte(s)"), cdBytes / static_cast<DOUBLE>(cullByte));
    }
    else {
        sRes = sFormat(xT("%.2f Bit(s)"),  cdBytes);
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sFormatBytes(
    const ULONGLONG cullBytes
)
{
    /*DEBUG*/// ulBytes - n/a

    std::string_t sRes = xT("<uknown>");

    const ULONGLONG cullTB   = 1024ULL * 1024ULL * 1024ULL * 1024ULL;
    const ULONGLONG cullGB   = 1024ULL * 1024ULL * 1024ULL;
    const ULONGLONG cullMB   = 1024ULL * 1024ULL;
    const ULONGLONG cullKB   = 1024ULL;
    const ULONGLONG cullByte = 1ULL;

    if (     cullBytes / cullTB   > 0ULL) {
        sRes = sFormat(xT("%.2f TB"),      static_cast<DOUBLE>(cullBytes) / static_cast<DOUBLE>(cullTB));
    }
    else if (cullBytes / cullGB   > 0ULL) {
        sRes = sFormat(xT("%.2f GB"),      static_cast<DOUBLE>(cullBytes) / static_cast<DOUBLE>(cullGB));
    }
    else if (cullBytes / cullMB   > 0ULL) {
        sRes = sFormat(xT("%.2f MB"),      static_cast<DOUBLE>(cullBytes) / static_cast<DOUBLE>(cullMB));
    }
    else if (cullBytes / cullKB   > 0ULL) {
        sRes = sFormat(xT("%.2f KB"),      static_cast<DOUBLE>(cullBytes) / static_cast<DOUBLE>(cullKB));
    }
    else if (cullBytes / cullByte > 0ULL) {
        sRes = sFormat(xT("%.2f Byte(s)"), static_cast<DOUBLE>(cullBytes) / static_cast<DOUBLE>(cullByte));
    }
    else {
        sRes = sFormat(xT("%.2f Bit(s)"),  static_cast<DOUBLE>(cullBytes));
    }

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sFormatPercentage(
    ULONGLONG ullMaxValue,
    ULONGLONG ullCurrValue
)
{
    /*DEBUG*/// ullMaxValue  - n/a
    /*DEBUG*/// ullCurrValue - n/a
    xCHECK_RET(0 == ullMaxValue, xT("0%"));    //devision by zero

    std::string_t sRes;

    sRes = lexical_cast( ullCurrValue * 100ULL / ullMaxValue );
    xCHECK_RET(true == sRes.empty(), xT("0%"));

    return sRes.append(xT("%"));
}
//---------------------------------------------------------------------------
/*static*/
std::wstring
CxString::sStrToWStr(
    const std::string &csStr,
    const UINT         cuiCodePage
)
{
    /*DEBUG*/// csStr - n/a
    /*DEBUG*/// uiCodePage - n/a

    std::wstring wsRes;

#if defined(xOS_ENV_WIN)
    INT iSize = ::MultiByteToWideChar(cuiCodePage, 0, csStr.c_str(), - 1, NULL, 0);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::wstring());

    wsRes.resize(iSize - 1);    //Р±РµР· '\0'
    iSize = ::MultiByteToWideChar(cuiCodePage, 0, csStr.c_str(), - 1, static_cast<LPWSTR>(&wsRes.at(0)), iSize);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::wstring());
#elif defined(xOS_ENV_UNIX)
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
    const UINT          cuiCodePage
)
{
    /*DEBUG*/// cwsStr - n/a
    /*DEBUG*/// uiCodePage - n/a

    std::string asRes;

#if defined(xOS_ENV_WIN)
    INT iSize = ::WideCharToMultiByte(cuiCodePage, 0, cwsStr.c_str(), - 1, NULL, 0, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::string());

    asRes.resize(iSize - 1);    //Р±РµР· '\0'
    iSize = ::WideCharToMultiByte(cuiCodePage, 0, cwsStr.c_str(), - 1, static_cast<LPSTR>(&asRes.at(0)), iSize, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::string());
#elif defined(xOS_ENV_UNIX)
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
    const UINT         cuiCodePageSource,
    const UINT         cuiCodePageDest
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
    const std::string_t &csSrc
)
{
    std::string asDst;

#if defined(xOS_ENV_WIN)
    BOOL bRes = FALSE;

    asDst.resize(csSrc.size());

    bRes = ::CharToOemBuff(csSrc.c_str(), &asDst.at(0), asDst.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::string());
#elif defined(xOS_ENV_UNIX)
    //TODO: asCharToOemBuff
    xNOT_IMPLEMENTED_RET(std::string());
#endif

    return asDst;
}
//---------------------------------------------------------------------------
/*static*/
std::string_t
CxString::sOemToCharBuff(
    const std::string &csSrc
)
{
    std::string_t sDst;

#if defined(xOS_ENV_WIN)
    BOOL bRes = FALSE;

    sDst.resize(csSrc.size());

    bRes = ::OemToCharBuff(csSrc.c_str(), &sDst.at(0), sDst.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::string_t());
#elif defined(xOS_ENV_UNIX)
    //TODO: sOemToCharBuff
    xNOT_IMPLEMENTED_RET(std::string_t());
#endif

    return sDst;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    other
*
*****************************************************************************/
