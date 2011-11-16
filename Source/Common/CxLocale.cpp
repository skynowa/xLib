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
std::string_t
CxLocale::sGetCurrent() {
    /*DEBUG*/// n/a

    std::string_t sRes;

#if defined(xOS_ENV_WIN)
    int  iRes = - 1;
    LCID lcId   = 0;

    lcId = ::GetSystemDefaultLCID();
    /*DEBUG*/// n/a

    //Retrieves information about a locale specified by identifier
    iRes = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, 0, 0);
    /*DEBUG*/xASSERT_RET(0 != iRes, std::string_t());

    sRes.resize(iRes);
    iRes = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, &sRes.at(0), sRes.size());
    /*DEBUG*/xASSERT_RET(0 != iRes, std::string_t());

    sRes.resize(iRes - sizeof('\0'));    //delete from end '\0'
#elif defined(xOS_ENV_UNIX)
    const char_t *pcszLocale = NULL;

    pcszLocale = std::xTSETLOCALE(LC_ALL, NULL);
    /*DEBUG*/xASSERT_RET(NULL != pcszLocale, std::string_t());

    sRes.assign(pcszLocale);
#endif

    return sRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxLocale::bSetCurrent(
    const std::string_t &csLocale
)
{
    /*DEBUG*/// csLocale - n/a

    const char_t *pcszLocale = (true == csLocale.empty()) ? NULL : csLocale.c_str();

    const char_t *pcszRes = NULL;

    pcszRes = ::xTSETLOCALE(LC_ALL, pcszLocale);
    /*DEBUG*/xASSERT_RET(NULL != pcszRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxLocale::bSetDefault() {
    /*DEBUG*/// n/a

    BOOL bRes = CxLocale::bSetCurrent(CxLocale::sGetCurrent());
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

xNAMESPACE_END(NxLib)
