/**
 * \file  Cout.cpp
 * \brief Tracing to debugger, std::cout
 */


#include "Cout.h"

#include <xLib/Core/Const.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>

#if   xENV_WIN
    #include "Platform/Win/Cout_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Cout_unix.inl"
#endif


namespace xl::log
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* virtual */
Cout::~Cout()
{
}
//-------------------------------------------------------------------------------------------------
void_t
Cout::write(
    cLevel           a_level,
    std::ctstring_t &a_msg
) const /* final */
{
    xCHECK_DO(!_isEnable, return);

    std::tstring_t msg;
    {
        if (a_level == ILog::Level::Trace) {
            msg = a_msg;
        } else {
            msg = _levelString(a_level) + xT(": ") + a_msg;
        }
    }

    _write_impl(msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
