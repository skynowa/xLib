/**
 * \file  CxConsole.inl
 * \brief console
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Sync/CxThread.h>


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_construct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_destruct_impl()
{
    xNA;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::_setAttributes_impl(
    const ExForeground &a_foreground,
    const ExBackground &a_background,
    cint_t             &a_attributes
) const
{
    ExForeground foregroundColor;
    {
        cint_t foregroundColorBlack   = 30;
        cint_t foregroundColorRed     = 31;
        cint_t foregroundColorBlue    = 34;
        cint_t foregroundColorGreen   = 32;
        cint_t foregroundColorCyan    = 36;
        cint_t foregroundColorMagenta = 35;
        cint_t foregroundColorYellow  = 33;
        cint_t foregroundColorWhite   = 37;
        cint_t foregroundColorGray    = 37;  // TODO: CxConsole::setAttributes() - foregroundColorGray

        int_t iRv = - 1;

	    switch (a_foreground) {
        case fgBlack:
            iRv = foregroundColorBlack;
            break;
        case fgRed:
            iRv = foregroundColorRed;
            break;
        case fgGreen:
            iRv = foregroundColorGreen;
            break;
        case fgYellow:
            iRv = foregroundColorYellow;
            break;
        case fgBlue:
            iRv = foregroundColorBlue;
            break;
        case fgMagenta:
            iRv = foregroundColorMagenta;
            break;
        case fgCyan:
            iRv = foregroundColorCyan;
            break;
        case fgWhite:
            iRv = foregroundColorWhite;
            break;
        case fgGray:
            iRv = foregroundColorGray;
            break;
        case fgUnknown:
        default:
            xTEST_FAIL;
            break;
        }

        foregroundColor = static_cast<ExForeground>( iRv );
    }

    ExBackground backgroundColor;
    {
        cint_t backgroundColorBlack   = 40;
        cint_t backgroundColorRed	  = 41;
        cint_t backgroundColorBlue	  = 44;
        cint_t backgroundColorGreen   = 42;
        cint_t backgroundColorCyan	  = 46;
        cint_t backgroundColorMagenta = 45;
        cint_t backgroundColorYellow  = 43;
        cint_t backgroundColorWhite   = 47;
        cint_t backgroundColorGray	  = 47; // TODO: CxConsole::setAttributes() - Unix - backgroundColorGray

        int_t iRv = - 1;

	    switch (a_background) {
        case fgBlack:
            iRv = backgroundColorBlack;
            break;
        case fgRed:
            iRv = backgroundColorRed;
            break;
        case fgGreen:
            iRv = backgroundColorGreen;
            break;
        case fgYellow:
            iRv = backgroundColorYellow;
            break;
        case fgBlue:
            iRv = backgroundColorBlue;
            break;
        case fgMagenta:
            iRv = backgroundColorMagenta;
            break;
        case fgCyan:
            iRv = backgroundColorCyan;
            break;
        case fgWhite:
            iRv = backgroundColorWhite;
            break;
        case fgGray:
            iRv = backgroundColorGray;
            break;
        case fgUnknown:
        default:
            xTEST_FAIL;
            break;
        }

        backgroundColor = static_cast<ExBackground>( iRv );
    }

    std::tstring_t attrs;
    {
        cint_t  attributeAllOff     = 0;
        cint_t  attributeBold       = 1;
        cint_t  attributeUnderscore = 4;
        cint_t  attributeBlink      = 5;
        cint_t  attributeReverse    = 7;
        cint_t  attributeConcealed  = 8;

        attrs += CxString::format(xT("\033[%im"), foregroundColor);
        attrs += CxString::format(xT("\033[%im"), backgroundColor);

        xCHECK_DO(a_attributes & CxConsole::atAllOff,     attrs += CxString::format(xT("\033[%im"), attributeAllOff));
        xCHECK_DO(a_attributes & CxConsole::atBold,       attrs += CxString::format(xT("\033[%im"), attributeBold));
        xCHECK_DO(a_attributes & CxConsole::atUnderscore, attrs += CxString::format(xT("\033[%im"), attributeUnderscore));
        xCHECK_DO(a_attributes & CxConsole::atBlink,      attrs += CxString::format(xT("\033[%im"), attributeBlink));
        xCHECK_DO(a_attributes & CxConsole::atReverse,    attrs += CxString::format(xT("\033[%im"), attributeReverse));
        xCHECK_DO(a_attributes & CxConsole::atConcealed,  attrs += CxString::format(xT("\033[%im"), attributeConcealed));
    }

    return attrs;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::_setAttributesDef_impl() const
{
    return xT("\033[0;0m");
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::_read_impl() const
{
    std::tstring_t sRv;

    // BUG: CxConsole::_read_impl()
    std::tcin >> sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_write_impl(
    std::ctstring_t &a_str
) const
{
    std::tcout << a_str;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_clear_impl() const
{
    writeLine( CxConst::ff() );
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_setTitle_impl(
    std::ctstring_t &a_title
) const
{
    writeLine( CxString::format(xT("%c]0;%s%c"), xT('\033'), a_title.c_str(), xT('\007')) );
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
