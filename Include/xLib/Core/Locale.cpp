/**
 * \file  Locale.cpp
 * \brief locale
 */


#include "Locale.h"

#include <xLib/Core/Format.h>
#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>

#if   xENV_WIN
    #include "Platform/Win/Locale_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Locale_unix.inl"
#endif


namespace xl::core
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Locale::current() const
{
    // n/a

    return _current_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Locale::setCurrent(
    std::ctstring_t &a_locale
) const
{
    xTEST_NA(a_locale);

    cptr_ctchar_t locale = a_locale.empty() ? nullptr : a_locale.c_str();

    cptr_ctchar_t pcszRv = xTSETLOCALE(LC_ALL, locale);
    xTEST_PTR(pcszRv);
}
//-------------------------------------------------------------------------------------------------
void_t
Locale::setDefault() const
{
    setCurrent( current() );
}
//-------------------------------------------------------------------------------------------------

} // namespace
