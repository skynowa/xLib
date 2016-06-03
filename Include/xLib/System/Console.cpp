/**
 * \file  Console.inl
 * \brief console
 */


#if !xOPTION_PROJECT_HEADER_ONLY
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

xNAMESPACE_BEGIN2(xlib, system)

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
    cExForeground &a_foreground,
    cExBackground &a_background,
    cint_t        &a_attributes
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif
    // n/a

    return _setAttributes_impl(a_foreground, a_background, a_attributes);
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Console::setAttributesDef() const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif
    // n/a

    return _setAttributesDef_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE std::tstring_t
Console::read() const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    return _read_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::write(
    std::ctstring_t &a_str
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    _write_impl(a_str);

    std::tcout.flush();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::writeLine(
    std::ctstring_t &a_str /* = xT("") */
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    write(a_str + Const::nl());
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::writeErrLine(
    std::ctstring_t &a_str
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    writeLine(xT("Error: ") + a_str);

    pause(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
xINLINE Console::ExModalResult
Console::msgBox(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cuint_t         &a_type
) const
{
    xUNUSED(a_type);

#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    ExModalResult mrRv;

    ctchar_t cmdAbort  = xT('a');
    ctchar_t cmdIgnore = xT('i');
    ctchar_t cmdRetry  = xT('r');

    std::tstring_t title;
    {
        title = _msgBoxLine(a_title) + Const::nl();
    }

    std::tstring_t multiText;
    {
    	std::vec_tstring_t text;
		String::split(a_text, Const::nl(), &text);

		xFOR_EACH_CONST(std::vec_tstring_t, it, text) {
			multiText += _msgBoxLine(*it) + Const::nl();
		}
    }

    writeLine();
    writeLine(xT("+------------------------------------------------------------------------------+"));
    writeLine(xT("|                                                                              |"));
    write(title);
    writeLine(xT("|                                                                              |"));
    write(multiText);
    writeLine(xT("|                                                                              |"));
    writeLine(xT("+------------------------------------------------------------------------------+"));
    writeLine();
    write(Format::str(xT("\nAbort ({}), Ignore ({}), Retry ({}): "), cmdAbort, cmdIgnore, cmdRetry));

    ctchar_t consoleCmd = CharT( std::tcin.get() ).toLower();   std::tcin.ignore();
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
    std::ctstring_t &a_prompt,
    cbool_t         &a_isVisible,
    std::tstring_t  *a_answer
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    xTEST_EQ(a_prompt.empty(), false);
    xTEST_PTR(a_answer);

    for ( ; ; ) {
        write(a_prompt + xT(": "));

        for ( ; ; ) {
            ctchar_t letter = static_cast<tchar_t>( std::tcin.get() );

            // asterisks
            // BUG: Console::prompt() - asterisks
            xCHECK_DO(a_isVisible, write(xT("*")));

            // ENTER
            xCHECK_DO(letter == 10, break);

            // BACKSPACE
            xCHECK_DO(letter == 0x8, a_answer->clear(); continue);

            a_answer->push_back(letter);
        }

        writeLine(Const::strEmpty());

        xCHECK_DO(a_answer->empty(), continue);

        break;
    }
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::pause(
    culong_t &a_timeoutMsec
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

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
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    _clear_impl();
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Console::setTitle(
    std::ctstring_t &a_title
) const
{
#if xENV_WIN
    xTEST_NA(_wnd);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

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
	std::ctstring_t &a_text
) const
{
	std::csize_t    lineSizeMax = ll80;
	std::ctstring_t border      = xT("|");
	ctchar_t        space       = xT(' ');
	std::ctstring_t paddingLeft = border + space;
	std::ctstring_t padingRight = xT(" ") + border;
	std::ctstring_t dot3        = xT(" ...");

	std::tstring_t line = paddingLeft + a_text;

	::ssize_t delta = lineSizeMax - line.size();
	if (delta < 0) {
		line.resize(lineSizeMax - padingRight.size() - dot3.size());	// set padding
		line += dot3;
	} else {
		std::ctstring_t add(delta - padingRight.size(), space);

		line += add;
	}

	line += padingRight;

	return line;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
