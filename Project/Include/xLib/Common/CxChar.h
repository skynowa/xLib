/**
 * \file  CxChar.h
 * \brief character
 */


#ifndef xLib_Common_CxCharH
#define xLib_Common_CxCharH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxChar :
    private CxNonCopyable
    /// character
{
public:
    static bool_t    isAlphaNum(ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is alphanumeric
    static bool_t    isAlpha   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is alphabetic
    static bool_t    isControl (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is a control character
    static bool_t    isDigitDec(ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is decimal digit
    static bool_t    isDigitHex(ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is hexadecimal digit

    static bool_t    isGraph   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character has graphical representation
    static bool_t    isPrint   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is printable
    static bool_t    isPunct   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is a punctuation character
    static bool_t    isSpace   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is a white-space

    static bool_t    isLower   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is lowercase letter
    static bool_t    isUpper   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Check if character is uppercase letter

    static tchar_t toLower   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Convert uppercase letter to lowercase
    static tchar_t toUpper   (ctchar_t &cchChar) xWARN_UNUSED_RV;
        ///< Convert lowercase letter to uppercase

private:
                   CxChar    ();
        ///< constructor
    virtual       ~CxChar    ();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Common_CxCharH
