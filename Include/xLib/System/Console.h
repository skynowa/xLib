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
	virtual ~Console();

	xNO_COPY_ASSIGN(Console);
///\}

    /*******************************************************************************
    *   Attributes
    *
    *******************************************************************************/

///\name options
///\{
	void setColorSupport(cbool_t flag);
		///< force set color support (for PS1, etc)
	void setEscapeValues(cbool_t flag);
		///< escaping values (UNIX only)
///\}

    enum class Foreground
        /// foreground (text) color
    {
        Unknown = 0,
        Default,
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        Gray
    };
    xUSING_CONST(Foreground);

    enum class Background
        /// background color
    {
        Unknown = 0,
        Default,
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
        Gray
    };
    xUSING_CONST(Background);

    enum class Attribute
        /// text attribute
    {
        Unknown = 0,  ///< Unknown
        AllOff,       ///< Reset all attributes
        Bold,         ///< Bold/Bright
        Dim,          ///< Dim
        Underline,    ///< Underlined
        Blink,        ///< Blink (not work with most of the terminal emulators)
        Reverse,      ///< Invert the foreground and background colors
        Hidden        ///< Hidden (useful for passwords)
    };
    xUSING_CONST(Attribute);

    std::tstring_t setAttributes(cForeground foreground, cBackground background,
                       cint_t attributes) const;
        ///< set text color
    std::tstring_t clearAttributes() const;
        ///< reset text color to default
    std::tstring_t setAttributesText(cForeground foreground, cBackground background,
                       cint_t attributes, std::ctstring_t &str) const;
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
    void_t         write(cForeground foreground, cBackground background, cint_t attributes,
                       std::ctstring_t &str) const;
        ///< write with colors
    void_t         writeLine(cForeground foreground, cBackground background, cint_t attributes,
                       std::ctstring_t &str) const;
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
    HWND                _wnd {};            ///< console window handle
    HMENU               _menu {};           ///< console menu handle
    HandleNativeInvalid _stdIn;             ///< standard input handle
    HandleNativeInvalid _stdOut;            ///< standard output handle
    WORD                _attributesDef {};  ///< default console attributes

    HWND  _wndHandle();
        ///< get console window handle
    HMENU _menuHandle(cbool_t isRevert);
        ///< get console menu handle
#endif

    bool_t _isColorSupport {};
		///< Say whether a given stream should be colorized or not
	bool_t _isEscapeValues {};
		///< escaping values
    FILE  *_getStdStream(std::ctostream_t &stream) const;
		///< Since C++ hasn't a true way to extract stream handler from the a given `std::ostream`
    bool_t _isColorized(std::tostream_t &stream = std::cout) const;
		///< Say whether a given stream should be colorized or not.
		///< It's always true for ATTY streams and may be true for streams marked with colorize flag
    bool_t _isAtty(std::ctostream_t &stream) const;
        ///< Test whether a given `std::ostream` object refers to a terminal

	std::tstring_t _escapeValue(std::ctstring_t &value) const;
		///< escape by "\[...\]"

xPLATFORM_IMPL:
    void_t         _construct_impl();
    void_t         _destruct_impl();
    std::tstring_t _setAttributes_impl(cForeground foreground, cBackground background,
    					cint_t attributes) const;
    std::tstring_t _clearAttributes_impl() const;
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
