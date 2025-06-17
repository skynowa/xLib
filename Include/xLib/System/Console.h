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

class Color;

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

    // UI
    void_t         setTitle(std::ctstring_t &title) const;
        ///< set title string

    std::tstring_t read() const;
        ///< read
    void_t         write(std::ctstring_t &str) const;
        ///< write
    void_t         writeLine(std::ctstring_t &str = {}) const;
        ///< write line
    void_t         writeErrLine(std::ctstring_t &str) const;
        ///< write error message
    void_t         write(const Color &color, std::ctstring_t &str) const;
        ///< write with colors
    void_t         writeLine(const Color &color, std::ctstring_t &str) const;
        ///< write with colors
    void_t         writeNl() const;
    	///< write new line (NL)
    void_t         pause(culong_t &timeoutMsec) const;
        ///< pause with timeout (msec)
    void_t         clear() const;
        ///< clear

xPLATFORM_IMPL:
#if xENV_WIN
    HandleNativeInvalid _stdIn;       ///< standard input handle
    HandleNativeInvalid _stdOut;      ///< standard output handle
    WORD                _attrsDef {}; ///< default console attributes
#endif

    void_t         _ctor_impl();
    void_t         _dtor_impl();
    void_t         _setTitle_impl(std::ctstring_t &title) const;
    std::tstring_t _read_impl() const;
    void_t         _write_impl(std::ctstring_t &str) const;
    void_t         _clear_impl() const;
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
