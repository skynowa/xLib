/**
 * \file  Console.cpp
 * \brief Shell console
 */


#include "Console.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Sync/ThreadCurrent.h>
#include <xLib/System/Color.h>

#if   xENV_WIN
    #include "Platform/Win/Console_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Console_unix.inl"
#endif

namespace xl::system
{

/**************************************************************************************************
*   public
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
void_t
Console::setTitle(
    std::ctstring_t &a_title
) const
{
    _setTitle_impl(a_title);
}
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
    std::ctstring_t &a_str
) const
{
    write(a_str + Const::nl());
}
//-------------------------------------------------------------------------------------------------
void_t
Console::write(
	const Color     &a_color,
    std::ctstring_t &a_str
) const
{
   /**
	* Windows vs Unix implementation
	*
	* Use sequence of write() methods, instead of concat strings
	*/

#if   xENV_WIN
	(void_t)a_color.set();
	write(a_str);
	(void_t)a_color.clear();
#elif xENV_UNIX
	write( a_color.set() );
	write(a_str);
	write( a_color.clear() );
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
Console::writeLine(
	const Color     &a_color,
    std::ctstring_t &a_str
) const
{
	write(a_color, a_str);
	writeNl();	// EOL - n/a for coloring
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
    culong_t a_timeoutMsec
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

        ThreadCurrent::sleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Console::clear() const
{
    _clear_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
