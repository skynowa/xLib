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
/* virtual */
Trace::~Trace()
{
}
//-------------------------------------------------------------------------------------------------
void_t
Trace::write(
    cLevel           a_level,
    std::ctstring_t &a_message
) const /* final */
{
    xCHECK_DO(!_isEnable, return);

    std::tstring_t msg;
    {
	#if 0
		va_list args;
		xVA_START(args, a_format);
		msg = FormatC::strV(a_format, args);
		xVA_END(args);
	#else
		msg = a_message;
	#endif

        if (a_level == ILog::Level::Trace) {
            // n/a
        } else {
            msg = _levelString(a_level) + xT(": ") + msg;
        }
    }

    _write_impl(msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
