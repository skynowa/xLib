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
Console::_ctor_impl()
{
    _stdIn = ::GetStdHandle(STD_INPUT_HANDLE);
    xTEST(_stdIn.isValid());

    _stdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    xTEST(_stdOut.isValid());

    // _attrsDef
    {
        CONSOLE_SCREEN_BUFFER_INFO info {};
        BOOL blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &info);
        xTEST_DIFF(blRv, FALSE);

        _attrsDef = info.wAttributes;
    }
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_dtor_impl()
{
    (native_handle_t)_stdIn.detach();
    (native_handle_t)_stdOut.detach();
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Color::_set_impl(
    cFG   a_fg,
    cBG   a_bg,
    cAttr a_attrs
) const
{
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
Color::_clear_impl() const
{
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
    xTEST(_stdIn.isValid());
    xTEST(_stdOut.isValid());

    BOOL blRv = ::SetConsoleTitle( a_title.c_str() );
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

} // namespace
