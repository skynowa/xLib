/**
 * \file  Locale.inl
 * \brief locale
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Locale.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Log/Trace.h>

#if   xENV_WIN
    #include "Platform/Win/Locale_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Locale_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif


xNAMESPACE_BEGIN2(xlib, core)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Locale::current() const
{
    // n/a

    return _current_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Locale::setCurrent(
    std::ctstring_t &a_locale
) const
{
    xTEST_NA(a_locale);

    cptr_ctchar_t locale = a_locale.empty() ? xPTR_NULL : a_locale.c_str();

    cptr_ctchar_t pcszRv = xTSETLOCALE(LC_ALL, locale);
    xTEST_PTR(pcszRv);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Locale::setDefault() const
{
    setCurrent( current() );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)
