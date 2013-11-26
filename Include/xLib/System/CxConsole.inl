/**
 * \file  CxConsole.cpp
 * \brief console
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Sync/CxThread.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxConsole::CxConsole()
#if xOS_ENV_WIN
    :
    _wnd          (NULL),
    _menu         (NULL),
    _stdIn        (),
    _stdOut       (),
    _attributesDef(0)
#endif
{
#if xOS_ENV_WIN
    _stdIn = ::GetStdHandle(STD_INPUT_HANDLE);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _stdIn.get());

    _stdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    xTEST_EQ(true, _stdOut.isValid());
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _stdOut.get());

    // _attributesDef
    {
        CONSOLE_SCREEN_BUFFER_INFO info = {};

        BOOL blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &info);
        xTEST_DIFF(FALSE, blRv);

        _attributesDef = info.wAttributes;
    }

    _wnd = _wndHandle();
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);

    // _menu - n/a
#endif
}
//-------------------------------------------------------------------------------------------------
inline CxConsole::~CxConsole()
{
#if xOS_ENV_WIN
    (native_handle_t)_stdIn.detach();
    (native_handle_t)_stdOut.detach();
#endif
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::setAttributes(
    const ExForeground &a_foreground,
    const ExBackground &a_background,
    cint_t             &a_attributes
) const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif
    // n/a

    //--------------------------------------------------
    ExForeground foregroundColor;

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

        const WORD foregroundColorBlack   = 0;
        const WORD foregroundColorRed	  = FOREGROUND_RED;
        const WORD foregroundColorBlue	  = FOREGROUND_BLUE;
        const WORD foregroundColorGreen   = FOREGROUND_GREEN;
        const WORD foregroundColorCyan	  = FOREGROUND_GREEN | FOREGROUND_BLUE;
        const WORD foregroundColorMagenta = FOREGROUND_RED | FOREGROUND_BLUE;
        const WORD foregroundColorYellow  = FOREGROUND_RED | FOREGROUND_GREEN;
        const WORD foregroundColorWhite   = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        const WORD foregroundColorGray	  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    #else
        cint_t  foregroundColorBlack      = 30;
        cint_t  foregroundColorRed        = 31;
        cint_t  foregroundColorBlue       = 34;
        cint_t  foregroundColorGreen      = 32;
        cint_t  foregroundColorCyan       = 36;
        cint_t  foregroundColorMagenta    = 35;
        cint_t  foregroundColorYellow     = 33;
        cint_t  foregroundColorWhite      = 37;
        cint_t  foregroundColorGray       = 37;    // TODO: foregroundColorGray
    #endif

        int_t iRv = - 1;

	    switch (a_foreground) {
        case fgBlack:
            iRv = foregroundColorBlack;
            break;
        case fgRed:
            iRv = foregroundColorRed;
            break;
        case fgGreen:
            iRv = foregroundColorGreen;
            break;
        case fgYellow:
            iRv = foregroundColorYellow;
            break;
        case fgBlue:
            iRv = foregroundColorBlue;
            break;
        case fgMagenta:
            iRv = foregroundColorMagenta;
            break;
        case fgCyan:
            iRv = foregroundColorCyan;
            break;
        case fgWhite:
            iRv = foregroundColorWhite;
            break;
        case fgGray:
            iRv = foregroundColorGray;
            break;
        case fgUnknown:
        default:
            xTEST_FAIL;
            break;
        }

        foregroundColor = static_cast<ExForeground>( iRv );
    }

    //--------------------------------------------------
    ExBackground backgroundColor;

    {
    #if xOS_ENV_WIN
        const WORD backgroundColorBlack   = 0;
        const WORD backgroundColorRed	  = BACKGROUND_RED;
        const WORD backgroundColorBlue	  = BACKGROUND_BLUE;
        const WORD backgroundColorGreen   = BACKGROUND_GREEN;
        const WORD backgroundColorCyan	  = BACKGROUND_GREEN | BACKGROUND_BLUE;
        const WORD backgroundColorMagenta = BACKGROUND_RED | BACKGROUND_BLUE;
        const WORD backgroundColorYellow  = BACKGROUND_RED | BACKGROUND_GREEN;
        const WORD backgroundColorWhite   = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        const WORD backgroundColorGray	  = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    #else
        cint_t  backgroundColorBlack      = 40;
        cint_t  backgroundColorRed	      = 41;
        cint_t  backgroundColorBlue	      = 44;
        cint_t  backgroundColorGreen      = 42;
        cint_t  backgroundColorCyan	      = 46;
        cint_t  backgroundColorMagenta    = 45;
        cint_t  backgroundColorYellow     = 43;
        cint_t  backgroundColorWhite      = 47;
        cint_t  backgroundColorGray	      = 47;    // TODO: backgroundColorGray
    #endif

        int_t iRv = - 1;

	    switch (a_background) {
        case fgBlack:
            iRv = backgroundColorBlack;
            break;
        case fgRed:
            iRv = backgroundColorRed;
            break;
        case fgGreen:
            iRv = backgroundColorGreen;
            break;
        case fgYellow:
            iRv = backgroundColorYellow;
            break;
        case fgBlue:
            iRv = backgroundColorBlue;
            break;
        case fgMagenta:
            iRv = backgroundColorMagenta;
            break;
        case fgCyan:
            iRv = backgroundColorCyan;
            break;
        case fgWhite:
            iRv = backgroundColorWhite;
            break;
        case fgGray:
            iRv = backgroundColorGray;
            break;
        case fgUnknown:
        default:
            xTEST_FAIL;
            break;
        }

        backgroundColor = static_cast<ExBackground>( iRv );
    }

    //--------------------------------------------------
#if xOS_ENV_WIN
    WORD           attrs = 0U;
#else
    std::tstring_t attrs;
#endif

    {
    #if xOS_ENV_WIN
        const WORD attributeAllOff     = 0;
        const WORD attributeBold       = FOREGROUND_INTENSITY;
        const WORD attributeUnderscore = - 1; xUNUSED(attributeUnderscore);   // not supported
        const WORD attributeBlink      = - 1; xUNUSED(attributeBlink);        // not supported
        const WORD attributeReverse    = - 1; xUNUSED(attributeReverse);      // not supported
        const WORD attributeConcealed  = - 1; xUNUSED(attributeConcealed);    // not supported
    #else
        cint_t  attributeAllOff        = 0;
        cint_t  attributeBold          = 1;
        cint_t  attributeUnderscore    = 4;
        cint_t  attributeBlink         = 5;
        cint_t  attributeReverse       = 7;
        cint_t  attributeConcealed     = 8;
    #endif

    #if xOS_ENV_WIN
        attrs |= foregroundColor;
        attrs |= backgroundColor;

        xCHECK_DO(a_attributes & CxConsole::atAllOff,     attrs |= attributeAllOff);
        xCHECK_DO(a_attributes & CxConsole::atBold,       attrs |= attributeBold);
        xCHECK_DO(a_attributes & CxConsole::atUnderscore, /* attrs |= attributeUnderscore */);   // not supported
        xCHECK_DO(a_attributes & CxConsole::atBlink,      /* attrs |= attributeBlink */);        // not supported
        xCHECK_DO(a_attributes & CxConsole::atReverse,    /* attrs |= attributeReverse */);      // not supported
        xCHECK_DO(a_attributes & CxConsole::atConcealed,  /* attrs |= attributeConcealed */);    // not supported
    #else
        attrs += CxString::format(xT("\033[%im"), foregroundColor);
        attrs += CxString::format(xT("\033[%im"), backgroundColor);

        xCHECK_DO(a_attributes & CxConsole::atAllOff,     attrs += CxString::format(xT("\033[%im"), attributeAllOff));
        xCHECK_DO(a_attributes & CxConsole::atBold,       attrs += CxString::format(xT("\033[%im"), attributeBold));
        xCHECK_DO(a_attributes & CxConsole::atUnderscore, attrs += CxString::format(xT("\033[%im"), attributeUnderscore));
        xCHECK_DO(a_attributes & CxConsole::atBlink,      attrs += CxString::format(xT("\033[%im"), attributeBlink));
        xCHECK_DO(a_attributes & CxConsole::atReverse,    attrs += CxString::format(xT("\033[%im"), attributeReverse));
        xCHECK_DO(a_attributes & CxConsole::atConcealed,  attrs += CxString::format(xT("\033[%im"), attributeConcealed));
    #endif
    }

