/**
 * \file  CxConsole.cpp
 * \brief console
 */


#include <xLib/Common/CxConsole.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
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
#if   xOS_ENV_WIN
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
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_hStdIn.hGet());

    _m_hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    xTEST_EQ(true, _m_hStdOut.bIsValid());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_hStdOut.hGet());

    _m_hWnd = _hWndHandle();
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);

    //_m_hMenu - n/a
#endif
}
//---------------------------------------------------------------------------
CxConsole::~CxConsole() {
#if   xOS_ENV_WIN
    (void)_m_hStdIn.hDetach();
    (void)_m_hStdOut.hDetach();
#endif
}
//---------------------------------------------------------------------------
//NOTE: http://lifeforce4.wordpress.com/, http://lifeforce4.wordpress.com/
std::tstring_t
CxConsole::sSetTextColor(
    const std::tstring_t &a_csText,
    const ExForeground   &a_cfgForeground,
    const bool           &a_cbIsBold,
    const bool           &a_cbIsUnderline,
    const ExBackground   &a_cbgBackground,
    const bool           &a_cbIsBlink
)
{
    // n/a

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    BOOL blRes = ::SetConsoleTextAttribute(_m_hStdOut.hGet(), a_cfgForeground);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    xCHECK_DO(true == a_cbIsUnderline, sRv += CxString::sFormat(xT("\033[%im"), atUnderscore));
    xCHECK_DO(true == a_cbIsBlink,     sRv += CxString::sFormat(xT("\033[%im"), atBlink)     );
    xCHECK_DO(true == a_cbIsBold,      sRv += CxString::sFormat(xT("\033[%im"), atBold)      );

    sRv += CxString::sFormat(xT("\033[%im"), a_cbgBackground);
    sRv += CxString::sFormat(xT("\033[%im"), a_cfgForeground);
    sRv += a_csText;
    sRv += xT("\033[0;0m");
#endif

    return sRv;
}
//---------------------------------------------------------------------------
std::tstring_t
CxConsole::sRead() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    ulong_t       ulRead                  = 0UL;
    const ulong_t culBuffSize             = 1024UL * 4UL;
    tchar_t       szBuff[culBuffSize + 1] = {0};

    BOOL blRes = ::ReadConsole(_m_hStdIn.hGet(), &szBuff[0], culBuffSize, &ulRead, NULL);
    xTEST_DIFF(FALSE, blRes);
    xTEST_PTR(szBuff);

    sRv.assign(szBuff, ulRead - CxConst::xCRNL.size());
#elif xOS_ENV_UNIX
    std::tcin >> sRv;
