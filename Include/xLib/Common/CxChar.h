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
class CxChar : public CxNonCopyable {
    public:
        static BOOL  bIsAlphaNum(const INT ciChar);
        static BOOL  bIsAlpha   (const INT ciChar);
        static BOOL  bIsControl (const INT ciChar);
        static BOOL  bIsDigitDec(const INT ciChar);
        static BOOL  bIsDigitHex(const INT ciChar);

        static BOOL  bIsGraph   (const INT ciChar);
        static BOOL  bIsPrint   (const INT ciChar);
        static BOOL  bIsPunct   (const INT ciChar);
        static BOOL  bIsSpace   (const INT ciChar);

        static BOOL  bIsLower   (const INT ciChar);
        static BOOL  bIsUpper   (const INT ciChar);

        static TCHAR chToLower  (const INT ciChar);
        static TCHAR chToUpper  (const INT ciChar);

    private:
        BOOL         _m_bRes;

                     CxChar     ();
        virtual     ~CxChar     ();
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxCharH
