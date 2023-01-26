/**
 * \file   Test_Console.cpp
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
    xTEST_CASE("setAttributes")
    {
        Console console;

        std::tstring_t text = xT("AAA BBB CCC 123456 !@##$%^%^&*!!!");

        Console::cForeground foreground = Console::Foreground::Green;
        Console::cBackground background = Console::Background::Default;
        cint_t              attributes =
			static_cast<int_t>(Console::Attribute::Bold) |
			static_cast<int_t>(Console::Attribute::Underline) |
			static_cast<int_t>(Console::Attribute::Reverse);

		console.write( console.setAttributes(foreground, background, attributes) );
		console.write(text);
		console.writeLine( console.clearAttributes() );

		console.writeLine(foreground, background, attributes, text);
    }

    xTEST_CASE("read")
    {
	#if xTEST_IGNORE
		Console console;

		m_sRv = console.read();
		xTEST_NA(m_sRv);
    #else
        Trace() << xT("[skip]");
	#endif
    }

    xTEST_CASE("write")
    {
	#if xTEST_IGNORE
		std::ctstring_t str = xT("\tConsole_test_string");

		Console console;

		console.write(str);
    #else
        Trace() << xT("[skip]");
	#endif
    }

    xTEST_CASE("writeLine")
    {
	#if xTEST_IGNORE
		std::ctstring_t str = xT("\tConsole_test_line");

		Console console;

		console.writeLine(str);
    #else
        Trace() << xT("[skip]");
	#endif
    }

    xTEST_CASE("writeLine")
    {
	#if xTEST_IGNORE
		std::ctstring_t str = xT("\tConsole_test_error");

		Console console;

		console.writeLine(str);
    #else
        Trace() << xT("[skip]");
	#endif
    }

    xTEST_CASE("pause")
    {
	#if xTEST_IGNORE
		Console console;

		console.pause(3 * 1000UL);
		console.pause(xTIMEOUT_INFINITE);
    #else
        Trace() << xT("[skip]");
	#endif
    }

    xTEST_CASE("clear")
    {
	#if xTEST_IGNORE
		Console console;

		console.clear();
    #else
        Trace() << xT("[skip]");
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
        Trace() << xT("[skip]");
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
		Trace() << xT("[skip]");
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
		Trace() << xT("[skip]");
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
		Trace() << xT("[skip]");
	#endif
    }
#endif

#if xENV_WIN
    xTEST_CASE("enableClose")
    {
	#if xTEST_IGNORE
		Console console;

		console.enableClose(false);
		console.enableClose(true);
	#else
		Trace() << xT("[skip]");
	#endif
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
