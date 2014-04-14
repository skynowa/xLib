/**
 * \file  CxLocale.cpp
 * \brief locale
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE2_BEGIN(xlib, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxLocale::current() const
{
    // n/a

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    int_t iRv  = - 1;
    LCID  id = 0;

    id = ::GetSystemDefaultLCID();
    // n/a

    //Retrieves information about a locale specified by identifier
    iRv = ::GetLocaleInfo(id, LOCALE_SENGLANGUAGE, 0, 0);
    xTEST_DIFF(iRv, 0);

    sRv.resize(iRv);
    iRv = ::GetLocaleInfo(id, LOCALE_SENGLANGUAGE, &sRv.at(0), static_cast<int_t>( sRv.size() ));
    xTEST_DIFF(iRv, 0);

    sRv.resize(iRv - sizeof('\0')); // delete from end '\0'
#elif xOS_ENV_UNIX
    ctchar_t *locale = std::xTSETLOCALE(LC_ALL, xPTR_NULL);
    xTEST_PTR(locale);

    sRv.assign(locale);
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocale::setCurrent(
    std::ctstring_t &a_locale
) const
{
    xTEST_NA(a_locale);

    ctchar_t *locale = a_locale.empty() ? xPTR_NULL : a_locale.c_str();

    ctchar_t *pcszRv = std::xTSETLOCALE(LC_ALL, locale);
    xTEST_PTR(pcszRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocale::setDefault() const
{
    setCurrent( current() );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, core)
