/**
 * \file  Console.inl
 * \brief console
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

    Foreground foregroundColor;
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

        int_t iRv = - 1;

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

    Background backgroundColor;
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

        int_t iRv = - 1;

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

    int_t attrs;
    {
        cint_t attributeAllOff     = 0;
        cint_t attributeBold       = 1;
        cint_t attributeUnderscore = 4;
        cint_t attributeBlink      = 5;
        cint_t attributeReverse    = 7;
        cint_t attributeConcealed  = 8;

        int_t iRv = - 1;

        switch ( static_cast<TextAttribute>(a_attributes) ) {
		case TextAttribute::AllOff:
			iRv = attributeAllOff;
			break;
		case TextAttribute::Bold:
			iRv = attributeBold;
			break;
		case TextAttribute::Underscore:
			iRv = attributeUnderscore;
			break;
		case TextAttribute::Blink:
			iRv = attributeBlink;
			break;
		case TextAttribute::Reverse:
			iRv = attributeReverse;
			break;
		case TextAttribute::Concealed:
			iRv = attributeConcealed;
			break;
		default:
			break;
		}

		attrs = iRv;

	#if 0
		// TODO: use mask
		xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::AllOff),     attrs = attributeAllOff);
		xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::Bold),       attrs = attributeBold);
		xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::Underscore), attrs = attributeUnderscore);
		xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::Blink),      attrs = attributeBlink);
		xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::Reverse),    attrs = attributeReverse);
		xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::Concealed),  attrs = attributeConcealed);
	#endif
    }

	// Terminals allow attribute combinations. The attributes must be separated by a semicolon (“;”).
	sRv += Format::str(xT("\e[{};{}m"), attrs, static_cast<int>(foregroundColor));	// TODO: [skynowa] StdStreamV2
	sRv += Format::str(xT("\e[{}m"), static_cast<int>(backgroundColor));			// TODO: [skynowa] StdStreamV2

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_setAttributesDef_impl() const
{
    return xT("\e[0;0m");
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
void_t
Console::_setTitle_impl(
    std::ctstring_t &a_title
) const
{
    writeLine( Format::str(xT("{}]0;{}{}"), xT('\e'), a_title, xT('\007')) );
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

xNAMESPACE_END2(xl, system)
