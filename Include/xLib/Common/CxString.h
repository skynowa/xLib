/**
 * \file  CxString.h
 * \brief strings utils
 */


#ifndef xLib_Common_CxStringH
#define xLib_Common_CxStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
//overload operators << for std::basic_ostream
namespace std {
    template<class Traits>
    inline basic_ostream<TCHAR, Traits> &
    operator << (basic_ostream<TCHAR, Traits> &osOut, const std::ustring &cusValue);
        ///< overload operators << for std::ustring

    template<class Traits, class T>
    inline basic_ostream<TCHAR, Traits> &
    operator << (basic_ostream<TCHAR, Traits> &osOut, const vector<T> &cvValueT);
        ///< overload operators << for std::vector

    template<class Traits, class T1, class T2>
    inline basic_ostream<TCHAR, Traits> &
    operator << (basic_ostream<TCHAR, Traits> &osOut, const map<T1, T2> &cmValueT);
        ///< overload operators << for std::map

    template<class Traits, class T1, class T2>
    inline basic_ostream<TCHAR, Traits> &
    operator << (basic_ostream<TCHAR, Traits> &osOut, const multimap<T1, T2> &cmmValueT);
        ///< overload operators << for std::multimap
}
//---------------------------------------------------------------------------
class CxString :
    public CxNonCopyable
{
    public:
        template<class T>
        static  std::tstring     lexical_cast     (const T &cValueT);

        template<class T>
        static  std::tstring     lexical_cast     (const T &cValueT, const INT ciBase);

        template<class T>
        static T            lexical_cast     (const std::tstring &csStr);

        template<class T>
        static T            lexical_cast     (const std::tstring &csStr, const INT ciBase);

        static std::tstring      sBoolToStr       (const BOOL cbBool);
        static BOOL         bStrToBool       (const std::tstring &csStr);

        static std::tstring      sTrimLeftChars   (const std::tstring &csStr, const std::tstring &csChars);
        static std::tstring      sTrimRightChars  (const std::tstring &csStr, const std::tstring &csChars);
        static std::tstring      sTrimChars       (const std::tstring &csStr, const std::tstring &csChars);
        static std::tstring      sTrimSpace       (const std::tstring &csStr);
        static std::tstring      sRemoveEol       (const std::tstring &csStr);

        static std::tstring      sReplaceAll      (const std::tstring &csStr, const std::tstring &csOldStr, const std::tstring &csNewStr);
        static std::tstring      sReplaceAll      (const std::tstring &csStr, const TCHAR ccOldStr, const TCHAR ccNewStr);
        static std::tstring      sRemoveAll       (const std::tstring &csStr, const std::tstring &csRemoveStr);

        static BOOL         bSplit           (const std::tstring &csStr, const std::tstring &csSep, std::vector<std::tstring> *pvsOut);
        static std::tstring      sJoin            (const std::vector<std::tstring> &cvsVec, const TCHAR cchSep);
        static std::tstring      sJoin            (const std::vector<std::tstring> &cvsVec, const std::tstring &csSep);
        static std::tstring      sCut             (const std::tstring &csStr, const std::tstring &csLeftSep, const std::tstring &csRightSep);
        static std::tstring      sCut             (const std::tstring &csStr, const size_t cuiStartPos = 0, const size_t cuiEndPos = std::tstring::npos);

        static std::tstring      sToLowerCase     (const std::tstring &csStr);
        static std::tstring      sToUpperCase     (const std::tstring &csStr);
        static std::tstring      sToLowerCase     (const std::tstring &csStr, size_t uiLength);
        static std::tstring      sToUpperCase     (const std::tstring &csStr, size_t uiLength);

        static std::tstring      sFormat          (LPCTSTR pcszFormat, ...);
        static std::tstring      sFormatV         (LPCTSTR pcszFormat, va_list palArgs);
        static std::tstring      sMinimize        (const std::tstring &csStr, const size_t cuiMaxLen);

        /****************************************************************************
        *
        *
        *****************************************************************************/

        static BOOL         bCompareNoCase   (const std::tstring &csStr1, const std::tstring &csStr2);

        /****************************************************************************
        *    formating
        *
        *****************************************************************************/

        static std::tstring      sTranslitLatToRus(const std::tstring &csStr);
        static std::tstring      sFormatBytes     (const DOUBLE cdBytes);
        static std::tstring      sFormatBytes     (const ULONGLONG cullBytes);
        static std::tstring      sFormatPercentage(ULONGLONG ullMaxValue, ULONGLONG ullCurrValue);

        static std::wstring sStrToWStr       (const std::string  &csStr,  const UINT cuiCodePage);
        static std::string  sWStrToStr       (const std::wstring &cwsStr, const UINT cuiCodePage);

        static std::string  sConvertCodePage (const std::string &csSource, const UINT cuiCodePageSource, const UINT cuiCodePageDest);

        static std::string  asCharToOemBuff  (const std::tstring     &csSrc);
        static std::tstring      sOemToCharBuff   (const std::string &csSrc);


        /****************************************************************************
        *    memory
        *
        *****************************************************************************/

        static VOID *       pvMemoryZeroSecure(VOID *pvBuff, size_t  uiBuffSize);


        /****************************************************************************
        *    other
        *
        *****************************************************************************/

        static std::tstring      sCreateGuid      ();
        static BOOL         bIsRepeated      (const std::tstring &csStr);

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

