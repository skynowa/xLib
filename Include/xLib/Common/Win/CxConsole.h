/****************************************************************************
* Class name:  CxConsole
* Description: console
* File name:   CxConsole.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.09.2010 10:06:20
*
*****************************************************************************/


#ifndef xLib_Coomon_Win_CxConsoleH
#define xLib_Coomon_Win_CxConsoleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
//---------------------------------------------------------------------------
class CxConsole :
    public CxNonCopyable
{
    public:
                                        CxConsole     ();
        virtual                        ~CxConsole     ();

        BOOL                            bSetTextColor (UINT uiColor);
        BOOL                            bEnableClose  (BOOL bFlag);
        tString                         sGetTitle     ();
        BOOL                            bSetTitle     (const tString &csTitle);
        BOOL                            bSetFullScreen();
        BOOL                            bClear        ();


        tString                         sRead         ();
        BOOL                            bWrite        (const tString &csStr);
        BOOL                            bWriteLine      (const tString &csStr);
        BOOL                            bWriteErrLine (const tString &csStr);
        BOOL                            bCenterWindow ();
        BOOL                            bPrompt       (const tString &csPrompt, tString *psAnswer);

    private:
        BOOL                            _m_bRes;
        HWND                            _m_hWnd;
        HMENU                           _m_hMenu;
        CxHandle _m_hStdIn;   //INVALID_HANDLE_VALUE
        CxHandle _m_hStdOut;  //INVALID_HANDLE_VALUE

        HWND                             hGetWndHandle ();
        HMENU                            hGetMenuHandle(BOOL bRevert);

};
//---------------------------------------------------------------------------
#endif    //xLib_Coomon_Win_CxConsoleH
