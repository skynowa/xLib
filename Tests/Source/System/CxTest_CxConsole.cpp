/**
 * \file   CxTest_CxConsole.cpp
 * \brief
 */


#include <Test/System/CxTest_CxConsole.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxConsole::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxConsole::setAttributes", a_caseLoops)
    {
        CxConsole console;

        std::tstring_t          text;
        CxConsole::ExForeground foreground = CxConsole::fgBlue;
        CxConsole::ExBackground background = CxConsole::bgYellow;
        int_t                   attributes = CxConsole::atBold | CxConsole::atUnderscore |
                                             CxConsole::atReverse;

        m_sRv = console.setAttributes(foreground, background, attributes);
        xTEST_NA(m_sRv);

        m_sRv = console.setAttributesDef();
        xTEST_NA(m_sRv);
    }

    xTEST_CASE("CxConsole::read", a_caseLoops)
    {
        #if xTEST_IGNORE
            CxConsole console;

            m_sRv = console.read();
            xTEST_NA(m_sRv);
        #endif
    }

    xTEST_CASE("CxConsole::write", a_caseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t str = xT("\tConsole_test_string");

            CxConsole console;

            console.write(str);
        #endif
    }

    xTEST_CASE("CxConsole::writeLine", a_caseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t str = xT("\tConsole_test_line");

            CxConsole console;

            console.writeLine(str);
        #endif
    }

    xTEST_CASE("CxConsole::writeLine", a_caseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t str = xT("\tConsole_test_error");

            CxConsole console;

            console.writeLine(str);
        #endif
    }

    xTEST_CASE("CxConsole::msgBox", a_caseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t text  = xT("iMsgBox_text");
            std::ctstring_t title = xT("iMsgBox_title");
            cuint_t         type  = 0U;


            CxConsole console;

            CxConsole::ExModalResult mrRes = console.msgBox(text, title, type);
            xUNUSED(mrRes);
        #endif
    }

    xTEST_CASE("CxConsole::prompt", a_caseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t prompt    = xT("vPrompt_simple_prompt");
            cbool_t         isVisible = true;
            std::tstring_t  answer    = xT("sAnswer_bla-bla-bla");

            CxConsole console;

            console.prompt(prompt, isVisible, &answer);
        #endif
    }

    xTEST_CASE("CxConsole::pause", a_caseLoops)
    {
        #if xTEST_IGNORE
            CxConsole console;

            console.pause(3 * 1000UL);
            console.pause(xTIMEOUT_INFINITE);
        #endif
    }

    xTEST_CASE("CxConsole::clear", a_caseLoops)
    {
        #if xTEST_IGNORE
            CxConsole console;

            console.clear();
        #endif
    }

    xTEST_CASE("CxConsole::title", a_caseLoops)
    {
        #if xOS_ENV_WIN && xTEST_IGNORE
            std::tstring_t title = xT("Title1");

            CxConsole console;

            console.setTitle(title);

            m_sRv = console.title();
            xTEST_EQ(m_sRv, title);
        #endif
    }

    xTEST_CASE("CxConsole::setTitle", a_caseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t title = xT("Title1");


            CxConsole console;

            console.setTitle(title);

            #if 1 && xOS_ENV_WIN
                m_sRv = console.title();
                xTEST_EQ(m_sRv, title);
            #endif
        #endif
    }

#if xOS_ENV_WIN && xTEST_IGNORE
    xTEST_CASE("CxConsole::centerWindow", a_caseLoops)
    {
        CxConsole console;

        console.centerWindow();
    }
#endif

#if xOS_ENV_WIN && xTEST_IGNORE
    xTEST_CASE("CxConsole::setFullScreen", a_caseLoops)
    {
        CxConsole console;

        console.setFullScreen();
    }
#endif

#if xOS_ENV_WIN && xTEST_IGNORE
    xTEST_CASE("CxConsole::enableClose", a_caseLoops)
    {
        CxConsole console;

        console.enableClose(false);
        console.enableClose(true);
    }
#endif
}
//------------------------------------------------------------------------------
