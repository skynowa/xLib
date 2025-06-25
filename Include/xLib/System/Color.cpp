/**
 * \file  Color.cpp
 * \brief Shell console color
 */


#include "Color.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Bitset.h>

namespace xl::system
{

/**************************************************************************************************
* public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/**
 * Colors and formatting (ANSI/VT100 Control sequences)
 *
 * https://misc.flogisoft.com/bash/tip_colors_and_formatting
 */
std::tstring_t
Color::set() const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    _enableAnsiColors();

    std::tstring_t sRv;

    FG fgColor {};
    {
        int_t iRv {};

        switch (_fg) {
        case FG::Default: iRv = 39;   break;
        case FG::Black:   iRv = 30;   break;
        case FG::Red:     iRv = 31;   break;
        case FG::Green:   iRv = 32;   break;
        case FG::Yellow:  iRv = 33;   break;
        case FG::Blue:    iRv = 34;   break;
        case FG::Magenta: iRv = 35;   break;
        case FG::Cyan:    iRv = 36;   break;
        case FG::White:   iRv = 37;   break;
        case FG::Gray:    iRv = 90;   break;
        }

        fgColor = static_cast<FG>( iRv );
    }

    BG bgColor {};
    {
        int_t iRv {};

        switch (_bg) {
        case BG::Default: iRv = 49;   break;
        case BG::Black:   iRv = 40;   break;
        case BG::Red:     iRv = 41;   break;
        case BG::Green:   iRv = 42;   break;
        case BG::Yellow:  iRv = 43;   break;
        case BG::Blue:    iRv = 44;   break;
        case BG::Magenta: iRv = 45;   break;
        case BG::Cyan:    iRv = 46;   break;
        case BG::White:   iRv = 47;   break;
        case BG::Gray:    iRv = 100;  break;
        }

        bgColor = static_cast<BG>( iRv );
    }

    std::tstring_t attrs;
    {
        // Terminals allow attribute combinations.
        // The attributes must be separated by a semicolon (“;”).
        std::vec_tstring_t values;

        Bitset bits( static_cast<int_t>(_attrs) );
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Reset)),     values.emplace_back(xT("0")));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Bold)),      values.emplace_back(xT("1")));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Dim)),       values.emplace_back(xT("2")));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Underline)), values.emplace_back(xT("4")));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Blink)),     values.emplace_back(xT("5")));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Reverse)),   values.emplace_back(xT("7")));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Hidden)),    values.emplace_back(xT("8")));

        attrs = String::join(values, xT(';'));
    }

    // TODO: [skynowa] StdStreamV2
    sRv = escape( Format::str(xT("\033[{};{};{}m"), attrs, static_cast<int>(fgColor),
        static_cast<int>(bgColor)) );

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::clear() const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return escape(xT("\033[0m"));
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::setText(
	std::ctstring_t &a_str
) const
{
	return set() + a_str + clear();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::escape(
	std::ctstring_t &a_str
) const
{
#if xENV_UNIX
	xCHECK_RET(!_isEscapeValues, a_str);

	return xT("\\[") + a_str + xT("\\]");
#else
	return a_str;
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
FILE *
Color::_getStdStream(
	std::ctostream_t &a_stream
) const
{
    if      (&a_stream == &std::tcout) {
        return stdout;
    }
    else if (&a_stream == &std::tcerr ||
             &a_stream == &std::tclog)
    {
        return stderr;
    }

    return nullptr;
}
//-------------------------------------------------------------------------------------------------
bool_t
Color::_isColorized(
	std::tostream_t &a_stream /* = std::tcout */
) const
{
   /**
	* An index to be used to access a private storage of I/O streams. See
	* colorize / nocolorize I/O manipulators for details
	*/
	static const int colorizeIndex = std::ios_base::xalloc();
	if ( static_cast<bool_t>(a_stream.iword(colorizeIndex)) ) {
		return true;
	}

	if ( _isAtty(a_stream) ) {
		return true;
	}

    return false;
}
//-------------------------------------------------------------------------------------------------
bool_t
Color::_isAtty(
	std::ctostream_t &a_stream
) const
{
    FILE *stdStream = _getStdStream(a_stream);
    if (stdStream == nullptr) {
       /**
		* Unfortunately, fileno() ends with segmentation fault
		* if invalid file descriptor is passed. So we need to
		* handle this case gracefully and assume it's not a tty
		* if standard stream is not detected, and 0 is returned
		*/

        return false;
    }

    return static_cast<bool_t>( xISATTY(xFILENO(stdStream)) );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   xPLATFORM_IMPL
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Color::_enableAnsiColors() const
{
#if   xENV_WIN
    static bool isEnabled = false;
    if (isEnabled) {
    	return;
    }

	HandleNativeInvalid stdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    xTEST(stdOut.isValid());

    DWORD dwMode = 0;
    BOOL blRv = ::GetConsoleMode(stdOut.get(), &dwMode);
    xTEST_DIFF(blRv, FALSE);

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    ::SetConsoleMode(stdOut.get(), dwMode);

    isEnabled = true;
#elif xENV_UNIX
    xNA;
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace
