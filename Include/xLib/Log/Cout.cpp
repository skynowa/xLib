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
            std::tstring_t levelStr = _levelString(a_level);

		#if 0
			case Level::Debug:   oss << "\033[30;42m " << level_str << " \033[0m "; break; // black on green
			case Level::Info:    oss << "\033[37;44m " << level_str << " \033[0m "; break; // white on blue
			case Level::Warning: oss << "\033[30;43m " << level_str << " \033[0m "; break; // black on yellow
			case Level::Error:   oss << "\033[37;41m " << level_str << " \033[0m "; break; // white on red
			case Level::Fatal:   oss << "\033[37;45m " << level_str << " \033[0m "; break; // white on magenta
		#endif
			if (1) {
				switch (a_level) {
				case Level::Trace:
					break;
				case Level::Debug:    std::tcout << "\033[30;42m " << levelStr << " \033[0m "; break; // black on green
				case Level::Info:     std::tcout << "\033[37;44m " << levelStr << " \033[0m "; break; // white on blue
				case Level::Warning:  std::tcout << "\033[30;43m " << levelStr << " \033[0m "; break; // black on yellow
				case Level::Error:    std::tcout << "\033[37;41m " << levelStr << " \033[0m "; break; // white on red
				case Level::Critical: std::tcout << "\033[37;45m " << levelStr << " \033[0m "; break; // white on magenta
				}
			}

            msg = /* levelStr + */ xT(": ") + a_msg;
        }
    }

    _write_impl(msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
