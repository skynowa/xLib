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

        BOOL         bSetTextColor (const UINT cuiColor);
        tString      sRead         ();
        BOOL         bWrite        (const tString &csStr);
        BOOL         bWriteLine    (const tString &csStr);
        BOOL         bWriteErrLine (const tString &csStr);
        EModalResult iMsgBox       (const tString &csText, const tString &csTitle, const UINT cuiType);
        BOOL         bPrompt       (const tString &csPrompt, tString *psAnswer);
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

        HWND         hGetWndHandle ();
        HMENU        hGetMenuHandle(const BOOL cbRevert);
    #elif defined(xOS_LINUX)

    #endif
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxConsoleH
