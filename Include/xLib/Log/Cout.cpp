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
#include <xLib/System/Color.h>
#include <xLib/System/Console.h>

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

			if (_isColorSupport) {
				constexpr auto attrBold = Color::Attr::Bold;

				const Color clBlackOnGreen  (true, false, Color::FG::Black, Color::BG::Green, attrBold);
				const Color clWhiteOnBlue   (true, false, Color::FG::White, Color::BG::Blue, attrBold);
				const Color clBlackOnYellow (true, false, Color::FG::Black, Color::BG::Yellow, attrBold);
				const Color clWhiteOnRed    (true, false, Color::FG::White, Color::BG::Red, attrBold);
				const Color clWhiteOnMagenta(true, false, Color::FG::White, Color::BG::Magenta, attrBold);

				Console console;

				switch (a_level) {
					case Level::Trace:    break;
					case Level::Debug:    console.write(clBlackOnGreen,   levelStr); break;
					case Level::Info:     console.write(clWhiteOnBlue,    levelStr); break;
					case Level::Warning:  console.write(clBlackOnYellow,  levelStr); break;
					case Level::Error:    console.write(clWhiteOnRed,     levelStr); break;
					case Level::Critical: console.write(clWhiteOnMagenta, levelStr); break;
				}

				msg = xT(": ") + a_msg;
			} else {
				msg = levelStr + xT(": ") + a_msg;
			}
        }
    }

    _write_impl(msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
