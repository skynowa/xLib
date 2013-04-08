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

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxConsole::CxConsole()
#if xOS_ENV_WIN
    :
    _m_hWnd          (NULL),
    _m_hMenu         (NULL),
    _m_hStdIn        (),
    _m_hStdOut       (),
    _m_wAttributesDef(0)
#endif
{
#if xOS_ENV_WIN
    _m_hStdIn = ::GetStdHandle(STD_INPUT_HANDLE);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_hStdIn.get());

    _m_hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    xTEST_EQ(true, _m_hStdOut.isValid());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _m_hStdOut.get());

    // _m_wAttributesDef
    {
        CONSOLE_SCREEN_BUFFER_INFO csbInfo = {};

        BOOL blRv = ::GetConsoleScreenBufferInfo(_m_hStdOut.get(), &csbInfo);
        xTEST_DIFF(FALSE, blRv);

        _m_wAttributesDef = csbInfo.wAttributes;
    }

    _m_hWnd = _wndHandle();
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);

    // _m_hMenu - n/a
#endif
}
//------------------------------------------------------------------------------
CxConsole::~CxConsole() {
#if xOS_ENV_WIN
    (native_handle_t)_m_hStdIn.detach();
    (native_handle_t)_m_hStdOut.detach();
#endif
}
//------------------------------------------------------------------------------
std::tstring_t
CxConsole::setAttributes(
    const ExForeground &a_cfgForeground,
    const ExBackground &a_cbgBackground,
    cint_t             &a_ciAttributes
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif
    // n/a

    //--------------------------------------------------
    ExForeground fgForegroundColor;

    {
    #if xOS_ENV_WIN
        /*
            #define COLOR_BLACK     0
            #define COLOR_BLUE      1
            #define COLOR_GREEN     2
            #define COLOR_AQUA      3
            #define COLOR_RED       4
            #define COLOR_PURPLE    5
            #define COLOR_YELLOW    6
            #define COLOR_WHITE     7
            #define COLOR_GRAY      8
            #define COLOR_LTBLUE    9
            #define COLOR_LTGREEN   A
            #define COLOR_LTAQUA    B
            #define COLOR_LTRED     C
            #define COLOR_LTPURPLE  D
            #define COLOR_LTYELLOW  E
            #define COLOR_LTWHITE   F
        */

        const WORD ciForegroundColorBlack   = 0;
        const WORD ciForegroundColorRed	    = FOREGROUND_RED;
        const WORD ciForegroundColorBlue	= FOREGROUND_BLUE;
        const WORD ciForegroundColorGreen   = FOREGROUND_GREEN;
        const WORD ciForegroundColorCyan	= FOREGROUND_GREEN | FOREGROUND_BLUE;
        const WORD ciForegroundColorMagenta = FOREGROUND_RED | FOREGROUND_BLUE;
        const WORD ciForegroundColorYellow  = FOREGROUND_RED | FOREGROUND_GREEN;
        const WORD ciForegroundColorWhite   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        const WORD ciForegroundColorGray	= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    #else
        cint_t  ciForegroundColorBlack      = 30;
        cint_t  ciForegroundColorRed        = 31;
        cint_t  ciForegroundColorBlue       = 34;
        cint_t  ciForegroundColorGreen      = 32;
        cint_t  ciForegroundColorCyan       = 36;
        cint_t  ciForegroundColorMagenta    = 35;
        cint_t  ciForegroundColorYellow     = 33;
        cint_t  ciForegroundColorWhite      = 37;
        cint_t  ciForegroundColorGray       = 37;    // TODO: ciForegroundColorGray
    #endif

        int_t iRv = - 1;

	    switch (a_cfgForeground) {
    	    case fgBlack:
    	        iRv = ciForegroundColorBlack;
    	        break;
		    case fgRed:
		        iRv = ciForegroundColorRed;
		        break;
		    case fgGreen:
		        iRv = ciForegroundColorGreen;
		        break;
		    case fgYellow:
		        iRv = ciForegroundColorYellow;
		        break;
    	    case fgBlue:
    	        iRv = ciForegroundColorBlue;
                break;
		    case fgMagenta:
		        iRv = ciForegroundColorMagenta;
		        break;
		    case fgCyan:
		        iRv = ciForegroundColorCyan;
		        break;
		    case fgWhite:
		        iRv = ciForegroundColorWhite;
		        break;
    	    case fgGray:
    	        iRv = ciForegroundColorGray;
    	        break;
            case fgUnknown:
    	    default:
    	        xTEST_FAIL;
    	        break;
        }

        fgForegroundColor = static_cast<ExForeground>( iRv );
    }

    //--------------------------------------------------
    ExBackground bgBackgroundColor;

    {
    #if xOS_ENV_WIN
        const WORD ciBackgroundColorBlack   = 0;
        const WORD ciBackgroundColorRed	    = BACKGROUND_RED;
        const WORD ciBackgroundColorBlue	= BACKGROUND_BLUE;
        const WORD ciBackgroundColorGreen   = BACKGROUND_GREEN;
        const WORD ciBackgroundColorCyan	= BACKGROUND_GREEN | BACKGROUND_BLUE;
        const WORD ciBackgroundColorMagenta = BACKGROUND_RED | BACKGROUND_BLUE;
        const WORD ciBackgroundColorYellow  = BACKGROUND_RED | BACKGROUND_GREEN;
        const WORD ciBackgroundColorWhite   = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        const WORD ciBackgroundColorGray	= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    #else
        cint_t  ciBackgroundColorBlack      = 40;
        cint_t  ciBackgroundColorRed	    = 41;
        cint_t  ciBackgroundColorBlue	    = 44;
        cint_t  ciBackgroundColorGreen      = 42;
        cint_t  ciBackgroundColorCyan	    = 46;
        cint_t  ciBackgroundColorMagenta    = 45;
        cint_t  ciBackgroundColorYellow     = 43;
        cint_t  ciBackgroundColorWhite      = 47;
        cint_t  ciBackgroundColorGray	    = 47;    // TODO: ciBackgroundColorGray
    #endif

        int_t iRv = - 1;

	    switch (a_cbgBackground) {
    	    case fgBlack:
                iRv = ciBackgroundColorBlack;
                break;
		    case fgRed:
                iRv = ciBackgroundColorRed;
                break;
		    case fgGreen:
                iRv = ciBackgroundColorGreen;
                break;
		    case fgYellow:
                iRv = ciBackgroundColorYellow;
                break;
    	    case fgBlue:
                iRv = ciBackgroundColorBlue;
                break;
		    case fgMagenta:
                iRv = ciBackgroundColorMagenta;
                break;
		    case fgCyan:
                iRv = ciBackgroundColorCyan;
                break;
		    case fgWhite:
                iRv = ciBackgroundColorWhite;
                break;
    	    case fgGray:
                iRv = ciBackgroundColorGray;
                break;
            case fgUnknown:
    	    default:
    	        xTEST_FAIL;
                break;
        }

        bgBackgroundColor = static_cast<ExBackground>( iRv );
    }

    //--------------------------------------------------
#if xOS_ENV_WIN
    WORD           wAttributes = 0U;
#else
    std::tstring_t sAttributes;
#endif

    {
    #if xOS_ENV_WIN
        const WORD ciAttributeAllOff     = 0;
        const WORD ciAttributeBold       = FOREGROUND_INTENSITY;
        const WORD ciAttributeUnderscore = COMMON_LVB_UNDERSCORE;     xUNUSED(ciAttributeUnderscore);   // not supported
        const WORD ciAttributeBlink      = - 1;                       xUNUSED(ciAttributeBlink);        // not supported
        const WORD ciAttributeReverse    = COMMON_LVB_REVERSE_VIDEO;  xUNUSED(ciAttributeReverse);      // not supported
        const WORD ciAttributeConcealed  = - 1;                       xUNUSED(ciAttributeConcealed);    // not supported
    #else
        cint_t  ciAttributeAllOff     = 0;
        cint_t  ciAttributeBold       = 1;
        cint_t  ciAttributeUnderscore = 4;
        cint_t  ciAttributeBlink      = 5;
        cint_t  ciAttributeReverse    = 7;
        cint_t  ciAttributeConcealed  = 8;
    #endif

    #if xOS_ENV_WIN
        wAttributes |= fgForegroundColor;
        wAttributes |= bgBackgroundColor;

        xCHECK_DO(a_ciAttributes & CxConsole::atAllOff,     wAttributes |= ciAttributeAllOff);
        xCHECK_DO(a_ciAttributes & CxConsole::atBold,       wAttributes |= ciAttributeBold);
        xCHECK_DO(a_ciAttributes & CxConsole::atUnderscore, /* wAttributes |= ciAttributeUnderscore */);   // not supported
        xCHECK_DO(a_ciAttributes & CxConsole::atBlink,      /* wAttributes |= ciAttributeBlink */);        // not supported
        xCHECK_DO(a_ciAttributes & CxConsole::atReverse,    /* wAttributes |= ciAttributeReverse */);      // not supported
        xCHECK_DO(a_ciAttributes & CxConsole::atConcealed,  /* wAttributes |= ciAttributeConcealed */);    // not supported
    #else
        sAttributes += CxString::format(xT("\033[%im"), fgForegroundColor);
        sAttributes += CxString::format(xT("\033[%im"), bgBackgroundColor);

        xCHECK_DO(a_ciAttributes & CxConsole::atAllOff,     sAttributes += CxString::format(xT("\033[%im"), ciAttributeAllOff));
        xCHECK_DO(a_ciAttributes & CxConsole::atBold,       sAttributes += CxString::format(xT("\033[%im"), ciAttributeBold));
        xCHECK_DO(a_ciAttributes & CxConsole::atUnderscore, sAttributes += CxString::format(xT("\033[%im"), ciAttributeUnderscore));
        xCHECK_DO(a_ciAttributes & CxConsole::atBlink,      sAttributes += CxString::format(xT("\033[%im"), ciAttributeBlink));
        xCHECK_DO(a_ciAttributes & CxConsole::atReverse,    sAttributes += CxString::format(xT("\033[%im"), ciAttributeReverse));
        xCHECK_DO(a_ciAttributes & CxConsole::atConcealed,  sAttributes += CxString::format(xT("\033[%im"), ciAttributeConcealed));
    #endif
    }

#if xOS_ENV_WIN
    BOOL blRes = ::SetConsoleTextAttribute(_m_hStdOut.get(), wAttributes);
    xTEST_DIFF(FALSE, blRes);

    return std::tstring_t();    // not need for Windows
#else
    return sAttributes;
#endif
}
//------------------------------------------------------------------------------
std::tstring_t
CxConsole::setAttributesDef() {
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif
    // n/a

    std::tstring_t sRv;

#if xOS_ENV_WIN
    BOOL blRes = ::SetConsoleTextAttribute(_m_hStdOut.get(), _m_wAttributesDef);
    xTEST_DIFF(FALSE, blRes);

    xUNUSED(sRv);
#else
    sRv = xT("\033[0;0m");
#endif

    return sRv;
}
//------------------------------------------------------------------------------
std::tstring_t
CxConsole::read() {
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

    std::tstring_t sRv;

#if xOS_ENV_WIN
    DWORD    ulRead                  = 0UL;
    culong_t culBuffSize             = 1024UL * 4UL;
    tchar_t  szBuff[culBuffSize + 1] = {0};

    BOOL blRes = ::ReadConsole(_m_hStdIn.get(), &szBuff[0], culBuffSize, &ulRead, NULL);
    xTEST_DIFF(FALSE, blRes);

    sRv.assign(szBuff, ulRead - CxConst::xCRNL.size());
#else
    // BUG: CxConsole::read
    std::tcin >> sRv;
#endif

    return sRv;
}
//------------------------------------------------------------------------------
void_t
CxConsole::write(
    std::ctstring_t &a_csStr
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

#if xOS_ENV_WIN
    DWORD dwWritten = 0UL;

    BOOL blRes = ::WriteConsole(
                    _m_hStdOut.get(),
                    &a_csStr.at(0), static_cast<DWORD>( a_csStr.size() ),
                    &dwWritten, NULL);
    xTEST_DIFF(FALSE, blRes);
    xTEST_EQ(static_cast<size_t>( dwWritten ), a_csStr.size());
#else
    std::tcout << a_csStr;
#endif

    std::tcout.flush();
}
//------------------------------------------------------------------------------
void_t
CxConsole::writeLine(
    std::ctstring_t &a_csStr /* = xT("") */
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

    write(a_csStr + CxConst::xNL);
}
//------------------------------------------------------------------------------
void_t
CxConsole::writeErrLine(
    std::ctstring_t &a_csStr
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

    writeLine(xT("Error: ") + a_csStr);

    pause(xTIMEOUT_INFINITE);
}
//------------------------------------------------------------------------------
CxConsole::ExModalResult
CxConsole::msgBox(
    std::ctstring_t &a_csText,
    std::ctstring_t &a_csTitle,
    cuint_t         &a_cuiType
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

    ExModalResult mrRes;

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    writeLine();
    writeLine(xT("################################################################################"));
    writeLine(xT("#  ") + a_csTitle);
    writeLine(xT("#"));
    writeLine(xT("#  ") + a_csText);
    writeLine(xT("#"));
    writeLine(xT("################################################################################"));
    writeLine();
    write(CxString::format(xT("\nAbort (%c), Ignore (%c), Retry (%c): "), cmAbort, cmIgnore, cmRetry));

    EConsoleCmd cmRes = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
    switch (cmRes) {
        case cmAbort:
            mrRes = mrAbort;
            writeLine(xT("Abort..."));
            break;
        case cmIgnore:
            mrRes = mrIgnore;
            writeLine(xT("Ignore..."));
            break;
        case cmRetry:
            mrRes = mrRetry;
            writeLine(xT("Retry..."));
            break;
        default:
            mrRes = mrRetry;
            writeLine(xT("Retry..."));
            break;
    }

    return mrRes;
}
//------------------------------------------------------------------------------
void_t
CxConsole::prompt(
    std::ctstring_t &a_csPrompt,
    cbool_t         &a_cbIsVisible,
    std::tstring_t  *a_psAnswer
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

    xTEST_EQ(false, a_csPrompt.empty());
    xTEST_PTR(a_psAnswer);

    xFOREVER {
        write(a_csPrompt + xT(": "));

        xFOREVER {
            ctchar_t chLetter = static_cast<tchar_t>( std::tcin.get() );

            // asterisks
            xCHECK_DO(a_cbIsVisible, write(xT("*")));

            // ENTER
            xCHECK_DO(10 == chLetter, break);

            // BACKSPACE
            xCHECK_DO(0x8 == chLetter, (*a_psAnswer).clear(); continue);

            (*a_psAnswer).push_back(chLetter);
        }

        writeLine(CxConst::xSTR_EMPTY);

        xCHECK_DO((*a_psAnswer).empty(), continue);

        break;
    }
}
//------------------------------------------------------------------------------
void_t
CxConsole::pause(
    culong_t &a_culTimeoutMs
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

    // TODO: CxConsole::pause
#if xTODO
    #if xOS_ENV_UNIX
        std::tcout << std::endl << "Press any key to continue..." << std::endl;

        ::FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        _getch();
    #else
        std::tcout << std::endl << "Press ENTER to continue..." << std::endl;

        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    #endif
#endif

    std::tstring_t sMsg;

	if (xTIMEOUT_INFINITE == a_culTimeoutMs) {
        sMsg = xT("Pause, press [ENTER] to continue...");

        writeLine(sMsg);

        std::cin.clear();
        std::cin.ignore();
	} else {
        sMsg = CxString::format(xT("Pause, wait for %lu msec to continue..."), a_culTimeoutMs);

        writeLine(sMsg);

		CxCurrentThread::sleep(a_culTimeoutMs);
	}
}
//------------------------------------------------------------------------------
void_t
CxConsole::clear() {
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

#if xOS_ENV_WIN
    COORD                      coordScreen   = {0};     // here's where we'll home the cursor
    DWORD                      cCharsWritten = 0UL;
    CONSOLE_SCREEN_BUFFER_INFO csbi          = {{0}};   // to get buffer info
    DWORD                      ulConSize     = 0UL;     // number of character cells in the current buffer

    // get the number of character cells in the current buffer
    BOOL blRes = ::GetConsoleScreenBufferInfo(_m_hStdOut.get(), &csbi);
    xTEST_DIFF(FALSE, blRes);

    ulConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // fill the entire screen with blanks
    blRes = ::FillConsoleOutputCharacter(_m_hStdOut.get(), xT(' '), ulConSize, coordScreen, &cCharsWritten);
    xTEST_DIFF(FALSE, blRes);

    // get the current text attribute
    blRes = ::GetConsoleScreenBufferInfo(_m_hStdOut.get(), &csbi);
    xTEST_DIFF(FALSE, blRes);

    // now set the buffer's attributes accordingly
    blRes = ::FillConsoleOutputAttribute(_m_hStdOut.get(), csbi.wAttributes, ulConSize, coordScreen, &cCharsWritten);
    xTEST_DIFF(FALSE, blRes);

    // put the cursor at (0, 0)
    blRes = ::SetConsoleCursorPosition(_m_hStdOut.get(), coordScreen );
    xTEST_DIFF(FALSE, blRes);
#else
    writeLine(CxConst::xFF);
#endif
}
//------------------------------------------------------------------------------
void_t
CxConsole::enableClose(
    cbool_t &a_cbFlag
)
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

