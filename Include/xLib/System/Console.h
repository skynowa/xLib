/**
 * \file  Console.h
 * \brief console
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, system)

class Console
    /// console
{
public:
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

    enum class TextAttribute
        /// text attribute
    {
        Unknown = 0,  ///<
        AllOff,       ///<
        Bold,         ///< Bold/Bright
        Dim,          ///< Dim
        Underline,    ///< Underlined
        Blink,        ///< Blink (not work with most of the terminal emulators)
        Reverse,      ///< Invert the foreground and background colors
        Hidden        ///< Hidden (useful for passwords)
    };
    xUSING_CONST(TextAttribute);

    enum class ModalResult
        /// modal result
    {
        Abort  = 3,
        Ignore = 5,
        Retry  = 4
    };
    xUSING_CONST(ModalResult);

                   Console();
        ///< constructor
    virtual       ~Console();
        ///< destructor

    std::tstring_t setAttributes(cForeground foreground, cBackground background,
                       cint_t attributes) const xWARN_UNUSED_RV;
        ///< set text color
    std::tstring_t setAttributesDef() const xWARN_UNUSED_RV;
        ///< set text color
    std::tstring_t read() const xWARN_UNUSED_RV;
        ///< read
    void_t         write(std::ctstring_t &str) const;
        ///< write
    void_t         writeLine(std::ctstring_t &str = xT("")) const;
        ///< write line
    void_t         writeErrLine(std::ctstring_t &str) const;
        ///< write error message
    ModalResult    msgBox(std::ctstring_t &text, std::ctstring_t &title, cuint_t &type) const
                       xWARN_UNUSED_RV;
        ///< show console message dialog
    void_t         prompt(std::ctstring_t &prompt, cbool_t &isVisible, std::tstring_t *answer)
                       const;
        ///< show console prompt dialog
    void_t         pause(culong_t &timeoutMsec) const;
        ///< pause with timeout (msec)
    void_t         clear() const;
        ///< clear

    void_t         setTitle(std::ctstring_t &title) const;
        ///< set title string
#if xENV_WIN
    std::tstring_t title() const xWARN_UNUSED_RV;
        ///< get title string
    void_t         centerWindow() const;
        ///< align to center
    void_t         setFullScreen() const;
        ///< set full screen
    void_t         enableClose(cbool_t &flag);
        ///< enable close button
#endif

private:
#if xENV_WIN
    HWND                _wnd {};            ///< console window handle
    HMENU               _menu {};           ///< console menu handle
    HandleNativeInvalid _stdIn;             ///< standard input handle
    HandleNativeInvalid _stdOut;            ///< standard output handle
    WORD                _attributesDef {};  ///< default console attributes

    HWND           _wndHandle() xWARN_UNUSED_RV;
        ///< get console window handle
    HMENU          _menuHandle(cbool_t &isRevert) xWARN_UNUSED_RV;
        ///< get console menu handle
#endif

	std::tstring_t _msgBoxLine(std::ctstring_t &text, std::csize_t &width) const;
		///< buil MsgBox text line
	void_t         _setStdinEcho(cbool_t &isEnable) const;
		///< set stdin echo on/off

    xNO_COPY_ASSIGN(Console)

xPLATFORM_IMPL:
    void_t         _construct_impl();
    void_t         _destruct_impl();
    std::tstring_t _setAttributes_impl(cForeground foreground, cBackground background,
    					cint_t attributes) const xWARN_UNUSED_RV;
    std::tstring_t _setAttributesDef_impl() const xWARN_UNUSED_RV;
    std::tstring_t _read_impl() const xWARN_UNUSED_RV;
    void_t         _write_impl(std::ctstring_t &str) const;
    void_t         _clear_impl() const;
    void_t         _setTitle_impl(std::ctstring_t &title) const;
    void_t         _setStdinEcho_impl(cbool_t &isEnable) const;
};

xNAMESPACE_END2(xl, system)
//-------------------------------------------------------------------------------------------------

#if xTODO
    #include <io.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <windows.h>

    bool_t
    create_console() {
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

    usage:

    #ifdef DEBUG
      create_console();
    #endif // DEBUG
#endif

#if xTODO
    #ifdef __unix__
        #include <curses.h>
    #elif __WIN32__ || _MSC_VER
        #include <conio.h>
    #endif

    inline void_t
    CtsConsole::promptPassword(char* const pwdBuffer, bool_t visible) {
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
