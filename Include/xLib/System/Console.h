/**
 * \file  Console.h
 * \brief Shell console
 *
 * \libs
 *
 * - https://github.com/ikalnytskyi/termcolor/blob/master/include/termcolor/termcolor.hpp
 * - https://github.com/yurablok/colored-cout/blob/master/colored_cout.h
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system
{

class Console
    /// Shell console
{
public:
///\name ctors, dtor
///\{
			 Console();
			 Console(cbool_t isColorSupport, cbool_t isEscapeValues);
	virtual ~Console();

	xNO_COPY_ASSIGN(Console);
///\}

    /*******************************************************************************
    *   Attributes
    *
    *******************************************************************************/

    enum class FG
        /// foreground (text) color
    {
		Unknown  = 0,
		Default  = 1,
		Black    = 2,
		Red      = 3,
		Green    = 4,
		Yellow   = 5,
		Blue     = 6,
		Magenta  = 7,
		Cyan     = 8,
		White    = 9,
		Gray     = 10
    };
    xUSING_CONST(FG);

    enum class BG
        /// background color
    {
		Unknown  = 0,
		Default  = 1,
		Black    = 2,
		Red      = 3,
		Green    = 4,
		Yellow   = 5,
		Blue     = 6,
		Magenta  = 7,
		Cyan     = 8,
		White    = 9,
		Gray     = 10
    };
    xUSING_CONST(BG);

	enum class Attr
		/// text attribute
	{
		Unknown    = 0,      ///< Unknown
		AllOff     = 1 << 0, ///< Reset all attributes
		Bold       = 1 << 1, ///< Bold/Bright
		Dim        = 1 << 2, ///< Dim
		Underline  = 1 << 3, ///< Underlined
		Blink      = 1 << 4, ///< Blink (not work with most of the terminal emulators)
		Reverse    = 1 << 5, ///< Invert the foreground and background colors
		Hidden     = 1 << 6  ///< Hidden (useful for passwords)
	};
	xUSING_CONST(Attr);

    std::tstring_t setAttrs(cFG fg, cBG bg, cAttr attrs) const;
        ///< set text color
    std::tstring_t clearAttrs() const;
        ///< reset text color to default
    std::tstring_t setAttrsText(cFG fg, cBG bg, cAttr attrs, std::ctstring_t &str) const;
        ///< set text color, text, reset text color to default

    /*******************************************************************************
    *   Actions
    *
    *******************************************************************************/

    std::tstring_t read() const;
        ///< read
    void_t         write(std::ctstring_t &str) const;
        ///< write
    void_t         writeLine(std::ctstring_t &str = {}) const;
        ///< write line
    void_t         writeErrLine(std::ctstring_t &str) const;
        ///< write error message
    void_t         write(cFG fg, cBG bg, cAttr attrs, std::ctstring_t &str) const;
        ///< write with colors
    void_t         writeLine(cFG fg, cBG bg, cAttr attrs, std::ctstring_t &str) const;
        ///< write with colors
    void_t         writeNl() const;
    	///< write new line (NL)
    void_t         pause(culong_t &timeoutMsec) const;
        ///< pause with timeout (msec)
    void_t         clear() const;
        ///< clear

    /*******************************************************************************
    *   UI
    *
    *******************************************************************************/

    void_t         setTitle(std::ctstring_t &title) const;
        ///< set title string
#if xENV_WIN
    std::tstring_t title() const;
        ///< get title string
    void_t         centerWindow() const;
        ///< align to center
    void_t         setFullScreen() const;
        ///< set full screen
    void_t         enableClose(cbool_t flag);
        ///< enable close button
#endif

private:
#if xENV_WIN
    HWND                _wnd {};      ///< console window handle
    HMENU               _menu {};     ///< console menu handle
    HandleNativeInvalid _stdIn;       ///< standard input handle
    HandleNativeInvalid _stdOut;      ///< standard output handle
    WORD                _attrsDef {}; ///< default console attributes

    HWND  _wndHandle();
        ///< get console window handle
    HMENU _menuHandle(cbool_t isRevert);
        ///< get console menu handle
#endif

    cbool_t _isColorSupport {};
		///< Say whether a given stream should be colorized or not
	cbool_t _isEscapeValues {};
		///< escaping values

    FILE  *        _getStdStream(std::ctostream_t &stream) const;
		///< Since C++ hasn't a true way to extract stream handler from the a given `std::ostream`
    bool_t         _isColorized(std::tostream_t &stream = std::cout) const;
		///< Say whether a given stream should be colorized or not.
		///< It's always true for ATTY streams and may be true for streams marked with colorize flag
    bool_t         _isAtty(std::ctostream_t &stream) const;
        ///< Test whether a given `std::ostream` object refers to a terminal
	std::tstring_t _escapeValue(std::ctstring_t &value) const;
		///< escape by "\[...\]"

xPLATFORM_IMPL:
    void_t         _construct_impl();
    void_t         _destruct_impl();
    std::tstring_t _setAttrs_impl(cFG fg, cBG bg, cAttr attrs) const;
    std::tstring_t _clearAttrs_impl() const;
    std::tstring_t _read_impl() const;
    void_t         _write_impl(std::ctstring_t &str) const;
    void_t         _clear_impl() const;
    void_t         _setTitle_impl(std::ctstring_t &title) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * \file  Console.h
 * \todo
 *
 */

#if xTODO
    #include <io.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <windows.h>

    bool_t
    create_console()
    {
      FreeConsole();

      if (AllocConsole()) {
        int_t hCrt = _open_osfhandle((long_t) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
        *stdout = *(::_fdopen(hCrt, "w"));
        ::setvbuf(stdout, nullptr, _IONBF, 0);

        *stderr = *(::_fdopen(hCrt, "w"));
        ::setvbuf(stderr, nullptr, _IONBF, 0);

        return true;
      }

      return false;
    }
#endif
//-------------------------------------------------------------------------------------------------
