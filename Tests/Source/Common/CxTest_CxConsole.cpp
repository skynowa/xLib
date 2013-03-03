/**
 * \file   CxTest_CxConsole.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxConsole.h>


//------------------------------------------------------------------------------
CxTest_CxConsole::CxTest_CxConsole() {

}
//------------------------------------------------------------------------------
CxTest_CxConsole::~CxTest_CxConsole() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxConsole::unit(
    culonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxConsole::setAttributes", cullCaseLoops)
    {
        CxConsole cnConsole;

        std::tstring_t          sText;
        CxConsole::ExForeground fgForeground = CxConsole::fgBlue;
        CxConsole::ExBackground bgBackground = CxConsole::bgYellow;
        int_t                     iAttributes  = CxConsole::atBold | CxConsole::atUnderscore | CxConsole::atReverse;

        m_sRv = cnConsole.setAttributes(fgForeground, bgBackground, iAttributes);
        xTEST_NA(m_sRv);

        m_sRv = cnConsole.setAttributesDef();
        xTEST_NA(m_sRv);
    }

    xTEST_CASE("CxConsole::read", cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_sRv = cnConsole.read();
            xTEST_NA(m_sRv);
        #endif
    }

    xTEST_CASE("CxConsole::write", cullCaseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t csStr = xT("\tConsole_test_string");

            CxConsole cnConsole;

            cnConsole.write(csStr);
        #endif
    }

    xTEST_CASE("CxConsole::writeLine", cullCaseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t csStr = xT("\tConsole_test_line");

            CxConsole cnConsole;

            cnConsole.writeLine(csStr);
        #endif
    }

    xTEST_CASE("CxConsole::writeLine", cullCaseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t csStr = xT("\tConsole_test_error");

            CxConsole cnConsole;

            cnConsole.writeLine(csStr);
        #endif
    }

    xTEST_CASE("CxConsole::msgBox", cullCaseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t csText  = xT("iMsgBox_text");
            std::ctstring_t csTitle = xT("iMsgBox_title");
            cuint_t         cuiType = 0U;


            CxConsole cnConsole;

            CxConsole::ExModalResult mrRes = cnConsole.msgBox(csText, csTitle, cuiType);
            xUNUSED(mrRes);
        #endif
    }

    xTEST_CASE("CxConsole::prompt", cullCaseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t csPrompt    = xT("vPrompt_simple_prompt");
            cbool_t           cbIsVisible = true;
            std::tstring_t       sAnswer     = xT("sAnswer_bla-bla-bla");

            CxConsole cnConsole;

            cnConsole.prompt(csPrompt, cbIsVisible, &sAnswer);
        #endif
    }

    xTEST_CASE("CxConsole::pause", cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            cnConsole.pause(3 * 1000UL);
            cnConsole.pause(xTIMEOUT_INFINITE);
        #endif
    }

    xTEST_CASE("CxConsole::clear", cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            cnConsole.clear();
        #endif
    }

    xTEST_CASE("CxConsole::title", cullCaseLoops)
    {
        #if   xOS_ENV_WIN && xTEST_IGNORE
            std::tstring_t csTitle = xT("Title1");

            CxConsole cnConsole;

            cnConsole.setTitle(csTitle);

            m_sRv = cnConsole.title();
            xTEST_EQ(m_sRv, csTitle);
        #endif
    }

    xTEST_CASE("CxConsole::setTitle", cullCaseLoops)
    {
        #if xTEST_IGNORE
            std::ctstring_t csTitle = xT("Title1");


            CxConsole cnConsole;

            cnConsole.setTitle(csTitle);

            #if 1 && xOS_ENV_WIN
                m_sRv = cnConsole.title();
                xTEST_EQ(m_sRv, csTitle);
            #endif
        #endif
    }

    xTEST_CASE("CxConsole::centerWindow", cullCaseLoops)
    {
        #if xTEST_IGNORE && xOS_ENV_WIN
            CxConsole cnConsole;

            cnConsole.centerWindow();
        #endif
    }

    xTEST_CASE("CxConsole::setFullScreen", cullCaseLoops)
    {
        #if   xOS_ENV_WIN && xTEST_IGNORE
            CxConsole cnConsole;

            cnConsole.setFullScreen();
        #endif
    }

    xTEST_CASE("CxConsole::enableClose", cullCaseLoops)
    {
        #if  xOS_ENV_WIN && xTEST_IGNORE
            CxConsole cnConsole;

            cnConsole.enableClose(false);
            cnConsole.enableClose(true);
        #endif
    }
}
//------------------------------------------------------------------------------
