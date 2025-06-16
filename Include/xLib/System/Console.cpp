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
Console::Console()
{
    _ctor_impl();
}
//-------------------------------------------------------------------------------------------------
Console::~Console()
{
    _dtor_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Console::Color
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Color::Color(
	cbool_t a_isColorSupport, ///< force set color support (for PS1, etc)
	cbool_t a_isEscapeValues  ///< escaping values (UNIX only)
) :
	_isColorSupport{a_isColorSupport},
	_isEscapeValues{a_isEscapeValues}
{
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::setAttrs(
    cFG   a_fg,
    cBG   a_bg,
    cAttr a_attrs
) const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return _setAttrs_impl(a_fg, a_bg, a_attrs);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::clearAttrs() const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return _clearAttrs_impl();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::setAttrsText(
    cFG              a_fg,
    cBG              a_bg,
    cAttr            a_attrs,
    std::ctstring_t &a_str
) const
{
	return setAttrs(a_fg, a_bg, a_attrs) + a_str + clearAttrs();
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
    Color::cFG              a_fg,
    Color::cBG              a_bg,
    Color::cAttr            a_attrs,
    std::ctstring_t &a_str
) const
{
   /**
	* Unix vs Windows implementation
	*
	* Use sequence of write() methods, instead of concat strings
	*/

	Color color(true, true);

	write( color.setAttrs(a_fg, a_bg, a_attrs) );
	write(a_str);
	write( color.clearAttrs() );
}
//-------------------------------------------------------------------------------------------------
void_t
Console::writeLine(
    Color::cFG              a_fg,
    Color::cBG              a_bg,
    Color::cAttr            a_attrs,
    std::ctstring_t &a_str
) const
{
	write(a_fg, a_bg, a_attrs, a_str);
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
Color::_getStdStream(
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
Color::_isColorized(
	std::tostream_t &a_stream /* = std::cout */
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
std::tstring_t
Color::_escapeValue(
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
