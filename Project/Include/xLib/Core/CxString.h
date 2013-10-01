/**
 * \file  CxString.h
 * \brief string utils
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
// overload operators << for std::basic_ostream
xNAMESPACE_BEGIN(std)

template<typename Traits>
inline basic_ostream<tchar_t, Traits> &
operator << (basic_ostream<tchar_t, Traits> &osOut, std::custring_t &cusValue);
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
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxString :
    private CxNonCopyable
    /// strings utils
{
public:
    /*******************************************************************************
    *   converters
    *
    *******************************************************************************/

    template<typename T>
    static std::tstring_t cast            (const T &cValueT) xWARN_UNUSED_RV;
        ///< convert type to std::tstring_t
    template<typename T>
    static std::tstring_t cast            (const T &cValueT, cint_t &ciBase) xWARN_UNUSED_RV;
        ///< convert type to std::tstring_t by base
    template<typename T>
    static T              cast            (std::ctstring_t &csStr) xWARN_UNUSED_RV;
        ///< convert std::tstring_t to type
    template<typename T>
    static T              cast            (std::ctstring_t &csStr, cint_t &ciBase) xWARN_UNUSED_RV;
        ///< convert std::tstring_t by base (8, 10, 16) to type

    static std::string    castA           (std::cwstring_t &csStr) xWARN_UNUSED_RV;
        ///< std::wstring in std::string
    static std::wstring   castW           (std::cstring_t &csStr) xWARN_UNUSED_RV;
        ///< std::string in std::wstring

    static std::wstring   strToWStr       (std::cstring_t  &csStr,  cuint_t &cuiCodePage) xWARN_UNUSED_RV;
        ///< std::string in std::wstring
    static std::string    wstrToStr       (std::cwstring_t &cwsStr, cuint_t &cuiCodePage) xWARN_UNUSED_RV;
        ///< std::wstring in std::string

    static std::wstring   strToWStr       (std::cstring_t  &csStdString,  const std::locale &clocLocale = std::locale()) xWARN_UNUSED_RV;
        ///< std::string in std::wstring
    static std::string    wstrToStr       (std::cwstring_t &csStdWString, const std::locale &clocLocale = std::locale()) xWARN_UNUSED_RV;
        ///< std::wstring in std::string

    static std::string    convertCodePage (std::cstring_t &csSource, cuint_t &cuiCodePageSource, cuint_t &cuiCodePageDest) xWARN_UNUSED_RV;
        ///< convert codepage

    static std::string    charToOemBuff   (std::ctstring_t &csSrc) xWARN_UNUSED_RV;
        ///< convert char to oem
    static std::tstring_t oemToCharBuff   (std::cstring_t &csSrc) xWARN_UNUSED_RV;
        ///< convert oem to char

    static std::tstring_t boolToStr       (cbool_t &cbBool) xWARN_UNUSED_RV;
        ///< bool_t to std::tstring_t
    static bool_t         strToBool       (std::ctstring_t &csStr) xWARN_UNUSED_RV;
        ///< convert std::tstring_t to bool_t

    static std::tstring_t toLowerCase     (std::ctstring_t &csStr) xWARN_UNUSED_RV;
        ///< convert to low case
    static std::tstring_t toUpperCase     (std::ctstring_t &csStr) xWARN_UNUSED_RV;
        ///< convert to uppercase
    static std::tstring_t toLowerCase     (std::ctstring_t &csStr, std::csize_t &cuiLength) xWARN_UNUSED_RV;
        ///< convert to low case
    static std::tstring_t toUpperCase     (std::ctstring_t &csStr, std::csize_t &cuiLength) xWARN_UNUSED_RV;
        ///< convert to uppercase

    /*******************************************************************************
    *   actions
    *
    *******************************************************************************/

    static std::tstring_t trimLeftChars   (std::ctstring_t &csStr, std::ctstring_t &csChars) xWARN_UNUSED_RV;
        ///< trim left chars
    static std::tstring_t trimRightChars  (std::ctstring_t &csStr, std::ctstring_t &csChars) xWARN_UNUSED_RV;
        ///< trim left chars
    static std::tstring_t trimChars       (std::ctstring_t &csStr, std::ctstring_t &csChars) xWARN_UNUSED_RV;
        ///< trim left, right chars
    static std::tstring_t trimSpace       (std::ctstring_t &csStr) xWARN_UNUSED_RV;
        ///< trim left, right spaces
    static std::tstring_t removeEol       (std::ctstring_t &csStr) xWARN_UNUSED_RV;
        ///< remove end of line from end of string

    static std::tstring_t replaceAll      (std::ctstring_t &csStr, std::ctstring_t &csOldStr, std::ctstring_t &csNewStr) xWARN_UNUSED_RV;
        ///< replace all strings
    static std::tstring_t replaceAll      (std::ctstring_t &csStr, ctchar_t &ccOldStr, ctchar_t &ccNewStr) xWARN_UNUSED_RV;
        ///< replace all chars
    static std::tstring_t removeAll       (std::ctstring_t &csStr, std::ctstring_t &csRemoveStr) xWARN_UNUSED_RV;
        ///< remove all strings

    static void_t         split           (std::ctstring_t &csStr, std::ctstring_t &csSep, std::vec_tstring_t *pvsOut);
        ///< split by separator
    static std::tstring_t join            (std::cvec_tstring_t &cvsVec, ctchar_t &cchSep) xWARN_UNUSED_RV;
        ///< join with char separator
    static std::tstring_t join            (std::cvec_tstring_t &cvsVec, std::ctstring_t &csSep) xWARN_UNUSED_RV;
        ///< join with string separator
    static std::tstring_t cut             (std::ctstring_t &csStr, std::ctstring_t &csLeftSep, std::ctstring_t &csRightSep) xWARN_UNUSED_RV;
        ///< cut using strings
    static std::tstring_t cut             (std::ctstring_t &csStr, std::csize_t &cuiStartPos = 0, std::csize_t &cuiEndPos = std::tstring_t::npos) xWARN_UNUSED_RV;
        ///< cut using string positions
    static std::tstring_t format          (ctchar_t *pcszFormat, ...) xWARN_UNUSED_RV;
        ///< format
    static std::tstring_t formatV         (ctchar_t *pcszFormat, va_list palArgs) xWARN_UNUSED_RV;
        ///< format
    static std::tstring_t minimize        (std::ctstring_t &csStr, std::csize_t &cuiMaxLen) xWARN_UNUSED_RV;
        ///< minimize

    /*******************************************************************************
    *   compare
    *
    *******************************************************************************/

    static bool_t         compareNoCase   (std::ctstring_t &csStr1, std::ctstring_t &csStr2) xWARN_UNUSED_RV;
        ///< no case compare

    /*******************************************************************************
    *    formating
    *
    *******************************************************************************/

    static std::tstring_t formatBytes     (culonglong_t &cullBytes) xWARN_UNUSED_RV;
        ///< format bytes (like Bit(s), Byte(s), MB, GB, TB)
    static std::tstring_t formatPercentage(culonglong_t &cullMaxValue, culonglong_t &cullCurrValue) xWARN_UNUSED_RV;
        ///< formatting percentage
    static std::tstring_t translitLatToRus(std::ctstring_t &csStr) xWARN_UNUSED_RV;
        ///< translit

    /*******************************************************************************
    *    memory
    *
    *******************************************************************************/

    static void_t *       memoryZeroSecure(void_t *pvBuff, std::csize_t &cuiBuffSize) xWARN_UNUSED_RV;
        ///< secure zero memory

    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    static std::tstring_t createGuid      () xWARN_UNUSED_RV;
        ///< generate GUID
    static bool_t         isRepeated      (std::ctstring_t &csStr) xWARN_UNUSED_RV;
        ///< is repeated

private:
                          CxString        ();
        ///< constructor
    virtual              ~CxString        ();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------

#include "CxString.inl"
