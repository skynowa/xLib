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
	Console(_isColorized(), true)
{
}
//-------------------------------------------------------------------------------------------------
Console::Console(
	cbool_t a_isColorSupport, ///< force set color support (for PS1, etc)
	cbool_t a_isEscapeValues  ///< escaping values (UNIX only)
) :
	_isColorSupport{a_isColorSupport},
	_isEscapeValues{a_isEscapeValues}
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
Console::_isAtty(
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
