/**
 * \file  CxLocale.cpp
 * \brief locale
 */


#include <xLib/Common/CxLocale.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring_t
CxLocale::sGetCurrent() {
    /*DEBUG*/// n/a

    std::tstring_t sRes;

#if xOS_ENV_WIN
    int  iRes = - 1;
    LCID lcId   = 0;

    lcId = ::GetSystemDefaultLCID();
    /*DEBUG*/// n/a

    //Retrieves information about a locale specified by identifier
    iRes = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, 0, 0);
    /*DEBUG*/xASSERT_RET(0 != iRes, std::tstring_t());

    sRes.resize(iRes);
    iRes = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != iRes, std::tstring_t());

    sRes.resize(iRes - sizeof('\0'));    //delete from end '\0'
#elif xOS_ENV_UNIX
    const tchar_t *pcszLocale = NULL;

    pcszLocale = std::xTSETLOCALE(LC_ALL, NULL);
    /*DEBUG*/xASSERT_RET(NULL != pcszLocale, std::tstring_t());

    sRes.assign(pcszLocale);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxLocale::bSetCurrent(
    const std::tstring_t &csLocale
)
{
    /*DEBUG*/// csLocale - n/a

    const tchar_t *pcszLocale = (true == csLocale.empty()) ? NULL : csLocale.c_str();

    const tchar_t *pcszRes = NULL;

    pcszRes = ::xTSETLOCALE(LC_ALL, pcszLocale);
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxLocale::bSetDefault() {
    /*DEBUG*/// n/a

    bool bRes = CxLocale::bSetCurrent(CxLocale::sGetCurrent());
   /*DEBUG*/xASSERT_RET(false != bRes, false);

   return true;
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

xNAMESPACE_END(NxLib)
