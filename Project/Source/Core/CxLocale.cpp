/**
 * \file  CxLocale.cpp
 * \brief locale
 */


#include <xLib/Core/CxLocale.h>

#include <xLib/Debug/CxDebugger.h>

xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
xINLINE_HO std::tstring_t
CxLocale::current()
{
    // n/a

    std::tstring_t sRv;

#if xOS_ENV_WIN
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
#else
    ctchar_t *pcszLocale = NULL;

    pcszLocale = std::xTSETLOCALE(LC_ALL, NULL);
    xTEST_PTR(pcszLocale);

    sRv.assign(pcszLocale);
#endif

    return sRv;
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxLocale::setCurrent(
    std::ctstring_t &a_locale
)
{
    xTEST_NA(a_locale);

    ctchar_t *pcszLocale = (a_locale.empty()) ? NULL : a_locale.c_str();

    ctchar_t *pcszRes = ::xTSETLOCALE(LC_ALL, pcszLocale);
    xTEST_PTR(pcszRes);
}
//------------------------------------------------------------------------------
/* static */
xINLINE_HO void_t
CxLocale::setDefault()
{
    setCurrent( CxLocale::current() );
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
