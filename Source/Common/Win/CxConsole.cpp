/****************************************************************************
* Class name:  CxConsole
* Description: console
* File name:   CxConsole.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.09.2010 10:06:20
*
*****************************************************************************/


#include <xLib/Common/Win/CxConsole.h>

#include <xLib/Filesystem/CxStdioFile.h>


#if defined(xOS_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxConsole
CxConsole::CxConsole() :
    _m_bRes   (FALSE),
    _m_hWnd   (NULL),
    _m_hMenu  (NULL),
    _m_hStdIn (),
    _m_hStdOut()
{
    _m_hStdIn  = ::GetStdHandle(STD_INPUT_HANDLE);
    /*DEBUG*/xASSERT_DO(FALSE != _m_hStdIn.bIsValid(), return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_hStdIn.hGet(),     return);

    _m_hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    /*DEBUG*/xASSERT_DO(FALSE != _m_hStdOut.bIsValid(), return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_hStdOut.hGet(),     return);

    _m_hWnd = hGetWndHandle();
    /*DEBUG*/xASSERT_DO(NULL != _m_hWnd, return);

    //_m_hMenu - n/a
}
//---------------------------------------------------------------------------
//TODO: ~CxConsole
CxConsole::~CxConsole() {
    _m_hMenu = NULL;
    _m_hWnd  = NULL;
}
//---------------------------------------------------------------------------
//TODO: bSetTextColor
BOOL CxConsole::bSetTextColor(UINT uiColor) {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    _m_bRes = ::SetConsoleTextAttribute(_m_hStdOut, uiColor);    //�����
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bEnableClose
BOOL CxConsole::bEnableClose(BOOL bFlag) {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    if (FALSE == bFlag) {
        _m_hMenu = hGetMenuHandle(FALSE);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        xCHECK_RET(FALSE == ::DeleteMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND), FALSE);
    } else {
        _m_hMenu = hGetMenuHandle(TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        xCHECK_RET(FALSE == ::AppendMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND, xT("")), FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: sGetTitle
tString CxConsole::sGetTitle() {
    /*DEBUG*///_m_hWnd - n/a
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  tString());
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), tString());

    const ULONG culBuffSize             = 1024;
    TCHAR       szBuff[culBuffSize + 1] = {0};
    ULONG       ulTitleSize             = 0;

    ulTitleSize = ::GetConsoleTitle(szBuff, culBuffSize);
    /*DEBUG*/xASSERT_RET(0 < ulTitleSize, tString());

    return tString(szBuff, ulTitleSize);
}
//---------------------------------------------------------------------------
//TODO: bSetTitle
BOOL CxConsole::bSetTitle(const tString &csTitle) {
    /*DEBUG*///_m_hWnd - n/a
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    _m_bRes = ::SetConsoleTitle(csTitle.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bSetFullScreen
BOOL CxConsole::bSetFullScreen() {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    COORD crdCoord = ::GetLargestConsoleWindowSize(_m_hStdOut);
    xCHECK_RET(crdCoord.X == 0 && crdCoord.Y == 0, FALSE);

    crdCoord.X -= 2;
    crdCoord.Y -= 2;

    SMALL_RECT recSmallRec = {
        0,                    //Left
        0,                    //Top
        crdCoord.X - 2,        //Right
        crdCoord.Y - 2        //Bottom
    };

    _m_bRes = ::SetConsoleScreenBufferSize(_m_hStdOut, crdCoord);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    _m_bRes = ::SetConsoleWindowInfo(_m_hStdOut, TRUE, &recSmallRec);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    _m_bRes = bCenterWindow();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bClear
BOOL CxConsole::bClear() {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    COORD                      coordScreen   = {0};        /*here's where we'll home the cursor*/
    ULONG                      cCharsWritten = 0;
    CONSOLE_SCREEN_BUFFER_INFO csbi          = {0};        /*to get buffer info*/
    ULONG                      ulConSize     = 0;        /*number of character cells in the current buffer*/

    //get the number of character cells in the current buffer
    _m_bRes = ::GetConsoleScreenBufferInfo(_m_hStdOut, &csbi);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    ulConSize = csbi.dwSize.X * csbi.dwSize.Y;

    //fill the entire screen with blanks
    _m_bRes = ::FillConsoleOutputCharacter(_m_hStdOut, (TCHAR)xT(' '), ulConSize, coordScreen, &cCharsWritten);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    //get the current text attribute
    _m_bRes = ::GetConsoleScreenBufferInfo(_m_hStdOut, &csbi);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    //now set the buffer's attributes accordingly
    _m_bRes = ::FillConsoleOutputAttribute(_m_hStdOut, csbi.wAttributes, ulConSize, coordScreen, &cCharsWritten);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    //put the cursor at (0, 0)
    _m_bRes = ::SetConsoleCursorPosition(_m_hStdOut, coordScreen );
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    return TRUE;
}



//---------------------------------------------------------------------------
//TODO: sRead ()
tString CxConsole::sRead() {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               tString());
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  tString());
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), tString());

    ULONG       ulRead                  = 0;
    const ULONG culBuffSize             = 1024 * 64;
    TCHAR       szBuff[culBuffSize + 1] = {0};

    _m_bRes = ::ReadConsole(_m_hStdIn, &szBuff[0], culBuffSize, &ulRead, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, tString());
    /*DEBUG*/xASSERT_RET(NULL  != szBuff,  tString());

    return tString(szBuff, ulRead - 2);    //������ "\r\n"
}
//---------------------------------------------------------------------------
//TODO: bWrite ()
BOOL CxConsole::bWrite(const tString &csStr) {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    ULONG ulWritten = 0;

    _m_bRes = ::WriteConsole(_m_hStdOut, &csStr.at(0), csStr.size(), &ulWritten, NULL);
    /*DEBUG*/xASSERT_RET(FALSE     != _m_bRes,      FALSE);
    /*DEBUG*/xASSERT_RET(ulWritten == csStr.size(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWriteLine
BOOL CxConsole::bWriteLine(const tString &csStr) {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    _m_bRes = bWrite(csStr + CxConst::xNL);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bWriteErrLine
BOOL CxConsole::bWriteErrLine(const tString &csStr) {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    _m_bRes = bWriteLine(xT("Error: ") + csStr);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    ////::Beep(40, 40);
    std::cin.get();

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bCenterWindow
BOOL CxConsole::bCenterWindow() {
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdIn.bIsValid(),  FALSE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_hStdOut.bIsValid(), FALSE);

    RECT rcOrigin = {0};
    _m_bRes = ::GetWindowRect(_m_hWnd, &rcOrigin);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    RECT rcDesktop = {0};
    _m_bRes = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    INT iDesktopX  = (rcDesktop.right  - rcDesktop.left) / 2;
    INT iDesktopY  = (rcDesktop.bottom - rcDesktop.top)  / 2;
    INT iWndWidth  = (rcOrigin.right   - rcOrigin.left);
    INT iWndHeight = (rcOrigin.bottom  - rcOrigin.top);
    INT X          = iDesktopX - iWndWidth / 2;        if (X < 0) {X = 0;}

    _m_bRes = ::MoveWindow(_m_hWnd, X, iDesktopY - iWndHeight / 2, iWndWidth, iWndHeight, TRUE);
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes,  FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bPrompt (���� ������)
BOOL CxConsole::bPrompt(const tString &csPrompt, tString *psAnswer) {
    /*DEBUG*/xASSERT_RET(false == csPrompt.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != psAnswer,         FALSE);

    while (TRUE) {
        _m_bRes = bWrite(csPrompt);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        //���� ������
        while (TRUE) {
            //������ ������ �� ������ �����
            CHAR chLetter = static_cast<CHAR>( tcin.get() );   tcin.ignore();

            //ENTER - ��������� ����� ������
            xCHECK_DO(0xd == chLetter, break);

            //BACKSPACE - ������� ��� ������
            xCHECK_DO(0x8 == chLetter, (*psAnswer).clear(); continue);

            //��������� ������ � ������
            (*psAnswer).push_back(chLetter);
        }

        _m_bRes = bWriteLine(xT(""));
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        //-------------------------------------
        //CHECK: ���� ��� ������
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
//TODO: hGetWndHandle
HWND CxConsole::hGetWndHandle() {
    /*DEBUG*/

    HWND    hRes         = NULL;
    tString sNewWndTitle;
    tString sOldWndTitle;

    //Fetch current window title.
    sOldWndTitle = sGetTitle();
    /*DEBUG*/xASSERT_RET(false == sOldWndTitle.empty(), NULL);

    //Format a "unique" szNewWndTitle.
    sNewWndTitle = CxString::sFormat(xT("%d/%d"), ::GetTickCount(), ::GetCurrentProcessId());

    //Change current window title.
    _m_bRes = bSetTitle(sNewWndTitle.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, NULL);

    //Ensure window title has been updated.
    ::Sleep(50);

    //Look for NewWindowTitle.
    hRes = ::FindWindow(NULL, sNewWndTitle.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRes, NULL);

    //Restore original window title.
    _m_bRes = bSetTitle(sOldWndTitle.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, NULL);

    //::CloseHandle(hRes);    hRes = NULL;

    return hRes;
}
//---------------------------------------------------------------------------
//TODO: hGetMenuHandle
HMENU CxConsole::hGetMenuHandle(BOOL bRevert) {
    /*DEBUG*/

    _m_hMenu = ::GetSystemMenu(_m_hWnd, bRevert);
    /*DEBUG*/xASSERT_RET(NULL != _m_hMenu, NULL);

    return _m_hMenu;
}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
