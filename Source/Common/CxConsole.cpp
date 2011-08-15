/****************************************************************************
* Class name:  CxConsole
* Description: console
* File name:   CxConsole.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.09.2010 10:06:20
*
*****************************************************************************/


#include <xLib/Common/CxConsole.h>

#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxProcess.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxConsole
CxConsole::CxConsole() :
#if defined(xOS_WIN)
    _m_hWnd   (NULL),
    _m_hMenu  (NULL),
    _m_hStdIn (),
    _m_hStdOut()
#elif defined(xOS_LINUX)

#endif
{
#if defined(xOS_WIN)
    _m_hStdIn  = ::GetStdHandle(STD_INPUT_HANDLE);
    /*DEBUG*/xASSERT_DO(FALSE != _m_hStdIn.bIsValid(), return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_hStdIn.hGet(),     return);

    _m_hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    /*DEBUG*/xASSERT_DO(FALSE != _m_hStdOut.bIsValid(), return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_hStdOut.hGet(),     return);

    _m_hWnd = hGetWndHandle();
    /*DEBUG*/xASSERT_DO(NULL != _m_hWnd, return);

    //_m_hMenu - n/a
#elif defined(xOS_LINUX)

#endif
}
//---------------------------------------------------------------------------
//DONE: ~CxConsole
CxConsole::~CxConsole() {

}
//---------------------------------------------------------------------------
//TODO: bSetTextColor (set text color)
//NOTE: http://lifeforce4.wordpress.com/
BOOL 
CxConsole::bSetTextColor(
    const UINT cuiColor
)
{
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    BOOL bRes = ::SetConsoleTextAttribute(_m_hStdOut, cuiColor);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: bSetTextColor
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bEnableClose (enable close button)
BOOL 
CxConsole::bEnableClose(
    const BOOL cbFlag
)
{
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    if (FALSE == cbFlag) {
        _m_hMenu = hGetMenuHandle(FALSE);
        /*DEBUG*/xASSERT_RET(NULL != _m_hMenu, FALSE);

        xCHECK_RET(FALSE == ::DeleteMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND), FALSE);
    } else {
        _m_hMenu = hGetMenuHandle(TRUE);
        /*DEBUG*/xASSERT_RET(NULL != _m_hMenu, FALSE);

        xCHECK_RET(FALSE == ::AppendMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND, xT("")), FALSE);
    }
#elif defined(xOS_LINUX)
    //TODO: bEnableClose
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: sGetTitle (get title string)
tString 
CxConsole::sGetTitle() {
    /*DEBUG*///_m_hWnd - n/a
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  tString());
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), tString());

    tString     sRes;

