/**
 * \file  Console_win.inl
 * \brief Shell console
 */


namespace xl::system
{

/**************************************************************************************************
*    private
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

    // get the number of character cells in the current buffer
    CONSOLE_SCREEN_BUFFER_INFO csbi {};
    BOOL blRv = ::GetConsoleScreenBufferInfo(_stdOut.get(), &csbi);
    xTEST_DIFF(blRv, FALSE);

    // number of chars cells in the current buffer
    const DWORD conSize = csbi.dwSize.X * csbi.dwSize.Y;

    COORD coordScreen  {}; // here's where we'll home the cursor
    DWORD charsWritten {};

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
    blRv = ::SetConsoleCursorPosition(_stdOut.get(), coordScreen);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

} // namespace
