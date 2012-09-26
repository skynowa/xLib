/**
 * \file  CxConsole.cpp
 * \brief console
 */


#include <xLib/Common/CxConsole.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxCurrentThread.h>
#include <xLib/Sync/CxCurrentProcess.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxConsole::CxConsole()
#if xOS_ENV_WIN
    :
    _m_hWnd   (NULL),
    _m_hMenu  (NULL),
    _m_hStdIn (),
    _m_hStdOut()
#elif xOS_ENV_UNIX

#endif
{
#if xOS_ENV_WIN
    _m_hStdIn  = ::GetStdHandle(STD_INPUT_HANDLE);
    /*DEBUG*/xASSERT_DO(false != _m_hStdIn.bIsValid(), return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_hStdIn.hGet(),     return);

    _m_hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    /*DEBUG*/xASSERT_DO(false != _m_hStdOut.bIsValid(), return);
    /*DEBUG*/xASSERT_DO(NULL  != _m_hStdOut.hGet(),     return);

    _m_hWnd = _hGetWndHandle();
    /*DEBUG*/xASSERT_DO(NULL != _m_hWnd, return);

    //_m_hMenu - n/a
#endif
}
//---------------------------------------------------------------------------
CxConsole::~CxConsole() {
#if xOS_ENV_WIN
    (void)_m_hStdIn.hDetach();
    (void)_m_hStdOut.hDetach();
#endif
}
//---------------------------------------------------------------------------
//NOTE: http://lifeforce4.wordpress.com/, http://lifeforce4.wordpress.com/
std::tstring_t
CxConsole::bSetTextColor(
    const std::tstring_t &a_csText,
    const ExForeground    a_cfgForeground,
    const bool            a_cbIsBold,
    const bool            a_cbIsUnderline,
    const ExBackground    a_cbgBackground,
    const bool            a_cbIsBlink
)
{
    /*DEBUG*/// n/a

    std::tstring_t sRv;

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               std::tstring_t());
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  std::tstring_t());
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), std::tstring_t());

    BOOL blRes = ::SetConsoleTextAttribute(_m_hStdOut.hGet(), a_cfgForeground);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, std::tstring_t());
#elif xOS_ENV_UNIX
    xCHECK_DO(true == a_cbIsUnderline, sRv += CxString::sFormat(xT("\033[%im"), atUnderscore));
    xCHECK_DO(true == a_cbIsBlink,     sRv += CxString::sFormat(xT("\033[%im"), atBlink)     );
    xCHECK_DO(true == a_cbIsBold,      sRv += CxString::sFormat(xT("\033[%im"), atBold)      );

    sRv += CxString::sFormat(xT("\033[%im"), a_cbgBackground);
    sRv += CxString::sFormat(xT("\033[%im"), a_cfgForeground);
    sRv += csText;
    sRv += xT("\033[0;0m");
#endif

    return sRv;
}
//---------------------------------------------------------------------------
std::tstring_t
CxConsole::sRead() {
    std::tstring_t sRv;

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               std::tstring_t());
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  std::tstring_t());
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), std::tstring_t());

    ulong_t       ulRead                  = 0UL;
    const ulong_t culBuffSize             = 1024UL * 4UL;
    tchar_t       szBuff[culBuffSize + 1] = {0};

    BOOL blRes = ::ReadConsole(_m_hStdIn.hGet(), &szBuff[0], culBuffSize, &ulRead, NULL);
    /*DEBUG*/xASSERT_RET(FALSE != blRes,  std::tstring_t());
    /*DEBUG*/xASSERT_RET(NULL  != szBuff, std::tstring_t());

    sRv.assign(szBuff, ulRead - CxConst::xCRNL.size());
#elif xOS_ENV_UNIX
    std::tcin >> sRv;
#endif

    return sRv;
}
//---------------------------------------------------------------------------
bool
CxConsole::bWrite(
    const std::tstring_t &a_csStr
)
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), false);

    ulong_t ulWritten = 0UL;

    BOOL blRes = ::WriteConsole(_m_hStdOut.hGet(), &a_csStr.at(0), a_csStr.size(), &ulWritten, NULL);
    /*DEBUG*/xASSERT_RET(FALSE     != blRes,          false);
    /*DEBUG*/xASSERT_RET(ulWritten == a_csStr.size(), false);