#endif

    return sRv;
}
//---------------------------------------------------------------------------
void
CxConsole::vWrite(
    const std::tstring_t &a_csStr
)
{
#if   xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    ulong_t ulWritten = 0UL;

    BOOL blRes = ::WriteConsole(_m_hStdOut.hGet(), &a_csStr.at(0), a_csStr.size(), &ulWritten, NULL);
    xTEST_DIFF(FALSE, blRes);
    xTEST_EQ(static_cast<size_t>( ulWritten ), a_csStr.size());
#elif xOS_ENV_UNIX
    std::tcout << a_csStr;
#endif

    std::tcout.flush();
}
//---------------------------------------------------------------------------
void
CxConsole::vWriteLine(
    const std::tstring_t &a_csStr /* = xT("") */
)
{
#if xOS_ENV_WIN
    //TODO: xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());
#endif

    vWrite(a_csStr + CxConst::xNL);
}
//---------------------------------------------------------------------------
void
CxConsole::vWriteErrLine(
    const std::tstring_t &a_csStr
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());
#endif

    vWriteLine(xT("Error: ") + a_csStr);
    vPause();
}
//---------------------------------------------------------------------------
CxConsole::ExModalResult
CxConsole::iMsgBox(
    const std::tstring_t &a_csText,
    const std::tstring_t &a_csTitle,
    const uint_t         &a_cuiType
)
{
    ExModalResult mrRes;

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    vWriteLine();
    vWriteLine(xT("################################################################################"));
    vWriteLine(xT("#  ") + a_csTitle);
    vWriteLine(xT("#"));
    vWriteLine(xT("#  ") + a_csText);
    vWriteLine(xT("#"));
    vWriteLine(xT("################################################################################"));
    vWriteLine();
    vWrite(CxString::sFormat(xT("\nAbort (%c), Ignore (%c), Retry (%c): "), cmAbort, cmIgnore, cmRetry));

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
    switch (cmRes) {
        case cmAbort:  { mrRes = mrAbort;  vWriteLine(xT("Abort..."));  } break;
        case cmIgnore: { mrRes = mrIgnore; vWriteLine(xT("Ignore...")); } break;
        case cmRetry:  { mrRes = mrRetry;  vWriteLine(xT("Retry..."));  } break;

        default:       { mrRes = mrRetry;  vWriteLine(xT("Retry..."));  } break;
    }

    return mrRes;
}
//---------------------------------------------------------------------------
void
CxConsole::vPrompt(
    const std::tstring_t &a_csPrompt,
    const bool           &a_cbIsVisible,
    std::tstring_t       *a_psAnswer
)
{
    xTEST_EQ(false, a_csPrompt.empty());
    xTEST_PTR(a_psAnswer);

    for ( ; ; ) {
        vWrite(a_csPrompt + xT(": "));

        for ( ; ; ) {
            const tchar_t chLetter = static_cast<tchar_t>( std::tcin.get() );

            // asterisks
            xCHECK_DO(true == a_cbIsVisible, vWrite(xT("*")));

            // ENTER
            xCHECK_DO(10 == chLetter, break);

            // BACKSPACE
            xCHECK_DO(0x8 == chLetter, (*a_psAnswer).clear(); continue);

            (*a_psAnswer).push_back(chLetter);
        }

        vWriteLine(CxConst::xSTR_EMPTY);

        xCHECK_DO(true == (*a_psAnswer).empty(), continue);

        break;
    }
}
//---------------------------------------------------------------------------
void
CxConsole::vPause() {
    

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

    vWrite(xT("Press [ENTER] to continue..."));

    std::cin.clear();
    std::cin.ignore();
}
//---------------------------------------------------------------------------
void
CxConsole::vClear() {
    

#if   xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    COORD                      coordScreen   = {0};     //here's where we'll home the cursor
    ulong_t                    cCharsWritten = 0UL;
    CONSOLE_SCREEN_BUFFER_INFO csbi          = {{0}};   //to get buffer info
    ulong_t                    ulConSize     = 0UL;     //number of character cells in the current buffer

    //get the number of character cells in the current buffer
    BOOL blRes = ::GetConsoleScreenBufferInfo(_m_hStdOut.hGet(), &csbi);
    xTEST_DIFF(FALSE, blRes);

    ulConSize = csbi.dwSize.X * csbi.dwSize.Y;

    //fill the entire screen with blanks
    blRes = ::FillConsoleOutputCharacter(_m_hStdOut.hGet(), (tchar_t)xT(' '), ulConSize, coordScreen, &cCharsWritten);
    xTEST_DIFF(FALSE, blRes);

    //get the current text attribute
    blRes = ::GetConsoleScreenBufferInfo(_m_hStdOut.hGet(), &csbi);
    xTEST_DIFF(FALSE, blRes);

    //now set the buffer's attributes accordingly
    blRes = ::FillConsoleOutputAttribute(_m_hStdOut.hGet(), csbi.wAttributes, ulConSize, coordScreen, &cCharsWritten);
    xTEST_DIFF(FALSE, blRes);

    //put the cursor at (0, 0)
    blRes = ::SetConsoleCursorPosition(_m_hStdOut.hGet(), coordScreen );
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    vWriteLine(CxConst::xFF);
#endif
}
//---------------------------------------------------------------------------
void
CxConsole::vEnableClose(
    const bool &a_cbFlag
)
{
    

#if   xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    _m_hMenu = _hMenuHandle(false);
    xTEST_EQ(true, NULL != _m_hMenu);

    if (false == a_cbFlag) {
        BOOL blRv = ::DeleteMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND);
        xTEST_DIFF(FALSE, blRv);
    } else {
        BOOL blRv = ::AppendMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND, xT(""));
        xTEST_DIFF(FALSE, blRv);

        BOOL bRv = ::EnableMenuItem(_hMenuHandle(false), SC_CLOSE, MF_ENABLED);
        xTEST_DIFF(TRUE, bRv);

        ::SetWindowPos(_hWndHandle(), NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME);
    }
#elif xOS_ENV_UNIX
    //TODO: bEnableClose
    xNOT_IMPLEMENTED;
