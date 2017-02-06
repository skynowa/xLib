/**
 * \file  Char.h
 * \brief character
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

template<typename T>
class Char
    /// character
{
public:
    explicit        Char(const T &ch, const xTLOCALE &locale = xTLOCALE());
        ///< constructor
    virtual        ~Char() {}
        ///< destructor

    T               character() const xWARN_UNUSED_RV;
        ///< get character
    const xTLOCALE& locale() const xWARN_UNUSED_RV;
        ///< get locale

    bool_t          isAlphaNum() const xWARN_UNUSED_RV;
        ///< Check if ch is alphanumeric
    bool_t          isAlpha() const xWARN_UNUSED_RV;
        ///< Check if ch is alphabetic
    bool_t          isControl() const xWARN_UNUSED_RV;
        ///< Check if ch is a control ch
    bool_t          isDigitDec() const xWARN_UNUSED_RV;
        ///< Check if ch is decimal digit
    bool_t          isDigitHex() const xWARN_UNUSED_RV;
        ///< Check if ch is hexadecimal digit

    bool_t          isGraph() const xWARN_UNUSED_RV;
        ///< Check if ch has graphical representation
    bool_t          isPrint() const xWARN_UNUSED_RV;
        ///< Check if ch is printable
    bool_t          isPunct() const xWARN_UNUSED_RV;
        ///< Check if ch is a punctuation ch
    bool_t          isSpace() const xWARN_UNUSED_RV;
        ///< Check if ch is a white-space

    bool_t          isLower() const xWARN_UNUSED_RV;
        ///< Check if ch is lowercase letter
    bool_t          isUpper() const xWARN_UNUSED_RV;
        ///< Check if ch is uppercase letter

    T               toLower() const xWARN_UNUSED_RV;
        ///< Convert uppercase letter to lowercase
    T               toUpper() const xWARN_UNUSED_RV;
        ///< Convert lowercase letter to uppercase
    std::tstring_t  symbol();
        ///< char as symbol

private:
    const T         _ch;
    const xTLOCALE &_locale;

    xNO_COPY_ASSIGN(Char)
};

typedef Char<char>    CharA;
typedef Char<wchar_t> CharW;
typedef Char<uchar_t> CharU;
typedef Char<tchar_t> CharT;

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Char.inl"
