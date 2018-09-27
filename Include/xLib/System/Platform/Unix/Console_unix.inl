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
std::tstring_t
Console::_setAttributes_impl(
    cForeground a_foreground,
    cBackground a_background,
    cint_t      a_attributes
) const
{
    Foreground foregroundColor;
    {
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
        case Foreground::fgBlack:
            iRv = foregroundColorBlack;
            break;
        case Foreground::fgRed:
            iRv = foregroundColorRed;
            break;
        case Foreground::fgGreen:
            iRv = foregroundColorGreen;
            break;
        case Foreground::fgYellow:
            iRv = foregroundColorYellow;
            break;
        case Foreground::fgBlue:
            iRv = foregroundColorBlue;
            break;
        case Foreground::fgMagenta:
            iRv = foregroundColorMagenta;
            break;
        case Foreground::fgCyan:
            iRv = foregroundColorCyan;
            break;
        case Foreground::fgWhite:
            iRv = foregroundColorWhite;
            break;
        case Foreground::fgGray:
            iRv = foregroundColorGray;
            break;
        case Foreground::fgUnknown:
        default:
            xTEST_FAIL;
            break;
        }

        foregroundColor = static_cast<Foreground>( iRv );
    }

    Background backgroundColor;
    {
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
        case Background::bgBlack:
            iRv = backgroundColorBlack;
            break;
        case Background::bgRed:
            iRv = backgroundColorRed;
            break;
        case Background::bgGreen:
            iRv = backgroundColorGreen;
            break;
        case Background::bgYellow:
            iRv = backgroundColorYellow;
            break;
        case Background::bgBlue:
            iRv = backgroundColorBlue;
            break;
        case Background::bgMagenta:
            iRv = backgroundColorMagenta;
            break;
        case Background::bgCyan:
            iRv = backgroundColorCyan;
            break;
        case Background::bgWhite:
            iRv = backgroundColorWhite;
            break;
        case Background::bgGray:
            iRv = backgroundColorGray;
            break;
        case Background::bgUnknown:
        default:
            xTEST_FAIL;
            break;
        }

        backgroundColor = static_cast<Background>( iRv );
    }

    std::tstring_t attrs;
    {
        cint_t attributeAllOff     = 0;
        cint_t attributeBold       = 1;
        cint_t attributeUnderscore = 4;
        cint_t attributeBlink      = 5;
        cint_t attributeReverse    = 7;
        cint_t attributeConcealed  = 8;

        attrs += Format::str(xT("\033[{}m"), (int)foregroundColor);  // TODO: [skynowa] StdStreamV2
        attrs += Format::str(xT("\033[{}m"), (int)backgroundColor);  // TODO: [skynowa] StdStreamV2

        xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::atAllOff),     attrs += Format::str(xT("\033[{}m"), attributeAllOff));
        xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::atBold),       attrs += Format::str(xT("\033[{}m"), attributeBold));
        xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::atUnderscore), attrs += Format::str(xT("\033[{}m"), attributeUnderscore));
        xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::atBlink),      attrs += Format::str(xT("\033[{}m"), attributeBlink));
        xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::atReverse),    attrs += Format::str(xT("\033[{}m"), attributeReverse));
        xCHECK_DO(a_attributes & static_cast<int_t>(TextAttribute::atConcealed),  attrs += Format::str(xT("\033[{}m"), attributeConcealed));
    }

    return attrs;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_setAttributesDef_impl() const
{
    return xT("\033[0;0m");
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
    writeLine( Format::str(xT("{}]0;{}{}"), xT('\033'), a_title, xT('\007')) );
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_setStdinEcho_impl(
    cbool_t &a_isEnable
) const
{
    struct termios tty; Utils::structZeroT(tty);

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
