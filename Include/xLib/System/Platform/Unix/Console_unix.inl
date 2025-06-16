/**
 * \file  Console_unix.inl
 * \brief Shell console
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Sync/Thread.h>


namespace xl::system
{

/**************************************************************************************************
*    Color
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

	sRv += escape( Format::str(xT("\033[{};{}m"), attrs, static_cast<int>(fgColor)) ); // TODO: [skynowa] StdStreamV2
	sRv += escape( Format::str(xT("\033[{}m"), static_cast<int>(bgColor)) );           // TODO: [skynowa] StdStreamV2

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::_clear_impl() const
{
	return escape(xT("\033[0;0m"));
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    Console
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Console::_ctor_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_dtor_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
/**
 * Change the title of a terminal
 *
 * https://www.zachpfeffer.com/single-post/Change-the-title-of-a-terminal-on-Ubuntu-1604
 *
 * set-title()
 * {
 *     ORIG=$PS1
 * 	   TITLE="\033]2;$@\a"
 * 	   PS1=${ORIG}${TITLE}
 * }
 *
 * ESC]0;stringBEL - Set icon name and window title to string
 * ESC]1;stringBEL - Set icon name to string
 * ESC]2;stringBEL - Set window title to string
 *
 * Icons:
 * https://unicode.org/emoji/charts/full-emoji-list.html
 * https://apps.timwhitlock.info/emoji/tables/unicode
 */
void_t
Console::_setTitle_impl(
    std::ctstring_t &a_title
) const
{
	Color color(true, true);

	write( color.escape(Format::str(xT("\033]0;{}\a"), a_title)) );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_read_impl() const
{
    std::tstring_t sRv;

    // BUG: Console::_read_impl()
    std::tcin >> sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_write_impl(
    std::ctstring_t &a_str
) const
{
    std::tcout << a_str << std::flush;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_clear_impl() const
{
    writeLine( Const::ff() );
}
//-------------------------------------------------------------------------------------------------

} // namespace