#if defined(xOS_WIN)
    const ULONG culBuffSize             = 1024;
    TCHAR       szBuff[culBuffSize + 1] = {0};
    ULONG       ulTitleSize             = 0;

    ulTitleSize = ::GetConsoleTitle(szBuff, culBuffSize);
    /*DEBUG*/xASSERT_RET(0 < ulTitleSize, tString());

    sRes.assign(szBuff, ulTitleSize);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(tString());
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: bSetTitle (set title string)
BOOL 
CxConsole::bSetTitle(
    const tString &csTitle
)
{
    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    /*DEBUG*///_m_hWnd - n/a
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    bRes = ::SetConsoleTitle(csTitle.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: bSetTitle
    bRes = FALSE;
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetFullScreen (set full screen)
BOOL 
CxConsole::bSetFullScreen() {
    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    //TODO: xOS_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    COORD crdCoord = ::GetLargestConsoleWindowSize(_m_hStdOut);
    xCHECK_RET(crdCoord.X == 0 && crdCoord.Y == 0, FALSE);

    crdCoord.X -= 2;
    crdCoord.Y -= 2;

    SMALL_RECT recSmallRec = {0, 0, crdCoord.X - 2, crdCoord.Y - 2};

    bRes = ::SetConsoleScreenBufferSize(_m_hStdOut, crdCoord);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);

    bRes = ::SetConsoleWindowInfo(_m_hStdOut, TRUE, &recSmallRec);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);

    bRes = bCenterWindow();
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    bRes = FALSE;
    xNOT_IMPLEMENTED_RET(FALSE);
#endif
    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (clear screen)
BOOL 
CxConsole::bClear() {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    BOOL                       bRes          = FALSE;
    COORD                      coordScreen   = {0};     //here's where we'll home the cursor
    ULONG                      cCharsWritten = 0;
    CONSOLE_SCREEN_BUFFER_INFO csbi          = {0};     //to get buffer info
    ULONG                      ulConSize     = 0;       //number of character cells in the current buffer

    //get the number of character cells in the current buffer
    bRes = ::GetConsoleScreenBufferInfo(_m_hStdOut, &csbi);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);

    ulConSize = csbi.dwSize.X * csbi.dwSize.Y;

    //fill the entire screen with blanks
    bRes = ::FillConsoleOutputCharacter(_m_hStdOut, (TCHAR)xT(' '), ulConSize, coordScreen, &cCharsWritten);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);

    //get the current text attribute
    bRes = ::GetConsoleScreenBufferInfo(_m_hStdOut, &csbi);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);

    //now set the buffer's attributes accordingly
    bRes = ::FillConsoleOutputAttribute(_m_hStdOut, csbi.wAttributes, ulConSize, coordScreen, &cCharsWritten);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);

    //put the cursor at (0, 0)
    bRes = ::SetConsoleCursorPosition(_m_hStdOut, coordScreen );
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);
#elif defined(xOS_LINUX)
    INT iRes = std::_tsystem(xT("clear"));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: sRead (read)
tString 
CxConsole::sRead() {
    tString sRes;

#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               tString());
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  tString());
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), tString());

    ULONG       ulRead                  = 0;
    const ULONG culBuffSize             = 1024 * 64;
    TCHAR       szBuff[culBuffSize + 1] = {0};

    BOOL bRes = ::ReadConsole(_m_hStdIn, &szBuff[0], culBuffSize, &ulRead, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,   tString());
    /*DEBUG*/xASSERT_RET(NULL  != szBuff, tString());

    sRes.assign(szBuff, ulRead - CxConst::xCRNL.size());
#elif defined(xOS_LINUX)
    //TODO: sRead
    xNOT_IMPLEMENTED_RET(tString());