#elif xOS_ENV_UNIX
    std::tcout << a_csStr;
#endif

    std::tcout.flush();

    return true;
}
//---------------------------------------------------------------------------
bool
CxConsole::bWriteLine(
    const std::tstring_t &a_csStr /* = xT("") */
)
{
#if xOS_ENV_WIN
    //TODO: xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), false);
#endif

    bool bRv = bWrite(a_csStr + CxConst::xNL);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxConsole::bWriteErrLine(
    const std::tstring_t &a_csStr
)
{
#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), false);
#endif

    bool bRv = bWriteLine(xT("Error: ") + a_csStr);
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    bRv = bPause();
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
CxConsole::ExModalResult
CxConsole::iMsgBox(
    const std::tstring_t &a_csText,
    const std::tstring_t &a_csTitle,
    const uint_t          a_cuiType
)
{
    ExModalResult mrRes;

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    bWriteLine();
    bWriteLine(xT("################################################################################"));
    bWriteLine(xT("#  ") + a_csTitle);
    bWriteLine(xT("#"));
    bWriteLine(xT("#  ") + a_csText);
    bWriteLine(xT("#"));
    bWriteLine(xT("################################################################################"));
    bWriteLine();
    bWrite(CxString::sFormat(xT("\nAbort (%c), Ignore (%c), Retry (%c): "), cmAbort, cmIgnore, cmRetry));

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
    switch (cmRes) {
        case cmAbort:  { mrRes = mrAbort;  bWriteLine(xT("Abort..."));  } break;
        case cmIgnore: { mrRes = mrIgnore; bWriteLine(xT("Ignore...")); } break;
        case cmRetry:  { mrRes = mrRetry;  bWriteLine(xT("Retry..."));  } break;

        default:       { mrRes = mrRetry;  bWriteLine(xT("Retry..."));  } break;
    }

    return mrRes;
}
//---------------------------------------------------------------------------
bool
CxConsole::bPrompt(
    const std::tstring_t &a_csPrompt,
    const bool            a_cbIsVisible,
    std::tstring_t       *a_psAnswer
)
{
    /*DEBUG*/xASSERT_RET(false == a_csPrompt.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_psAnswer,         false);

    for ( ; ; ) {
        bool bRv = bWrite(a_csPrompt + xT(": "));
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        for ( ; ; ) {
            const tchar_t chLetter = static_cast<tchar_t>( std::tcin.get() );

            // asterisks
            xCHECK_DO(true == a_cbIsVisible, bWrite(xT("*")));

            // ENTER
            xCHECK_DO(10 == chLetter, break);

            // BACKSPACE
            xCHECK_DO(0x8 == chLetter, (*a_psAnswer).clear(); continue);

            (*a_psAnswer).push_back(chLetter);
        }

        bRv = bWriteLine(CxConst::xSTR_EMPTY);
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        xCHECK_DO(true == (*a_psAnswer).empty(), continue);

        break;
    }

    return true;
}
//---------------------------------------------------------------------------
bool
CxConsole::bPause() {
    /*DEBUG*/

#if xTODO
    #if   xOS_ENV_UNIX
        std::tcout << std::endl << "Press any key to continue..." << std::endl;

        ::FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        _getch();
    #elif xOS_ENV_UNIX
        std::tcout << std::endl << "Press ENTER to continue..." << std::endl;

        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    #endif
#endif

    bool bRv = bWrite(xT("Press [ENTER] to continue..."));
    /*DEBUG*/xASSERT_RET(true == bRv, false);

    std::cin.clear();
    std::cin.ignore();

    return true;
}
//---------------------------------------------------------------------------
bool
CxConsole::bClear() {
    /*DEBUG*/

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), false);

    COORD                      coordScreen   = {0};     //here's where we'll home the cursor
    ulong_t                    cCharsWritten = 0UL;
    CONSOLE_SCREEN_BUFFER_INFO csbi          = {{0}};   //to get buffer info
    ulong_t                    ulConSize     = 0UL;     //number of character cells in the current buffer

    //get the number of character cells in the current buffer
    BOOL blRes = ::GetConsoleScreenBufferInfo(_m_hStdOut.hGet(), &csbi);
    /*DEBUG*/xASSERT_RET(FALSE != blRes,  false);

    ulConSize = csbi.dwSize.X * csbi.dwSize.Y;

    //fill the entire screen with blanks
    blRes = ::FillConsoleOutputCharacter(_m_hStdOut.hGet(), (tchar_t)xT(' '), ulConSize, coordScreen, &cCharsWritten);
    /*DEBUG*/xASSERT_RET(FALSE != blRes,  false);

    //get the current text attribute
    blRes = ::GetConsoleScreenBufferInfo(_m_hStdOut.hGet(), &csbi);
    /*DEBUG*/xASSERT_RET(FALSE != blRes,  false);

    //now set the buffer's attributes accordingly
    blRes = ::FillConsoleOutputAttribute(_m_hStdOut.hGet(), csbi.wAttributes, ulConSize, coordScreen, &cCharsWritten);
    /*DEBUG*/xASSERT_RET(FALSE != blRes,  false);

    //put the cursor at (0, 0)
    blRes = ::SetConsoleCursorPosition(_m_hStdOut.hGet(), coordScreen );
    /*DEBUG*/xASSERT_RET(FALSE != blRes,  false);
#elif xOS_ENV_UNIX
    bool bRv = bWriteLine(CxConst::xFF);
    /*DEBUG*/xASSERT_RET(true == bRv,  false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxConsole::bEnableClose(
    const bool a_cbFlag
)
{
    /*DEBUG*/

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), false);

    _m_hMenu = _hGetMenuHandle(false);
    /*DEBUG*/xASSERT_RET(NULL != _m_hMenu, false);

    if (false == a_cbFlag) {
        xCHECK_RET(false == ::DeleteMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND), false);
    } else {
        xCHECK_RET(false == ::AppendMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND, xT("")), false);

        BOOL bRv = ::EnableMenuItem(_hGetMenuHandle(false), SC_CLOSE, MF_ENABLED);
        /*DEBUG*/xASSERT_RET(TRUE != bRv, false);

        ::SetWindowPos(_hGetWndHandle(), NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME);
    }
