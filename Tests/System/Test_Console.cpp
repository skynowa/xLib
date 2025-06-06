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

        auto fg = Console::FG::Green;
        auto bg = Console::BG::Default;
        auto attrs =
			static_cast<int_t>(Console::Attr::Bold) |
			static_cast<int_t>(Console::Attr::Underline) |
			static_cast<int_t>(Console::Attr::Reverse);

        Console console(true, true);
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
        Cout() << xT("[skip]");
	#endif
    }

    xTEST_CASE("write")
    {
	#if xTEST_IGNORE
		std::ctstring_t str = xT("\tConsole_test_string");

		Console console;
		console.write(str);
    #else
        Cout() << xT("[skip]");
	#endif
    }

    xTEST_CASE("writeLine")
    {
	#if xTEST_IGNORE
		std::ctstring_t str = xT("\tConsole_test_line");

		Console console;
		console.writeLine(str);
    #else
        Cout() << xT("[skip]");
	#endif
    }

    xTEST_CASE("writeLine")
    {
	#if xTEST_IGNORE
		std::ctstring_t str = xT("\tConsole_test_error");

		Console console;
		console.writeLine(str);
    #else
        Cout() << xT("[skip]");
	#endif
    }

    xTEST_CASE("pause")
    {
	#if xTEST_IGNORE
		Console console;
		console.pause(3 * 1000UL);
		console.pause(xTIMEOUT_INFINITE);
    #else
        Cout() << xT("[skip]");
	#endif
    }

    xTEST_CASE("clear")
    {
	#if xTEST_IGNORE
		Console console;
		console.clear();
    #else
        Cout() << xT("[skip]");
	#endif
    }

    xTEST_CASE("setTitle")
    {
	#if xTEST_IGNORE
		std::ctstring_t title = xT("Title1");

		Console console;
		console.setTitle(title);

		#if 1 && xENV_WIN
			m_sRv = console.title();
			xTEST_EQ(m_sRv, title);
		#endif
    #else
        Cout() << xT("[skip]");
	#endif
    }

#if xENV_WIN
    xTEST_CASE("title")
    {
	#if xTEST_IGNORE
		std::tstring_t title = xT("Title1");

		Console console;
		console.setTitle(title);
		m_sRv = console.title();
		xTEST_EQ(m_sRv, title);
	#else
		Cout() << xT("[skip]");
	#endif
    }
#endif

#if xENV_WIN
    xTEST_CASE("centerWindow")
    {
	#if xTEST_IGNORE
		Console console;
		console.centerWindow();
	#else
		Cout() << xT("[skip]");
	#endif
    }
#endif

#if xENV_WIN
    xTEST_CASE("setFullScreen")
    {
	#if xTEST_IGNORE
		Console console;
		console.setFullScreen();
	#else
		Cout() << xT("[skip]");
	#endif
    }
#endif

#if xENV_WIN
    xTEST_CASE("enableClose")
    {
	#if xTEST_IGNORE
		Console console;
		console.enableClose(true);
	#else
		Cout() << xT("[skip]");
	#endif
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
