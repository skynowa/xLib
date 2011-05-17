/****************************************************************************
* Class name:  CxString
* Description: strings utils
* File name:   CxString.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.04.2009 17:01:15
*
*****************************************************************************/


#ifndef xLib_Common_CxStringH
#define xLib_Common_CxStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
class CxString : public CxNonCopyable {
    public:
        //---------------------------------------------------------------------------
        //EColor - comsole colors
        enum EAttribute {
            atAllOff = 0, atBold = 1, atUnderscore = 4, atBlink = 5, atReverse = 7, atConcealed  = 8
        };

        enum EForeground {
            fgBlack  = 30, fgRed  = 31, fgGreen  = 32, fgYellow  = 33, fgBlue  = 34, fgMagenta  = 35, fgCyan  = 36, fgWhite  = 37,
            fgBlack_ = 90, fgRed_ = 91, fgGreen_ = 92, fgYellow_ = 93, fgBlue_ = 94, fgMagenta_ = 95, fgCyan_ = 96, fgWhite_ = 97
        };

        enum EBackground {
            bgBlack  = 40,  bgRed  = 41,  bgGreen  = 42,  bgYellow  = 43,  bgBlue  = 44,  bgMagenta  = 45,  bgCyan  = 46,  bgWhite  = 47,
            bgBlack_ = 100, bgRed_ = 101, bgGreen_ = 102, bgYellow_ = 103, bgBlue_ = 104, bgMagenta_ = 105, bgCyan_ = 106, bgWhite_ = 107
        };

        template<class T>
        static  tString     lexical_cast     (const T &cValueT);

        template<class T>
        static  tString     lexical_cast     (const T &cValueT, const INT ciBase);

        template<class T>
        static T            lexical_cast     (const tString &csStr);

        template<class T>
        static T            lexical_cast     (const tString &csStr, const INT ciBase);

        static tString      sBoolToStr       (const BOOL cbBool);
        static BOOL         bStrToBool       (const tString &csStr);

        static tString      sTrimLeftChars   (const tString &csStr, const tString &csChars);
        static tString      sTrimRightChars  (const tString &csStr, const tString &csChars);
        static tString      sTrimChars       (const tString &csStr, const tString &csChars);
        static tString      sTrimSpace       (const tString &csStr);
        static tString      sRemoveEol       (const tString &csStr);

        static tString      sReplaceAll      (const tString &csStr, const tString &csOldStr, const tString &csNewStr);
        static tString      sReplaceAll      (const tString &csStr, const TCHAR ccOldStr, const TCHAR ccNewStr);
        static tString      sRemoveAll       (const tString &csStr, const tString &csRemoveStr);

        static BOOL         bSplit           (const tString &csStr, const tString &csSep, std::vector<tString> *pvsOut);
        static tString      sJoin            (const std::vector<tString> &cvsVec, const TCHAR cchSep);
        static tString      sJoin            (const std::vector<tString> &cvsVec, const tString &csSep);
        static tString      sCut             (const tString &csStr, const tString &csLeftSep, const tString &csRightSep);
        static tString      sCut             (const tString &csStr, const size_t cuiStartPos = 0, const size_t cuiEndPos = tString::npos);

        static tString      sToLowerCase     (const tString &csStr);
        static tString      sToUpperCase     (const tString &csStr);
        static tString      sToLowerCase     (const tString &csStr, size_t uiLength);
        static tString      sToUpperCase     (const tString &csStr, size_t uiLength);

        static tString      sFormat          (LPCTSTR pcszFormat, ...);
        static tString      sFormatV         (LPCTSTR pcszFormat, va_list palArgs);
        static tString      sMinimize        (const tString &csStr, const size_t cuiMaxLen);

        /****************************************************************************
        *
        *
        *****************************************************************************/

        static BOOL         bCompareNoCase   (const tString &csStr1, const tString &csStr2);

        /****************************************************************************
        *    formating
        *
        *****************************************************************************/

        static tString      sTranslitLatToRus(const tString &csStr);
        static tString      sFormatBytes     (const DOUBLE cdBytes);
        static tString      sFormatBytes     (const ULONGLONG cullBytes);
        static tString      sFormatPercentage(ULONGLONG ullMaxValue, ULONGLONG ullCurrValue);
        static tString      sFormatNixTerminal(const tString &csText, EForeground fgForeground, BOOL bIsBold, BOOL bIsUnderline, EBackground bgBackground, BOOL bIsBlink);

        static std::wstring sStrToWStr       (const std::string  &csStr,  const UINT cuiCodePage);
        static std::string  sWStrToStr       (const std::wstring &cwsStr, const UINT cuiCodePage);

        static std::string  sConvertCodePage (const std::string &csSource, const UINT cuiCodePageSource, const UINT cuiCodePageDest);

        static std::string  asCharToOemBuff  (const tString     &csSrc);
        static tString      sOemToCharBuff   (const std::string &csSrc);


        /****************************************************************************
        *    memory
        *
        *****************************************************************************/

        static VOID *       pvMemoryZeroSecure(VOID *pvBuff, size_t  uiBuffSize);


        /****************************************************************************
        *    other
        *
        *****************************************************************************/

        static tString      sCreateGuid      ();
        static BOOL         bIsRepeated      (const tString &csStr);

    private:
                 CxString();
        virtual ~CxString();
};
//---------------------------------------------------------------------------
#include <Common/CxString.inl>
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxStringH

/*
std::string str("i am string");
std::vector<unsigned char> data;//i am array
std::copy(str.begin(), str.end(), std::back_inserter(data));
*/