#elif xOS_ENV_UNIX
    //TODO: bEnableClose
    xNOT_IMPLEMENTED_RET(false);
#endif

    return true;
}
//---------------------------------------------------------------------------
std::tstring_t
CxConsole::sGetTitle() {
    /*DEBUG*/

    std::tstring_t sRv;

#if xOS_ENV_WIN
    /*DEBUG*///_m_hWnd - n/a
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  std::tstring_t());
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), std::tstring_t());

    const ulong_t culBuffSize             = 1024UL;
    tchar_t       szBuff[culBuffSize + 1] = {0};
    ulong_t       ulTitleSize             = 0UL;

    ulTitleSize = ::GetConsoleTitle(szBuff, culBuffSize);
    /*DEBUG*/xASSERT_RET(0 < ulTitleSize, std::tstring_t());

    sRv.assign(szBuff, ulTitleSize);
#elif xOS_ENV_UNIX
    //TODO: sGetTitle
    xNOT_IMPLEMENTED_RET(std::tstring_t());
#endif

    return sRv;
}
//---------------------------------------------------------------------------
bool
CxConsole::bSetTitle(
    const std::tstring_t &a_csTitle
)
{
    /*DEBUG*/

#if xOS_ENV_WIN
    /*DEBUG*///_m_hWnd - n/a
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), false);

    BOOL blRes = ::SetConsoleTitle(a_csTitle.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    //TODO: bSetTitle

    bool bRv = bWriteLine( CxString::sFormat(xT("%c]0;%s%c"), xT('\033'), a_csTitle.c_str(), xT('\007')) );
    /*DEBUG*/xASSERT_RET(true == bRv,  false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxConsole::bSetFullScreen() {
    /*DEBUG*/

#if xOS_ENV_WIN
    //TODO: xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), false);

    COORD crdCoord = ::GetLargestConsoleWindowSize(_m_hStdOut.hGet());
    xCHECK_RET(crdCoord.X == 0 && crdCoord.Y == 0, false);

    crdCoord.X -= 2;
    crdCoord.Y -= 2;

    SMALL_RECT recSmallRec = {0};
    recSmallRec.Left   = 0;
    recSmallRec.Top    = 0;
    recSmallRec.Right  = crdCoord.X - 2;
    recSmallRec.Bottom = crdCoord.Y - 2;

    BOOL blRes = ::SetConsoleScreenBufferSize(_m_hStdOut.hGet(), crdCoord);
    /*DEBUG*/xASSERT_RET(FALSE != blRes,  false);

    blRes = ::SetConsoleWindowInfo(_m_hStdOut.hGet(), true, &recSmallRec);
    /*DEBUG*/xASSERT_RET(FALSE != blRes,  false);

    bool bRv = bCenterWindow();
    /*DEBUG*/xASSERT_RET(true == bRv,  false);
#elif xOS_ENV_UNIX
    //TODO: bSetFullScreen
    xNOT_IMPLEMENTED_RET(false);
#endif
    return true;
}
//---------------------------------------------------------------------------
bool
CxConsole::bCenterWindow() {
    /*DEBUG*/

#if xOS_ENV_WIN
    /*DEBUG*/xASSERT_RET(NULL  != _m_hWnd,               false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdIn.bIsValid(),  false);
    /*DEBUG*/xASSERT_RET(false != _m_hStdOut.bIsValid(), false);

    BOOL blRes = FALSE;

    RECT rcOrigin = {0};
    blRes = ::GetWindowRect(_m_hWnd, &rcOrigin);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    RECT rcDesktop = {0};
    blRes = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);

    int iDesktopX  = (rcDesktop.right  - rcDesktop.left) / 2;
    int iDesktopY  = (rcDesktop.bottom - rcDesktop.top)  / 2;
    int iWndWidth  = (rcOrigin.right   - rcOrigin.left);
    int iWndHeight = (rcOrigin.bottom  - rcOrigin.top);
    int X          = iDesktopX - iWndWidth / 2;        if (X < 0) {X = 0;}

    blRes = ::MoveWindow(_m_hWnd, X, iDesktopY - iWndHeight / 2, iWndWidth, iWndHeight, true);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    //TODO: bCenterWindow
    xNOT_IMPLEMENTED_RET(false);
#endif

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if xOS_ENV_WIN

HWND
CxConsole::_hGetWndHandle() {
    /*DEBUG*/

    HWND         hRv         = NULL;
    bool         bRv         = false;
    std::tstring_t sNewWndTitle;
    std::tstring_t sOldWndTitle;

    //Fetch current window title.
    sOldWndTitle = sGetTitle();
    /*DEBUG*/xASSERT_RET(false == sOldWndTitle.empty(), NULL);

    //Format a "unique" szNewWndTitle.
    sNewWndTitle = CxString::sFormat(xT("%lu/%lu"), ::GetTickCount(), CxCurrentProcess::ulGetId());

    //Change current window title.
    bRv = bSetTitle(sNewWndTitle);
    /*DEBUG*/xASSERT_RET(true == bRv, NULL);

    //Ensure window title has been updated.
    CxCurrentThread::bSleep(50UL);

    //Look for NewWindowTitle.
    hRv = ::FindWindow(NULL, sNewWndTitle.c_str());
    /*DEBUG*/xASSERT_RET(NULL != hRv, NULL);

    //Restore original window title.
    bRv = bSetTitle(sOldWndTitle);
    /*DEBUG*/xASSERT_RET(true == bRv, NULL);

    return hRv;
}

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

HMENU
CxConsole::_hGetMenuHandle(
    const bool a_cbRevert
)
{
    /*DEBUG*/

    _m_hMenu = ::GetSystemMenu(_m_hWnd, a_cbRevert);
    /*DEBUG*/if (false == a_cbRevert) { xASSERT_RET(NULL != _m_hMenu, NULL); }
    /*DEBUG*/if (true  == a_cbRevert) { xASSERT_RET(NULL == _m_hMenu, NULL); }

    return _m_hMenu;
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
