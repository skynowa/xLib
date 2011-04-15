/****************************************************************************
* Class name:  CxLocale
* Description: locale
* File name:   CxLocale.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     09.08.2009 19:47:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Common/CxLocale.h>

#include <locale.h>


/****************************************************************************
*	public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + sGetCurrent (get current)
/*static*/ 
tString
CxLocale::sGetCurrent() {
	/*DEBUG*/// n/a
	
	tString sRes;
	
#if defined(xOS_WIN)
    INT  iRes = - 1;
    LCID lcId   = 0;

    lcId = ::GetSystemDefaultLCID();
    /*DEBUG*/// n/a

    //Retrieves information about a locale specified by identifier
    iRes = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, 0, 0);
    /*DEBUG*/xASSERT_RET(0 != iRes, tString());

    sRes.resize(iRes);
    iRes = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != iRes, tString());

    sRes.assign(sRes.c_str());	//delete from end '\0'
#elif defined(xOS_LINUX)
    const TCHAR  *pszLocale = NULL;

    pszLocale = _tsetlocale(LC_ALL, NULL);
    /*DEBUG*/xASSERT_RET(NULL != pszLocale, tString());

    sRes.assign(pszLocale);
#endif
	
	return sRes;
}
//---------------------------------------------------------------------------
//TODO: - bSetCurrent (set current)
/*static*/ 
BOOL
CxLocale::bSetCurrent(const tString &csLocale) {
	/*DEBUG*/xASSERT_RET(false == csLocale.empty(), FALSE);

	LPCTSTR pcszLocale = NULL;

    pcszLocale = _tsetlocale(LC_ALL, csLocale.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pcszLocale, FALSE);
 
    return TRUE;

/*
	_tsetlocale(LC_ALL, csLocale.c_str());
*/
 
	//-------------------------------------
	//2
	////BOOL bRes = FALSE;

	////bRes = ::SetLocaleInfo((LCID)csLocale.c_str(), LC_ALL,  0);
	/////*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	////return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bSetDefault (set default)
/*static*/ 
BOOL
CxLocale::bSetDefault() {
    /*DEBUG*/// n/a

	BOOL bRes = FALSE;
	
	bRes = CxLocale::bSetCurrent(CxLocale::sGetCurrent());
   /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
   
   return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*	private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxLocale
CxLocale::CxLocale() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//TODO: + ~CxLocale
/*virtual*/
CxLocale::~CxLocale() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------







//int GetLocaleInfo(
//				  __in   LCID Locale,
//				  __in   LCTYPE LCType,
//				  __out  LPTSTR lpLCData,
//				  __in   int cchData
//				  );

//BOOL SetLocaleInfo(
//				   __in  LCID Locale,
//				   __in  LCTYPE LCType,
//				   __in  LPCTSTR lpLCData
//				   );
