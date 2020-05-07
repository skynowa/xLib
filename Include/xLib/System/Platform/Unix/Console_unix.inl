/**
 * \file  Console_unix.inl
 * \brief Shell console
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Sync/Thread.h>


xNAMESPACE_BEGIN2(xl, system)

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
        cint_t foregroundColorDefault = 39;
        cint_t foregroundColorBlack   = 30;
        cint_t foregroundColorRed     = 31;
        cint_t foregroundColorBlue    = 34;
        cint_t foregroundColorGreen   = 32;
        cint_t foregroundColorCyan    = 36;
        cint_t foregroundColorMagenta = 35;
        cint_t foregroundColorYellow  = 33;
        cint_t foregroundColorWhite   = 37;
        cint_t foregroundColorGray    = 37;  // TODO: [skynowa] Console::setAttributes() - foregroundColorGray

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
        cint_t backgroundColorDefault = 49;
        cint_t backgroundColorBlack   = 40;
        cint_t backgroundColorRed     = 41;
        cint_t backgroundColorBlue    = 44;
        cint_t backgroundColorGreen   = 42;
        cint_t backgroundColorCyan    = 46;
        cint_t backgroundColorMagenta = 45;
        cint_t backgroundColorYellow  = 43;
        cint_t backgroundColorWhite   = 47;
        cint_t backgroundColorGray    = 47; // TODO: [skynowa] Console::setAttributes() - Unix - backgroundColorGray

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

        cint_t attributeAllOff    = 0;
        cint_t attributeBold      = 1;
        cint_t attributeDim       = 2;
        cint_t attributeUnderline = 4;
        cint_t attributeBlink     = 5;
        cint_t attributeReverse   = 7;
        cint_t attributeHidden    = 8;

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

	sRv += _escapeValue( Format::str(xT("\e[{};{}m"), attrs, static_cast<int>(foregroundColor)) ); // TODO: [skynowa] StdStreamV2
	sRv += _escapeValue( Format::str(xT("\e[{}m"), static_cast<int>(backgroundColor)) );           // TODO: [skynowa] StdStreamV2

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_setAttributesDef_impl() const
{
	return _escapeValue(xT("\e[0;0m"));
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
 * 	   TITLE="\e]2;$@\a"
 * 	   PS1=${ORIG}${TITLE}
 * }
 *
 * ESC]0;stringBEL - Set icon name and window title to string
 * ESC]1;stringBEL - Set icon name to string
 * ESC]2;stringBEL - Set window title to string
 *
 * Icons:
 * https://unicode.org/emoji/charts/full-emoji-list.html
 */
void_t
Console::_setTitle_impl(
    std::ctstring_t &a_title
) const
{
    write( _escapeValue(Format::str(xT("\e]0;{}\a"), a_title)) );
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_setStdinEcho_impl(
    cbool_t &a_isEnable
) const
{
    struct termios tty {};

    int_t iRv = ::tcgetattr(STDIN_FILENO, &tty);
    xTEST_DIFF(iRv, -1);

    if (a_isEnable) {
        tty.c_lflag |= static_cast<uint_t>(ECHO);
    } else {
        tty.c_lflag &= static_cast<uint_t>(~ECHO);
    }

    iRv = ::tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    xTEST_DIFF(iRv, -1);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_escapeValue(
	std::ctstring_t &a_value
) const
{
	return xT("\\[") + a_value + xT("\\]");
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
