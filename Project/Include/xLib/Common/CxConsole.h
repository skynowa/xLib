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
        enum ExModalResult
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

        enum ExAttribute
            /// attribute
        {
            atAllOff = 0, atBold = 1, atUnderscore = 4, 
            atBlink = 5, atReverse = 7, atConcealed  = 8
        };

        enum ExForeground
            /// foreground color
        {
        #if   xOS_ENV_WIN
            fgBlack  = 0, fgRed  = FOREGROUND_RED, fgGreen  = FOREGROUND_GREEN, fgYellow  = 33, 
            fgBlue  = FOREGROUND_BLUE, fgMagenta  = 35, fgCyan  = 36, fgWhite  = 37
        #elif xOS_ENV_UNIX
            fgBlack  = 30, fgRed  = 31, fgGreen  = 32, fgYellow  = 33, 
            fgBlue  = 34, fgMagenta  = 35, fgCyan  = 36, fgWhite  = 37,
            fgBlack_ = 90, fgRed_ = 91, fgGreen_ = 92, fgYellow_ = 93, 
            fgBlue_ = 94, fgMagenta_ = 95, fgCyan_ = 96, fgWhite_ = 97
        #endif
        };

        enum ExBackground
            /// background color
        {
        #if   xOS_ENV_WIN
            bgBlack  = 0,  bgRed  = BACKGROUND_RED,  bgGreen  = BACKGROUND_GREEN,  bgYellow  = 43,  
            bgBlue  = BACKGROUND_BLUE,  bgMagenta  = 45,  bgCyan  = 46,  bgWhite  = 47
        #elif xOS_ENV_UNIX
            bgBlack  = 40,  bgRed  = 41,  bgGreen  = 42,  bgYellow  = 43,  
            bgBlue  = 44,  bgMagenta  = 45,  bgCyan  = 46,  bgWhite  = 47,
            bgBlack_ = 100, bgRed_ = 101, bgGreen_ = 102, bgYellow_ = 103, 
            bgBlue_ = 104, bgMagenta_ = 105, bgCyan_ = 106, bgWhite_ = 107
        #endif
        };

        std::tstring_t sSetTextColor (const std::tstring_t &csText, const ExForeground &cfgForeground, const bool &cbIsBold, const bool &cbIsUnderline, const ExBackground &cbgBackground, const bool &cbIsBlink);
            ///< set text color
        std::tstring_t sRead         ();
            ///< read
        void           vWrite        (const std::tstring_t &csStr);
            ///< write
        void           vWriteLine    (const std::tstring_t &csStr = xT(""));
            ///< write line
        void           vWriteErrLine (const std::tstring_t &csStr);
            ///< write error message
        ExModalResult  iMsgBox       (const std::tstring_t &csText, const std::tstring_t &csTitle, const uint_t &cuiType);
            ///< show console message dialog
        void           vPrompt       (const std::tstring_t &csPrompt, const bool &cbIsVisible, std::tstring_t *psAnswer);
            ///< show console prompt dialog
        void           vPause        ();
            ///< pause
        void           vClear        ();
            ///< clear

        std::tstring_t sTitle        ();
            ///< get title string
        void           vSetTitle     (const std::tstring_t &csTitle);
            ///< set title string
        void           vCenterWindow ();
            ///< allign to center
        void           vSetFullScreen ();
            ///< set full screen
        void           vEnableClose  (const bool &cbFlag);
            ///< enable close button

    private:
    #if   xOS_ENV_WIN
        HWND           _m_hWnd;       ///< console window handle
        HMENU          _m_hMenu;      ///< console menu handle
        CxFileHandle   _m_hStdIn;     ///< standart input handle
        CxFileHandle   _m_hStdOut;    ///< standart output handle

        HWND           _hWndHandle    ();
            ///< get console window handle
        HMENU          _hMenuHandle   (const bool &cbRevert);
            ///< get console menu handle
    #elif xOS_ENV_UNIX
        xNA;
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