#endif

    return sRes;
}
//---------------------------------------------------------------------------
//TODO: bWrite (write)
BOOL 
CxConsole::bWrite(
    const tString &csStr
)
{
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    ULONG ulWritten = 0;

    BOOL bRes = ::WriteConsole(_m_hStdOut, &csStr.at(0), csStr.size(), &ulWritten, NULL);
    /*DEBUG*/xASSERT_RET(FALSE     != bRes,         FALSE);
    /*DEBUG*/xASSERT_RET(ulWritten == csStr.size(), FALSE);
#elif defined(xOS_LINUX)
    //TODO: bWrite
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWriteLine (write line)
BOOL 
CxConsole::bWriteLine(
    const tString &csStr
)
{
#if defined(xOS_WIN)
    //TODO: xOS_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    BOOL bRes = bWrite(csStr + CxConst::xNL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: bWriteLine
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWriteErrLine (write error message)
BOOL 
CxConsole::bWriteErrLine(
    const tString &csStr
)
{
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);
#elif defined(xOS_LINUX)

#endif

    BOOL bRes = bWriteLine(xT("Error: ") + csStr);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    ////CxDebbuger::bBeep(40UL, 40UL);
    std::cin.get();

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bCenterWindow (allign to center)
BOOL 
CxConsole::bCenterWindow() {
#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    BOOL bRes = FALSE;

    RECT rcOrigin = {0};
    bRes = ::GetWindowRect(_m_hWnd, &rcOrigin);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    RECT rcDesktop = {0};
    bRes = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    INT iDesktopX  = (rcDesktop.right  - rcDesktop.left) / 2;
    INT iDesktopY  = (rcDesktop.bottom - rcDesktop.top)  / 2;
    INT iWndWidth  = (rcOrigin.right   - rcOrigin.left);
    INT iWndHeight = (rcOrigin.bottom  - rcOrigin.top);
    INT X          = iDesktopX - iWndWidth / 2;        if (X < 0) {X = 0;}

    bRes = ::MoveWindow(_m_hWnd, X, iDesktopY - iWndHeight / 2, iWndWidth, iWndHeight, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: bCenterWindow
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: iMsgBox (message box)
CxConsole::EModalResult 
CxConsole::iMsgBox(
    const tString &csText, 
    const tString &csTitle, 
    const UINT     cuiType
)
{
    EModalResult mrRes;

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    tcout << xT("\n################################################################################\n");
    tcout << xT("#    ") << csTitle << xT("\n");
    tcout << xT("#\n");
    tcout << xT("#    ") << csText  << xT("\n");
    tcout << xT("#");
    tcout << xT("\n################################################################################\n");
    tcout << xT("\n");
    tcout << xT("\nAbort (a), Ignore (i), Retry (r): ");
    tcout.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( tcin.get() );   tcin.ignore();
    switch (cmRes) {
        case cmAbort:  { mrRes = mrAbort;  } break;
        case cmIgnore: { mrRes = mrIgnore; } break;
        case cmRetry:  { mrRes = mrRetry;  } break;

        default:       { mrRes = mrRetry;  } break;
    }

    return mrRes; 
}
//---------------------------------------------------------------------------
//DONE: bPrompt (prompt dialog)
BOOL 
CxConsole::bPrompt(
    const tString &csPrompt, 
    tString *psAnswer
)
{
    /*DEBUG*/xASSERT_RET(false == csPrompt.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psAnswer,         FALSE);

    while (true) {
        BOOL bRes = bWrite(csPrompt);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        while (true) {
            const TCHAR chLetter = static_cast<TCHAR>( tcin.get() );   tcin.ignore();

            //ENTER
            xCHECK_DO(0xd == chLetter, break);

            //BACKSPACE
            xCHECK_DO(0x8 == chLetter, (*psAnswer).clear(); continue);

            (*psAnswer).push_back(chLetter);
        }

        bRes = bWriteLine(CxConst::xSTR_EMPTY);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        xCHECK_DO(true == (*psAnswer).empty(), continue);

        break;
    }

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: hGetWndHandle
#if defined(xOS_WIN)

HWND 
CxConsole::hGetWndHandle() {
    /*DEBUG*/

    HWND    hRes         = NULL;
    BOOL    bRes         = FALSE;
    tString sNewWndTitle;
    tString sOldWndTitle;

    //Fetch current window title.
    sOldWndTitle = sGetTitle();
    /*DEBUG*/xASSERT_RET(false == sOldWndTitle.empty(), NULL);

    //Format a "unique" szNewWndTitle.
    sNewWndTitle = CxString::sFormat(xT("%li/%li"), ::GetTickCount(), CxProcess::ulGetCurrId());

    //Change current window title.
    bRes = bSetTitle(sNewWndTitle);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, NULL);

    //Ensure window title has been updated.
    CxThread::bSleep(50UL);

    //Look for NewWindowTitle.
    hRes = ::FindWindow(NULL, sNewWndTitle.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    //Restore original window title.
    bRes = bSetTitle(sOldWndTitle);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, NULL);

    return hRes;
}

#endif
//---------------------------------------------------------------------------
//DONE: hGetMenuHandle
#if defined(xOS_WIN)

HMENU
CxConsole::hGetMenuHandle(
    const BOOL cbRevert
)
{
    /*DEBUG*/

    _m_hMenu = ::GetSystemMenu(_m_hWnd, cbRevert);
    /*DEBUG*/xASSERT_RET(NULL != _m_hMenu, NULL);

    return _m_hMenu;
}

#endif
//---------------------------------------------------------------------------
