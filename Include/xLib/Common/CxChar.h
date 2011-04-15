/****************************************************************************
* Class name:  CxChar
* Description: character
* File name:   CxChar.h
* Compilers:   Visual C++ 2010 
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     11:01:2010 13:20:00
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_CxCharH
#define xLib_Common_CxCharH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxChar : public CxNonCopyable {
	public:
        static BOOL  bIsAlphaNum(INT iChar);
        static BOOL  bIsAlpha   (INT iChar);
        static BOOL  bIsControl (INT iChar);
        static BOOL  bIsDigitDec(INT iChar);
        static BOOL  bIsDigitHex(INT iChar);

        static BOOL  bIsGraph   (INT iChar);
        static BOOL  bIsPrint   (INT iChar);
        static BOOL  bIsPunct   (INT iChar);
        static BOOL  bIsSpace   (INT iChar);

        static BOOL  bIsLower   (INT iChar);
        static BOOL  bIsUpper   (INT iChar);

        static CHAR  chToLower  (INT iChar);
        static CHAR  chToUpper  (INT iChar);

	private:
		BOOL         _m_bRes;

                     CxChar     ();
        virtual     ~CxChar     ();
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxCharH
