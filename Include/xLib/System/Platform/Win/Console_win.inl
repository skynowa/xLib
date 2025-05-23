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
    xTEST_DIFF(xNATIVE_HANDLE_NULL, _stdOut.get());

    // _attributesDef
    {
        CONSOLE_SCREEN_BUFFER_INFO info {};
        BOOL blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &info);
        xTEST_DIFF(blRv, FALSE);

        _attributesDef = info.wAttributes;
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
Console::_setAttributes_impl(
    cForeground a_foreground,
    cBackground a_background,
    cint_t      a_attributes
) const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    Foreground foregroundColor {};
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

        constexpr WORD foregroundColorDefault {};
        constexpr WORD foregroundColorBlack   {};
        constexpr WORD foregroundColorRed     {FOREGROUND_RED};
        constexpr WORD foregroundColorBlue    {FOREGROUND_BLUE};
        constexpr WORD foregroundColorGreen   {FOREGROUND_GREEN};
        constexpr WORD foregroundColorCyan    {FOREGROUND_GREEN | FOREGROUND_BLUE};
        constexpr WORD foregroundColorMagenta {FOREGROUND_RED | FOREGROUND_BLUE};
        constexpr WORD foregroundColorYellow  {FOREGROUND_RED | FOREGROUND_GREEN};
        constexpr WORD foregroundColorWhite   {FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE};
        constexpr WORD foregroundColorGray    {FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE};

        int_t iRv {};

        switch (a_foreground) {
        case Foreground::Default:
            iRv = foregroundColorDefault;
            break;
        case Foreground::Black:
            iRv = foregroundColorBlack;
            break;
        case Foreground::Red:
            iRv = foregroundColorRed;
            break;
        case Foreground::Green:
            iRv = foregroundColorGreen;
            break;
        case Foreground::Yellow:
            iRv = foregroundColorYellow;
            break;
        case Foreground::Blue:
            iRv = foregroundColorBlue;
            break;
        case Foreground::Magenta:
            iRv = foregroundColorMagenta;
            break;
        case Foreground::Cyan:
            iRv = foregroundColorCyan;
            break;
        case Foreground::White:
            iRv = foregroundColorWhite;
            break;
        case Foreground::Gray:
            iRv = foregroundColorGray;
            break;
        case Foreground::Unknown:
        default:
            xTEST_FAIL;
            break;
        }

        foregroundColor = static_cast<Foreground>(iRv);
    }

    Background backgroundColor {};
    {
        constexpr WORD backgroundColorDefault {};
        constexpr WORD backgroundColorBlack   {};
        constexpr WORD backgroundColorRed     {BACKGROUND_RED};
        constexpr WORD backgroundColorBlue    {BACKGROUND_BLUE};
        constexpr WORD backgroundColorGreen   {BACKGROUND_GREEN};
        constexpr WORD backgroundColorCyan    {BACKGROUND_GREEN | BACKGROUND_BLUE};
        constexpr WORD backgroundColorMagenta {BACKGROUND_RED | BACKGROUND_BLUE};
        constexpr WORD backgroundColorYellow  {BACKGROUND_RED | BACKGROUND_GREEN};
        constexpr WORD backgroundColorWhite   {BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE};
        constexpr WORD backgroundColorGray    {BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE};

        int_t iRv {};

        switch (a_background) {
        case Background::Default:
            iRv = backgroundColorDefault;
            break;
        case Background::Black:
            iRv = backgroundColorBlack;
            break;
        case Background::Red:
            iRv = backgroundColorRed;
            break;
        case Background::Green:
            iRv = backgroundColorGreen;
            break;
        case Background::Yellow:
            iRv = backgroundColorYellow;
            break;
        case Background::Blue:
            iRv = backgroundColorBlue;
            break;
        case Background::Magenta:
            iRv = backgroundColorMagenta;
            break;
        case Background::Cyan:
            iRv = backgroundColorCyan;
            break;
        case Background::White:
            iRv = backgroundColorWhite;
            break;
        case Background::Gray:
            iRv = backgroundColorGray;
            break;
        case Background::Unknown:
        default:
            xTEST_FAIL;
            break;
        }

        backgroundColor = static_cast<Background>(iRv);
    }

    WORD attrs {};
    {
        constexpr WORD attributeAllOff    {};
        constexpr WORD attributeBold      {FOREGROUND_INTENSITY};
        constexpr WORD attributeDim       {}; // IMPL: dim
        constexpr WORD attributeUnderline {}; xUNUSED(attributeUnderline); // not supported
        constexpr WORD attributeBlink     {}; xUNUSED(attributeBlink);     // not supported
        constexpr WORD attributeReverse   {}; xUNUSED(attributeReverse);   // not supported
        constexpr WORD attributeHidden    {}; xUNUSED(attributeHidden);    // not supported

        attrs |= static_cast<WORD>(foregroundColor);
        attrs |= static_cast<WORD>(backgroundColor);

        Bitset bits(a_attributes);

        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attribute::AllOff)),    attrs |= static_cast<WORD>(attributeAllOff));
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attribute::Bold)),      attrs |= static_cast<WORD>(attributeBold));
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attribute::Dim)),       /* attrs |= static_cast<WORD>(attributeDim) */);       // IMPL: dim
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attribute::Underline)), /* attrs |= static_cast<WORD>(attributeUnderline) */); // not supported
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attribute::Blink)),     /* attrs |= static_cast<WORD>(attributeBlink) */);     // not supported
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attribute::Reverse)),   /* attrs |= static_cast<WORD>(attributeReverse) */);   // not supported
        xCHECK_DO(bits.isSetBit(static_cast<WORD>(Attribute::Hidden)),    /* attrs |= static_cast<WORD>(attributeHidden) */);    // not supported
    }

    BOOL blRv = ::SetConsoleTextAttribute(_stdOut.get(), attrs);
    xTEST_DIFF(blRv, FALSE);

    return {};    // not need for Windows
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_clearAttributes_impl() const
{
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    BOOL blRv = ::SetConsoleTextAttribute(_stdOut.get(), _attributesDef);
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

    DWORD     read               {};
    constexpr ulong_t buffSize   {1024UL * 4UL};
    tchar_t   buff[buffSize + 1] {};

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

    int_t desktopX  = (desktop.right  - desktop.left) / 2;
    int_t desktopY  = (desktop.bottom - desktop.top)  / 2;
    int_t wndWidth  = (origin.right   - origin.left);
    int_t wndHeight = (origin.bottom  - origin.top);
    int_t x         = desktopX - wndWidth / 2;        if (x < 0) { x = 0; }

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

        blRv = ::SetWindowPos(_wndHandle(), nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE |
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
HWND
Console::_wndHandle()
{
    HWND           hRv = nullptr;
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
