/**
 * \file  Console_win.inl
 * \brief Shell console
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Sync/Thread.h>


namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Console::_construct_impl()
{
    _stdIn = ::GetStdHandle(STD_INPUT_HANDLE);
    xTEST(_stdIn.isValid());
    xTEST_DIFF(_stdIn.get(), xNATIVE_HANDLE_NULL);

    _stdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    xTEST(_stdOut.isValid());
    xTEST_DIFF(_stdOut.get(), xNATIVE_HANDLE_NULL);

    // _attrsDef
    {
        CONSOLE_SCREEN_BUFFER_INFO info {};
        BOOL blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &info);
        xTEST_DIFF(blRv, FALSE);

        _attrsDef = info.wAttributes;
    }

    _wnd = _wndHandle();
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);

    // _menu - n/a
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_destruct_impl()
{
    (native_handle_t)_stdIn.detach();
    (native_handle_t)_stdOut.detach();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_setAttrs_impl(
    cFG   a_fg,
    cBG   a_bg,
    cAttr a_attrs
) const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    FG fgColor {};
    {
       /**
        * \code{.cpp}
        * #define COLOR_BLACK     0
        * #define COLOR_BLUE      1
        * #define COLOR_GREEN     2
        * #define COLOR_AQUA      3
        * #define COLOR_RED       4
        * #define COLOR_PURPLE    5
        * #define COLOR_YELLOW    6
        * #define COLOR_WHITE     7
        * #define COLOR_GRAY      8
        * #define COLOR_LTBLUE    9
        * #define COLOR_LTGREEN   A
        * #define COLOR_LTAQUA    B
        * #define COLOR_LTRED     C
        * #define COLOR_LTPURPLE  D
        * #define COLOR_LTYELLOW  E
        * #define COLOR_LTWHITE   F
        * \endcode
        */

        constexpr WORD fgColorDefault {};
        constexpr WORD fgColorBlack   {};
        constexpr WORD fgColorRed     {FOREGROUND_RED};
        constexpr WORD fgColorBlue    {FOREGROUND_BLUE};
        constexpr WORD fgColorGreen   {FOREGROUND_GREEN};
        constexpr WORD fgColorCyan    {FOREGROUND_GREEN | FOREGROUND_BLUE};
        constexpr WORD fgColorMagenta {FOREGROUND_RED | FOREGROUND_BLUE};
        constexpr WORD fgColorYellow  {FOREGROUND_RED | FOREGROUND_GREEN};
        constexpr WORD fgColorWhite   {FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE};
        constexpr WORD fgColorGray    {FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE};

        int_t iRv {};

        switch (a_fg) {
        case FG::Default:
            iRv = fgColorDefault;
            break;
        case FG::Black:
            iRv = fgColorBlack;
            break;
        case FG::Red:
            iRv = fgColorRed;
            break;
        case FG::Green:
            iRv = fgColorGreen;
            break;
        case FG::Yellow:
            iRv = fgColorYellow;
            break;
        case FG::Blue:
            iRv = fgColorBlue;
            break;
        case FG::Magenta:
            iRv = fgColorMagenta;
            break;
        case FG::Cyan:
            iRv = fgColorCyan;
            break;
        case FG::White:
            iRv = fgColorWhite;
            break;
        case FG::Gray:
            iRv = fgColorGray;
            break;
        case FG::Unknown:
        default:
            xTEST_FAIL;
            break;
        }

        fgColor = static_cast<FG>(iRv);
    }

    BG bgColor {};
    {
        constexpr WORD bgColorDefault {};
        constexpr WORD bgColorBlack   {};
        constexpr WORD bgColorRed     {BACKGROUND_RED};
        constexpr WORD bgColorBlue    {BACKGROUND_BLUE};
        constexpr WORD bgColorGreen   {BACKGROUND_GREEN};
        constexpr WORD bgColorCyan    {BACKGROUND_GREEN | BACKGROUND_BLUE};
        constexpr WORD bgColorMagenta {BACKGROUND_RED | BACKGROUND_BLUE};
        constexpr WORD bgColorYellow  {BACKGROUND_RED | BACKGROUND_GREEN};
        constexpr WORD bgColorWhite   {BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE};
        constexpr WORD bgColorGray    {BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE};

        int_t iRv {};

        switch (a_bg) {
        case BG::Default:
            iRv = bgColorDefault;
            break;
        case BG::Black:
            iRv = bgColorBlack;
            break;
        case BG::Red:
            iRv = bgColorRed;
            break;
        case BG::Green:
            iRv = bgColorGreen;
            break;
        case BG::Yellow:
            iRv = bgColorYellow;
            break;
        case BG::Blue:
            iRv = bgColorBlue;
            break;
        case BG::Magenta:
            iRv = bgColorMagenta;
            break;
        case BG::Cyan:
            iRv = bgColorCyan;
            break;
        case BG::White:
            iRv = bgColorWhite;
            break;
        case BG::Gray:
            iRv = bgColorGray;
            break;
        case BG::Unknown:
        default:
            xTEST_FAIL;
            break;
        }

        bgColor = static_cast<BG>(iRv);
    }

    WORD attrs {};
    {
        constexpr WORD attrAllOff    {};
        constexpr WORD attrBold      {FOREGROUND_INTENSITY};
        constexpr WORD attrDim       {}; // IMPL: dim
        constexpr WORD attrUnderline {}; xUNUSED(attrUnderline); // not supported
        constexpr WORD attrBlink     {}; xUNUSED(attrBlink);     // not supported
        constexpr WORD attrReverse   {}; xUNUSED(attrReverse);   // not supported
        constexpr WORD attrHidden    {}; xUNUSED(attrHidden);    // not supported

        attrs |= static_cast<WORD>(fgColor);
        attrs |= static_cast<WORD>(bgColor);

        Bitset bits( static_cast<WORD>(a_attrs) );

        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attr::AllOff)),    attrs |= static_cast<WORD>(attrAllOff));
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attr::Bold)),      attrs |= static_cast<WORD>(attrBold));
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attr::Dim)),       /* attrs |= static_cast<WORD>(attrDim) */);       // IMPL: dim
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attr::Underline)), /* attrs |= static_cast<WORD>(attrUnderline) */); // not supported
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attr::Blink)),     /* attrs |= static_cast<WORD>(attrBlink) */);     // not supported
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attr::Reverse)),   /* attrs |= static_cast<WORD>(attrReverse) */);   // not supported
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attr::Hidden)),    /* attrs |= static_cast<WORD>(attrHidden) */);    // not supported
    }

    BOOL blRv = ::SetConsoleTextAttribute(_stdOut.get(), attrs);
    xTEST_DIFF(blRv, FALSE);

    return {};    // not need for Windows
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_clearAttrs_impl() const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    BOOL blRv = ::SetConsoleTextAttribute(_stdOut.get(), _attrsDef);
    xTEST_DIFF(blRv, FALSE);

    return {};
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_read_impl() const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    std::tstring_t sRv;

    DWORD           read               {};
    constexpr DWORD buffSize           {1024UL * 4UL};
    tchar_t         buff[buffSize + 1] {};

    BOOL blRv = ::ReadConsole(_stdIn.get(), &buff[0], buffSize, &read, nullptr);
    xTEST_DIFF(blRv, FALSE);

    sRv.assign(buff, read - Const::crNl().size());

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_write_impl(
    std::ctstring_t &a_str
) const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    DWORD written {};
    BOOL blRv = ::WriteConsole(_stdOut.get(), &a_str.at(0), static_cast<DWORD>( a_str.size() ),
        &written, nullptr);
    xTEST_DIFF(blRv, FALSE);
    xTEST_EQ(static_cast<size_t>( written ), a_str.size());

    // TODO: [skynowa] Console::_write_impl() - flush
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_clear_impl() const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    COORD                      coordScreen  {}; // here's where we'll home the cursor
    DWORD                      charsWritten {};
    CONSOLE_SCREEN_BUFFER_INFO csbi         {}; // to get buffer info
    DWORD                      conSize      {}; // number of chars cells in the current buffer

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
void_t
Console::_setTitle_impl(
    std::ctstring_t &a_title
) const
{
    xTEST_NA(_wnd);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    BOOL blRv = ::SetConsoleTitle( a_title.c_str() );
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::title() const
{
    xTEST_NA(_wnd);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    std::tstring_t sRv;

    constexpr DWORD buffSize           {1024UL};
    tchar_t         buff[buffSize + 1] {};
    DWORD           titleSize          {};

    titleSize = ::GetConsoleTitle(buff, buffSize);
    xTEST_LESS(0UL, titleSize);

    sRv.assign(buff, titleSize);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::centerWindow() const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    BOOL blRv {};

    RECT origin  {};
    blRv = ::GetWindowRect(_wnd, &origin);
    xTEST_DIFF(blRv, FALSE);

    RECT desktop {};
    blRv = ::SystemParametersInfo(SPI_GETWORKAREA, 0, &desktop, 0);
    xTEST_DIFF(blRv, FALSE);

    cint_t desktopX  = (desktop.right  - desktop.left) / 2;
    cint_t desktopY  = (desktop.bottom - desktop.top)  / 2;
    cint_t wndWidth  = (origin.right   - origin.left);
    cint_t wndHeight = (origin.bottom  - origin.top);
    cint_t x         = desktopX - wndWidth / 2;        if (x < 0) { x = 0; }

    blRv = ::MoveWindow(_wnd, x, desktopY - wndHeight / 2, wndWidth, wndHeight, true);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------
void_t
Console::setFullScreen() const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    COORD coord = ::GetLargestConsoleWindowSize(_stdOut.get());
    xTEST(coord.X != 0 && coord.Y != 0);

    coord.X -= 2;
    coord.Y -= 2;

    SMALL_RECT smallRec {};
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
void_t
Console::enableClose(
    cbool_t a_flag
)
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    _menu = _menuHandle(false);
    xTEST(_menu != nullptr);

    if (!a_flag) {
        BOOL blRv = ::DeleteMenu(_menu, SC_CLOSE, MF_BYCOMMAND);
        xTEST_DIFF(blRv, FALSE);
    } else {
        BOOL blRv = ::AppendMenu(_menu, SC_CLOSE, MF_BYCOMMAND, xT(""));
        xTEST_DIFF(blRv, FALSE);

        blRv = ::EnableMenuItem(_menuHandle(false), SC_CLOSE, MF_ENABLED);
        xTEST_DIFF(TRUE, blRv);

        blRv = ::SetWindowPos(_wnd, nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER |
            SWP_DRAWFRAME);
        xTEST_DIFF(blRv, FALSE);
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
HWND
Console::_wndHandle()
{
    HWND           hRv {};
    std::tstring_t newWndTitle;
    std::tstring_t oldWndTitle;

    // fetch current window title.
    oldWndTitle = title();
    xTEST(!oldWndTitle.empty());

    // format a "unique" szNewWndTitle.
    newWndTitle = Format::str(xT("{}/{}"), ::GetTickCount(), ::GetCurrentProcessId());

    // change current window title.
    setTitle(newWndTitle);

    // ensure window title has been updated.
    Thread::currentSleep(50UL);

    // look for NewWindowTitle.
    hRv = ::FindWindow(nullptr, newWndTitle.c_str());
    xTEST_DIFF(hRv, xWND_NATIVE_HANDLE_NULL);

    // restore original window title.
    setTitle(oldWndTitle);

    return hRv;
}
//-------------------------------------------------------------------------------------------------
HMENU
Console::_menuHandle(
    cbool_t a_isRevert
)
{
    _menu = ::GetSystemMenu(_wnd, a_isRevert);

    if (a_isRevert) {
        xTEST(_menu == nullptr);
    } else {
        xTEST(_menu != nullptr);
    }

    return _menu;
}
//-------------------------------------------------------------------------------------------------

} // namespace
