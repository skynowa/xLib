/**
 * \file  CxConsole.h
 * \brief console
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxConsole :
    private CxNonCopyable
    /// console
{
public:
    enum ExForeground
        /// foreground color
    {
        fgUnknown,
        fgBlack,
        fgRed,
        fgGreen,
        fgYellow,
        fgBlue,
        fgMagenta,
        fgCyan,
        fgWhite,
        fgGray
    };

    enum ExBackground
        /// background color
    {
        bgUnknown,
        bgBlack,
        bgRed,
        bgGreen,
        bgYellow,
        bgBlue,
        bgMagenta,
        bgCyan,
        bgWhite,
        bgGray
    };

    enum ExTextAttribute
        /// text attribute
    {
        atUnknown,
        atAllOff,
        atBold,
        atUnderscore,
        atBlink,
        atReverse,
        atConcealed
    };

    enum ExModalResult
        /// modal result
    {
        mrAbort  = 3,
        mrIgnore = 5,
        mrRetry  = 4
    };

                    CxConsole       ();
        ///< constructor
    virtual        ~CxConsole       ();
        ///< destructor

    std::tstring_t  setAttributes   (const ExForeground &cfgForeground, const ExBackground &cbgBackground,
                                     cint_t &ciAttributes) xWARN_UNUSED_RV;
        ///< set text color
    std::tstring_t  setAttributesDef() xWARN_UNUSED_RV;
        ///< set text color
    std::tstring_t  read            () xWARN_UNUSED_RV;
        ///< read
    void_t          write           (std::ctstring_t &csStr);
        ///< write
    void_t          writeLine       (std::ctstring_t &csStr = xT(""));
        ///< write line
    void_t          writeErrLine    (std::ctstring_t &csStr);
        ///< write error message
    ExModalResult   msgBox          (std::ctstring_t &csText, std::ctstring_t &csTitle, cuint_t &cuiType) xWARN_UNUSED_RV;
        ///< show console message dialog
    void_t          prompt          (std::ctstring_t &csPrompt, cbool_t &cbIsVisible, std::tstring_t *psAnswer);
        ///< show console prompt dialog
    void_t          pause           (culong_t &culTimeoutMs);
        ///< pause with timeout (msec)
    void_t          clear           ();
        ///< clear

    std::tstring_t  title           () xWARN_UNUSED_RV;
        ///< get title string
    void_t          setTitle        (std::ctstring_t &csTitle);
        ///< set title string
    void_t          centerWindow    ();
        ///< align to center
    void_t          setFullScreen   ();
        ///< set full screen
    void_t          enableClose     (cbool_t &cbFlag);
        ///< enable close button

private:
#if xOS_ENV_WIN
    HWND            _m_hWnd;             ///< console window handle
    HMENU           _m_hMenu;            ///< console menu handle
    CxHandleInvalid _m_hStdIn;           ///< standard input handle
    CxHandleInvalid _m_hStdOut;          ///< standard output handle
    WORD            _m_wAttributesDef;   ///< default console attributes

    HWND            _wndHandle      () xWARN_UNUSED_RV;
        ///< get console window handle
    HMENU           _menuHandle     (cbool_t &cbRevert) xWARN_UNUSED_RV;
        ///< get console menu handle
#endif
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------


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
        ::setvbuf(stdout, NULL, _IONBF, 0);

        *stderr = *(::_fdopen(hCrt, "w"));
        ::setvbuf(stderr, NULL, _IONBF, 0);

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
        for (;;) {
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
