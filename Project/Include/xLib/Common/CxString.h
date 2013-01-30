/**
 * \file  CxString.h
 * \brief string utils
 */


#ifndef xLib_Common_CxStringH
#define xLib_Common_CxStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
// overload operators << for std::basic_ostream
xNAMESPACE_BEGIN(std)

    template<typename Traits>
    inline basic_ostream<tchar_t, Traits> &
    operator << (basic_ostream<tchar_t, Traits> &osOut, const std::ustring_t &cusValue);
        ///< overload operators << for std::ustring_t

    template<typename Traits, class T>
    inline basic_ostream<tchar_t, Traits> &
    operator << (basic_ostream<tchar_t, Traits> &osOut, const vector<T> &cvValueT);
        ///< overload operators << for std::vector

    template<typename Traits, class T1, class T2>
    inline basic_ostream<tchar_t, Traits> &
    operator << (basic_ostream<tchar_t, Traits> &osOut, const map<T1, T2> &cmValueT);
        ///< overload operators << for std::map

    template<typename Traits, class T1, class T2>
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
    /****************************************************************************
    *   converters
    *
    *****************************************************************************/

    template<typename T>
    static std::tstring_t cast            (const T &cValueT);
        ///< convert type to std::tstring_t
    template<typename T>
    static std::tstring_t cast            (const T &cValueT, const int &ciBase);
        ///< convert type to std::tstring_t by base
    template<typename T>
    static T              cast            (const std::tstring_t &csStr);
        ///< convert std::tstring_t to type
    template<typename T>
    static T              cast            (const std::tstring_t &csStr, const int &ciBase);
        ///< convert std::tstring_t by base (8, 10, 16) to type

    static std::string    castA           (const std::wstring &csStr);
        ///< std::wstring in std::string
    static std::wstring   castW           (const std::string &csStr);
        ///< std::string in std::wstring

    static std::wstring   strToWStr       (const std::string  &csStr,  const uint_t &cuiCodePage);
        ///< std::string in std::wstring
    static std::string    wstrToStr       (const std::wstring &cwsStr, const uint_t &cuiCodePage);
        ///< std::wstring in std::string

    static std::wstring   strToWStr       (const std::string  &csStdString,  const std::locale &clocLocale = std::locale());
        ///< std::string in std::wstring
    static std::string    wstrToStr       (const std::wstring &csStdWString, const std::locale &clocLocale = std::locale());
        ///< std::wstring in std::string

    static std::string    convertCodePage (const std::string &csSource, const uint_t &cuiCodePageSource, const uint_t &cuiCodePageDest);
        ///< convert codepage

    static std::string    charToOemBuff   (const std::tstring_t &csSrc);
        ///< convert char to oem
    static std::tstring_t oemToCharBuff   (const std::string &csSrc);
        ///< convert oem to char

    static std::tstring_t boolToStr       (const bool &cbBool);
        ///< bool to std::tstring_t
    static bool           strToBool       (const std::tstring_t &csStr);
        ///< convert std::tstring_t to bool

    static std::tstring_t toLowerCase     (const std::tstring_t &csStr);
        ///< convert to low case
    static std::tstring_t toUpperCase     (const std::tstring_t &csStr);
        ///< convert to uppercase
    static std::tstring_t toLowerCase     (const std::tstring_t &csStr, const size_t &cuiLength);
        ///< convert to low case
    static std::tstring_t toUpperCase     (const std::tstring_t &csStr, const size_t &cuiLength);
        ///< convert to uppercase

    /****************************************************************************
    *   actions
    *
    *****************************************************************************/

    static std::tstring_t trimLeftChars   (const std::tstring_t &csStr, const std::tstring_t &csChars);
        ///< trim left chars
    static std::tstring_t trimRightChars  (const std::tstring_t &csStr, const std::tstring_t &csChars);
        ///< trim left chars
    static std::tstring_t trimChars       (const std::tstring_t &csStr, const std::tstring_t &csChars);
        ///< trim left, right chars
    static std::tstring_t trimSpace       (const std::tstring_t &csStr);
        ///< trim left, right spaces
    static std::tstring_t removeEol       (const std::tstring_t &csStr);
        ///< remove end of line from end of string

    static std::tstring_t replaceAll      (const std::tstring_t &csStr, const std::tstring_t &csOldStr, const std::tstring_t &csNewStr);
        ///< replace all strings
    static std::tstring_t replaceAll      (const std::tstring_t &csStr, const tchar_t &ccOldStr, const tchar_t &ccNewStr);
        ///< replace all chars
    static std::tstring_t removeAll       (const std::tstring_t &csStr, const std::tstring_t &csRemoveStr);
        ///< remove all strings

    static void           split           (const std::tstring_t &csStr, const std::tstring_t &csSep, std::vec_tstring_t *pvsOut);
        ///< split by separator
    static std::tstring_t join            (const std::vec_tstring_t &cvsVec, const tchar_t &cchSep);
        ///< join with char separator
    static std::tstring_t join            (const std::vec_tstring_t &cvsVec, const std::tstring_t &csSep);
        ///< join with string separator
    static std::tstring_t cut             (const std::tstring_t &csStr, const std::tstring_t &csLeftSep, const std::tstring_t &csRightSep);
        ///< cut using strings
    static std::tstring_t cut             (const std::tstring_t &csStr, const size_t &cuiStartPos = 0, const size_t &cuiEndPos = std::tstring_t::npos);
        ///< cut using string positions
    static std::tstring_t format          (const tchar_t *pcszFormat, ...);
        ///< format
    static std::tstring_t formatV         (const tchar_t *pcszFormat, va_list palArgs);
        ///< format
    static std::tstring_t minimize        (const std::tstring_t &csStr, const size_t &cuiMaxLen);
        ///< minimize

    /****************************************************************************
    *   compare
    *
    *****************************************************************************/

    static bool           compareNoCase   (const std::tstring_t &csStr1, const std::tstring_t &csStr2);
        ///< no case compare

    /****************************************************************************
    *    formating
    *
    *****************************************************************************/

    static std::tstring_t formatBytes     (const ulonglong_t &cullBytes);
        ///< format bytes (like Bit(s), Byte(s), MB, GB, TB)
    static std::tstring_t formatPercentage(const ulonglong_t &cullMaxValue, const ulonglong_t &cullCurrValue);
        ///< formatting percentage
    static std::tstring_t translitLatToRus(const std::tstring_t &csStr);
        ///< translit

    /****************************************************************************
    *    memory
    *
    *****************************************************************************/

    static void *         memoryZeroSecure(void *pvBuff, const size_t &cuiBuffSize);
        ///< secure zero memory

    /****************************************************************************
    *    other
    *
    *****************************************************************************/

    static std::tstring_t  createGuid     ();
        ///< generate GUID
    static bool            isRepeated     (const std::tstring_t &csStr);
        ///< is repeated

private:
                           CxString       ();
        ///< constructor
    virtual               ~CxString       ();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxString.inl"
//---------------------------------------------------------------------------
#endif // xLib_Common_CxStringH
