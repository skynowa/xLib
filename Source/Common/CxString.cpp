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
//DONE: sBoolToStr
/*static*/
std::tstring
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
    const std::tstring &csStr
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
std::tstring
CxString::sTrimLeftChars(
    const std::tstring &csStr,
    const std::tstring &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::tstring sRes;
    sRes.assign(csStr);

    return sRes.erase(0, sRes.find_first_not_of(csChars));
}
//---------------------------------------------------------------------------
//DONE: sTrimRightChars
/*static*/
std::tstring
CxString::sTrimRightChars(
    const std::tstring &csStr,
    const std::tstring &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::tstring sRes;
    sRes.assign(csStr);

    return sRes.erase(sRes.find_last_not_of(csChars) + 1);
}
//---------------------------------------------------------------------------
//DONE: sTrimChars
/*static*/
std::tstring
CxString::sTrimChars(
    const std::tstring &csStr,
    const std::tstring &csChars
)
{
    /*DEBUG*/// csStr   - n/a
    /*DEBUG*/// csChars - n/a

    std::tstring sRes;
    sRes.assign(csStr);

    sRes.assign( sTrimRightChars(sRes, csChars) );
    sRes.assign( sTrimLeftChars (sRes, csChars) );

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sTrimSpace
/*static*/
std::tstring
CxString::sTrimSpace(
    const std::tstring &csStr
)
{
    /*DEBUG*/// csStr - n/a

    return sTrimChars(csStr, CxConst::xWHITE_SPACES);
}
//---------------------------------------------------------------------------
//DONE: sRemoveEol
/*static*/
std::tstring
CxString::sRemoveEol(
    const std::tstring &csStr
)
{
    /*DEBUG*/// csStr - n/a

    return sTrimRightChars(csStr, CxConst::xEOL);
}
//---------------------------------------------------------------------------
//DONE: sReplaceAll
/*static*/
std::tstring
CxString::sReplaceAll(
    const std::tstring &csStr,
    const std::tstring &csOldStr,
    const std::tstring &csNewStr
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// csOldStr - n/a
    /*DEBUG*/// csNewStr - n/a

    xCHECK_RET(true == csStr.empty(),    csStr);
    xCHECK_RET(true == csOldStr.empty(), csStr);

    std::tstring sRes;
    sRes.assign(csStr);

    size_t uiPos = 0;

    for ( ; ; ) {
        uiPos = sRes.find(csOldStr, uiPos);
        xCHECK_DO(std::tstring::npos == uiPos, break);

        sRes.replace(uiPos, csOldStr.size(), csNewStr);

        uiPos += csNewStr.size();
    }

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sReplaceAll
/*static*/
std::tstring
CxString::sReplaceAll(
    const std::tstring &csStr,
    const TCHAR    cchOldStr,
    const TCHAR    cchNewStr
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// cchOldStr - n/a
    /*DEBUG*/// cchNewStr - n/a

    return sReplaceAll(csStr, std::tstring(1, cchOldStr), std::tstring(1, cchNewStr));
}
//---------------------------------------------------------------------------
//DONE: sRemoveAll
/*static*/
std::tstring
CxString::sRemoveAll(
    const std::tstring &csStr,
    const std::tstring &csRemoveStr
)
{
    /*DEBUG*/// csStr      - n/a
    /*DEBUG*/// csRemoveStr - n/a

    return sReplaceAll(csStr, csRemoveStr, std::tstring());
}
//---------------------------------------------------------------------------
//DONE: СЂР°Р·Р±РёРІР°РµС‚ СЃС‚СЂРѕРєСѓ РЅР° С„СЂР°РіРјРµРЅС‚С‹ РїРѕ СЃРёРјРІРѕР»Сѓ-СЂР°Р·РґРµР»РёС‚РµР»СЋ, РІРѕР·РІСЂР°С‰Р°СЏ РјР°СЃСЃРёРІ СЃС‚СЂРѕРє (vector)
/*static*/
BOOL
CxString::bSplit(
    const std::tstring        &csStr,
    const std::tstring        &csSep,
    std::vector<std::tstring> *pvsOut
)
{
    /*DEBUG*/// csStr    - n/a
    /*DEBUG*/// csSep    - n/a
    /*DEBUG*/// pvsOut - n/a

    xCHECK_RET(true == csStr.empty(), TRUE);
    xCHECK_RET(true == csSep.empty(), TRUE);
    xCHECK_RET(NULL == pvsOut,        FALSE);

    std::vector<std::tstring> vsRes;
    size_t               uiPrevPos = 0;     //start of string
    size_t               uiPos     = 0;

    for ( ; ; ) {
        uiPos = csStr.find(csSep, uiPrevPos);
        xCHECK_DO(std::tstring::npos == uiPos, break);

        vsRes.push_back(csStr.substr(uiPrevPos, uiPos - uiPrevPos));

        uiPrevPos = uiPos + csSep.size();
    }
    vsRes.push_back( csStr.substr(uiPrevPos, csStr.size() - uiPrevPos) );

    //out
    std::swap(*pvsOut, vsRes);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sJoin ("СЃРєР»РµРёРІР°РµС‚" СЃС‚СЂРѕРєРё РІРµРєС‚РѕСЂР° СЃРёРјРІРѕР»РѕРј-СЂР°Р·РґРµР»РёС‚РµР»РµРј)
/*static*/
std::tstring
CxString::sJoin(
    const std::vector<std::tstring> &cvsVec,
    const std::tstring              &csSep
)
{
    /*DEBUG*/// cvsVec - n/a
    /*DEBUG*/// csSep    - n/a

    std::tstring sRes;

    for (std::vector<std::tstring>::const_iterator it = cvsVec.begin(); it != cvsVec.end(); ++ it) {
        sRes.append(*it);

        xCHECK_DO(it < cvsVec.end() - 1, sRes.append(csSep));
    }

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sJoin ("СЃРєР»РµРёРІР°РµС‚" СЃС‚СЂРѕРєРё РІРµРєС‚РѕСЂР° СЃРёРјРІРѕР»РѕРј-СЂР°Р·РґРµР»РёС‚РµР»РµРј)
/*static*/
std::tstring
CxString::sJoin(
    const std::vector<std::tstring> &cvsVec,
    const TCHAR                 cchSep
)
{
    /*DEBUG*/// cvsVec - n/a
    /*DEBUG*/// csSep    - n/a

    return sJoin(cvsVec, std::tstring(1, cchSep));
}
//---------------------------------------------------------------------------
//DONE: sCut
/*static*/
std::tstring
CxString::sCut(
    const std::tstring &csStr,
    const std::tstring &csLeftSep,
    const std::tstring &csRightSep
)
{
    /*DEBUG*/// csStr      - n/a
    /*DEBUG*/// csLeftSep  - n/a
    /*DEBUG*/// csRightSep - n/a

    size_t uiStartDelimPos = 0;
    size_t uiStopDelimPos  = 0;

    uiStartDelimPos = csStr.find(csLeftSep);
    xCHECK_RET(std::tstring::npos == uiStartDelimPos, std::tstring());
    uiStartDelimPos += csLeftSep.size();

    uiStopDelimPos  = csStr.rfind(csRightSep);
    xCHECK_RET(std::tstring::npos == uiStopDelimPos, std::tstring());

    xCHECK_RET(uiStartDelimPos >= uiStopDelimPos, std::tstring());

    return csStr.substr(uiStartDelimPos, uiStopDelimPos - uiStartDelimPos);
}
//---------------------------------------------------------------------------
//DONE: sCut
/*static*/
std::tstring
CxString::sCut(
    const std::tstring &csStr,
    const size_t  cuiStartPos /*= 0*/,
    const size_t  cuiEndPos   /*= std::tstring:npos*/
)
{
    /*
    + Р•СЃР»Рё indexA = indexB, РІРѕР·РІСЂР°С‰Р°РµС‚СЃСЏ РїСѓСЃС‚Р°СЏ СЃС‚СЂРѕРєР°
    + Р•СЃР»Рё indexB РЅРµ СѓРєР°Р·Р°РЅ, substring РІРѕР·РІСЂР°С‰Р°РµС‚ СЃРёРјРІРѕР»С‹ РґРѕ РєРѕРЅС†Р° СЃС‚СЂРѕРєРё
    - Р•СЃР»Рё РєР°РєРѕР№-С‚Рѕ РёР· Р°СЂРіСѓРјРµРЅС‚РѕРІ РјРµРЅСЊС€Рµ 0 РёР»Рё СЏРІР»СЏРµС‚СЃСЏ NaN - РѕРЅ СЃС‡РёС‚Р°РµС‚СЃСЏ СЂР°РІРЅС‹Рј 0
    + Р•СЃР»Рё РєР°РєРѕР№-С‚Рѕ РёР· Р°СЂРіСѓРјРµРЅС‚РѕРІ Р±РѕР»СЊС€Рµ, С‡РµРј РґР»РёРЅР° СЃС‚СЂРѕРєРё - РѕРЅ СЃС‡РёС‚Р°РµС‚СЃСЏ СЂР°РІРЅС‹Рј РґР»РёРЅРµ СЃС‚СЂРѕРєРё
    + Р•СЃР»Рё indexA > indexB, С‚РѕРіРґР° substring РІРµРґРµС‚ СЃРµР±СЏ, РєР°Рє Р±СѓРґС‚Рѕ Р°СЂРіСѓРјРµРЅС‚С‹ РїРѕРјРµРЅСЏР»РёСЃСЊ РјРµСЃС‚Р°РјРё.
    - Р•СЃР»Рё СЃС‚СЂРѕРєР° РЅРµ РЅР°Р№РґРµРЅР°, РІС‹Р·РѕРІ РІРѕР·РІСЂР°С‰Р°РµС‚ -1
    */

    xCHECK_RET(true        == csStr.empty(), std::tstring());
    xCHECK_RET(cuiStartPos >  cuiEndPos,     std::tstring());

    size_t uiSize = ( (std::string::npos == cuiEndPos) ? (csStr.size()) : (cuiEndPos) ) - cuiStartPos/* + 1*/;

    return csStr.substr(cuiStartPos, uiSize);
}
//---------------------------------------------------------------------------
//DONE: sToLowerCase (convert to lowcase)
/*static*/
std::tstring
CxString::sToLowerCase(
    const std::tstring &csStr
)
{
    /*DEBUG*/// n/a

    return sToLowerCase(csStr, csStr.size());
}
//---------------------------------------------------------------------------
//DONE: sToUpperCase (convert to uppercase)
/*static*/
std::tstring
CxString::sToUpperCase(
    const std::tstring &csStr
)
{
    /*DEBUG*/// n/a

    return sToUpperCase(csStr, csStr.size());
}
//---------------------------------------------------------------------------
//DONE: sToLowerCase
/*static*/
std::tstring
CxString::sToLowerCase(
    const std::tstring &csStr,
    size_t         uiLength
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csStr.empty(), std::tstring());
    xCHECK_DO (csStr.size() < uiLength, uiLength = csStr.size());

    std::tstring sRes;
    sRes.assign(csStr);

#if defined(xOS_WIN)
    ULONG ulRes = ::CharLowerBuff(static_cast<LPTSTR>( &sRes[0] ), uiLength);
    /*DEBUG*/xASSERT_RET(uiLength == ulRes, std::tstring());
#elif defined(xOS_LINUX)
    std::transform(sRes.begin(), sRes.begin() + uiLength, sRes.begin(), CxChar::chToLower);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sToUpperCase
/*static*/
std::tstring
CxString::sToUpperCase(
    const std::tstring &csStr,
    size_t         uiLength
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csStr.empty(), std::tstring());
    xCHECK_DO (csStr.size() < uiLength, uiLength = csStr.size());

    std::tstring sRes;
    sRes.assign(csStr);

#if defined(xOS_WIN)
    ULONG ulRes = ::CharUpperBuff(static_cast<LPTSTR>( &sRes[0] ), uiLength);
    /*DEBUG*/xASSERT_RET(uiLength == ulRes, std::tstring());
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
    const std::tstring &csStr1,
    const std::tstring &csStr2
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
        bNoCase(const std::tstring::value_type &cchChar1, const std::tstring::value_type &cchChar2) {
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
std::tstring
CxString::sFormat(
    LPCTSTR pcszFormat, ...
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(NULL == pcszFormat, std::tstring());

    std::tstring sRes;

    va_list palArgs;
    xVA_START(palArgs, pcszFormat);

    sRes = sFormatV(pcszFormat, palArgs);

    xVA_END(palArgs);

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sFormatV
/*static*/
#if 1
    std::tstring
    CxString::sFormatV(
        LPCTSTR pcszFormat,
        va_list palArgs
    )
    {
        /*DEBUG*/// n/a
        xCHECK_RET(NULL == pcszFormat, std::tstring());

        std::tstring sBuff(64, 0);
        INT     iWrittenSize = - 1;

        for ( ; ; ) {
            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);

            {
                iWrittenSize = _vsntprintf(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
                xCHECK_DO(iWrittenSize > - 1 && static_cast<size_t>( iWrittenSize ) < sBuff.size(), break);

                sBuff.resize(sBuff.size() * 2);
            }

            xVA_END(_palArgs);
        }

        sBuff.resize(iWrittenSize);

        return sBuff;
    }
#else
    std::tstring
    CxString::sFormatV(
        LPCTSTR pcszFormat,
        va_list palArgs
    )
    {
        /*DEBUG*/// n/a
        xCHECK_RET(NULL == pcszFormat, std::tstring());

        std::tstring sBuff(64, 0);
        INT     iWrittenSize = - 1;

        //--------------------------------------------------
        //calc size
        {
            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);
            iWrittenSize = _vsntprintf(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
            xVA_END(_palArgs);

            /*DEBUG*/assert(- 1 < iWrittenSize);
            xCHECK_RET(0 >  iWrittenSize, std::tstring());
            xCHECK_RET(0 == iWrittenSize, sBuff);
        }

        //--------------------------------------------------
        //format
        if (sBuff.size() <= static_cast<size_t>( iWrittenSize )) {
            sBuff.resize(iWrittenSize + 1);

            va_list _palArgs;
            xVA_COPY(_palArgs, palArgs);
            iWrittenSize = _vsntprintf(&sBuff.at(0), sBuff.size(), pcszFormat, _palArgs);
            xVA_END(_palArgs);

            /*DEBUG*/assert(- 1          <  iWrittenSize);
            /*DEBUG*/assert(sBuff.size() == static_cast<size_t>( iWrittenSize ) + 1);
            xCHECK_RET(0             >  iWrittenSize,                           std::tstring());
            xCHECK_RET(sBuff.size() != static_cast<size_t>( iWrittenSize ) + 1, std::tstring());
        }

        sBuff.resize(iWrittenSize);

        return sBuff;
    }
#endif
//---------------------------------------------------------------------------
//DONE: sMinimize
/*static*/
std::tstring
CxString::sMinimize(
    const std::tstring &csStr,
    const size_t   cuiMaxLen
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csStr.empty(), std::tstring());
    xCHECK_RET(0    == cuiMaxLen,     std::tstring());

    std::tstring sRes;

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
std::tstring
CxString::sCreateGuid() {
    /*DEBUG*/// n/a

    std::tstring sRes;

#if defined(xOS_WIN)
    GUID    guidId = {0};
    HRESULT hrGuid = S_FALSE;

    hrGuid = CoCreateGuid(&guidId);
    /*DEBUG*/xASSERT_RET(SUCCEEDED(hrGuid), std::tstring());

    sRes = sFormat(
                xT("%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"),
                guidId.Data1,
                guidId.Data2,
                guidId.Data3,
                guidId.Data4[0], guidId.Data4[1],
                guidId.Data4[2], guidId.Data4[3], guidId.Data4[4], guidId.Data4[5], guidId.Data4[6], guidId.Data4[7]
    );
    /*DEBUG*/xASSERT_RET(false == sRes.empty(), std::tstring());
#elif defined(xOS_LINUX)
    //TODO: (sCreateGuid)
    //#include <uuid/uuid.h>
    xNOT_IMPLEMENTED_RET(std::tstring());
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bIsRepeated
/*static*/
BOOL CxString::bIsRepeated(
    const std::tstring &csStr
)
{
    /*DEBUG*/// n/a

    return static_cast<BOOL>( std::tstring::npos == csStr.find_first_not_of(csStr.at(0)) );
}
//---------------------------------------------------------------------------


/****************************************************************************
*    coders
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: sTranslitLatToRus
/*static*/
std::tstring
CxString::sTranslitLatToRus(
    const std::tstring &csStr
)
{
    /*DEBUG*/// n/a
    xCHECK_RET(true == csStr.empty(), std::tstring());

    //translit table
    const std::tstring csDict[][2] = {
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

    std::tstring sRes;
    sRes.assign(csStr);

    for (size_t i = 0; i < xARRAY_SIZE(csDict); ++ i) {
        sRes.assign( sReplaceAll(sRes, csDict[i][0], csDict[i][1]) );
    }

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: sFormatBytes (С„РѕСЂРјР°С‚РёСЂРѕРІР°РЅРёРµ Р±Р°Р№С‚РѕРІ РІ Bits, Bytes, KB, MB, GB)
/*static*/
std::tstring
CxString::sFormatBytes(
    const DOUBLE cdBytes
)
{
    /*DEBUG*/// dBytes - n/a

    std::tstring sRes = xT("Uknown");

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
//DONE: sFormatBytes (С„РѕСЂРјР°С‚РёСЂРѕРІР°РЅРёРµ Р±Р°Р№С‚РѕРІ РІ Bits, Bytes, KB, MB, GB)
/*static*/
std::tstring
CxString::sFormatBytes(
    const ULONGLONG cullBytes
)
{
    /*DEBUG*/// ulBytes - n/a

    std::tstring sRes = xT("<uknown>");

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
std::tstring
CxString::sFormatPercentage(
    ULONGLONG ullMaxValue,
    ULONGLONG ullCurrValue
)
{
    /*DEBUG*/// ullMaxValue  - n/a
    /*DEBUG*/// ullCurrValue - n/a
    xCHECK_RET(0 == ullMaxValue, xT("0%"));    //devision by zero

    std::tstring sRes;

    sRes = lexical_cast( ullCurrValue * 100ULL / ullMaxValue );
    xCHECK_RET(true == sRes.empty(), xT("0%"));

    return sRes.append(xT("%"));
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

    wsRes.resize(iSize - 1);    //Р±РµР· '\0'
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

    asRes.resize(iSize - 1);    //Р±РµР· '\0'
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
    const std::tstring &csSrc
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
std::tstring
CxString::sOemToCharBuff(
    const std::string &csSrc
)
{
    std::tstring sDst;

#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    sDst.resize(csSrc.size());

    bRes = ::OemToCharBuff(csSrc.c_str(), &sDst.at(0), sDst.size());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, std::tstring());
#elif defined(xOS_LINUX)
    //TODO: (sOemToCharBuff)
    xNOT_IMPLEMENTED_RET(std::tstring());
#endif

    return sDst;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    other
*
*****************************************************************************/

