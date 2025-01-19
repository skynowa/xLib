/**
 * \file  ConsoleUI.h
 * \brief Shell console UI
 *
 * \see
 * https://github.com/ikalnytskyi/termcolor/blob/master/include/termcolor/termcolor.hpp
 * https://github.com/yurablok/colored-cout/blob/master/colored_cout.h
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/System/Console.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system
{

class ConsoleUI
	/// Shell console
{
public:
///\name ctors, dtor
///\{
			 ConsoleUI() = default;
	virtual ~ConsoleUI() = default;

	xNO_COPY_ASSIGN(ConsoleUI);
///\}

	enum class Result
		/// modal result
	{
		Abort  = 0,
		Ignore = 1,
		Retry  = 2
	};
	xUSING_CONST(Result);

	Result msgBox(std::ctstring_t &title, std::ctstring_t &text) const;
		///< show console message dialog
	void_t promptBox(std::ctstring_t &title, std::ctstring_t &text, cbool_t isVisible,
				std::tstring_t *answer) const;
		///< show console prompt dialog

private:
	Console _console;

	std::tstring_t _boxLine(std::ctstring_t &text, std::csize_t width) const;
		///< build MsgBox text line
	void_t         _setStdinEcho(cbool_t isEnable) const;
		///< set stdin echo on/off

xPLATFORM_IMPL:
	void_t _setStdinEcho_impl(cbool_t isEnable) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO: ConsoleUI
 *
 */

#if xTODO
	#ifdef __unix__
		#include <curses.h>
	#elif __WIN32__ || _MSC_VER
		#include <conio.h>
	#endif

	inline void_t
	CtsConsole::promptPassword(char* const pwdBuffer, bool_t visible)
	{
	#if __WIN32__ || _MSC_VER
		bool_t     passwordEntered = false;
		char     ch;
		size_t   idx = 0;
		while (passwordEntered == false) {
			ch = _getch();
			if (visible) {
				printf("*");
			}
			if (ch == 0x0D) {
				passwordEntered = true;
				printf("\n");
			}
			pwdBuffer[idx++] = ch;
		}
		pwdBuffer[idx] = '\0';
	#elif __unix__
		#define CTS_KEYCODE_ENTER   10

		initscr();             /* start curses mode */
		cbreak();
		keypad(stdscr, true);  /* enable keyboard mapping */
		noecho();              /* turn off echoing */

		int_t key = 0;
		int_t idx = 0;
		for ( ;; ) {
		  key = getch();
		  if (key == CTS_KEYCODE_ENTER)  {
			  endwin();
			  break;
		  }
		  pwdBuffer[idx++] = key;
		}
		pwdBuffer[idx] = '\0';
	#endif
	};
#endif
//-------------------------------------------------------------------------------------------------
