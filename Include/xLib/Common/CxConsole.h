/****************************************************************************
* Class name:  CxConsole
* Description: console
* File name:   CxConsole.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.09.2010 10:06:20
*
*****************************************************************************/


#ifndef xLib_Common_CxConsoleH
#define xLib_Common_CxConsoleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
class CxConsole :
    public CxNonCopyable
{
    public:
        enum EModalResult {
            mrAbort  = 3,
            mrIgnore = 5,
            mrRetry  = 4
        };

                     CxConsole     ();
        virtual     ~CxConsole     ();

        //EColor - comsole colors
        enum EAttribute {
            atAllOff = 0, atBold = 1, atUnderscore = 4, atBlink = 5, atReverse = 7, atConcealed  = 8
        };

        enum EForeground {
            fgBlack  = 30, fgRed  = 31, fgGreen  = 32, fgYellow  = 33, fgBlue  = 34, fgMagenta  = 35, fgCyan  = 36, fgWhite  = 37,
            fgBlack_ = 90, fgRed_ = 91, fgGreen_ = 92, fgYellow_ = 93, fgBlue_ = 94, fgMagenta_ = 95, fgCyan_ = 96, fgWhite_ = 97
        };

        enum EBackground {
            bgBlack  = 40,  bgRed  = 41,  bgGreen  = 42,  bgYellow  = 43,  bgBlue  = 44,  bgMagenta  = 45,  bgCyan  = 46,  bgWhite  = 47,
            bgBlack_ = 100, bgRed_ = 101, bgGreen_ = 102, bgYellow_ = 103, bgBlue_ = 104, bgMagenta_ = 105, bgCyan_ = 106, bgWhite_ = 107
        };

        tString      bSetTextColor (const tString &csText, const EForeground cfgForeground, const BOOL cbIsBold, const BOOL cbIsUnderline, const EBackground cbgBackground, const BOOL cbIsBlink);
        tString      sRead         ();
        BOOL         bWrite        (const tString &csStr);
        BOOL         bWriteLine    (const tString &csStr = xT(""));
        BOOL         bWriteErrLine (const tString &csStr);
        EModalResult iMsgBox       (const tString &csText, const tString &csTitle, const UINT cuiType);
        BOOL         bPrompt       (const tString &csPrompt, const BOOL cbIsVisible, tString *psAnswer);
        BOOL         bPause        ();
        BOOL         bClear        ();

        tString      sGetTitle     ();
        BOOL         bSetTitle     (const tString &csTitle);
        BOOL         bCenterWindow ();
        BOOL         bSetFullScreen();
        BOOL         bEnableClose  (const BOOL cbFlag);

    private:
    #if defined(xOS_WIN)
        HWND         _m_hWnd;
        HMENU        _m_hMenu;
        CxFileHandle _m_hStdIn;
        CxFileHandle _m_hStdOut;

        HWND         _hGetWndHandle ();
        HMENU        _hGetMenuHandle(const BOOL cbRevert);
    #elif defined(xOS_LINUX)

    #endif
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxConsoleH

#if xTODO
    #include <io.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <windows.h>

    BOOL 
    create_console() {
      FreeConsole();
      if (AllocConsole()) {
        int hCrt = _open_osfhandle((long) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
        *stdout = *(::_fdopen(hCrt, "w"));
        ::setvbuf(stdout, NULL, _IONBF, 0);

        *stderr = *(::_fdopen(hCrt, "w"));
        ::setvbuf(stderr, NULL, _IONBF, 0);

        return TRUE;
      }
      return FALSE;
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
        keypad(stdscr, TRUE);  /* enable keyboard mapping */
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
