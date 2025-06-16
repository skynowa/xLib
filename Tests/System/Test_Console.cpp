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
    xTEST_CASE("setAttrs")
    {
        std::ctstring_t text = xT("AAA BBB CCC 123456 !@##$%^%^&*!!!");

        const auto fg = Console::FG::Green;
        const auto bg = Console::BG::Default;

		const auto attrs = static_cast<Console::Attr>(
				static_cast<int_t>(Console::Attr::Bold) |
				static_cast<int_t>(Console::Attr::Underline) |
				static_cast<int_t>(Console::Attr::Blink));

        Console console(true, false);
		console.write( console.setAttrs(fg, bg, attrs) );
		console.write(text);
		console.writeLine( console.clearAttrs() );
		console.writeLine(fg, bg, attrs, text);
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