#endif
}
//---------------------------------------------------------------------------
std::tstring_t
CxConsole::sTitle() {
    

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    //_m_hWnd - n/a
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    const ulong_t culBuffSize             = 1024UL;
    tchar_t       szBuff[culBuffSize + 1] = {0};
    ulong_t       ulTitleSize             = 0UL;

    ulTitleSize = ::GetConsoleTitle(szBuff, culBuffSize);
    xTEST_LESS(0UL, ulTitleSize);

    sRv.assign(szBuff, ulTitleSize);
#elif xOS_ENV_UNIX
    //TODO: sGetTitle
    xNOT_IMPLEMENTED;
#endif

    return sRv;
}
//---------------------------------------------------------------------------
void
CxConsole::vSetTitle(
    const std::tstring_t &a_csTitle
)
{
    

#if   xOS_ENV_WIN
    //_m_hWnd - n/a
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    BOOL blRes = ::SetConsoleTitle(a_csTitle.c_str());
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    //TODO: bSetTitle

    vWriteLine( CxString::sFormat(xT("%c]0;%s%c"), xT('\033'), a_csTitle.c_str(), xT('\007')) );
#endif
}
//---------------------------------------------------------------------------
void
CxConsole::vSetFullScreen() {
    

#if   xOS_ENV_WIN
    //TODO: xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    COORD crdCoord = ::GetLargestConsoleWindowSize(_m_hStdOut.hGet());
    xTEST_EQ(true, 0 == crdCoord.X && 0 == crdCoord.Y);

    crdCoord.X -= 2;
    crdCoord.Y -= 2;

    SMALL_RECT recSmallRec = {0};
    recSmallRec.Left   = 0;
    recSmallRec.Top    = 0;
    recSmallRec.Right  = crdCoord.X - 2;
    recSmallRec.Bottom = crdCoord.Y - 2;

    BOOL blRes = ::SetConsoleScreenBufferSize(_m_hStdOut.hGet(), crdCoord);
    xTEST_DIFF(FALSE, blRes);

    blRes = ::SetConsoleWindowInfo(_m_hStdOut.hGet(), true, &recSmallRec);
    xTEST_DIFF(FALSE, blRes);

    vCenterWindow();
#elif xOS_ENV_UNIX
    //TODO: vSetFullScreen
    xNOT_IMPLEMENTED;
#endif
}
//---------------------------------------------------------------------------
void
CxConsole::vCenterWindow() {
    

#if   xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.bIsValid());
    xTEST_EQ(true, _m_hStdOut.bIsValid());

    BOOL blRes = FALSE;

    RECT rcOrigin = {0};
    blRes = ::GetWindowRect(_m_hWnd, &rcOrigin);
    xTEST_DIFF(FALSE, blRes);

    RECT rcDesktop = {0};
    blRes = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    xTEST_DIFF(FALSE, blRes);

    int iDesktopX  = (rcDesktop.right  - rcDesktop.left) / 2;
    int iDesktopY  = (rcDesktop.bottom - rcDesktop.top)  / 2;
    int iWndWidth  = (rcOrigin.right   - rcOrigin.left);
    int iWndHeight = (rcOrigin.bottom  - rcOrigin.top);
    int X          = iDesktopX - iWndWidth / 2;        if (X < 0) { X = 0; }

    blRes = ::MoveWindow(_m_hWnd, X, iDesktopY - iWndHeight / 2, iWndWidth, iWndHeight, true);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    // TODO: vCenterWindow
    xNOT_IMPLEMENTED;
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

HWND
CxConsole::_hWndHandle() {
    

    HWND           hRv = NULL;
    std::tstring_t sNewWndTitle;
    std::tstring_t sOldWndTitle;

    //Fetch current window title.
    sOldWndTitle = sTitle();
    xTEST_EQ(false, sOldWndTitle.empty());

    //Format a "unique" szNewWndTitle.
    sNewWndTitle = CxString::sFormat(xT("%lu/%lu"), ::GetTickCount(), CxCurrentProcess::ulId());

    //Change current window title.
    vSetTitle(sNewWndTitle);

    //Ensure window title has been updated.
    CxCurrentThread::vSleep(50UL);

    //Look for NewWindowTitle.
    hRv = ::FindWindow(NULL, sNewWndTitle.c_str());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, hRv);

    //Restore original window title.
    vSetTitle(sOldWndTitle);

    return hRv;
}

#endif
//---------------------------------------------------------------------------
#if   xOS_ENV_WIN

HMENU
CxConsole::_hMenuHandle(
    const bool &a_cbRevert
)
{
    

    _m_hMenu = ::GetSystemMenu(_m_hWnd, a_cbRevert);
    if (false == a_cbRevert) { xTEST_EQ(true, NULL != _m_hMenu); }
    if (true  == a_cbRevert) { xTEST_EQ(true, NULL == _m_hMenu); }

    return _m_hMenu;
}

#endif
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
