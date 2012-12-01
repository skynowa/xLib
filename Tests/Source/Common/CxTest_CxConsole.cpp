/**
 * \file   CxTest_CxConsole.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxConsole.h>


//---------------------------------------------------------------------------
CxTest_CxConsole::CxTest_CxConsole() {

}
//---------------------------------------------------------------------------
CxTest_CxConsole::~CxTest_CxConsole() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxConsole::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxConsole::sSetAttributes", cullCaseLoops)
    {
        CxConsole cnConsole;

        std::tstring_t          sText;
        CxConsole::ExForeground fgForeground = CxConsole::fgBlue;
        CxConsole::ExBackground bgBackground = CxConsole::bgYellow;
        int                     iAttributes  = CxConsole::atBold | CxConsole::atUnderscore | CxConsole::atReverse;

        m_sRv = cnConsole.sSetAttributes(fgForeground, bgBackground, iAttributes);
        xTEST_NA(m_sRv);

        m_sRv = cnConsole.sSetAttributesDef();
        xTEST_NA(m_sRv);
    }

    xTEST_CASE("CxConsole::sRead", cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_sRv = cnConsole.sRead();
            xTEST_NA(m_sRv);
        #endif
    }

    xTEST_CASE("CxConsole::vWrite", cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_string");

            CxConsole cnConsole;

            cnConsole.vWrite(csStr);
        #endif
    }

    xTEST_CASE("CxConsole::vWriteLine", cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_line");

            CxConsole cnConsole;

            cnConsole.vWriteLine(csStr);
        #endif
    }

    xTEST_CASE("CxConsole::vWriteLine", cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_error");

            CxConsole cnConsole;

            cnConsole.vWriteLine(csStr);
        #endif
    }

    xTEST_CASE("CxConsole::iMsgBox", cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csText  = xT("iMsgBox_text");
            const std::tstring_t csTitle = xT("iMsgBox_title");
            const uint_t    cuiType = 0U;


            CxConsole cnConsole;

            CxConsole::ExModalResult mrRes = cnConsole.iMsgBox(csText, csTitle, cuiType);
            xUNUSED(mrRes);
        #endif
    }

    xTEST_CASE("CxConsole::vPrompt", cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csPrompt    = xT("vPrompt_simple_prompt");
            const bool           cbIsVisible = true;
            std::tstring_t       sAnswer     = xT("sAnswer_bla-bla-bla");

            CxConsole cnConsole;

            cnConsole.vPrompt(csPrompt, cbIsVisible, &sAnswer);
        #endif
    }

    xTEST_CASE("CxConsole::vPause", cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            cnConsole.vPause(3 * 1000UL);
            cnConsole.vPause(xTIMEOUT_INFINITE);
        #endif
    }

    xTEST_CASE("CxConsole::vClear", cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            cnConsole.vClear();
        #endif
    }

    xTEST_CASE("CxConsole::sTitle", cullCaseLoops)
    {
        #if   xOS_ENV_WIN && xTEST_IGNORE
            std::tstring_t csTitle = xT("Title1");

            CxConsole cnConsole;

            cnConsole.vSetTitle(csTitle);

            m_sRv = cnConsole.sTitle();
            xTEST_EQ(m_sRv, csTitle);
        #endif
    }

    xTEST_CASE("CxConsole::vSetTitle", cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csTitle = xT("Title1");


            CxConsole cnConsole;

            cnConsole.vSetTitle(csTitle);

            #if 1 && xOS_ENV_WIN
                m_sRv = cnConsole.sTitle();
                xTEST_EQ(m_sRv, csTitle);
            #endif
        #endif
    }

    xTEST_CASE("CxConsole::vCenterWindow", cullCaseLoops)
    {
        #if xTEST_IGNORE && xOS_ENV_WIN
            CxConsole cnConsole;

            cnConsole.vCenterWindow();
        #endif
    }

    xTEST_CASE("CxConsole::vSetFullScreen", cullCaseLoops)
    {
        #if   xOS_ENV_WIN && xTEST_IGNORE
            CxConsole cnConsole;

            cnConsole.vSetFullScreen();
        #endif
    }

    xTEST_CASE("CxConsole::vEnableClose", cullCaseLoops)
    {
        #if  xOS_ENV_WIN && xTEST_IGNORE
            CxConsole cnConsole;

            cnConsole.vEnableClose(false);
            cnConsole.vEnableClose(true);
        #endif
    }
}
//---------------------------------------------------------------------------
