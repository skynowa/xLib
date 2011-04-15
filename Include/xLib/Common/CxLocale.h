/****************************************************************************
* Class name:  CxLocale
* Description: locale
* File name:   CxLocale.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     09.08.2009 19:47:14
* Version:     1.0.0.0 Debug
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
#endif	//xLib_Common_CxLocaleH



//-------------------------------------
////_tsetlocale(LC_ALL, NULL);
////setlocale(LC_ALL, "Russian"); 
//////_tsetlocale(LC_ALL, _T(""));
