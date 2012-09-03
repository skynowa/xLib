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
/*virtual*/
bool
CxTest_CxConsole::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //bSetTextColor
    xTEST_CASE(cullCaseLoops)
    {
        #if xTODO
            CxConsole cnConsole;

            const std::tstring_t     csText;
            const EForeground cfgForeground;
            const bool        cbIsBold;
            const bool        cbIsUnderline;
            const EBackground cbgBackground;
            const bool        cbIsBlink;

            m_sRv = cnConsole.bSetTextColor(csText, cfgForeground, cbIsBold, cbIsUnderline, cbgBackground, cbIsBlink);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //sRead
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_sRv = cnConsole.sRead();
            // n/a
        #endif
    }

    //--------------------------------------------------
    //bWrite
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_string");


            CxConsole cnConsole;

            m_bRv = cnConsole.bWrite(csStr);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //bWriteLine
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_line");


            CxConsole cnConsole;

            m_bRv = cnConsole.bWriteLine(csStr);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //bWriteErrLine
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_error");


            CxConsole cnConsole;

            m_bRv = cnConsole.bWriteLine(csStr);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //iMsgBox
    xTEST_CASE(cullCaseLoops)
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

    //--------------------------------------------------
    //bPrompt
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csPrompt    = xT("bPrompt_simple_prompt");
            const bool           cbIsVisible = true;
            std::tstring_t       sAnswer     = xT("sAnswer_bla-bla-bla");


            CxConsole cnConsole;

            m_bRv = cnConsole.bPrompt(csPrompt, cbIsVisible, &sAnswer);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //bPause
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_bRv = cnConsole.bPause();
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_bRv = cnConsole.bClear();
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //sGetTitle
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN && xTEST_IGNORE
            std::tstring_t csTitle = xT("Title1");


            CxConsole cnConsole;

            m_bRv = cnConsole.bSetTitle(csTitle);
            xTEST_EQ(true, m_bRv);

            m_sRv = cnConsole.sGetTitle();
            xTEST_EQ(m_sRv, csTitle);
        #endif
    }

    //--------------------------------------------------
    //bSetTitle
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csTitle = xT("Title1");


            CxConsole cnConsole;

            m_bRv = cnConsole.bSetTitle(csTitle);
            xTEST_EQ(true, m_bRv);

            #if 1 && xOS_ENV_WIN
                m_sRv = cnConsole.sGetTitle();
                xTEST_EQ(m_sRv, csTitle);
            #endif
        #endif
    }

    //--------------------------------------------------
    //bCenterWindow
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE && xOS_ENV_WIN
            CxConsole cnConsole;

            m_bRv = cnConsole.bCenterWindow();
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //bSetFullScreen
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN && xTEST_IGNORE
            CxConsole cnConsole;

            m_bRv = cnConsole.bSetFullScreen();
            xTEST_EQ(true, m_bRv);
        #endif
    }

    //--------------------------------------------------
    //bEnableClose
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN && xTEST_IGNORE
            CxConsole cnConsole;

            m_bRv = cnConsole.bEnableClose(false);
            xTEST_EQ(true, m_bRv);

            m_bRv = cnConsole.bEnableClose(true);
            xTEST_EQ(true, m_bRv);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
