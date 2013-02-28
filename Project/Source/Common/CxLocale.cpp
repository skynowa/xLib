/**
 * \file  CxLocale.cpp
 * \brief locale
 */


#include <xLib/Common/CxLocale.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxLocale::current() {
    // n/a

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    int_t  iRv  = - 1;
    LCID lcId = 0;

    lcId = ::GetSystemDefaultLCID();
    // n/a

    //Retrieves information about a locale specified by identifier
    iRv = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, 0, 0);
    xTEST_DIFF(0, iRv);

    sRv.resize(iRv);
    iRv = ::GetLocaleInfo(lcId, LOCALE_SENGLANGUAGE, &sRv.at(0), static_cast<int_t>( sRv.size() ));
    xTEST_DIFF(0, iRv);

    sRv.resize(iRv - sizeof('\0'));    //delete from end '\0'
#elif xOS_ENV_UNIX
    ctchar_t *pcszLocale = NULL;

    pcszLocale = std::xTSETLOCALE(LC_ALL, NULL);
    xTEST_PTR(pcszLocale);

    sRv.assign(pcszLocale);
#endif

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
void
CxLocale::setCurrent(
    std::ctstring_t &csLocale
)
{
    // csLocale - n/a

    ctchar_t *pcszLocale = (true == csLocale.empty()) ? NULL : csLocale.c_str();

    ctchar_t *pcszRes = NULL;

    pcszRes = ::xTSETLOCALE(LC_ALL, pcszLocale);
    xTEST_PTR(pcszRes);
}
//------------------------------------------------------------------------------
/* static */
void
CxLocale::setDefault() {
    // n/a

    setCurrent(CxLocale::current());
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxLocale::CxLocale() {
    // n/a
}
//------------------------------------------------------------------------------
/* virtual */
CxLocale::~CxLocale() {
    // n/a
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
