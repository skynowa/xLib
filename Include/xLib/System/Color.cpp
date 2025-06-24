/**
 * \file  Color.cpp
 * \brief Shell console color
 */


#include "Color.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Format.h>
#include <xLib/Core/Bitset.h>

#if   xENV_WIN
    #include "Platform/Win/Color_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/Color_unix.inl"
#endif

namespace xl::system
{

/**************************************************************************************************
*   Color
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::set() const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return _set_impl(_fg, _bg, _attrs);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::clear() const
{
	xCHECK_RET(!_isColorSupport, xT(""));

    return _clear_impl();
}
//-------------------------------------------------------------------------------------------------
#if xENV_UNIX

std::tstring_t
Color::setText(
	std::ctstring_t &a_str
) const
{
	return set() + a_str + clear();
}

#endif
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::escape(
	std::ctstring_t &a_str
) const
{
#if xENV_UNIX
	xCHECK_RET(!_isEscapeValues, a_str);

	return xT("\\[") + a_str + xT("\\]");
#else
	return a_str;
#endif
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
    if      (&a_stream == &std::tcout) {
        return stdout;
    }
    else if (&a_stream == &std::tcerr ||
             &a_stream == &std::tclog)
    {
        return stderr;
    }

    return nullptr;
}
//-------------------------------------------------------------------------------------------------
bool_t
Color::_isColorized(
	std::tostream_t &a_stream /* = std::tcout */
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

} // namespace
