/****************************************************************************
* Class name:  CxChar
* Description: character
* File name:   CxChar.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     11:01:2010 13:20:00
*
*****************************************************************************/


#ifndef xLib_Common_CxCharH
#define xLib_Common_CxCharH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxChar :
    public CxNonCopyable
{
    public:
        static BOOL  bIsAlphaNum(const TCHAR cchChar);
        	///< Check if character is alphanumeric
        static BOOL  bIsAlpha   (const TCHAR cchChar);
    		///< Check if character is alphabetic
        static BOOL  bIsControl (const TCHAR cchChar);
			///< Check if character is a control character
        static BOOL  bIsDigitDec(const TCHAR cchChar);
			///< Check if character is decimal digit
        static BOOL  bIsDigitHex(const TCHAR cchChar);
			///< Check if character is hexadecimal digit

        static BOOL  bIsGraph   (const TCHAR cchChar);
			///< Check if character has graphical representation
        static BOOL  bIsPrint   (const TCHAR cchChar);
			///< Check if character is printable
        static BOOL  bIsPunct   (const TCHAR cchChar);
			///< Check if character is a punctuation character
        static BOOL  bIsSpace   (const TCHAR cchChar);
			///< Check if character is a white-space

        static BOOL  bIsLower   (const TCHAR cchChar);
			///< Check if character is lowercase letter
        static BOOL  bIsUpper   (const TCHAR cchChar);
			///< Check if character is uppercase letter

        static TCHAR chToLower  (const TCHAR cchChar);
			///< Convert uppercase letter to lowercase
        static TCHAR chToUpper  (const TCHAR cchChar);
			///< Convert lowercase letter to uppercase

    private:
                     CxChar     ();
            ///< constructor
        virtual     ~CxChar     ();
			///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxCharH
