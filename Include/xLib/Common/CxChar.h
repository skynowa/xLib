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
        static bool  bIsAlphaNum(const tchar cchChar);
            ///< Check if character is alphanumeric
        static bool  bIsAlpha   (const tchar cchChar);
            ///< Check if character is alphabetic
        static bool  bIsControl (const tchar cchChar);
            ///< Check if character is a control character
        static bool  bIsDigitDec(const tchar cchChar);
            ///< Check if character is decimal digit
        static bool  bIsDigitHex(const tchar cchChar);
            ///< Check if character is hexadecimal digit

        static bool  bIsGraph   (const tchar cchChar);
            ///< Check if character has graphical representation
        static bool  bIsPrint   (const tchar cchChar);
            ///< Check if character is printable
        static bool  bIsPunct   (const tchar cchChar);
            ///< Check if character is a punctuation character
        static bool  bIsSpace   (const tchar cchChar);
            ///< Check if character is a white-space

        static bool  bIsLower   (const tchar cchChar);
            ///< Check if character is lowercase letter
        static bool  bIsUpper   (const tchar cchChar);
            ///< Check if character is uppercase letter

        static tchar chToLower  (const tchar cchChar);
            ///< Convert uppercase letter to lowercase
        static tchar chToUpper  (const tchar cchChar);
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
