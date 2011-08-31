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
    /// strings utils
{
    public:
        template<class T>
        static  std::tstring lexical_cast      (const T &cValueT);
            ///< convert type to std::tstring

        template<class T>
        static  std::tstring lexical_cast      (const T &cValueT, const INT ciBase);
            ///< convert type to std::tstring by base

        template<class T>
        static T             lexical_cast      (const std::tstring &csStr);
            ///< convert std::tstring to type

        template<class T>
        static T             lexical_cast      (const std::tstring &csStr, const INT ciBase);
            ///< convert std::tstring by base (8, 10, 16) to type

        static std::tstring  sBoolToStr        (const BOOL cbBool);
            ///< BOOL to std::tstring
        static BOOL          bStrToBool        (const std::tstring &csStr);
            ///< convert std::tstring to BOOL

        static std::tstring  sTrimLeftChars    (const std::tstring &csStr, const std::tstring &csChars);
            ///< trim left chars
        static std::tstring  sTrimRightChars   (const std::tstring &csStr, const std::tstring &csChars);
            ///< trim left chars
        static std::tstring  sTrimChars        (const std::tstring &csStr, const std::tstring &csChars);
            ///< trim left, right chars
        static std::tstring  sTrimSpace        (const std::tstring &csStr);
            ///< trim left, right spaces
        static std::tstring  sRemoveEol        (const std::tstring &csStr);
            ///< remove end of line from end of string

        static std::tstring  sReplaceAll       (const std::tstring &csStr, const std::tstring &csOldStr, const std::tstring &csNewStr);
            ///< replace all strings
        static std::tstring  sReplaceAll       (const std::tstring &csStr, const TCHAR ccOldStr, const TCHAR ccNewStr);
            ///< replace all chars
        static std::tstring  sRemoveAll        (const std::tstring &csStr, const std::tstring &csRemoveStr);
            ///< remove all strings

        static BOOL          bSplit            (const std::tstring &csStr, const std::tstring &csSep, std::vector<std::tstring> *pvsOut);
            ///< split by separator
        static std::tstring  sJoin             (const std::vector<std::tstring> &cvsVec, const TCHAR cchSep);
            ///< join with char separator
        static std::tstring  sJoin             (const std::vector<std::tstring> &cvsVec, const std::tstring &csSep);
            ///< oin with string separator
        static std::tstring  sCut              (const std::tstring &csStr, const std::tstring &csLeftSep, const std::tstring &csRightSep);
            ///< cut using strings
        static std::tstring  sCut              (const std::tstring &csStr, const size_t cuiStartPos = 0, const size_t cuiEndPos = std::tstring::npos);
            ///< cut using string positions

        static std::tstring  sToLowerCase      (const std::tstring &csStr);
            ///< convert to lowcase
        static std::tstring  sToUpperCase      (const std::tstring &csStr);
            ///< convert to uppercase
        static std::tstring  sToLowerCase      (const std::tstring &csStr, size_t uiLength);
            ///< convert to lowcase
        static std::tstring  sToUpperCase      (const std::tstring &csStr, size_t uiLength);
            ///< convert to uppercase

        static std::tstring  sFormat           (LPCTSTR pcszFormat, ...);
            ///< format
        static std::tstring  sFormatV          (LPCTSTR pcszFormat, va_list palArgs);
            ///< format
        static std::tstring  sMinimize         (const std::tstring &csStr, const size_t cuiMaxLen);
            ///< minimize

        /****************************************************************************
        *
        *
        *****************************************************************************/

        static BOOL          bCompareNoCase    (const std::tstring &csStr1, const std::tstring &csStr2);
            ///< no case compare

        /****************************************************************************
        *    formating
        *
        *****************************************************************************/

        static std::tstring  sTranslitLatToRus (const std::tstring &csStr);
            ///< translit
        static std::tstring  sFormatBytes      (const DOUBLE cdBytes);
            ///< format bytes (like Bit(s), Byte(s), MB, GB, TB)
        static std::tstring  sFormatBytes      (const ULONGLONG cullBytes);
            ///< ormat bytes (like Bit(s), Byte(s), MB, GB, TB)
        static std::tstring  sFormatPercentage (ULONGLONG ullMaxValue, ULONGLONG ullCurrValue);
            ///< formatting percentage

        static std::wstring  sStrToWStr        (const std::string  &csStr,  const UINT cuiCodePage);
            ///< std::string in std::wstring
        static std::string   sWStrToStr        (const std::wstring &cwsStr, const UINT cuiCodePage);
            ///< std::wstring in std::string

        static std::string   sConvertCodePage  (const std::string &csSource, const UINT cuiCodePageSource, const UINT cuiCodePageDest);
            ///< convert codepage

        static std::string   asCharToOemBuff   (const std::tstring &csSrc);
            ///< convert char to oem
        static std::tstring  sOemToCharBuff    (const std::string  &csSrc);
            ///< convert oem to char


        /****************************************************************************
        *    memory
        *
        *****************************************************************************/

        static VOID *        pvMemoryZeroSecure(VOID *pvBuff, size_t  uiBuffSize);
            ///< secure zero memory


        /****************************************************************************
        *    other
        *
        *****************************************************************************/

        static std::tstring  sCreateGuid       ();
            ///< generate GUID
        static BOOL          bIsRepeated       (const std::tstring &csStr);
            ///< is repeated

    private:
                             CxString          ();
            ///< constructor
        virtual             ~CxString          ();
            ///< destructor

       static  INT           vsntprintf_safe    (TCHAR *pszBuff, const size_t  cuiBuffSize, const TCHAR *pcszFormat, va_list alList);
            ///< call _vsnprintf, but always NUL-terminate
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

