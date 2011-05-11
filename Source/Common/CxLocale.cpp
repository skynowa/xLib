/****************************************************************************
* Class name:  CxLocale
* Description: locale
* File name:   CxLocale.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.08.2009 19:47:14
*
*****************************************************************************/


#include <xLib/Common/CxLocale.h>

#include <locale.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: sGetCurrent (get current)
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

    sRes.assign(sRes.c_str(), iRes);    //delete from end '\0'
#elif defined(xOS_LINUX)
    const TCHAR *pcszLocale = NULL;

    pcszLocale = _tsetlocale(LC_ALL, NULL);
    /*DEBUG*/xASSERT_RET(NULL != pcszLocale, tString());

    sRes.assign(pcszLocale);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//DONE: bSetCurrent (set current)
/*static*/
BOOL
CxLocale::bSetCurrent(const tString &csLocale) {
    /*DEBUG*/// csLocale - n/a

    LPCTSTR pcszLocale = (true == csLocale.empty()) ? NULL : csLocale.c_str();

#if defined(xOS_WIN)
    BOOL bRes = FALSE;

    bRes = ::SetLocaleInfo((LCID)pcszLocale, LC_ALL, 0);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    LPCTSTR pcszRes = NULL;

    pcszRes = _tsetlocale(LC_ALL, pcszLocale);
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bSetDefault (set default)
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
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxLocale
CxLocale::CxLocale() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxLocale
/*virtual*/
CxLocale::~CxLocale() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
