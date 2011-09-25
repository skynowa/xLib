/**
 * \file  CxLocale.cpp
 * \brief locale
 */


#include <xLib/Common/CxLocale.h>

#include <locale.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring
CxLocale::sGetCurrent() {
    /*DEBUG*/// n/a

    std::tstring sRes;

#if defined(xOS_WIN)
    INT  iRes = - 1;
    LCID lcId   = 0;

    lcId = ::GetSystemDefaultLCID();
    /*DEBUG*/// n/a

    //Retrieves information about a locale specified by identifier
    iRes = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, 0, 0);
    /*DEBUG*/xASSERT_RET(0 != iRes, std::tstring());

    sRes.resize(iRes);
    iRes = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != iRes, std::tstring());

    sRes.resize(iRes - sizeof('\0'));    //delete from end '\0'
#elif defined(xOS_LINUX)
    const TCHAR *pcszLocale = NULL;

    pcszLocale = xTSETLOCALE(LC_ALL, NULL);
    /*DEBUG*/xASSERT_RET(NULL != pcszLocale, std::tstring());

    sRes.assign(pcszLocale);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxLocale::bSetCurrent(
    const std::tstring &csLocale
)
{
    /*DEBUG*/// csLocale - n/a

    LPCTSTR pcszLocale = (true == csLocale.empty()) ? NULL : csLocale.c_str();

    LPCTSTR pcszRes = NULL;

    pcszRes = xTSETLOCALE(LC_ALL, pcszLocale);
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
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
CxLocale::CxLocale() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
/*virtual*/
CxLocale::~CxLocale() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
