/****************************************************************************
* Class name:  CxLocale
* Description: locale
* File name:   CxLocale.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.08.2009 19:47:14
*
*****************************************************************************/


#ifndef xLib_Common_CxLocaleH
#define xLib_Common_CxLocaleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxLocale : public CxNonCopyable {
    public:
       static tString sGetCurrent();
       static BOOL    bSetCurrent(const tString &csLocale);
       static BOOL    bSetDefault();

    private:
                      CxLocale   ();
       virtual       ~CxLocale   ();
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxLocaleH



//-------------------------------------
////_tsetlocale(LC_ALL, NULL);
////setlocale(LC_ALL, "Russian"); 
//////_tsetlocale(LC_ALL, xT(""));
