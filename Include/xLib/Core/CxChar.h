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
xNAMESPACE_BEGIN(NxLib)

class CxChar
    /// character
{
public:
    static bool_t  isAlphaNum(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is alphanumeric
    static bool_t  isAlpha(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is alphabetic
    static bool_t  isControl(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is a control ch
    static bool_t  isDigitDec(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is decimal digit
    static bool_t  isDigitHex(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is hexadecimal digit

    static bool_t  isGraph(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch has graphical representation
    static bool_t  isPrint(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is printable
    static bool_t  isPunct(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is a punctuation ch
    static bool_t  isSpace(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is a white-space

    static bool_t  isLower(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is lowercase letter
    static bool_t  isUpper(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Check if ch is uppercase letter

    static tchar_t toLower(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Convert uppercase letter to lowercase
    static tchar_t toUpper(ctchar_t &ch) xWARN_UNUSED_RV;
        ///< Convert lowercase letter to uppercase

private:
                   CxChar();
        ///< constructor
    virtual       ~CxChar();
        ///< destructor

    xNO_COPY_ASSIGN(CxChar)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxChar.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxCharH
