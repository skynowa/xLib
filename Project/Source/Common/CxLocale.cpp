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
/* static */
std::tstring_t
CxLocale::sGetCurrent() {
    /*DEBUG*/// n/a

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    int  iRv = - 1;
    LCID lcId   = 0;

    lcId = ::GetSystemDefaultLCID();
    /*DEBUG*/// n/a

    //Retrieves information about a locale specified by identifier
    iRv = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, 0, 0);
    /*DEBUG*/xASSERT_RET(0 != iRv, std::tstring_t());

    sRv.resize(iRv);
    iRv = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, &sRv.at(0), sRv.size());
    /*DEBUG*/xASSERT_RET(0 != iRv, std::tstring_t());

    sRv.resize(iRv - sizeof('\0'));    //delete from end '\0'
#elif xOS_ENV_UNIX
    const tchar_t *pcszLocale = NULL;

    pcszLocale = std::xTSETLOCALE(LC_ALL, NULL);
    /*DEBUG*/xASSERT_RET(NULL != pcszLocale, std::tstring_t());

    sRv.assign(pcszLocale);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
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
/* static */
bool
CxLocale::bSetDefault() {
    /*DEBUG*/// n/a

    bool bRv = CxLocale::bSetCurrent(CxLocale::sGetCurrent());
   /*DEBUG*/xASSERT_RET(true == bRv, false);

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
/* virtual */
CxLocale::~CxLocale() {
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
