/**
 * \file  CxString.h
 * \brief string utils
 */


#pragma once

#ifndef xLib_CxStringH
#define xLib_CxStringH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(xlib)

class CxString
    /// strings utils
{
public:
    /*******************************************************************************
    *   converters
    *
    *******************************************************************************/

    template<class T>
    static std::tstring_t cast(const T &value) xWARN_UNUSED_RV;
        ///< convert type to std::tstring_t
    template<class T>
    static std::tstring_t cast(const T &value, cint_t &base) xWARN_UNUSED_RV;
        ///< convert type to std::tstring_t by base
    template<class T>
    static T              cast(std::ctstring_t &str) xWARN_UNUSED_RV;
        ///< convert std::tstring_t to type
    template<class T>
    static T              cast(std::ctstring_t &str, cint_t &base) xWARN_UNUSED_RV;
        ///< convert std::tstring_t by base (8, 10, 16) to type

    static std::string    castA(std::cwstring_t &str) xWARN_UNUSED_RV;
        ///< std::wstring in std::string
    static std::wstring   castW(std::cstring_t &str) xWARN_UNUSED_RV;
        ///< std::string in std::wstring

    static std::wstring   strToWStr(std::cstring_t &str, cuint_t &codePage) xWARN_UNUSED_RV;
        ///< std::string in std::wstring
    static std::string    wstrToStr(std::cwstring_t &str, cuint_t &codePage) xWARN_UNUSED_RV;
        ///< std::wstring in std::string

    static std::wstring   strToWStr(std::cstring_t  &stdString,
                              const std::locale &locale = std::locale()) xWARN_UNUSED_RV;
        ///< std::string in std::wstring
    static std::string    wstrToStr(std::cwstring_t &stdWString,
                              const std::locale &locale = std::locale()) xWARN_UNUSED_RV;
        ///< std::wstring in std::string

    static std::string    convertCodePage(std::cstring_t &source, cuint_t &codePageSource,
                              cuint_t &codePageDest) xWARN_UNUSED_RV;
        ///< convert codepage

    static std::string    charToOemBuff(std::ctstring_t &str) xWARN_UNUSED_RV;
        ///< convert char to oem
    static std::tstring_t oemToCharBuff(std::cstring_t &str) xWARN_UNUSED_RV;
        ///< convert oem to char

    static std::tstring_t boolToStr(cbool_t &value) xWARN_UNUSED_RV;
        ///< bool_t to std::tstring_t
    static bool_t         strToBool(std::ctstring_t &str) xWARN_UNUSED_RV;
        ///< convert std::tstring_t to bool_t

    static std::tstring_t toLowerCase(std::ctstring_t &str) xWARN_UNUSED_RV;
        ///< convert to low case
    static std::tstring_t toUpperCase(std::ctstring_t &str) xWARN_UNUSED_RV;
        ///< convert to uppercase
    static std::tstring_t toLowerCase(std::ctstring_t &str, std::csize_t &length)
                              xWARN_UNUSED_RV;
        ///< convert to low case
    static std::tstring_t toUpperCase(std::ctstring_t &str, std::csize_t &length)
                              xWARN_UNUSED_RV;
        ///< convert to uppercase

    /*******************************************************************************
    *   actions
    *
    *******************************************************************************/

    static std::tstring_t trimLeftChars(std::ctstring_t &str, std::ctstring_t &chars)
                              xWARN_UNUSED_RV;
        ///< trim left chars
    static std::tstring_t trimRightChars(std::ctstring_t &str, std::ctstring_t &chars)
                              xWARN_UNUSED_RV;
        ///< trim left chars
    static std::tstring_t trimChars(std::ctstring_t &str, std::ctstring_t &chars)
                              xWARN_UNUSED_RV;
        ///< trim left, right chars
    static std::tstring_t trimSpace(std::ctstring_t &str) xWARN_UNUSED_RV;
        ///< trim left, right spaces
    static std::tstring_t removeEol(std::ctstring_t &str) xWARN_UNUSED_RV;
        ///< remove end of line from end of string

    static std::tstring_t replaceAll(std::ctstring_t &str, std::ctstring_t &strOld,
                              std::ctstring_t &strNew) xWARN_UNUSED_RV;
        ///< replace all strings
    static std::tstring_t replaceAll(std::ctstring_t &str, ctchar_t &charOld, ctchar_t &charNew)
                              xWARN_UNUSED_RV;
        ///< replace all chars
    static std::tstring_t removeAll(std::ctstring_t &str, std::ctstring_t &removeStr)
                              xWARN_UNUSED_RV;
        ///< remove all strings

    static void_t         split(std::ctstring_t &str, std::ctstring_t &sep,
                              std::vec_tstring_t *rv);
        ///< split by separator
    static std::tstring_t join(std::cvec_tstring_t &vec, ctchar_t &sep) xWARN_UNUSED_RV;
        ///< join with char separator
    static std::tstring_t join(std::cvec_tstring_t &vec, std::ctstring_t &sep) xWARN_UNUSED_RV;
        ///< join with string separator
    static std::tstring_t cut(std::ctstring_t &str, std::ctstring_t &sepLeft,
                              std::ctstring_t &sepRight) xWARN_UNUSED_RV;
        ///< cut using strings
    static std::tstring_t cut(std::ctstring_t &str, std::csize_t &posBegin = 0,
                              std::csize_t &posEnd = std::tstring_t::npos) xWARN_UNUSED_RV;
        ///< cut using string positions
    static std::tstring_t format(ctchar_t *format, ...) xWARN_UNUSED_RV;
        ///< format
    static std::tstring_t formatV(ctchar_t *format, va_list args) xWARN_UNUSED_RV;
        ///< format
    static std::tstring_t minimize(std::ctstring_t &str, std::csize_t &maxLength) xWARN_UNUSED_RV;
        ///< minimize

    /*******************************************************************************
    *   search, compare
    *
    *******************************************************************************/

    static std::size_t    findNoCase(std::ctstring_t &str, std::ctstring_t &target,
                              std::csize_t &pos = 0, const std::locale &a_locale = std::locale())
                              xWARN_UNUSED_RV;
        ///< no case search
    static bool_t         compareNoCase(std::ctstring_t &str1, std::ctstring_t &str2,
                              const std::locale &a_locale = std::locale()) xWARN_UNUSED_RV;
        ///< no case compare


    /*******************************************************************************
    *    formating
    *
    *******************************************************************************/

    static std::tstring_t formatBytes(culonglong_t &bytes) xWARN_UNUSED_RV;
        ///< format bytes (like Bit(s), Byte(s), MB, GB, TB)
    static std::tstring_t formatPercentage(culonglong_t &maxValue, culonglong_t &currentValue)
                              xWARN_UNUSED_RV;
        ///< formatting percentage

    /*******************************************************************************
    *    memory
    *
    *******************************************************************************/

    static void_t *       memoryZeroSecure(void_t *buff, std::csize_t &buffSize)
                              xWARN_UNUSED_RV;
        ///< secure zero memory

    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    static bool_t         isRepeated(std::ctstring_t &str) xWARN_UNUSED_RV;
        ///< is repeated

private:
                          CxString();
        ///< constructor
                         ~CxString();
        ///< destructor

    xNO_COPY_ASSIGN(CxString)
};

xNAMESPACE_END(xlib)
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(xlib)

class CxStringCI
    /// strings utils (case insensitive)
{
public:
    /*******************************************************************************
    *   search, compare
    *
    *******************************************************************************/

    static std::size_t    find(std::ctstring_t &str, std::ctstring_t &target, std::csize_t &pos = 0,
                              const std::locale &a_locale = std::locale()) xWARN_UNUSED_RV;
        ///< no case search
    static bool_t         compare(std::ctstring_t &str1, std::ctstring_t &str2,
                              const std::locale &a_locale = std::locale()) xWARN_UNUSED_RV;
        ///< no case compare

private:
                          CxStringCI();
        ///< constructor
                         ~CxStringCI();
        ///< destructor

    xNO_COPY_ASSIGN(CxStringCI)
};

xNAMESPACE_END(xlib)
//-------------------------------------------------------------------------------------------------
#include "CxString.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxStringH
