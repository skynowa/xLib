/**
 * \file  String.h
 * \brief string utils
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class String
    /// strings utils
{
public:
///@name ctors, dtor
///@{
	xNO_DEFAULT_CONSTRUCT(String)
	xNO_COPY_ASSIGN(String)
///@}

    /*******************************************************************************
    *   converters
    *
    *******************************************************************************/

    template<typename T>
    static
    T              castTo(std::ctstring_t &value);
        ///< cast to bools, chars, ints, doubles, enums

    template<typename T>
    static
    std::tstring_t cast(const T &value);
        ///< convert type to std::tstring_t
    template<typename T>
    static
    std::tstring_t cast(const T &value, cint_t base);
        ///< convert type to std::tstring_t by base (8, 10, 16)
    template<typename T>
    static
    T              cast(std::ctstring_t &str);
        ///< convert std::tstring_t to type
    template<typename T>
    static
    T              cast(std::ctstring_t &str, cint_t base);
        ///< convert std::tstring_t by base (8, 10, 16) to type

    static
    std::string    castA(std::cwstring_t &str);
        ///< std::wstring in std::string
    static
    std::wstring   castW(std::cstring_t &str);
        ///< std::string in std::wstring

    static
    std::string    castA(std::cwstring_t &str, cuint_t codePage);
        ///< std::wstring in std::string
    static
    std::wstring   castW(std::cstring_t &str, cuint_t codePage);
        ///< std::string in std::wstring

    static
    std::string    castA(std::cwstring_t &str, const std::locale &locale);
        ///< std::wstring in std::string
    static
    std::wstring   castW(std::cstring_t  &str, const std::locale &locale);
        ///< std::string in std::wstring

    static
    std::string    castCodePage(std::cstring_t &str, cuint_t codePageSource, cuint_t codePageDest);
        ///< convert codepage

    static
    std::string    castToOem(std::ctstring_t &str);
        ///< convert char to oem
    static
    std::tstring_t castFromOem(std::cstring_t &str);
        ///< convert oem to char

    static
    std::tstring_t castBool(cbool_t value);
        ///< bool_t to std::tstring_t
    static
    bool_t         castBool(std::ctstring_t &str);
        ///< convert std::tstring_t to bool_t

    static
    std::tstring_t toLowerCase(std::ctstring_t &str);
        ///< convert to low case
    static
    std::tstring_t toUpperCase(std::ctstring_t &str);
        ///< convert to uppercase
    static
    std::tstring_t toLowerCase(std::ctstring_t &str, std::csize_t length);
        ///< convert to low case
    static
    std::tstring_t toUpperCase(std::ctstring_t &str, std::csize_t length);
        ///< convert to uppercase

    /*******************************************************************************
    *   actions
    *
    *******************************************************************************/

    static
    std::tstring_t trimLeftChars(std::ctstring_t &str, std::ctstring_t &chars);
        ///< trim left chars
    static
    std::tstring_t trimRightChars(std::ctstring_t &str, std::ctstring_t &chars);
        ///< trim left chars
    static
    std::tstring_t trimChars(std::ctstring_t &str, std::ctstring_t &chars);
        ///< trim left, right chars
    static
    std::tstring_t trimSpace(std::ctstring_t &str);
        ///< trim left, right spaces
    static
    std::tstring_t removeEol(std::ctstring_t &str);
        ///< remove end of line from end of string
    static
    std::tstring_t quoted(std::ctstring_t &str, ctchar_t delimiter = xT('\"'),
                       ctchar_t escape = xT('\\'));
        ///< quote string

    static
    std::tstring_t replaceAll(std::ctstring_t &str, std::ctstring_t &strOld,
                       std::ctstring_t &strNew);
        ///< replace all strings
    static
    std::tstring_t replaceAll(std::ctstring_t &str, ctchar_t &charOld, ctchar_t &charNew);
        ///< replace all chars
    static
    std::tstring_t removeAll(std::ctstring_t &str, std::ctstring_t &removeStr);
        ///< remove all strings

	// split
    static
    void_t         split(std::ctstring_t &str, std::ctstring_t &sep, std::vec_tstring_t *rv);
        ///< split by separator
	template<typename T>
    static
    void_t         split(std::ctstring_t &str, std::ctstring_t &sepLine,
                        std::ctstring_t &sepKeyValue, T *map);
        ///< split by separator

    // join
    static
    std::tstring_t join(std::cvec_tstring_t &vec, ctchar_t &sep);
        ///< join with char separator
    static
    std::tstring_t join(std::cvec_tstring_t &vec, std::ctstring_t &sep);
        ///< join with string separator
    template<typename T>
    static
    std::tstring_t join(const T &map, std::ctstring_t &sepLine, std::ctstring_t &sepKeyValue);
        ///< join with string separator

    static
    std::tstring_t cut(std::ctstring_t &str, std::ctstring_t &sepLeft, std::ctstring_t &sepRight);
        ///< cut using strings
    static
    std::tstring_t rcut(std::ctstring_t &str, std::ctstring_t &sepLeft, std::ctstring_t &sepRight);
        ///< cut using strings
    static
    std::tstring_t cut(std::ctstring_t &str, std::csize_t posBegin,
                       std::csize_t posEnd = std::tstring_t::npos);
        ///< cut using string positions
    static
    std::tstring_t minimize(std::ctstring_t &str, std::csize_t maxLength);
        ///< minimize

    /*******************************************************************************
    *    formating
    *
    *******************************************************************************/

    static
    std::tstring_t formatBytes(culonglong_t &bytes);
        ///< format bytes (like Bit(s), Byte(s), MB, GB, TB)
    static
    std::tstring_t formatPercentage(culonglong_t &maxValue, culonglong_t &currentValue);
        ///< formatting percentage

    /*******************************************************************************
    *    memory
    *
    *******************************************************************************/

    static
    void_t *       memoryZeroSecure(void_t *buff, std::csize_t buffSize);
        ///< secure zero memory

    /*******************************************************************************
    *    other
    *
    *******************************************************************************/

    static
    bool_t         isRepeated(std::ctstring_t &str);
        ///< is repeated

xPLATFORM_IMPL:
    static
    std::string    _castA_impl(std::cwstring_t &str, cuint_t codePage);
    static
    std::wstring   _castW_impl(std::cstring_t &str, cuint_t codePage);
    static
    std::string    _castToOem_impl(std::ctstring_t &str);
    static
    std::tstring_t _castFromOem_impl(std::cstring_t &str);
    static
    std::tstring_t _toLowerCase_impl(std::ctstring_t &str, std::csize_t length);
    static
    std::tstring_t _toUpperCase_impl(std::ctstring_t &str, std::csize_t length);
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class StringCI
    /// strings utils (case insensitive)
{
public:
///@name ctors, dtor
///@{
	xNO_DEFAULT_CONSTRUCT(StringCI)
	xNO_COPY_ASSIGN(StringCI)
///@}

    /*******************************************************************************
    *   search, compare
    *
    *******************************************************************************/

    static
    std::size_t find(std::ctstring_t &str, std::ctstring_t &target, std::csize_t pos = 0,
                    const xTLOCALE &locale = xTLOCALE());
        ///< no case search
    static
    bool_t      contains(std::ctstring_t &str, std::ctstring_t &target, std::csize_t pos = 0,
                    const xTLOCALE &locale = xTLOCALE());
        ///< no case search
    static
    bool_t      compare(std::ctstring_t &str1, std::ctstring_t &str2,
                    const xTLOCALE &locale = xTLOCALE());
        ///< no case compare

xPLATFORM_IMPL:
    static
    bool_t      _compare_impl(std::ctstring_t &str1, std::ctstring_t &str2,
                    const xTLOCALE &locale = xTLOCALE());
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "String.inl"
