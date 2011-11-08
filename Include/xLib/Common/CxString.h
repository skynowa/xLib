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
    inline basic_ostream<char_t, Traits> &
    operator << (basic_ostream<char_t, Traits> &osOut, const std::ustring &cusValue);
        ///< overload operators << for std::ustring

    template<class Traits, class T>
    inline basic_ostream<char_t, Traits> &
    operator << (basic_ostream<char_t, Traits> &osOut, const vector<T> &cvValueT);
        ///< overload operators << for std::vector

    template<class Traits, class T1, class T2>
    inline basic_ostream<char_t, Traits> &
    operator << (basic_ostream<char_t, Traits> &osOut, const map<T1, T2> &cmValueT);
        ///< overload operators << for std::map

    template<class Traits, class T1, class T2>
    inline basic_ostream<char_t, Traits> &
    operator << (basic_ostream<char_t, Traits> &osOut, const multimap<T1, T2> &cmmValueT);
        ///< overload operators << for std::multimap
}
//---------------------------------------------------------------------------
class CxString :
    public CxNonCopyable
    /// strings utils
{
    public:
        template<class T>
        static  std::string_t lexical_cast      (const T &cValueT);
            ///< convert type to std::string_t

        template<class T>
        static  std::string_t lexical_cast      (const T &cValueT, const int ciBase);
            ///< convert type to std::string_t by base

        template<class T>
        static T             lexical_cast      (const std::string_t &csStr);
            ///< convert std::string_t to type

        template<class T>
        static T             lexical_cast      (const std::string_t &csStr, const int ciBase);
            ///< convert std::string_t by base (8, 10, 16) to type

        static std::string_t  sBoolToStr        (const BOOL cbBool);
            ///< BOOL to std::string_t
        static BOOL          bStrToBool        (const std::string_t &csStr);
            ///< convert std::string_t to BOOL

        static std::string_t  sTrimLeftChars    (const std::string_t &csStr, const std::string_t &csChars);
            ///< trim left chars
        static std::string_t  sTrimRightChars   (const std::string_t &csStr, const std::string_t &csChars);
            ///< trim left chars
        static std::string_t  sTrimChars        (const std::string_t &csStr, const std::string_t &csChars);
            ///< trim left, right chars
        static std::string_t  sTrimSpace        (const std::string_t &csStr);
            ///< trim left, right spaces
        static std::string_t  sRemoveEol        (const std::string_t &csStr);
            ///< remove end of line from end of string

        static std::string_t  sReplaceAll       (const std::string_t &csStr, const std::string_t &csOldStr, const std::string_t &csNewStr);
            ///< replace all strings
        static std::string_t  sReplaceAll       (const std::string_t &csStr, const char_t ccOldStr, const char_t ccNewStr);
            ///< replace all chars
        static std::string_t  sRemoveAll        (const std::string_t &csStr, const std::string_t &csRemoveStr);
            ///< remove all strings

        static BOOL          bSplit            (const std::string_t &csStr, const std::string_t &csSep, std::vector<std::string_t> *pvsOut);
            ///< split by separator
        static std::string_t  sJoin             (const std::vector<std::string_t> &cvsVec, const char_t cchSep);
            ///< join with char separator
        static std::string_t  sJoin             (const std::vector<std::string_t> &cvsVec, const std::string_t &csSep);
            ///< oin with string separator
        static std::string_t  sCut              (const std::string_t &csStr, const std::string_t &csLeftSep, const std::string_t &csRightSep);
            ///< cut using strings
        static std::string_t  sCut              (const std::string_t &csStr, const size_t cuiStartPos = 0, const size_t cuiEndPos = std::string_t::npos);
            ///< cut using string positions

        static std::string_t  sToLowerCase      (const std::string_t &csStr);
            ///< convert to lowcase
        static std::string_t  sToUpperCase      (const std::string_t &csStr);
            ///< convert to uppercase
        static std::string_t  sToLowerCase      (const std::string_t &csStr, size_t uiLength);
            ///< convert to lowcase
        static std::string_t  sToUpperCase      (const std::string_t &csStr, size_t uiLength);
            ///< convert to uppercase

        static std::string_t  sFormat           (const char_t *pcszFormat, ...);
            ///< format
        static std::string_t  sFormatV          (const char_t *pcszFormat, va_list palArgs);
            ///< format
        static std::string_t  sMinimize         (const std::string_t &csStr, const size_t cuiMaxLen);
            ///< minimize

        /****************************************************************************
        *
        *
        *****************************************************************************/

        static BOOL          bCompareNoCase    (const std::string_t &csStr1, const std::string_t &csStr2);
            ///< no case compare

        /****************************************************************************
        *    formating
        *
        *****************************************************************************/

        static std::string_t  sTranslitLatToRus (const std::string_t &csStr);
            ///< translit
        static std::string_t  sFormatBytes      (const double cdBytes);
            ///< format bytes (like Bit(s), Byte(s), MB, GB, TB)
        static std::string_t  sFormatBytes      (const ULONGLONG cullBytes);
            ///< ormat bytes (like Bit(s), Byte(s), MB, GB, TB)
        static std::string_t  sFormatPercentage (ULONGLONG ullMaxValue, ULONGLONG ullCurrValue);
            ///< formatting percentage

        static std::wstring  sStrToWStr        (const std::string  &csStr,  const UINT cuiCodePage);
            ///< std::string in std::wstring
        static std::string   sWStrToStr        (const std::wstring &cwsStr, const UINT cuiCodePage);
            ///< std::wstring in std::string

        static std::string   sConvertCodePage  (const std::string &csSource, const UINT cuiCodePageSource, const UINT cuiCodePageDest);
            ///< convert codepage

        static std::string   asCharToOemBuff   (const std::string_t &csSrc);
            ///< convert char to oem
        static std::string_t  sOemToCharBuff    (const std::string  &csSrc);
            ///< convert oem to char


        /****************************************************************************
        *    memory
        *
        *****************************************************************************/

        static void *        pvMemoryZeroSecure(void *pvBuff, size_t  uiBuffSize);
            ///< secure zero memory


        /****************************************************************************
        *    other
        *
        *****************************************************************************/

        static std::string_t  sCreateGuid       ();
            ///< generate GUID
        static BOOL          bIsRepeated       (const std::string_t &csStr);
            ///< is repeated

    private:
                             CxString          ();
            ///< constructor
        virtual             ~CxString          ();
            ///< destructor
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

