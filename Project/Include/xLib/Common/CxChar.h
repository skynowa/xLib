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
    static bool    isAlphaNum(const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is alphanumeric
    static bool    isAlpha   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is alphabetic
    static bool    isControl (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is a control character
    static bool    isDigitDec(const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is decimal digit
    static bool    isDigitHex(const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is hexadecimal digit

    static bool    isGraph   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character has graphical representation
    static bool    isPrint   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is printable
    static bool    isPunct   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is a punctuation character
    static bool    isSpace   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is a white-space

    static bool    isLower   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is lowercase letter
    static bool    isUpper   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Check if character is uppercase letter

    static tchar_t toLower   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
        ///< Convert uppercase letter to lowercase
    static tchar_t toUpper   (const tchar_t &cchChar) xWARN_UNUSED_RESULT;
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
