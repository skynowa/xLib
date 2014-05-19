/**
 * \file  CxChar.h
 * \brief character
 */


#pragma once

#ifndef xLib_CxCharH
#define xLib_CxCharH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class CxChar
    /// character
{
public:
                CxChar(ctchar_t &ch, const std::locale &locale = std::locale());
        ///< constructor
    virtual    ~CxChar() {}
        ///< destructor

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

private:
    tchar_t     _ch;
    std::locale _locale;

    xNO_COPY_ASSIGN(CxChar)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "CxChar.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxCharH
