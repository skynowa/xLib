/**
 * \file  Trace.cpp
 * \brief Tracing to debugger, std::cout
 */


#include "Trace.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>

#if   xENV_WIN
    #include "Platform/Win/Trace_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Trace_unix.inl"
#endif


namespace xl::log
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Trace::~Trace() /* final */
{
#if 0
	write(Level::Trace, xT("%s"), _oss.str().c_str()); /// TODO: fix
#else
	write(Level::Trace, xT(""));
#endif
}
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Trace::write(
    cLevel        a_level,
    cptr_ctchar_t a_format, ...
) const
{
    xCHECK_DO(!isEnabled(), return);

    std::tstring_t msg;
    {
        va_list args;
        xVA_START(args, a_format);
        msg = FormatC::strV(a_format, args);
        xVA_END(args);

        if (a_level == Level::Trace) {
            // n/a
        } else {
            msg = _levelString(a_level) + xT(": ") + msg;
        }
    }

    _write_impl(msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
