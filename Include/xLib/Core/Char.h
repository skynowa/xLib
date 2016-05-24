/**
 * \file  Char.h
 * \brief character
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Char
    /// character
{
public:
    explicit    Char(ctchar_t &ch, const xLOCALE &locale = xLOCALE());
        ///< constructor
    virtual    ~Char() {}
        ///< destructor

    ctchar_t&   character() const xWARN_UNUSED_RV;
        ///< get character
    const xLOCALE& locale() const xWARN_UNUSED_RV;
        ///< get locale

    bool_t      isAlphaNum() const xWARN_UNUSED_RV;
        ///< Check if ch is alphanumeric
    bool_t      isAlpha() const xWARN_UNUSED_RV;
        ///< Check if ch is alphabetic
    bool_t      isControl() const xWARN_UNUSED_RV;
        ///< Check if ch is a control ch
    bool_t      isDigitDec() const xWARN_UNUSED_RV;
        ///< Check if ch is decimal digit
    bool_t      isDigitHex() const xWARN_UNUSED_RV;
        ///< Check if ch is hexadecimal digit

    bool_t      isGraph() const xWARN_UNUSED_RV;
        ///< Check if ch has graphical representation
    bool_t      isPrint() const xWARN_UNUSED_RV;
        ///< Check if ch is printable
    bool_t      isPunct() const xWARN_UNUSED_RV;
        ///< Check if ch is a punctuation ch
    bool_t      isSpace() const xWARN_UNUSED_RV;
        ///< Check if ch is a white-space

    bool_t      isLower() const xWARN_UNUSED_RV;
        ///< Check if ch is lowercase letter
    bool_t      isUpper() const xWARN_UNUSED_RV;
        ///< Check if ch is uppercase letter

    tchar_t     toLower() const xWARN_UNUSED_RV;
        ///< Convert uppercase letter to lowercase
    tchar_t     toUpper() const xWARN_UNUSED_RV;
        ///< Convert lowercase letter to uppercase
    std::tstring_t symbol();
        ///< char as symbol

private:
    tchar_t _ch;
    xLOCALE _locale;

    xNO_COPY_ASSIGN(Char)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Char.cpp"
#endif
