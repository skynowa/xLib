/****************************************************************************
* Class name:  CxString
* Description: strings
* File name:   CxString.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.04.2009 17:01:15
*
*****************************************************************************/


#include <xLib/Common/CxString.h>


#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxArray.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: sBoolToStr
/*static*/
tString
CxString::sBoolToStr(
    const BOOL cbBool
)
{
    /*DEBUG*/// bBool - n/a

    return (FALSE == cbBool) ? xT("FALSE") : xT("TRUE");
}
//---------------------------------------------------------------------------
//DONE: bStrToBool
/*static*/
BOOL
CxString::bStrToBool(
    const tString &csStr
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(FALSE != bCompareNoCase(xT("TRUE"),  csStr), TRUE);
    xCHECK_RET(FALSE != bCompareNoCase(xT("FALSE"), csStr), FALSE);

    return FALSE;
}
//---------------------------------------------------------------------------
//DONE: sTrimLeftChars
/*static*/
tString
CxString::sTrimLeftChars(
    const tString &csStr,
    const tString &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    tString sRes;
    sRes.assign(csStr);

    return sRes.erase(0, sRes.find_first_not_of(csChars));
}
//---------------------------------------------------------------------------
//DONE: sTrimRightChars
/*static*/
tString
CxString::sTrimRightChars(
    const tString &csStr,
    const tString &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    tString sRes;
    sRes.assign(csStr);

    return sRes.erase(sRes.find_last_not_of(csChars) + 1);
}
//---------------------------------------------------------------------------
//DONE: sTrimChars
/*static*/
tString
CxString::sTrimChars(
    const tString &csStr,
    const tString &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    tString sRes;
    sRes.assign(csStr);

    sRes.assign( sTrimRightChars(sRes, csChars) );
    sRes.assign( sTrimLeftChars (sRes, csChars) );

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sTrimSpace
/*static*/
tString
CxString::sTrimSpace(
    const tString &csStr
)
{
    /*DEBUG*/// csStr - n/a

    return sTrimChars(csStr, CxConst::xWHITE_SPACES);
}
//---------------------------------------------------------------------------
//DONE: sRemoveEol
/*static*/
tString
CxString::sRemoveEol(
    const tString &csStr
)
{
    /*DEBUG*/// csStr - n/a

    return sTrimRightChars(csStr, CxConst::xEOL);
}
//---------------------------------------------------------------------------
//DONE: sReplaceAll
/*static*/
tString
CxString::sReplaceAll(
    const tString &csStr,
    const tString &csOldStr,
    const tString &csNewStr
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// csOldStr - n/a
    /*DEBUG*/// csNewStr - n/a

    xCHECK_RET(true == csStr.empty(),    csStr);
    xCHECK_RET(true == csOldStr.empty(), csStr);

    tString sRes;
    sRes.assign(csStr);

    size_t uiPos = 0;

    for ( ; ; ) {
        uiPos = sRes.find(csOldStr, uiPos);
        xCHECK_DO(tString::npos == uiPos, break);

        sRes.replace(uiPos, csOldStr.size(), csNewStr);

        uiPos += csNewStr.size();
    }

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sReplaceAll
/*static*/
tString
CxString::sReplaceAll(
    const tString &csStr,
    const TCHAR    cchOldStr,
    const TCHAR    cchNewStr
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// cchOldStr - n/a
    /*DEBUG*/// cchNewStr - n/a

    return sReplaceAll(csStr, tString(1, cchOldStr), tString(1, cchNewStr));
}
//---------------------------------------------------------------------------
//DONE: sRemoveAll
/*static*/
tString
CxString::sRemoveAll(
    const tString &csStr,
    const tString &csRemoveStr
)
{
    /*DEBUG*/// csStr      - n/a
    /*DEBUG*/// csRemoveStr - n/a

    return sReplaceAll(csStr, csRemoveStr, tString());
}
//---------------------------------------------------------------------------
//DONE: разбивает строку на фрагменты по символу-разделителю, возвращая массив строк (vector)
/*static*/
BOOL
CxString::bSplit(
    const tString        &csStr,
    const tString        &csSep,
    std::vector<tString> *pvsOut
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// csSep    - n/a
    /*DEBUG*/// pvecsOut - n/a

    xCHECK_RET(true == csStr.empty(), TRUE);
    xCHECK_RET(true == csSep.empty(), TRUE);
    xCHECK_RET(NULL == pvsOut,        FALSE);

    std::vector<tString> vsRes;
    size_t               uiPrevPos = 0;     //start of string
    size_t               uiPos     = 0;

    for ( ; ; ) {
        uiPos = csStr.find(csSep, uiPrevPos);
        xCHECK_DO(tString::npos == uiPos, break);

        vsRes.push_back(csStr.substr(uiPrevPos, uiPos - uiPrevPos));

        uiPrevPos = uiPos + csSep.size();
    }
    vsRes.push_back( csStr.substr(uiPrevPos, csStr.size() - uiPrevPos) );

    //out
    std::swap(*pvsOut, vsRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sJoin ("склеивает" строки вектора символом-разделителем)
/*static*/
tString
CxString::sJoin(
    const std::vector<tString> &cvsVec,
    const tString              &csSep
)
{
    /*DEBUG*/// cvecsVec - n/a
    /*DEBUG*/// csSep    - n/a

    tString sRes;

    for (std::vector<tString>::const_iterator it = cvsVec.begin(); it != cvsVec.end(); ++ it) {
        sRes.append(*it);

        xCHECK_DO(it < cvsVec.end() - 1, sRes.append(csSep));
    }

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sJoin ("склеивает" строки вектора символом-разделителем)
/*static*/
tString
CxString::sJoin(
    const std::vector<tString> &cvsVec,
    const TCHAR                 cchSep
)
{
    /*DEBUG*/// cvecsVec - n/a
    /*DEBUG*/// csSep    - n/a

    return sJoin(cvsVec, tString(1, cchSep));
}
//---------------------------------------------------------------------------
//DONE: sCut
/*static*/
tString
CxString::sCut(
    const tString &csStr,
    const tString &csLeftSep,
    const tString &csRightSep
)
{
    /*DEBUG*/// csStr      - n/a
    /*DEBUG*/// csLeftSep  - n/a
    /*DEBUG*/// csRightSep - n/a

    size_t uiStartDelimPos = 0;
    size_t uiStopDelimPos  = 0;

    uiStartDelimPos = csStr.find(csLeftSep);
    xCHECK_RET(tString::npos == uiStartDelimPos, tString());
    uiStartDelimPos += csLeftSep.size();

    uiStopDelimPos  = csStr.rfind(csRightSep);
    xCHECK_RET(tString::npos == uiStopDelimPos, tString());

    xCHECK_RET(uiStartDelimPos >= uiStopDelimPos, tString());

    return csStr.substr(uiStartDelimPos, uiStopDelimPos - uiStartDelimPos);
}
//---------------------------------------------------------------------------
//DONE: sCut
/*static*/
tString
CxString::sCut(
    const tString &csStr,
    const size_t  cuiStartPos /*= 0*/,
    const size_t  cuiEndPos   /*= tString:npos*/
)
{
    /*
    + Если indexA = indexB, возвращается пустая строка
    + Если indexB не указан, substring возвращает символы до конца строки
    - Если какой-то из аргументов меньше 0 или является NaN - он считается равным 0
    + Если какой-то из аргументов больше, чем длина строки - он считается равным длине строки
    + Если indexA > indexB, тогда substring ведет себя, как будто аргументы поменялись местами.
    - Если строка не найдена, вызов возвращает -1
    */

    xCHECK_RET(true        == csStr.empty(), tString());
    xCHECK_RET(cuiStartPos >  cuiEndPos,     tString());

    size_t uiSize = ( (std::string::npos == cuiEndPos) ? (csStr.size()) : (cuiEndPos) ) - cuiStartPos/* + 1*/;

    return csStr.substr(cuiStartPos, uiSize);
}
//---------------------------------------------------------------------------
//DONE: sToLowerCase (convert to lowcase)
/*static*/
tString
CxString::sToLowerCase(
    const tString &csStr
)
{
    /*DEBUG*/// n/a

    return sToLowerCase(csStr, csStr.size());
}
//---------------------------------------------------------------------------
//DONE: sToUpperCase (convert to uppercase)
/*static*/
tString
CxString::sToUpperCase(
    const tString &csStr
)
{
    /*DEBUG*/// n/a

    return sToUpperCase(csStr, csStr.size());
}
//---------------------------------------------------------------------------
//DONE: sToLowerCase
/*static*/
tString
CxString::sToLowerCase(
    const tString &csStr,
    size_t         uiLength
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csStr.empty(), tString());
    xCHECK_DO (csStr.size() < uiLength, uiLength = csStr.size());

    tString sRes;
    sRes.assign(csStr);

#if defined(xOS_WIN)
    ULONG ulRes = ::CharLowerBuff(static_cast<LPTSTR>( &sRes[0] ), uiLength);
    /*DEBUG*/xASSERT_RET(uiLength == ulRes, tString());
#elif defined(xOS_LINUX)
    std::transform(sRes.begin(), sRes.begin() + uiLength, sRes.begin(), CxChar::chToLower);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sToUpperCase
/*static*/
tString
CxString::sToUpperCase(
    const tString &csStr,
    size_t         uiLength
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csStr.empty(), tString());
    xCHECK_DO (csStr.size() < uiLength, uiLength = csStr.size());

    tString sRes;
    sRes.assign(csStr);

#if defined(xOS_WIN)
    ULONG ulRes = ::CharUpperBuff(static_cast<LPTSTR>( &sRes[0] ), uiLength);
    /*DEBUG*/xASSERT_RET(uiLength == ulRes, tString());
#elif defined(xOS_LINUX)
    std::transform(sRes.begin(), sRes.begin() + uiLength, sRes.begin(), CxChar::chToUpper);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bCompareNoCase (Compares two character strings. The comparison is not case-sensitive.)
/*static*/
BOOL
CxString::bCompareNoCase(
    const tString &csStr1,
    const tString &csStr2
)
{
    /*DEBUG*/// csStr1 - n/a
    /*DEBUG*/// csStr2 - n/a
    xCHECK_RET(csStr1.size() != csStr2.size(), FALSE);

#if defined(xOS_WIN)
    INT iRes = - 1;

    iRes = ::lstrcmpi(csStr1.c_str(), csStr2.c_str());
    /*DEBUG*/// n/a
    xCHECK_RET(0 != iRes, FALSE);
#elif defined(xOS_LINUX)
    struct SCompare {
        static bool
        bNoCase(const tString::value_type &cchChar1, const tString::value_type &cchChar2) {
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
//DONE: pvMemoryZeroSecure (secure zero memory)
VOID *
CxString::pvMemoryZeroSecure(
    VOID   *pvBuff,
    size_t  uiBuffSize)
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
//DONE: sFormat
/*static*/
tString
CxString::sFormat(
    LPCTSTR pcszFormat, ...
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == pcszFormat, tString());

    tString sRes;

    va_list palArgs;
    va_start(palArgs, pcszFormat);

    sRes = sFormatV(pcszFormat, palArgs);

    va_end(palArgs);

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sFormatV
/*static*/
#if xDEPRECIATE
    tString
    CxString::sFormatV(
        LPCTSTR pcszFormat,
        va_list palArgs
    )
    {
        /*DEBUG*/// n/a
        xCHECK_RET(NULL == pcszFormat, tString());

        tString sBuff;
        size_t  uiWrittenSize = static_cast<size_t>( - 1 );

        sBuff.resize(128);

        for ( ; ; ) {
            va_list _palArgs;
            va_copy(_palArgs, palArgs);

            {
                uiWrittenSize = static_cast<size_t>( _vsntprintf(&sBuff.at(0), sBuff.size() - 1, pcszFormat, _palArgs) );
                xCHECK_DO(uiWrittenSize != static_cast<size_t>( - 1 ) && uiWrittenSize < sBuff.size(), break);    //FIX: downcast

                sBuff.resize(sBuff.size() * 2);
            }

            va_end(_palArgs);
        }

        sBuff.resize(uiWrittenSize);

        return sBuff;
    }
#else
    tString
    CxString::sFormatV(
        LPCTSTR pcszFormat,
        va_list palArgs
    )
    {
        /*DEBUG*/// n/a
        xCHECK_RET(NULL == pcszFormat, tString());

        tString sBuff(128, 0);
        INT     iWrittenSize = - 1;

        for ( ; ; ) {
            va_list _palArgs;
            va_copy(_palArgs, palArgs);

            {
                iWrittenSize = _vsntprintf(&sBuff.at(0), sBuff.size() - 1, pcszFormat, _palArgs);
                xCHECK_DO(iWrittenSize > - 1 && iWrittenSize < static_cast<INT>( sBuff.size() ), break);    //FIX: downcast

                sBuff.resize(sBuff.size() * 2);
            }

            va_end(_palArgs);
        }

        sBuff.resize(iWrittenSize);

        return sBuff;
    }
#endif
//---------------------------------------------------------------------------
//DONE: sMinimize
/*static*/
tString
CxString::sMinimize(
    const tString &csStr,
    const size_t   cuiMaxLen
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csStr.empty(), tString());
    xCHECK_RET(0    == cuiMaxLen,     tString());

    tString sRes;

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
//DONE: sCreateGuid (generate GUID)
/*static*/
tString
CxString::sCreateGuid() {
    /*DEBUG*/// n/a

    tString sRes;

#if defined(xOS_WIN)
    GUID    guidId = {0};
    HRESULT hrGuid = S_FALSE;

    hrGuid = CoCreateGuid(&guidId);
    /*DEBUG*/xASSERT_RET(SUCCEEDED(hrGuid), tString());

    sRes = sFormat(
                xT("%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"),
                guidId.Data1,
                guidId.Data2,
                guidId.Data3,
                guidId.Data4[0], guidId.Data4[1],
                guidId.Data4[2], guidId.Data4[3], guidId.Data4[4], guidId.Data4[5], guidId.Data4[6], guidId.Data4[7]
    );
    /*DEBUG*/xASSERT_RET(false == sRes.empty(), tString());
#elif defined(xOS_LINUX)
    //TODO: (sCreateGuid)
    //#include <uuid/uuid.h>
    xNOT_IMPLEMENTED_RET(tString());
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bIsRepeated
/*static*/
BOOL CxString::bIsRepeated(
    const tString &csStr
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( tString::npos == csStr.find_first_not_of(csStr.at(0)) );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    coders
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: sTranslitLatToRus
/*static*/
tString
CxString::sTranslitLatToRus(
    const tString &csStr
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csStr.empty(), tString());

    //translit table
    const tString csDict[][2] = {
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

    tString sRes;
    sRes.assign(csStr);

    for (size_t i = 0; i < xARRAY_SIZE(csDict); ++ i) {
        sRes.assign( sReplaceAll(sRes, csDict[i][0], csDict[i][1]) );
    }

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sFormatBytes (форматирование байтов в Bits, Bytes, KB, MB, GB)
/*static*/
tString
CxString::sFormatBytes(
    const DOUBLE cdBytes
)
{
    /*DEBUG*/// dBytes - n/a

    tString sRes = xT("Uknown");

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
//DONE: sFormatBytes (форматирование байтов в Bits, Bytes, KB, MB, GB)
/*static*/
tString
CxString::sFormatBytes(
    const ULONGLONG cullBytes
)
{
    /*DEBUG*/// ulBytes - n/a

    tString sRes = xT("<uknown>");

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
//DONE: sFormatPercentage (formatting percentage)
/*static*/
tString
CxString::sFormatPercentage(
    ULONGLONG ullMaxValue,
    ULONGLONG ullCurrValue
)
{
    /*DEBUG*/// ullMaxValue  - n/a
    /*DEBUG*/// ullCurrValue - n/a
    xCHECK_RET(0 == ullMaxValue, xT("0%"));    //devision by zero

    tString sRes;

    sRes = lexical_cast( ullCurrValue * 100ULL / ullMaxValue );
    xCHECK_RET(true == sRes.empty(), xT("0%"));

    return sRes.append(xT("%"));
}
//---------------------------------------------------------------------------
//DONE: sFormatNixTerminal (format Linux terminal colors)
//NOTE: http://lifeforce4.wordpress.com/
/*static*/
tString
CxString::sFormatNixTerminal(
    const tString &csText,
    EForeground    fgForeground,
    BOOL           bIsBold,
    BOOL           bIsUnderline,
    EBackground    bgBackground,
    BOOL           bIsBlink
)
{
    /*DEBUG*/// n/a

    tString sRes;

    xCHECK_DO(TRUE == bIsUnderline, sRes += CxString::sFormat(xT("\033[%im"), atUnderscore));
    xCHECK_DO(TRUE == bIsBlink,     sRes += CxString::sFormat(xT("\033[%im"), atBlink)     );
    xCHECK_DO(TRUE == bIsBold,      sRes += CxString::sFormat(xT("\033[%im"), atBold)      );

    sRes += CxString::sFormat(xT("\033[%im"), bgBackground);
    sRes += CxString::sFormat(xT("\033[%im"), fgForeground);
    sRes += csText;
    sRes += xT("\033[0;0m");

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sStrToWStr (std::string in std::wstring)
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

#if defined(xOS_WIN)
    INT iSize = ::MultiByteToWideChar(cuiCodePage, 0, csStr.c_str(), - 1, NULL, 0);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::wstring());

    wsRes.resize(iSize - 1);    //без '\0'
    iSize = ::MultiByteToWideChar(cuiCodePage, 0, csStr.c_str(), - 1, static_cast<LPWSTR>(&wsRes.at(0)), iSize);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::wstring());
#elif defined(xOS_LINUX)
    //TODO: (sStrToWStr)
    xNOT_IMPLEMENTED_RET(std::wstring());
#endif

    return wsRes;
}
//---------------------------------------------------------------------------
//DONE: sWStrToStr (std::wstring in std::string)
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

#if defined(xOS_WIN)
    INT iSize = ::WideCharToMultiByte(cuiCodePage, 0, cwsStr.c_str(), - 1, NULL, 0, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::string());

    asRes.resize(iSize - 1);    //без '\0'
    iSize = ::WideCharToMultiByte(cuiCodePage, 0, cwsStr.c_str(), - 1, static_cast<LPSTR>(&asRes.at(0)), iSize, NULL, NULL);
    /*DEBUG*/xASSERT_RET(0 < iSize, std::string());
#elif defined(xOS_LINUX)
    //TODO: (sWStrToStr)
    xNOT_IMPLEMENTED_RET(std::string());
#endif

    return asRes;
}
//---------------------------------------------------------------------------
//DONE: sConvertCodePage (convert codepage)
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
//TODO: asCharToOemBuff
/*static*/
std::string
CxString::asCharToOemBuff(
    const tString &csSrc
)
{
    std::string asDst;

#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    asDst.resize(csSrc.size());

    bRes = ::CharToOemBuff(csSrc.c_str(), &asDst.at(0), asDst.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::string());
#elif defined(xOS_LINUX)
    //TODO: (asCharToOemBuff)
    xNOT_IMPLEMENTED_RET(std::string());
#endif

    return asDst;
}
//---------------------------------------------------------------------------
//TODO: sOemToCharBuff
/*static*/
tString
CxString::sOemToCharBuff(
    const std::string &csSrc
)
{
    tString sDst;

#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    sDst.resize(csSrc.size());

    bRes = ::OemToCharBuff(csSrc.c_str(), &sDst.at(0), sDst.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, tString());
#elif defined(xOS_LINUX)
    //TODO: (sOemToCharBuff)
    xNOT_IMPLEMENTED_RET(tString());
#endif

    return sDst;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    other
*
*****************************************************************************/