#if xOS_ENV_WIN
    BOOL blRv = ::SetConsoleTextAttribute(_stdOut.get(), attrs);
    xTEST_DIFF(FALSE, blRv);

    return std::tstring_t();    // not need for Windows
#else
    return attrs;
#endif
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::setAttributesDef() const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif
    // n/a

    std::tstring_t sRv;

#if xOS_ENV_WIN
    BOOL blRv = ::SetConsoleTextAttribute(_stdOut.get(), _attributesDef);
    xTEST_DIFF(FALSE, blRv);

    xUNUSED(sRv);
#else
    sRv = xT("\033[0;0m");
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::read() const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

    std::tstring_t sRv;

#if xOS_ENV_WIN
    DWORD    read               = 0UL;
    culong_t buffSize           = 1024UL * 4UL;
    tchar_t  buff[buffSize + 1] = {0};

    BOOL blRv = ::ReadConsole(_stdIn.get(), &buff[0], buffSize, &read, NULL);
    xTEST_DIFF(FALSE, blRv);

    sRv.assign(buff, read - CxConst::crNl().size());
#else
    // BUG: CxConsole::read
    std::tcin >> sRv;
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::write(
    std::ctstring_t &a_str
) const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

#if xOS_ENV_WIN
    DWORD written = 0UL;

    BOOL blRv = ::WriteConsole(
                    _stdOut.get(),
                    &a_str.at(0), static_cast<DWORD>( a_str.size() ),
                    &written, NULL);
    xTEST_DIFF(FALSE, blRv);
    xTEST_EQ(static_cast<size_t>( written ), a_str.size());
