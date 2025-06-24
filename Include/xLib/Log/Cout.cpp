/**
 * \file  Cout.cpp
 * \brief Tracing to debugger, std::cout
 */


#include "Cout.h"

#include <xLib/System/Color.h>

#if   xENV_WIN
    #include "Platform/Win/Cout_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Cout_unix.inl"
#endif

//-------------------------------------------------------------------------------------------------
namespace
{

///\name Colors
///\{
constexpr Color clBlackOnGreen  (true, false, Color::FG::Black, Color::BG::Green,   Color::Attr::Bold);
constexpr Color clWhiteOnBlue   (true, false, Color::FG::White, Color::BG::Blue,    Color::Attr::Bold);
constexpr Color clBlackOnYellow (true, false, Color::FG::Black, Color::BG::Yellow,  Color::Attr::Bold);
constexpr Color clWhiteOnRed    (true, false, Color::FG::White, Color::BG::Red,     Color::Attr::Bold);
constexpr Color clWhiteOnMagenta(true, false, Color::FG::White, Color::BG::Magenta, Color::Attr::Bold);
///\}

}
//-------------------------------------------------------------------------------------------------
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
		std::tstring_t levelStr = _levelIcon(a_level);

		if (_isColorSupport) {
			switch (a_level) {
				case Level::Trace:    xNA;                                          break;
				case Level::Debug:    _console.write(::clBlackOnGreen,   levelStr); break;
				case Level::Info:     _console.write(::clWhiteOnBlue,    levelStr); break;
				case Level::Warning:  _console.write(::clBlackOnYellow,  levelStr); break;
				case Level::Error:    _console.write(::clWhiteOnRed,     levelStr); break;
				case Level::Critical: _console.write(::clWhiteOnMagenta, levelStr); break;
			}

			if (a_level != Level::Trace) {
				msg += xT(": ");
			}

			msg += a_msg;
		} else {
			msg = levelStr + xT(": ") + a_msg;
		}
    }

    _write_impl(msg);
}
//-------------------------------------------------------------------------------------------------

} // namespace
