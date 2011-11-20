/**
 * \file  CxConsole.h
 * \brief console
 */


#ifndef xLib_Common_CxConsoleH
#define xLib_Common_CxConsoleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN
    #include <xLib/Common/Win/CxHandleT.h>
#elif xOS_ENV_UNIX

#endif
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxConsole :
    public CxNonCopyable
    /// console
{
    public:
        enum EModalResult
            /// modal result
        {
            mrAbort  = 3,
            mrIgnore = 5,
            mrRetry  = 4
        };

                     CxConsole     ();
            ///< constructor
        virtual     ~CxConsole     ();
            ///< destructor

        enum EAttribute
            /// attribute
        {
            atAllOff = 0, atBold = 1, atUnderscore = 4, atBlink = 5, atReverse = 7, atConcealed  = 8
        };

        enum EForeground
            /// foreground color
        {
            fgBlack  = 30, fgRed  = 31, fgGreen  = 32, fgYellow  = 33, fgBlue  = 34, fgMagenta  = 35, fgCyan  = 36, fgWhite  = 37,
            fgBlack_ = 90, fgRed_ = 91, fgGreen_ = 92, fgYellow_ = 93, fgBlue_ = 94, fgMagenta_ = 95, fgCyan_ = 96, fgWhite_ = 97
        };

        enum EBackground
            /// background color
        {
            bgBlack  = 40,  bgRed  = 41,  bgGreen  = 42,  bgYellow  = 43,  bgBlue  = 44,  bgMagenta  = 45,  bgCyan  = 46,  bgWhite  = 47,
            bgBlack_ = 100, bgRed_ = 101, bgGreen_ = 102, bgYellow_ = 103, bgBlue_ = 104, bgMagenta_ = 105, bgCyan_ = 106, bgWhite_ = 107
        };

        std::tstring bSetTextColor (const std::tstring &csText, const EForeground cfgForeground, const bool cbIsBold, const bool cbIsUnderline, const EBackground cbgBackground, const bool cbIsBlink);
            ///< set text color
        std::tstring sRead         ();
            ///< read
        bool         bWrite        (const std::tstring &csStr);
            ///< write
        bool         bWriteLine    (const std::tstring &csStr = xT(""));
            ///< write line
        bool         bWriteErrLine (const std::tstring &csStr);
            ///< write error message
        EModalResult iMsgBox       (const std::tstring &csText, const std::tstring &csTitle, const UINT cuiType);
            ///< show console message dialog
        bool         bPrompt       (const std::tstring &csPrompt, const bool cbIsVisible, std::tstring *psAnswer);
            ///< show console prompt dialog
        bool         bPause        ();
            ///< pause
        bool         bClear        ();
            ///< clear

        std::tstring sGetTitle     ();
            ///< get title string
        bool         bSetTitle     (const std::tstring &csTitle);
            ///< set title string
        bool         bCenterWindow ();
            ///< allign to center
        bool         bSetFullScreen();
            ///< set full screen
        bool         bEnableClose  (const bool cbFlag);
            ///< enable close button

    private:
    #if xOS_ENV_WIN
        HWND         _m_hWnd;       ///< console window handle
        HMENU        _m_hMenu;      ///< console menu handle
        CxFileHandle _m_hStdIn;     ///< standart input handle
        CxFileHandle _m_hStdOut;    ///< standart output handle

        HWND         _hGetWndHandle ();
            ///< get console window handle
        HMENU        _hGetMenuHandle(const bool cbRevert);
            ///< get console menu handle
    #elif xOS_ENV_UNIX

    #endif
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Common_CxConsoleH


#if xTODO
    #include <io.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <windows.h>

    bool
    create_console() {
      FreeConsole();
      if (AllocConsole()) {
        int hCrt = _open_osfhandle((long) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
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
