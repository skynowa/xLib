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
CxConsole::CxConsole()
#if defined(xOS_WIN)
    :
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
//DONE: bSetTextColor (set text color)
//NOTE: http://lifeforce4.wordpress.com/, http://lifeforce4.wordpress.com/
tString
CxConsole::bSetTextColor(
    const tString      &csText,
    const EForeground   cfgForeground,
    const BOOL          cbIsBold,
    const BOOL          cbIsUnderline,
    const EBackground   cbgBackground,
    const BOOL          cbIsBlink
)
{
    /*DEBUG*/// n/a

    tString sRes;

#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    BOOL bRes = ::SetConsoleTextAttribute(_m_hStdOut, cfgForeground);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, tString());
#elif defined(xOS_LINUX)
    xCHECK_DO(TRUE == cbIsUnderline, sRes += CxString::sFormat(xT("\033[%im"), atUnderscore));
    xCHECK_DO(TRUE == cbIsBlink,     sRes += CxString::sFormat(xT("\033[%im"), atBlink)     );
    xCHECK_DO(TRUE == cbIsBold,      sRes += CxString::sFormat(xT("\033[%im"), atBold)      );

    sRes += CxString::sFormat(xT("\033[%im"), cbgBackground);
    sRes += CxString::sFormat(xT("\033[%im"), cfgForeground);
    sRes += csText;
    sRes += xT("\033[0;0m");
#endif

    return sRes;
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
    tcin >> sRes;
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

    bRes = ::FlushConsoleInputBuffer(_m_hStdOut);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    tcout << csStr;

    tcout.flush();
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
#elif defined(xOS_LINUX)

#endif

    BOOL bRes = bWrite(csStr + CxConst::xNL);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

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

    bRes = bPause();
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

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
    tcout << xT("#  ") << csTitle << xT("\n");
    tcout << xT("#\n");
    tcout << xT("#  ") << csText  << xT("\n");
    tcout << xT("#");
    tcout << xT("\n################################################################################\n");
    tcout << xT("\n");
    tcout << CxString::sFormat(xT("\nAbort (%c), Ignore (%c), Retry (%c): "), cmAbort, cmIgnore, cmRetry);
    tcout.flush();

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( tcin.get() );   tcin.ignore();
    switch (cmRes) {
        case cmAbort:  { mrRes = mrAbort;  bWriteLine(xT("Abort..."));  } break;
        case cmIgnore: { mrRes = mrIgnore; bWriteLine(xT("Ognore...")); } break;
        case cmRetry:  { mrRes = mrRetry;  bWriteLine(xT("Retry..."));  } break;

        default:       { mrRes = mrRetry;  bWriteLine(xT("Retry..."));  } break;
    }

    return mrRes;
}
//---------------------------------------------------------------------------
//DONE: bPrompt (prompt dialog)
BOOL
CxConsole::bPrompt(
    const tString &csPrompt,
    const BOOL     cbIsVisible,
    tString       *psAnswer
)
{
    /*DEBUG*/xASSERT_RET(false == csPrompt.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psAnswer,         FALSE);

    while (true) {
        BOOL bRes = bWrite(csPrompt + xT(": "));
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        while (true) {
            const TCHAR chLetter = static_cast<TCHAR>( tcin.get() );   tcin.ignore();

            //asteriks
            xCHECK_DO(TRUE == cbIsVisible, bWrite(xT("*")));

            //ENTER
            xCHECK_DO(0x0D == chLetter, break);

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
//DONE: bPause (pause)
BOOL
CxConsole::bPause() {
    /*DEBUG*/

#if xTODO
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
        cout << endl << "Press any key to continue..." << endl;

        ::FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        _getch();
    #elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
        cout << endl << "Press ENTER to continue..." << endl;

        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    #endif
#endif

    BOOL bRes = bWrite(xT("Press [ENTER] to continue..."));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    std::cin.clear();
    std::cin.ignore();

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (clear screen)
BOOL
CxConsole::bClear() {
    BOOL bRes = FALSE;

#if defined(xOS_WIN)
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

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
    bRes = bWriteLine(CxConst::xFF);
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);
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
    tString sRes;

#if defined(xOS_WIN)
    /*DEBUG*///_m_hWnd - n/a
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  tString());
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), tString());

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
    bRes = bWriteLine( CxString::sFormat(xT("%c]0;%s%c"), xT('\033'), csTitle.c_str(), xT('\007')) );
    /*DEBUG*/xASSERT_RET(FALSE != bRes,  FALSE);
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
    //TODO: bSetFullScreen
    bRes = FALSE;
    xNOT_IMPLEMENTED_RET(FALSE);
#endif
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
