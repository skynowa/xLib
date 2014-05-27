/**
 * \file  CxLocale.inl
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

#if   xENV_WIN
    #include "Platform/Win/CxLocale_win.inl"
#elif xENV_UNIX
    #if   xENV_LINUX
        #include "Platform/Unix/CxLocale_unix.inl"
    #elif xENV_BSD
        #include "Platform/Unix/CxLocale_unix.inl"
    #elif xENV_APPLE
        #include "Platform/Unix/CxLocale_unix.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxLocale::current() const
{
    // n/a

    return _current_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocale::setCurrent(
    std::ctstring_t &a_locale
) const
{
    xTEST_NA(a_locale);

    ctchar_t *locale = a_locale.empty() ? xPTR_NULL : a_locale.c_str();

    ctchar_t *pcszRv = xTSETLOCALE(LC_ALL, locale);
    xTEST_PTR(pcszRv);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxLocale::setDefault() const
{
    setCurrent( current() );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
