/**
 * \file  CxChar.h
 * \brief character
 */


#ifndef xLib_Common_CxCharH
#define xLib_Common_CxCharH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxChar :
    public CxNonCopyable
    /// character
{
    public:
        static BOOL  bIsAlphaNum(const char_t cchChar);
            ///< Check if character is alphanumeric
        static BOOL  bIsAlpha   (const char_t cchChar);
            ///< Check if character is alphabetic
        static BOOL  bIsControl (const char_t cchChar);
            ///< Check if character is a control character
        static BOOL  bIsDigitDec(const char_t cchChar);
            ///< Check if character is decimal digit
        static BOOL  bIsDigitHex(const char_t cchChar);
            ///< Check if character is hexadecimal digit

        static BOOL  bIsGraph   (const char_t cchChar);
            ///< Check if character has graphical representation
        static BOOL  bIsPrint   (const char_t cchChar);
            ///< Check if character is printable
        static BOOL  bIsPunct   (const char_t cchChar);
            ///< Check if character is a punctuation character
        static BOOL  bIsSpace   (const char_t cchChar);
            ///< Check if character is a white-space

        static BOOL  bIsLower   (const char_t cchChar);
            ///< Check if character is lowercase letter
        static BOOL  bIsUpper   (const char_t cchChar);
            ///< Check if character is uppercase letter

        static char_t chToLower  (const char_t cchChar);
            ///< Convert uppercase letter to lowercase
        static char_t chToUpper  (const char_t cchChar);
            ///< Convert lowercase letter to uppercase

    private:
                     CxChar     ();
            ///< constructor
        virtual     ~CxChar     ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Common_CxCharH
