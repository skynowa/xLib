/**
 * \file  CxString.h
 * \brief strings utils
 */


#ifndef xLib_Common_CxStringH
#define xLib_Common_CxStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
//overload operators << for std::basic_ostream
xNAMESPACE_BEGIN(std)

    template<class Traits>
    inline basic_ostream<tchar_t, Traits> &
    operator << (basic_ostream<tchar_t, Traits> &osOut, const std::ustring_t &cusValue);
        ///< overload operators << for std::ustring_t

    template<class Traits, class T>
    inline basic_ostream<tchar_t, Traits> &
    operator << (basic_ostream<tchar_t, Traits> &osOut, const vector<T> &cvValueT);
        ///< overload operators << for std::vector

    template<class Traits, class T1, class T2>
    inline basic_ostream<tchar_t, Traits> &
    operator << (basic_ostream<tchar_t, Traits> &osOut, const map<T1, T2> &cmValueT);
        ///< overload operators << for std::map

    template<class Traits, class T1, class T2>
    inline basic_ostream<tchar_t, Traits> &
    operator << (basic_ostream<tchar_t, Traits> &osOut, const multimap<T1, T2> &cmmValueT);
        ///< overload operators << for std::multimap

xNAMESPACE_END(std)
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxString :
    private CxNonCopyable
    /// strings utils
{
    public:
        template<class T>
        static std::tstring_t string_cast       (const T &cValueT);
            ///< convert type to std::tstring_t

        template<class T>
        static std::tstring_t string_cast       (const T &cValueT, const int &ciBase);
            ///< convert type to std::tstring_t by base

        template<class T>
        static T              string_cast       (const std::tstring_t &csStr);
            ///< convert std::tstring_t to type

        template<class T>
        static T              string_cast       (const std::tstring_t &csStr, const int &ciBase);
            ///< convert std::tstring_t by base (8, 10, 16) to type

        static std::tstring_t sBoolToStr        (const bool &cbBool);
            ///< bool to std::tstring_t
        static bool           bStrToBool        (const std::tstring_t &csStr);
            ///< convert std::tstring_t to bool

        static std::tstring_t sTrimLeftChars    (const std::tstring_t &csStr, const std::tstring_t &csChars);
            ///< trim left chars
        static std::tstring_t sTrimRightChars   (const std::tstring_t &csStr, const std::tstring_t &csChars);
            ///< trim left chars
        static std::tstring_t sTrimChars        (const std::tstring_t &csStr, const std::tstring_t &csChars);
            ///< trim left, right chars
        static std::tstring_t sTrimSpace        (const std::tstring_t &csStr);
            ///< trim left, right spaces
        static std::tstring_t sRemoveEol        (const std::tstring_t &csStr);
            ///< remove end of line from end of string

        static std::tstring_t sReplaceAll       (const std::tstring_t &csStr, const std::tstring_t &csOldStr, const std::tstring_t &csNewStr);
            ///< replace all strings
        static std::tstring_t sReplaceAll       (const std::tstring_t &csStr, const tchar_t &ccOldStr, const tchar_t &ccNewStr);
            ///< replace all chars
        static std::tstring_t sRemoveAll        (const std::tstring_t &csStr, const std::tstring_t &csRemoveStr);
            ///< remove all strings

        static void           vSplit            (const std::tstring_t &csStr, const std::tstring_t &csSep, std::vec_tstring_t *pvsOut);
            ///< split by separator
        static std::tstring_t sJoin             (const std::vec_tstring_t &cvsVec, const tchar_t &cchSep);
            ///< join with char separator
        static std::tstring_t sJoin             (const std::vec_tstring_t &cvsVec, const std::tstring_t &csSep);
            ///< oin with string separator
        static std::tstring_t sCut              (const std::tstring_t &csStr, const std::tstring_t &csLeftSep, const std::tstring_t &csRightSep);
            ///< cut using strings
        static std::tstring_t sCut              (const std::tstring_t &csStr, const size_t &cuiStartPos = 0, const size_t &cuiEndPos = std::tstring_t::npos);
            ///< cut using string positions

        static std::tstring_t sToLowerCase      (const std::tstring_t &csStr);
            ///< convert to lowcase
        static std::tstring_t sToUpperCase      (const std::tstring_t &csStr);
            ///< convert to uppercase
        static std::tstring_t sToLowerCase      (const std::tstring_t &csStr, const size_t &cuiLength);
            ///< convert to lowcase
        static std::tstring_t sToUpperCase      (const std::tstring_t &csStr, const size_t &cuiLength);
            ///< convert to uppercase

        static std::tstring_t sFormat           (const tchar_t *pcszFormat, ...);
            ///< format
        static std::tstring_t sFormatV          (const tchar_t *pcszFormat, va_list palArgs);
            ///< format
        static std::tstring_t sMinimize         (const std::tstring_t &csStr, const size_t &cuiMaxLen);
            ///< minimize

        /****************************************************************************
        *
        *
        *****************************************************************************/

        static bool           bCompareNoCase    (const std::tstring_t &csStr1, const std::tstring_t &csStr2);
            ///< no case compare

        /****************************************************************************
        *    formating
        *
        *****************************************************************************/

        static std::tstring_t sTranslitLatToRus (const std::tstring_t &csStr);
            ///< translit
        static std::tstring_t sFormatBytes      (const double &cdBytes);
            ///< format bytes (like Bit(s), Byte(s), MB, GB, TB)
        static std::tstring_t sFormatBytes      (const ulonglong_t &cullBytes);
            ///< ormat bytes (like Bit(s), Byte(s), MB, GB, TB)
        static std::tstring_t sFormatPercentage (const ulonglong_t &cullMaxValue, const ulonglong_t &cullCurrValue);
            ///< formatting percentage

        static std::wstring   sStrToWStr        (const std::string  &csStr,  const uint_t &cuiCodePage);
            ///< std::string in std::wstring
        static std::string    sWStrToStr        (const std::wstring &cwsStr, const uint_t &cuiCodePage);
            ///< std::wstring in std::string

        static std::string    sConvertCodePage  (const std::string &csSource, const uint_t &cuiCodePageSource, const uint_t &cuiCodePageDest);
            ///< convert codepage

        static std::string    asCharToOemBuff   (const std::tstring_t &csSrc);
            ///< convert char to oem
        static std::tstring_t sOemToCharBuff    (const std::string &csSrc);
            ///< convert oem to char


        /****************************************************************************
        *    memory
        *
        *****************************************************************************/

        static void *         pvMemoryZeroSecure(void *pvBuff, const size_t &cuiBuffSize);
            ///< secure zero memory


        /****************************************************************************
        *    other
        *
        *****************************************************************************/

        static std::tstring_t  sCreateGuid      ();
            ///< generate GUID
        static bool            bIsRepeated      (const std::tstring_t &csStr);
            ///< is repeated

    private:
                               CxString         ();
            ///< constructor
        virtual               ~CxString         ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxString.inl"
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxStringH
