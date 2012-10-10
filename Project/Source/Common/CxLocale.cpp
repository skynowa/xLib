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
CxLocale::sCurrent() {
    /*DEBUG*/// n/a

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    int  iRv = - 1;
    LCID lcId   = 0;

    lcId = ::GetSystemDefaultLCID();
    /*DEBUG*/// n/a

    //Retrieves information about a locale specified by identifier
    iRv = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, 0, 0);
    /*DEBUG*/xTEST_DIFF(0, iRv);

    sRv.resize(iRv);
    iRv = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, &sRv.at(0), sRv.size());
    /*DEBUG*/xTEST_DIFF(0, iRv);

    sRv.resize(iRv - sizeof('\0'));    //delete from end '\0'
#elif xOS_ENV_UNIX
    const tchar_t *pcszLocale = NULL;

    pcszLocale = std::xTSETLOCALE(LC_ALL, NULL);
    /*DEBUG*/xTEST_PTR(pcszLocale);

    sRv.assign(pcszLocale);
#endif

    return sRv;
}
//---------------------------------------------------------------------------
/* static */
void
CxLocale::vSetCurrent(
    const std::tstring_t &csLocale
)
{
    /*DEBUG*/// csLocale - n/a

    const tchar_t *pcszLocale = (true == csLocale.empty()) ? NULL : csLocale.c_str();

    const tchar_t *pcszRes = NULL;

    pcszRes = ::xTSETLOCALE(LC_ALL, pcszLocale);
    /*DEBUG*/xTEST_PTR(pcszRes);
}
//---------------------------------------------------------------------------
/* static */
void
CxLocale::vSetDefault() {
    /*DEBUG*/// n/a

    vSetCurrent(CxLocale::sCurrent());
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
