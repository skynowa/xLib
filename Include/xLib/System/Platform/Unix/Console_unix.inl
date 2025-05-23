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
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Console::_construct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_destruct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
/**
 * Colors and formatting (ANSI/VT100 Control sequences)
 *
 * https://misc.flogisoft.com/bash/tip_colors_and_formatting
 */
std::tstring_t
Console::_setAttributes_impl(
    cForeground a_foreground,
    cBackground a_background,
    cint_t      a_attributes
) const
{
    std::tstring_t sRv;

    Foreground foregroundColor {};
    {
        constexpr int_t foregroundColorDefault = 39;
        constexpr int_t foregroundColorBlack   = 30;
        constexpr int_t foregroundColorRed     = 31;
        constexpr int_t foregroundColorBlue    = 34;
        constexpr int_t foregroundColorGreen   = 32;
        constexpr int_t foregroundColorCyan    = 36;
        constexpr int_t foregroundColorMagenta = 35;
        constexpr int_t foregroundColorYellow  = 33;
        constexpr int_t foregroundColorWhite   = 37;
        constexpr int_t foregroundColorGray    = 37;  // TODO: [skynowa] Console::setAttributes() - foregroundColorGray

        int_t iRv {};

        switch (a_foreground) {
        case Foreground::Default:
            iRv = foregroundColorDefault;
            break;
        case Foreground::Black:
            iRv = foregroundColorBlack;
            break;
        case Foreground::Red:
            iRv = foregroundColorRed;
            break;
        case Foreground::Green:
            iRv = foregroundColorGreen;
            break;
        case Foreground::Yellow:
            iRv = foregroundColorYellow;
            break;
        case Foreground::Blue:
            iRv = foregroundColorBlue;
            break;
        case Foreground::Magenta:
            iRv = foregroundColorMagenta;
            break;
        case Foreground::Cyan:
            iRv = foregroundColorCyan;
            break;
        case Foreground::White:
            iRv = foregroundColorWhite;
            break;
        case Foreground::Gray:
            iRv = foregroundColorGray;
            break;
        case Foreground::Unknown:
        default:
            xTEST_FAIL;
            break;
        }

        foregroundColor = static_cast<Foreground>( iRv );
    }

    Background backgroundColor {};
    {
        constexpr int_t backgroundColorDefault = 49;
        constexpr int_t backgroundColorBlack   = 40;
        constexpr int_t backgroundColorRed     = 41;
        constexpr int_t backgroundColorBlue    = 44;
        constexpr int_t backgroundColorGreen   = 42;
        constexpr int_t backgroundColorCyan    = 46;
        constexpr int_t backgroundColorMagenta = 45;
        constexpr int_t backgroundColorYellow  = 43;
        constexpr int_t backgroundColorWhite   = 47;
        constexpr int_t backgroundColorGray    = 47; // TODO: [skynowa] Console::setAttributes() - Unix - backgroundColorGray

        int_t iRv {};

        switch (a_background) {
        case Background::Default:
            iRv = backgroundColorDefault;
            break;
        case Background::Black:
            iRv = backgroundColorBlack;
            break;
        case Background::Red:
            iRv = backgroundColorRed;
            break;
        case Background::Green:
            iRv = backgroundColorGreen;
            break;
        case Background::Yellow:
            iRv = backgroundColorYellow;
            break;
        case Background::Blue:
            iRv = backgroundColorBlue;
            break;
        case Background::Magenta:
            iRv = backgroundColorMagenta;
            break;
        case Background::Cyan:
            iRv = backgroundColorCyan;
            break;
        case Background::White:
            iRv = backgroundColorWhite;
            break;
        case Background::Gray:
            iRv = backgroundColorGray;
            break;
        case Background::Unknown:
        default:
            xTEST_FAIL;
            break;
        }

        backgroundColor = static_cast<Background>( iRv );
    }

    std::tstring_t attrs;
    {
        // Terminals allow attribute combinations.
        // The attributes must be separated by a semicolon (“;”).
        std::vec_tstring_t values;

        constexpr int_t attributeAllOff    = 0;
        constexpr int_t attributeBold      = 1;
        constexpr int_t attributeDim       = 2;
        constexpr int_t attributeUnderline = 4;
        constexpr int_t attributeBlink     = 5;
        constexpr int_t attributeReverse   = 7;
        constexpr int_t attributeHidden    = 8;

		Bitset bits(a_attributes);

		xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attribute::AllOff)),    values.push_back( std::to_string(attributeAllOff) ));
		xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attribute::Bold)),      values.push_back( std::to_string(attributeBold) ));
		xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attribute::Dim)),       values.push_back( std::to_string(attributeDim) ));
		xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attribute::Underline)), values.push_back( std::to_string(attributeUnderline) ));
		xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attribute::Blink)),     values.push_back( std::to_string(attributeBlink) ));
		xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attribute::Reverse)),   values.push_back( std::to_string(attributeReverse) ));
		xCHECK_DO(bits.isSetBit(static_cast<int_t>(Attribute::Hidden)),    values.push_back( std::to_string(attributeHidden) ));

		attrs = String::join(values, xT(';'));
    }

	sRv += _escapeValue( Format::str(xT("\033[{};{}m"), attrs, static_cast<int>(foregroundColor)) ); // TODO: [skynowa] StdStreamV2
	sRv += _escapeValue( Format::str(xT("\033[{}m"), static_cast<int>(backgroundColor)) );           // TODO: [skynowa] StdStreamV2

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_clearAttributes_impl() const
{
	return _escapeValue(xT("\033[0;0m"));
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
    write( _escapeValue(Format::str(xT("\033]0;{}\a"), a_title)) );
}
//-------------------------------------------------------------------------------------------------

} // namespace