#else
    std::tcout << a_str;
#endif

    std::tcout.flush();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::writeLine(
    std::ctstring_t &a_str /* = xT("") */
) const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

    write(a_str + CxConst::nl());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::writeErrLine(
    std::ctstring_t &a_str
) const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

    writeLine(xT("Error: ") + a_str);

    pause(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
inline CxConsole::ExModalResult
CxConsole::msgBox(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cuint_t         &a_type
) const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

    ExModalResult mrRv;

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    writeLine();
    writeLine(xT("################################################################################"));
    writeLine(xT("#  ") + a_title);
    writeLine(xT("#"));
    writeLine(xT("#  ") + a_text);
    writeLine(xT("#"));
    writeLine(xT("################################################################################"));
    writeLine();
    write(CxString::format(xT("\nAbort (%c), Ignore (%c), Retry (%c): "), cmAbort, cmIgnore, cmRetry));

    EConsoleCmd cmRv = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
    switch (cmRv) {
    case cmAbort:
        mrRv = mrAbort;
        writeLine(xT("Abort..."));
        break;
    case cmIgnore:
        mrRv = mrIgnore;
        writeLine(xT("Ignore..."));
        break;
    case cmRetry:
        mrRv = mrRetry;
        writeLine(xT("Retry..."));
        break;
    default:
        mrRv = mrRetry;
        writeLine(xT("Retry..."));
        break;
    }

    return mrRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::prompt(
    std::ctstring_t &a_prompt,
    cbool_t         &a_isVisible,
    std::tstring_t  *a_answer
) const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

    xTEST_EQ(false, a_prompt.empty());
    xTEST_PTR(a_answer);

    xFOREVER {
        write(a_prompt + xT(": "));

        xFOREVER {
            ctchar_t letter = static_cast<tchar_t>( std::tcin.get() );

            // asterisks
            xCHECK_DO(a_isVisible, write(xT("*")));

            // ENTER
            xCHECK_DO(10 == letter, break);

            // BACKSPACE
            xCHECK_DO(0x8 == letter, (*a_answer).clear(); continue);

            (*a_answer).push_back(letter);
        }

        writeLine(CxConst::strEmpty());

        xCHECK_DO((*a_answer).empty(), continue);

        break;
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::pause(
    culong_t &a_timeoutMsec
) const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
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

    std::tstring_t msg;

	if (xTIMEOUT_INFINITE == a_timeoutMsec) {
        msg = xT("Pause, press [ENTER] to continue...");

        writeLine(msg);

        std::cin.clear();
        std::cin.ignore();
	} else {
        msg = CxString::format(xT("Pause, wait for %lu msec to continue..."), a_timeoutMsec);

        writeLine(msg);

		CxThread::currentSleep(a_timeoutMsec);
	}
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::clear() const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

#if xOS_ENV_WIN
    COORD                      coordScreen  = {0};   // here's where we'll home the cursor
    DWORD                      charsWritten = 0UL;
    CONSOLE_SCREEN_BUFFER_INFO csbi         = {{0}}; // to get buffer info
    DWORD                      conSize      = 0UL;   // number of chars cells in the current buffer

    // get the number of character cells in the current buffer
    BOOL blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &csbi);
    xTEST_DIFF(FALSE, blRv);

    conSize = csbi.dwSize.X * csbi.dwSize.Y;

    // fill the entire screen with blanks
    blRv = ::FillConsoleOutputCharacter(_stdOut.get(), xT(' '), conSize, coordScreen,
        &charsWritten);
    xTEST_DIFF(FALSE, blRv);

    // get the current text attribute
    blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &csbi);
    xTEST_DIFF(FALSE, blRv);

    // now set the buffer's attributes accordingly
    blRv = ::FillConsoleOutputAttribute(_stdOut.get(), csbi.wAttributes, conSize, coordScreen,
        &charsWritten);
    xTEST_DIFF(FALSE, blRv);

    // put the cursor at (0, 0)
    blRv = ::SetConsoleCursorPosition(_stdOut.get(), coordScreen );
    xTEST_DIFF(FALSE, blRv);
#else
    writeLine(CxConst::ff());
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::enableClose(
    cbool_t &a_flag
) const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

#if xOS_ENV_WIN
    _menu = _menuHandle(false);
    xTEST_EQ(true, NULL != _menu);

    if (!a_flag) {
        BOOL blRv = ::DeleteMenu(_menu, SC_CLOSE, MF_BYCOMMAND);
        xTEST_DIFF(FALSE, blRv);
    } else {
        BOOL blRv = ::AppendMenu(_menu, SC_CLOSE, MF_BYCOMMAND, xT(""));
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
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::title() const
{
#if xOS_ENV_WIN
    xTEST_NA(_wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

    std::tstring_t sRv;

#if xOS_ENV_WIN
    const DWORD buffSize           = 1024UL;
    tchar_t     buff[buffSize + 1] = {0};
    DWORD       titleSize          = 0UL;

    titleSize = ::GetConsoleTitle(buff, buffSize);
    xTEST_LESS(0UL, titleSize);

    sRv.assign(buff, titleSize);
#else
    // TODO: sTitle
    xNOT_IMPLEMENTED;
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::setTitle(
    std::ctstring_t &a_title
) const
{
#if xOS_ENV_WIN
    xTEST_NA(_wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

#if xOS_ENV_WIN
    BOOL blRv = ::SetConsoleTitle(a_title.c_str());
    xTEST_DIFF(FALSE, blRv);
#else
    // TODO: vSetTitle
    writeLine( CxString::format(xT("%c]0;%s%c"), xT('\033'), a_title.c_str(), xT('\007')) );
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::setFullScreen() const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

#if xOS_ENV_WIN
    COORD coord = ::GetLargestConsoleWindowSize(_stdOut.get());
    xTEST_EQ(true, 0 != coord.X && 0 != coord.Y);

    coord.X -= 2;
    coord.Y -= 2;

    SMALL_RECT smallRec = {0};
    smallRec.Left   = 0;
    smallRec.Top    = 0;
    smallRec.Right  = coord.X - 2;
    smallRec.Bottom = coord.Y - 2;

    BOOL blRv = ::SetConsoleScreenBufferSize(_stdOut.get(), coord);
    xTEST_DIFF(FALSE, blRv);

    blRv = ::SetConsoleWindowInfo(_stdOut.get(), true, &smallRec);
    xTEST_DIFF(FALSE, blRv);

    centerWindow();
#else
    // TODO: setFullScreen
    xNOT_IMPLEMENTED;
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::centerWindow() const
{
#if xOS_ENV_WIN
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, _wnd);
    xTEST_EQ(true, _stdIn.isValid());
    xTEST_EQ(true, _stdOut.isValid());
#endif

#if xOS_ENV_WIN
    BOOL blRv = FALSE;

    RECT origin = {0};
    blRv = ::GetWindowRect(_wnd, &origin);
    xTEST_DIFF(FALSE, blRv);

    RECT desktop = {0};
    blRv = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop, 0);
    xTEST_DIFF(FALSE, blRv);

    int_t desktopX  = (desktop.right  - desktop.left) / 2;
    int_t desktopY  = (desktop.bottom - desktop.top)  / 2;
    int_t wndWidth  = (origin.right   - origin.left);
    int_t wndHeight = (origin.bottom  - origin.top);
    int_t x         = desktopX - wndWidth / 2;        if (x < 0) { x = 0; }

    blRv = ::MoveWindow(_wnd, x, desktopY - wndHeight / 2, wndWidth, wndHeight, true);
    xTEST_DIFF(FALSE, blRv);
#else
    // TODO: centerWindow
    xNOT_IMPLEMENTED;
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline HWND
CxConsole::_wndHandle()
{
    HWND           hRv = NULL;
    std::tstring_t newWndTitle;
    std::tstring_t oldWndTitle;

    // fetch current window title.
    oldWndTitle = title();
    xTEST_EQ(false, oldWndTitle.empty());

    // format a "unique" szNewWndTitle.
    newWndTitle = CxString::format(xT("%lu/%lu"), ::GetTickCount(), ::GetCurrentProcessId());

    // change current window title.
    setTitle(newWndTitle);

    // ensure window title has been updated.
    CxThread::currentSleep(50UL);

    // look for NewWindowTitle.
    hRv = ::FindWindow(NULL, newWndTitle.c_str());
    xTEST_DIFF(xWND_NATIVE_HANDLE_NULL, hRv);

    // restore original window title.
    setTitle(oldWndTitle);

    return hRv;
}

#endif
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

inline HMENU
CxConsole::_menuHandle(
    cbool_t &a_isRevert
)
{
    _menu = ::GetSystemMenu(_wnd, a_isRevert);
    if (!a_isRevert) {
        xTEST_EQ(true, NULL != _menu);
    }
    if (true  == a_isRevert) {
        xTEST_EQ(true, NULL == _menu);
    }

    return _menu;
}

#endif
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
