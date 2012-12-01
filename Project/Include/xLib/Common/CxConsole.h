/**
 * \file  CxConsole.h
 * \brief console
 */


#ifndef xLib_Common_CxConsoleH
#define xLib_Common_CxConsoleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxHandleT.h>
//---------------------------------------------------------------------------
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

                       CxConsole        ();
            ///< constructor
        virtual       ~CxConsole        ();
            ///< destructor

        std::tstring_t sSetAttributes   (const ExForeground &cfgForeground, const ExBackground &cbgBackground,
                                         const int &ciAttributes);
            ///< set text color
        std::tstring_t sSetAttributesDef();
            ///< set text color
        std::tstring_t sRead            ();
            ///< read
        void           vWrite           (const std::tstring_t &csStr);
            ///< write
        void           vWriteLine       (const std::tstring_t &csStr = xT(""));
            ///< write line
        void           vWriteErrLine    (const std::tstring_t &csStr);
            ///< write error message
        ExModalResult  iMsgBox          (const std::tstring_t &csText, const std::tstring_t &csTitle, const uint_t &cuiType);
            ///< show console message dialog
        void           vPrompt          (const std::tstring_t &csPrompt, const bool &cbIsVisible, std::tstring_t *psAnswer);
            ///< show console prompt dialog
        void           vPause           (const ulong_t &culTimeoutMs);
            ///< pause with timeout (msec)
        void           vClear           ();
            ///< clear

        std::tstring_t sTitle           ();
            ///< get title string
        void           vSetTitle        (const std::tstring_t &csTitle);
            ///< set title string
        void           vCenterWindow    ();
            ///< allign to center
        void           vSetFullScreen   ();
            ///< set full screen
        void           vEnableClose     (const bool &cbFlag);
            ///< enable close button

    private:
    #if xOS_ENV_WIN
        HWND           _m_hWnd;             ///< console window handle
        HMENU          _m_hMenu;            ///< console menu handle
        CxFileHandle   _m_hStdIn;           ///< standart input handle
        CxFileHandle   _m_hStdOut;          ///< standart output handle
        WORD           _m_wAttributesDef;   ///< default console attributes

        HWND           _hWndHandle      ();
            ///< get console window handle
        HMENU          _hMenuHandle     (const bool &cbRevert);
            ///< get console menu handle
    #endif
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Common_CxConsoleH


#if xTODO
    #include <io.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <windows.h>

    bool
    create_console() {
      FreeConsole();
      if (AllocConsole()) {
        int hCrt = _open_osfhandle((long_t) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
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

    inline void
    CtsConsole::promptPassword(char* const pwdBuffer, bool visible) {
    #if __WIN32__ || _MSC_VER
        bool     passwordEntered = false;
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

        int key = 0;
        int idx = 0;
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
