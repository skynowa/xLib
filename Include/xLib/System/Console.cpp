/**
 * \file  Console.inl
 * \brief console
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Console.h"
#endif

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Sync/Thread.h>

#if   xENV_WIN
    #include "Platform/Win/Console_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Console_unix.inl"

    #if   xENV_LINUX

    #elif xENV_BSD

    #elif xENV_APPLE

    #endif
#endif

xNAMESPACE_BEGIN2(xl, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Console::Console()
#if xENV_WIN
    :
    _wnd          (xPTR_NULL),
    _menu         (xPTR_NULL),
    _stdIn        (),
    _stdOut       (),
    _attributesDef(0)
#endif
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE
Console::~Console()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Console::setAttributes(
    cForeground &a_foreground,
    cBackground &a_background,
    cint_t        &a_attributes
) const
{
    return _setAttributes_impl(a_foreground, a_background, a_attributes);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Console::setAttributesDef() const
{
    return _setAttributesDef_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Console::read() const
{
    return _read_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::write(
    std::ctstring_t &a_str
) const
{
    _write_impl(a_str);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::writeLine(
    std::ctstring_t &a_str /* = xT("") */
) const
{
    write(a_str + Const::nl());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::writeErrLine(
    std::ctstring_t &a_str
) const
{
    writeLine(xT("Error: ") + a_str);

    pause(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
xINLINE Console::ModalResult
Console::msgBox(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cuint_t         &a_type
) const
{
    xUNUSED(a_type);

    ModalResult mrRv;

    std::csize_t width     = 100;
    ctchar_t     cmdAbort  = xT('a');
    ctchar_t     cmdIgnore = xT('i');
    ctchar_t     cmdRetry  = xT('r');

    std::tstring_t title;
    {
        title = _msgBoxLine(a_title, width) + Const::nl();
    }

    std::tstring_t multiText;
    {
    	std::vec_tstring_t text;
		String::split(a_text, Const::nl(), &text);

		xFOR_EACH_CONST(std::vec_tstring_t, it, text) {
			multiText += _msgBoxLine(*it, width) + Const::nl();
		}
    }

    writeLine();
    writeLine(Format::str(xT("+{}+"), std::tstring_t(width - 2, xT('-'))));
    writeLine(Format::str(xT("|{}|"), std::tstring_t(width - 2, xT(' '))));
    write(title);
    writeLine(Format::str(xT("|{}|"), std::tstring_t(width - 2, xT(' '))));
    write(multiText);
    writeLine(Format::str(xT("|{}|"), std::tstring_t(width - 2, xT(' '))));
    writeLine(Format::str(xT("+{}+"), std::tstring_t(width - 2, xT('-'))));
    writeLine();
    write(Format::str(xT("\nAbort ({}), Ignore ({}), Retry ({}): "), cmdAbort, cmdIgnore, cmdRetry));

    ctchar_t consoleCmd = CharT( static_cast<ctchar_t>(std::tcin.get()) ).toLower();
    std::tcin.ignore();

    switch (consoleCmd) {
    case cmdAbort:
        mrRv = mrAbort;
        writeLine(xT("Abort..."));
        break;
    case cmdIgnore:
        mrRv = mrIgnore;
        writeLine(xT("Ignore..."));
        break;
    case cmdRetry:
        mrRv = mrRetry;
        writeLine(xT("Retry..."));
        break;
    default:
        mrRv = mrRetry;
        writeLine(xT("Retry..."));
        break;
    }

    return mrRv;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::prompt(
    std::ctstring_t &a_prompt,		///< input text
    cbool_t         &a_isVisible,	///< is input text visible
    std::tstring_t  *a_answer		///< [out] answer
) const
{
    xTEST_EQ(a_prompt.empty(), false);
    xTEST_PTR(a_answer);

	if ( !a_isVisible ) {
		_setStdinEcho(false);
	}

    for ( ; ; ) {
        write(a_prompt + xT(": "));

        for ( ; ; ) {
            ctchar_t ch = static_cast<ctchar_t>( std::tcin.get() );
            xCHECK_DO(ch == 10, break);	// ENTER
            xCHECK_DO(ch == 0x8, a_answer->clear(); continue);	// BACKSPACE

            a_answer->push_back(ch);
        }

        writeLine(Const::strEmpty());

        xCHECK_DO(a_answer->empty(), continue);

        break;
    }

	if ( !a_isVisible ) {
		_setStdinEcho(true);
	}
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::pause(
    culong_t &a_timeoutMsec
) const
{
    std::tstring_t msg;

    if (a_timeoutMsec == xTIMEOUT_INFINITE) {
        msg = xT("Pause, press [ENTER] to continue...");

        writeLine(msg);

        std::cin.clear();
        std::cin.ignore();
    } else {
        msg = Format::str(xT("Pause, wait for {} msec to continue..."), a_timeoutMsec);

        writeLine(msg);

        Thread::currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::clear() const
{
    _clear_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::setTitle(
    std::ctstring_t &a_title
) const
{
    _setTitle_impl(a_title);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Console::_msgBoxLine(
	std::ctstring_t &a_text,	///< text
	std::csize_t    &a_width	///< msgbox width
) const
{
	std::ctstring_t border      = xT("|");
	ctchar_t        space       = xT(' ');
	std::ctstring_t paddingLeft = border + space;
	std::ctstring_t padingRight = xT(" ") + border;
	std::ctstring_t dot3        = xT(" ...");

	std::tstring_t line = paddingLeft + a_text;

	::ssize_t delta = static_cast< ::ssize_t >(a_width - line.size());
	if (delta < 0) {
		line.resize(a_width - padingRight.size() - dot3.size());	// set padding
		line += dot3;
	} else {
		std::ctstring_t add(static_cast<std::size_t>(delta) - padingRight.size(), space);

		line += add;
	}

	line += padingRight;

	return line;
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::_setStdinEcho(
	cbool_t &a_isEnable
) const
{
    _setStdinEcho_impl(a_isEnable);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, system)
