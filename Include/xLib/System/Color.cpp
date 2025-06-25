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
*   Color
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::set() const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return _set_impl(_fg, _bg, _attrs);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::clear() const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return _clear_impl();
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
*    Impl
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/**
 * Colors and formatting (ANSI/VT100 Control sequences)
 *
 * https://misc.flogisoft.com/bash/tip_colors_and_formatting
 */
std::tstring_t
Color::_set_impl(
    cFG   a_fg,
    cBG   a_bg,
    cAttr a_attrs
) const
{
    std::tstring_t sRv;

    FG fgColor {};
    {
        constexpr int_t fgColorDefault = 39;
        constexpr int_t fgColorBlack   = 30;
        constexpr int_t fgColorRed     = 31;
        constexpr int_t fgColorBlue    = 34;
        constexpr int_t fgColorGreen   = 32;
        constexpr int_t fgColorCyan    = 36;
        constexpr int_t fgColorMagenta = 35;
        constexpr int_t fgColorYellow  = 33;
        constexpr int_t fgColorWhite   = 37;
        constexpr int_t fgColorGray    = 37;  // TODO: [skynowa] Console::set() - fgColorGray

        int_t iRv {};

        switch (a_fg) {
        case FG::Default:
            iRv = fgColorDefault;
            break;
        case FG::Black:
            iRv = fgColorBlack;
            break;
        case FG::Red:
            iRv = fgColorRed;
            break;
        case FG::Green:
            iRv = fgColorGreen;
            break;
        case FG::Yellow:
            iRv = fgColorYellow;
            break;
        case FG::Blue:
            iRv = fgColorBlue;
            break;
        case FG::Magenta:
            iRv = fgColorMagenta;
            break;
        case FG::Cyan:
            iRv = fgColorCyan;
            break;
        case FG::White:
            iRv = fgColorWhite;
            break;
        case FG::Gray:
            iRv = fgColorGray;
            break;
        case FG::Unknown:
        default:
            xTEST_FAIL;
            break;
        }

        fgColor = static_cast<FG>( iRv );
    }

    BG bgColor {};
    {
        constexpr int_t bgColorDefault = 49;
        constexpr int_t bgColorBlack   = 40;
        constexpr int_t bgColorRed     = 41;
        constexpr int_t bgColorBlue    = 44;
        constexpr int_t bgColorGreen   = 42;
        constexpr int_t bgColorCyan    = 46;
        constexpr int_t bgColorMagenta = 45;
        constexpr int_t bgColorYellow  = 43;
        constexpr int_t bgColorWhite   = 47;
        constexpr int_t bgColorGray    = 47; // TODO: [skynowa] Console::set() - Unix - bgColorGray

        int_t iRv {};

        switch (a_bg) {
        case BG::Default:
            iRv = bgColorDefault;
            break;
        case BG::Black:
            iRv = bgColorBlack;
            break;
        case BG::Red:
            iRv = bgColorRed;
            break;
        case BG::Green:
            iRv = bgColorGreen;
            break;
        case BG::Yellow:
            iRv = bgColorYellow;
            break;
        case BG::Blue:
            iRv = bgColorBlue;
            break;
        case BG::Magenta:
            iRv = bgColorMagenta;
            break;
        case BG::Cyan:
            iRv = bgColorCyan;
            break;
        case BG::White:
            iRv = bgColorWhite;
            break;
        case BG::Gray:
            iRv = bgColorGray;
            break;
        case BG::Unknown:
        default:
            xTEST_FAIL;
            break;
        }

        bgColor = static_cast<BG>( iRv );
    }

    std::tstring_t attrs;
    {
        // Terminals allow attribute combinations.
        // The attributes must be separated by a semicolon (“;”).
        std::vec_tstring_t values;

        constexpr int_t attrAllOff    = 0;
        constexpr int_t attrBold      = 1;
        constexpr int_t attrDim       = 2;
        constexpr int_t attrUnderline = 4;
        constexpr int_t attrBlink     = 5;
        constexpr int_t attrReverse   = 7;
        constexpr int_t attrHidden    = 8;

        Bitset bits( static_cast<int_t>(a_attrs) );

        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::AllOff)),    values.emplace_back( std::to_string(attrAllOff) ));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Bold)),      values.emplace_back( std::to_string(attrBold) ));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Dim)),       values.emplace_back( std::to_string(attrDim) ));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Underline)), values.emplace_back( std::to_string(attrUnderline) ));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Blink)),     values.emplace_back( std::to_string(attrBlink) ));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Reverse)),   values.emplace_back( std::to_string(attrReverse) ));
        xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attr::Hidden)),    values.emplace_back( std::to_string(attrHidden) ));

        attrs = String::join(values, xT(';'));
    }

    // TODO: [skynowa] StdStreamV2
    sRv = escape( Format::str(xT("\033[{};{};{}m"), attrs, static_cast<int>(fgColor),
        static_cast<int>(bgColor)) );

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::_clear_impl() const
{
    return escape(xT("\033[0m"));
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

} // namespace
