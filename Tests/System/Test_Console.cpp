/**
 * \file  Test_Console.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Console)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Console::unit()
{
    xTEST_CASE("set")
    {
        std::ctstring_t text = xT("AAA BBB CCC 123456 !@##$%^%^&*!!!");

        const auto fg = Color::FG::Green;
        const auto bg = Color::BG::Default;

        const auto attrs = static_cast<Color::Attr>(
                static_cast<int_t>(Color::Attr::Bold) |
                static_cast<int_t>(Color::Attr::Underline) |
                static_cast<int_t>(Color::Attr::Dim));

        Color color(true, false, fg, bg, attrs);

        Console console;
        console.write( color.set() );
        console.write(text);
        console.writeLine( color.clear() );

        console.writeLine(color, text);
    }

    xTEST_CASE("read")
    {
    #if xTEST_IGNORE
        Console console;
        m_sRv = console.read();
        xTEST_NA(m_sRv);
    #else
        LogCout() << xT("[skip]");
    #endif
    }

    xTEST_CASE("write")
    {
    #if xTEST_IGNORE
        std::ctstring_t str = xT("\tConsole_test_string");

        Console console;
        console.write(str);
    #else
        LogCout() << xT("[skip]");
    #endif
    }

    xTEST_CASE("writeLine")
    {
    #if xTEST_IGNORE
        std::ctstring_t str = xT("\tConsole_test_line");

        Console console;
        console.writeLine(str);
    #else
        LogCout() << xT("[skip]");
    #endif
    }

    xTEST_CASE("writeLine")
    {
    #if xTEST_IGNORE
        std::ctstring_t str = xT("\tConsole_test_error");

        Console console;
        console.writeLine(str);
    #else
        LogCout() << xT("[skip]");
    #endif
    }

    xTEST_CASE("pause")
    {
    #if xTEST_IGNORE
        Console console;
        console.pause(3 * 1000UL);
        console.pause(xTIMEOUT_INFINITE);
    #else
        LogCout() << xT("[skip]");
    #endif
    }

    xTEST_CASE("clear")
    {
    #if xTEST_IGNORE
        Console console;
        console.clear();
    #else
        LogCout() << xT("[skip]");
    #endif
    }

    xTEST_CASE("setTitle")
    {
    #if xTEST_IGNORE
        std::ctstring_t title = xT("Title1");

        Console console;
        console.setTitle(title);
    #else
        LogCout() << xT("[skip]");
    #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
