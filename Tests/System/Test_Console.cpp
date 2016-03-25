/**
 * \file   Test_Console.cpp
 * \brief
 */


#include "Test_Console.h"

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

        std::tstring_t          text;
        Console::ExForeground foreground = Console::fgBlue;
        Console::ExBackground background = Console::bgYellow;
        int_t                   attributes = Console::atBold | Console::atUnderscore |
                                             Console::atReverse;

        m_sRv = console.setAttributes(foreground, background, attributes);
        xTEST_NA(m_sRv);

        m_sRv = console.setAttributesDef();
        xTEST_NA(m_sRv);
    }

    xTEST_CASE("read")
    {
        #if xTEST_IGNORE
            Console console;

            m_sRv = console.read();
            xTEST_NA(m_sRv);
        #endif
    }

    xTEST_CASE("write")
    {
        #if xTEST_IGNORE
            std::ctstring_t str = xT("\tConsole_test_string");

            Console console;

            console.write(str);
        #endif
    }

    xTEST_CASE("writeLine")
    {
        #if xTEST_IGNORE
            std::ctstring_t str = xT("\tConsole_test_line");

            Console console;

            console.writeLine(str);
        #endif
    }

    xTEST_CASE("writeLine")
    {
        #if xTEST_IGNORE
            std::ctstring_t str = xT("\tConsole_test_error");

            Console console;

            console.writeLine(str);
        #endif
    }

    xTEST_CASE("msgBox")
    {
        #if xTEST_IGNORE
            std::ctstring_t text  = xT("iMsgBox_text");
            std::ctstring_t title = xT("iMsgBox_title");
            cuint_t         type  = 0U;


            Console console;

            Console::ExModalResult mrRes = console.msgBox(text, title, type);
            xUNUSED(mrRes);
        #endif
    }

    xTEST_CASE("prompt")
    {
        #if xTEST_IGNORE
            std::ctstring_t prompt    = xT("vPrompt_simple_prompt");
            cbool_t         isVisible = true;
            std::tstring_t  answer    = xT("sAnswer_bla-bla-bla");

            Console console;

            console.prompt(prompt, isVisible, &answer);
        #endif
    }

    xTEST_CASE("pause")
    {
        #if xTEST_IGNORE
            Console console;

            console.pause(3 * 1000UL);
            console.pause(xTIMEOUT_INFINITE);
        #endif
    }

    xTEST_CASE("clear")
    {
        #if xTEST_IGNORE
            Console console;

            console.clear();
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
        #endif
    }

#if xENV_WIN && xTEST_IGNORE
    xTEST_CASE("title")
    {
        std::tstring_t title = xT("Title1");

        Console console;

        console.setTitle(title);

        m_sRv = console.title();
        xTEST_EQ(m_sRv, title);
    }
#endif

#if xENV_WIN && xTEST_IGNORE
    xTEST_CASE("centerWindow")
    {
        Console console;

        console.centerWindow();
    }
#endif

#if xENV_WIN && xTEST_IGNORE
    xTEST_CASE("setFullScreen")
    {
        Console console;

        console.setFullScreen();
    }
#endif

#if xENV_WIN && xTEST_IGNORE
    xTEST_CASE("enableClose")
    {
        Console console;

        console.enableClose(false);
        console.enableClose(true);
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