#if xOS_ENV_WIN
    _m_hMenu = _menuHandle(false);
    xTEST_EQ(true, NULL != _m_hMenu);

    if (!a_cbFlag) {
        BOOL blRv = ::DeleteMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND);
        xTEST_DIFF(FALSE, blRv);
    } else {
        BOOL blRv = ::AppendMenu(_m_hMenu, SC_CLOSE, MF_BYCOMMAND, xT(""));
        xTEST_DIFF(FALSE, blRv);

        blRv = ::EnableMenuItem(_menuHandle(false), SC_CLOSE, MF_ENABLED);
        xTEST_DIFF(TRUE, blRv);

        blRv = ::SetWindowPos(_wndHandle(), NULL, 0, 0, 0, 0,
                              SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_DRAWFRAME);
        xTEST_DIFF(FALSE, blRv);
    }
#else
    // TODO: vEnableClose
    xNOT_IMPLEMENTED;
#endif
}
//------------------------------------------------------------------------------
std::tstring_t
CxConsole::title() {
#if xOS_ENV_WIN
    xTEST_NA(_m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

    std::tstring_t sRv;

#if xOS_ENV_WIN
    const DWORD cdwBuffSize             = 1024UL;
    tchar_t     szBuff[cdwBuffSize + 1] = {0};
    DWORD       dwTitleSize             = 0UL;

    dwTitleSize = ::GetConsoleTitle(szBuff, cdwBuffSize);
    xTEST_LESS(0UL, dwTitleSize);

    sRv.assign(szBuff, dwTitleSize);
#else
    // TODO: sTitle
    xNOT_IMPLEMENTED;
#endif

    return sRv;
}
//------------------------------------------------------------------------------
void_t
CxConsole::setTitle(
    std::ctstring_t &a_csTitle
)
{
#if xOS_ENV_WIN
    xTEST_NA(_m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

#if xOS_ENV_WIN
    BOOL blRes = ::SetConsoleTitle(a_csTitle.c_str());
    xTEST_DIFF(FALSE, blRes);
#else
    // TODO: vSetTitle
    writeLine( CxString::format(xT("%c]0;%s%c"), xT('\033'), a_csTitle.c_str(), xT('\007')) );
#endif
}
//------------------------------------------------------------------------------
void_t
CxConsole::setFullScreen() {
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

#if xOS_ENV_WIN
    COORD crdCoord = ::GetLargestConsoleWindowSize(_m_hStdOut.get());
    xTEST_EQ(true, 0 != crdCoord.X && 0 != crdCoord.Y);

    crdCoord.X -= 2;
    crdCoord.Y -= 2;

    SMALL_RECT recSmallRec = {0};
    recSmallRec.Left   = 0;
    recSmallRec.Top    = 0;
    recSmallRec.Right  = crdCoord.X - 2;
    recSmallRec.Bottom = crdCoord.Y - 2;

    BOOL blRes = ::SetConsoleScreenBufferSize(_m_hStdOut.get(), crdCoord);
    xTEST_DIFF(FALSE, blRes);

    blRes = ::SetConsoleWindowInfo(_m_hStdOut.get(), true, &recSmallRec);
    xTEST_DIFF(FALSE, blRes);

    centerWindow();
#else
    // TODO: setFullScreen
    xNOT_IMPLEMENTED;
#endif
}
//------------------------------------------------------------------------------
void_t
CxConsole::centerWindow() {
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _m_hWnd);
    xTEST_EQ(true, _m_hStdIn.isValid());
    xTEST_EQ(true, _m_hStdOut.isValid());
#endif

#if xOS_ENV_WIN
    BOOL blRes = FALSE;

    RECT rcOrigin = {0};
    blRes = ::GetWindowRect(_m_hWnd, &rcOrigin);
    xTEST_DIFF(FALSE, blRes);

    RECT rcDesktop = {0};
    blRes = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &rcDesktop, 0);
    xTEST_DIFF(FALSE, blRes);

    int_t iDesktopX  = (rcDesktop.right  - rcDesktop.left) / 2;
    int_t iDesktopY  = (rcDesktop.bottom - rcDesktop.top)  / 2;
    int_t iWndWidth  = (rcOrigin.right   - rcOrigin.left);
    int_t iWndHeight = (rcOrigin.bottom  - rcOrigin.top);
    int_t x          = iDesktopX - iWndWidth / 2;        if (x < 0) { x = 0; }

    blRes = ::MoveWindow(_m_hWnd, x, iDesktopY - iWndHeight / 2, iWndWidth, iWndHeight, true);
    xTEST_DIFF(FALSE, blRes);
#else
    // TODO: vCenterWindow
    xNOT_IMPLEMENTED;
#endif
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
#if xOS_ENV_WIN

HWND
CxConsole::_wndHandle() {
    HWND           hRv = NULL;
    std::tstring_t sNewWndTitle;
    std::tstring_t sOldWndTitle;

    // fetch current window title.
    sOldWndTitle = title();
    xTEST_EQ(false, sOldWndTitle.empty());

    // format a "unique" szNewWndTitle.
    sNewWndTitle = CxString::format(xT("%lu/%lu"), ::GetTickCount(), CxCurrentProcess::id());

    // change current window title.
    setTitle(sNewWndTitle);

    // ensure window title has been updated.
    CxCurrentThread::sleep(50UL);

    // look for NewWindowTitle.
    hRv = ::FindWindow(NULL, sNewWndTitle.c_str());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, hRv);

    // restore original window title.
    setTitle(sOldWndTitle);

    return hRv;
}

#endif
//------------------------------------------------------------------------------
#if xOS_ENV_WIN

HMENU
CxConsole::_menuHandle(
    cbool_t &a_cbRevert
)
{
    _m_hMenu = ::GetSystemMenu(_m_hWnd, a_cbRevert);
    if (!a_cbRevert) {
        xTEST_EQ(true, NULL != _m_hMenu);
    }
    if (true  == a_cbRevert) {
        xTEST_EQ(true, NULL == _m_hMenu);
    }

    return _m_hMenu;
}

#endif
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
