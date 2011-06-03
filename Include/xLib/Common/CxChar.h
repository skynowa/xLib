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
        static BOOL  bIsAlpha   (const TCHAR cchChar);
        static BOOL  bIsControl (const TCHAR cchChar);
        static BOOL  bIsDigitDec(const TCHAR cchChar);
        static BOOL  bIsDigitHex(const TCHAR cchChar);

        static BOOL  bIsGraph   (const TCHAR cchChar);
        static BOOL  bIsPrint   (const TCHAR cchChar);
        static BOOL  bIsPunct   (const TCHAR cchChar);
        static BOOL  bIsSpace   (const TCHAR cchChar);

        static BOOL  bIsLower   (const TCHAR cchChar);
        static BOOL  bIsUpper   (const TCHAR cchChar);

        static TCHAR chToLower  (const TCHAR cchChar);
        static TCHAR chToUpper  (const TCHAR cchChar);

    private:
                     CxChar     ();
        virtual     ~CxChar     ();
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxCharH
