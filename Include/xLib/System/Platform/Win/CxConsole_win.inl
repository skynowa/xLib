/**
 * \file  CxConsole.inl
 * \brief console
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Sync/CxThread.h>


xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_construct_impl()
{
    _stdIn = ::GetStdHandle(STD_INPUT_HANDLE);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_DIFF(_stdIn.get(), xNATIVE_HANDLE_NULL);

    _stdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    xTEST_EQ(_stdOut.isValid(), true);
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _stdOut.get());

    // _attributesDef
    {
        CONSOLE_SCREEN_BUFFER_INFO info = {};

        BOOL blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &info);
        xTEST_DIFF(blRv, FALSE);

        _attributesDef = info.wAttributes;
    }

    _wnd = _wndHandle();
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);

    // _menu - n/a
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_destruct_impl()
{
    (native_handle_t)_stdIn.detach();
    (native_handle_t)_stdOut.detach();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::_setAttributes_impl(
    const ExForeground &a_foreground,
    const ExBackground &a_background,
    cint_t             &a_attributes
) const
{
    ExForeground foregroundColor;
    {
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

    ExBackground backgroundColor;
    {
        const WORD backgroundColorBlack   = 0;
        const WORD backgroundColorRed	  = BACKGROUND_RED;
        const WORD backgroundColorBlue	  = BACKGROUND_BLUE;
        const WORD backgroundColorGreen   = BACKGROUND_GREEN;
        const WORD backgroundColorCyan	  = BACKGROUND_GREEN | BACKGROUND_BLUE;
        const WORD backgroundColorMagenta = BACKGROUND_RED | BACKGROUND_BLUE;
        const WORD backgroundColorYellow  = BACKGROUND_RED | BACKGROUND_GREEN;
        const WORD backgroundColorWhite   = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
        const WORD backgroundColorGray	  = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

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

    WORD attrs = 0U;
    {
        const WORD attributeAllOff     = 0;
        const WORD attributeBold       = FOREGROUND_INTENSITY;
        const WORD attributeUnderscore = - 1; xUNUSED(attributeUnderscore);   // not supported
        const WORD attributeBlink      = - 1; xUNUSED(attributeBlink);        // not supported
        const WORD attributeReverse    = - 1; xUNUSED(attributeReverse);      // not supported
        const WORD attributeConcealed  = - 1; xUNUSED(attributeConcealed);    // not supported

        attrs |= foregroundColor;
        attrs |= backgroundColor;

        xCHECK_DO(a_attributes & CxConsole::atAllOff,     attrs |= attributeAllOff);
        xCHECK_DO(a_attributes & CxConsole::atBold,       attrs |= attributeBold);
        xCHECK_DO(a_attributes & CxConsole::atUnderscore, /* attrs |= attributeUnderscore */);   // not supported
        xCHECK_DO(a_attributes & CxConsole::atBlink,      /* attrs |= attributeBlink */);        // not supported
        xCHECK_DO(a_attributes & CxConsole::atReverse,    /* attrs |= attributeReverse */);      // not supported
        xCHECK_DO(a_attributes & CxConsole::atConcealed,  /* attrs |= attributeConcealed */);    // not supported
    }

    BOOL blRv = ::SetConsoleTextAttribute(_stdOut.get(), attrs);
    xTEST_DIFF(blRv, FALSE);

    return std::tstring_t();    // not need for Windows
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::_setAttributesDef_impl() const
{
    BOOL blRv = ::SetConsoleTextAttribute(_stdOut.get(), _attributesDef);
    xTEST_DIFF(blRv, FALSE);

    return std::tstring_t();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::_read_impl() const
{
    std::tstring_t sRv;

    DWORD    read               = 0UL;
    culong_t buffSize           = 1024UL * 4UL;
    tchar_t  buff[buffSize + 1] = {0};

    BOOL blRv = ::ReadConsole(_stdIn.get(), &buff[0], buffSize, &read, xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);

    sRv.assign(buff, read - CxConst::crNl().size());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_write_impl(
    std::ctstring_t &a_str
) const
{
    DWORD written = 0UL;

    BOOL blRv = ::WriteConsole(_stdOut.get(), &a_str.at(0), static_cast<DWORD>( a_str.size() ),
        &written, xPTR_NULL);
    xTEST_DIFF(blRv, FALSE);
    xTEST_EQ(static_cast<size_t>( written ), a_str.size());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_clear_impl() const
{
    COORD                      coordScreen  = {0};   // here's where we'll home the cursor
    DWORD                      charsWritten = 0UL;
    CONSOLE_SCREEN_BUFFER_INFO csbi         = {{0}}; // to get buffer info
    DWORD                      conSize      = 0UL;   // number of chars cells in the current buffer

    // get the number of character cells in the current buffer
    BOOL blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &csbi);
    xTEST_DIFF(blRv, FALSE);

    conSize = csbi.dwSize.X * csbi.dwSize.Y;

    // fill the entire screen with blanks
    blRv = ::FillConsoleOutputCharacter(_stdOut.get(), xT(' '), conSize, coordScreen,
        &charsWritten);
    xTEST_DIFF(blRv, FALSE);

    // get the current text attribute
    blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &csbi);
    xTEST_DIFF(blRv, FALSE);

    // now set the buffer's attributes accordingly
    blRv = ::FillConsoleOutputAttribute(_stdOut.get(), csbi.wAttributes, conSize, coordScreen,
        &charsWritten);
    xTEST_DIFF(blRv, FALSE);

    // put the cursor at (0, 0)
    blRv = ::SetConsoleCursorPosition(_stdOut.get(), coordScreen );
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::_setTitle_impl(
    std::ctstring_t &a_title
) const
{
    BOOL blRv = ::SetConsoleTitle( a_title.c_str() );
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::title() const
{
    xTEST_NA(_wnd);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);

    std::tstring_t sRv;

    const DWORD buffSize           = 1024UL;
    tchar_t     buff[buffSize + 1] = {0};
    DWORD       titleSize          = 0UL;

    titleSize = ::GetConsoleTitle(buff, buffSize);
    xTEST_LESS(0UL, titleSize);

    sRv.assign(buff, titleSize);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::centerWindow() const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);

    BOOL blRv = FALSE;

    RECT origin = {0};
    blRv = ::GetWindowRect(_wnd, &origin);
    xTEST_DIFF(blRv, FALSE);

    RECT desktop = {0};
    blRv = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop, 0);
    xTEST_DIFF(blRv, FALSE);

    int_t desktopX  = (desktop.right  - desktop.left) / 2;
    int_t desktopY  = (desktop.bottom - desktop.top)  / 2;
    int_t wndWidth  = (origin.right   - origin.left);
    int_t wndHeight = (origin.bottom  - origin.top);
    int_t x         = desktopX - wndWidth / 2;        if (x < 0) { x = 0; }

    blRv = ::MoveWindow(_wnd, x, desktopY - wndHeight / 2, wndWidth, wndHeight, true);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::setFullScreen() const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);

    COORD coord = ::GetLargestConsoleWindowSize(_stdOut.get());
    xTEST_EQ(coord.X != 0 && coord.Y != 0, true);

    coord.X -= 2;
    coord.Y -= 2;

    SMALL_RECT smallRec = {0};
    smallRec.Left   = 0;
    smallRec.Top    = 0;
    smallRec.Right  = coord.X - 2;
    smallRec.Bottom = coord.Y - 2;

    BOOL blRv = ::SetConsoleScreenBufferSize(_stdOut.get(), coord);
    xTEST_DIFF(blRv, FALSE);

    blRv = ::SetConsoleWindowInfo(_stdOut.get(), true, &smallRec);
    xTEST_DIFF(blRv, FALSE);

    centerWindow();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::enableClose(
    cbool_t &a_flag
)
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);

    _menu = _menuHandle(false);
    xTEST_EQ(_menu != xPTR_NULL, true);

    if (!a_flag) {
        BOOL blRv = ::DeleteMenu(_menu, SC_CLOSE, MF_BYCOMMAND);
        xTEST_DIFF(blRv, FALSE);
    } else {
        BOOL blRv = ::AppendMenu(_menu, SC_CLOSE, MF_BYCOMMAND, xT(""));
        xTEST_DIFF(blRv, FALSE);

        blRv = ::EnableMenuItem(_menuHandle(false), SC_CLOSE, MF_ENABLED);
        xTEST_DIFF(TRUE, blRv);

        blRv = ::SetWindowPos(_wndHandle(), xPTR_NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE |
            SWP_NOZORDER | SWP_DRAWFRAME);
        xTEST_DIFF(blRv, FALSE);
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline HWND
CxConsole::_wndHandle()
{
    HWND           hRv = xPTR_NULL;
    std::tstring_t newWndTitle;
    std::tstring_t oldWndTitle;

    // fetch current window title.
    oldWndTitle = title();
    xTEST_EQ(oldWndTitle.empty(), false);

    // format a "unique" szNewWndTitle.
    newWndTitle = CxString::format(xT("%lu/%lu"), ::GetTickCount(), ::GetCurrentProcessId());

    // change current window title.
    setTitle(newWndTitle);

    // ensure window title has been updated.
    CxThread::currentSleep(50UL);

    // look for NewWindowTitle.
    hRv = ::FindWindow(xPTR_NULL, newWndTitle.c_str());
    xTEST_DIFF(hRv, xWND_NATIVE_HANDLE_NULL);

    // restore original window title.
    setTitle(oldWndTitle);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
inline HMENU
CxConsole::_menuHandle(
    cbool_t &a_isRevert
)
{
    _menu = ::GetSystemMenu(_wnd, a_isRevert);

    if (a_isRevert) {
        xTEST_EQ(_menu == xPTR_NULL, true);
    } else {
        xTEST_EQ(_menu != xPTR_NULL, true);
    }

    return _menu;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
