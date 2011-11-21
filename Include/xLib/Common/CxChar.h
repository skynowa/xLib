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
        static bool  bIsAlphaNum(const tchar_t cchChar);
            ///< Check if character is alphanumeric
        static bool  bIsAlpha   (const tchar_t cchChar);
            ///< Check if character is alphabetic
        static bool  bIsControl (const tchar_t cchChar);
            ///< Check if character is a control character
        static bool  bIsDigitDec(const tchar_t cchChar);
            ///< Check if character is decimal digit
        static bool  bIsDigitHex(const tchar_t cchChar);
            ///< Check if character is hexadecimal digit

        static bool  bIsGraph   (const tchar_t cchChar);
            ///< Check if character has graphical representation
        static bool  bIsPrint   (const tchar_t cchChar);
            ///< Check if character is printable
        static bool  bIsPunct   (const tchar_t cchChar);
            ///< Check if character is a punctuation character
        static bool  bIsSpace   (const tchar_t cchChar);
            ///< Check if character is a white-space

        static bool  bIsLower   (const tchar_t cchChar);
            ///< Check if character is lowercase letter
        static bool  bIsUpper   (const tchar_t cchChar);
            ///< Check if character is uppercase letter

        static tchar_t chToLower  (const tchar_t cchChar);
            ///< Convert uppercase letter to lowercase
        static tchar_t chToUpper  (const tchar_t cchChar);
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
