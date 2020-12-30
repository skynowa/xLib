/**
 * \file  Console.cpp
 * \brief Shell console
 */


#include "Console.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Bitset.h>
#include <xLib/Sync/Thread.h>

#if   xENV_WIN
    #include "Platform/Win/Console_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Console_unix.inl"
#endif

namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Console::Console() :
	_isColorSupport{ _isColorized() }
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
Console::~Console()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Attributes
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void
Console::setColorSupport(
	cbool_t a_flag
)
{
	_isColorSupport = a_flag;
}
//-------------------------------------------------------------------------------------------------
void
Console::setEscapeValues(
	cbool_t a_flag
)
{
	_isEscapeValues = a_flag;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::setAttributes(
    cForeground a_foreground,
    cBackground a_background,
    cint_t      a_attributes
) const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return _setAttributes_impl(a_foreground, a_background, a_attributes);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::clearAttributes() const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return _clearAttributes_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::setAttributesText(
    cForeground      a_foreground,
    cBackground      a_background,
    cint_t           a_attributes,
    std::ctstring_t &a_str
) const
{
	return
		setAttributes(a_foreground, a_background, a_attributes) +
		a_str +
		clearAttributes();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Actions
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::read() const
{
    return _read_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
Console::write(
    std::ctstring_t &a_str
) const
{
    _write_impl(a_str);
}
//-------------------------------------------------------------------------------------------------
void_t
Console::writeLine(
    std::ctstring_t &a_str /* = {} */
) const
{
    write(a_str);
    writeNl();
}
//-------------------------------------------------------------------------------------------------
void_t
Console::writeErrLine(
    std::ctstring_t &a_str
) const
{
    writeLine(xT("Error: ") + a_str);

    pause(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
void_t
Console::write(
    cForeground      a_foreground,
    cBackground      a_background,
    cint_t           a_attributes,
    std::ctstring_t &a_str
) const
{
   /**
	* Unix vs Windows implementation
	*
	* Use sequence of write() methods, instead of concat strings
	*/

	write( setAttributes(a_foreground, a_background, a_attributes) );
	write(a_str);
	write( clearAttributes() );
}
//-------------------------------------------------------------------------------------------------
void_t
Console::writeLine(
    cForeground      a_foreground,
    cBackground      a_background,
    cint_t           a_attributes,
    std::ctstring_t &a_str
) const
{
	write(a_foreground, a_background, a_attributes, a_str);
	writeNl();
}
//-------------------------------------------------------------------------------------------------
void_t
Console::writeNl() const
{
    write( Const::nl() );
}
//-------------------------------------------------------------------------------------------------
void_t
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
void_t
Console::clear() const
{
    _clear_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   UI
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Console::ModalResult
Console::msgBox(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cuint_t         &a_type
) const
{
    xUNUSED(a_type);

    ModalResult mrRv {};

    std::csize_t width     {100};
    ctchar_t     cmdAbort  {xT('a')};
    ctchar_t     cmdIgnore {xT('i')};
    ctchar_t     cmdRetry  {xT('r')};

    std::ctstring_t title = _msgBoxLine(a_title, width) + Const::nl();

    std::tstring_t multiText;
    {
    	std::vec_tstring_t text;
		String::split(a_text, Const::nl(), &text);

		for (const auto &it : text) {
			multiText += _msgBoxLine(it, width) + Const::nl();
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
        mrRv = ModalResult::Abort;
        writeLine(xT("Abort..."));
        break;
    case cmdIgnore:
        mrRv = ModalResult::Ignore;
        writeLine(xT("Ignore..."));
        break;
    case cmdRetry:
        mrRv = ModalResult::Retry;
        writeLine(xT("Retry..."));
        break;
    default:
        mrRv = ModalResult::Retry;
        writeLine(xT("Retry..."));
        break;
    }

    return mrRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::prompt(
    std::ctstring_t &a_prompt,		///< input text
    cbool_t          a_isVisible,	///< is input text visible
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
void_t
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
FILE *
Console::_getStdStream(
	std::ctostream_t &a_stream
) const
{
    if      (&a_stream == &std::cout) {
        return stdout;
    }
    else if (&a_stream == &std::cerr ||
             &a_stream == &std::clog)
    {
        return stderr;
    }

    return nullptr;
}
//-------------------------------------------------------------------------------------------------
bool_t
Console::_isColorized(
	std::tostream_t &a_stream /* = std::cout */
) const
{
	// An index to be used to access a private storage of I/O streams. See
	// colorize / nocolorize I/O manipulators for details.
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
Console::_isAtty(
	std::ctostream_t &a_stream
) const
{
    FILE *stdStream = _getStdStream(a_stream);
    if (stdStream == nullptr) {
		// Unfortunately, fileno() ends with segmentation fault
		// if invalid file descriptor is passed. So we need to
		// handle this case gracefully and assume it's not a tty
		// if standard stream is not detected, and 0 is returned.
        return false;
    }

    return static_cast<bool_t>( xISATTY(xFILENO(stdStream)) );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
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
void_t
Console::_setStdinEcho(
	cbool_t a_isEnable
) const
{
    _setStdinEcho_impl(a_isEnable);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_escapeValue(
	std::ctstring_t &a_value
) const
{
#if xENV_UNIX
	xCHECK_RET(!_isEscapeValues, a_value);

	return xT("\\[") + a_value + xT("\\]");
#else
	return a_value;
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace
