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
    const ulonglong_t cullBlockLoops
)
{
    //--------------------------------------------------
    //bSetTextColor
    xTEST_CASE(cullBlockLoops)
    {
        #if xTODO
            CxConsole cnConsole;

            const std::tstring_t     csText;
            const EForeground cfgForeground;
            const bool        cbIsBold;
            const bool        cbIsUnderline;
            const EBackground cbgBackground;
            const bool        cbIsBlink;

            m_sRes = cnConsole.bSetTextColor(csText, cfgForeground, cbIsBold, cbIsUnderline, cbgBackground, cbIsBlink);
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //sRead
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_sRes = cnConsole.sRead();
            // n/a
        #endif
    }

    //--------------------------------------------------
    //bWrite
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_string");


            CxConsole cnConsole;

            m_bRes = cnConsole.bWrite(csStr);
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bWriteLine
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_line");


            CxConsole cnConsole;

            m_bRes = cnConsole.bWriteLine(csStr);
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bWriteErrLine
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csStr = xT("\tConsole_test_error");


            CxConsole cnConsole;

            m_bRes = cnConsole.bWriteLine(csStr);
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //iMsgBox
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csText  = xT("iMsgBox_text");
            const std::tstring_t csTitle = xT("iMsgBox_title");
            const uint_t    cuiType = 0U;


            CxConsole cnConsole;

            CxConsole::EModalResult mrRes = cnConsole.iMsgBox(csText, csTitle, cuiType);
            xUNUSED(mrRes);
        #endif
    }

    //--------------------------------------------------
    //bPrompt
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csPrompt    = xT("bPrompt_simple_prompt");
            const bool    cbIsVisible = true;
            std::tstring_t       sAnswer     = xT("sAnswer_bla-bla-bla");


            CxConsole cnConsole;

            m_bRes = cnConsole.bPrompt(csPrompt, cbIsVisible, &sAnswer);
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bPause
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_bRes = cnConsole.bPause();
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_bRes = cnConsole.bClear();
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //sGetTitle
    xTEST_CASE(cullBlockLoops)
    {
        #if 1 && xOS_ENV_WIN
            std::tstring_t csTitle = xT("Title1");


            CxConsole cnConsole;

            m_bRes = cnConsole.bSetTitle(csTitle);
            xTEST_DIFF(false, m_bRes);

            m_sRes = cnConsole.sGetTitle();
            xTEST_EQ(m_sRes, csTitle);
        #endif
    }

    //--------------------------------------------------
    //bSetTitle
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::tstring_t csTitle = xT("Title1");


            CxConsole cnConsole;

            m_bRes = cnConsole.bSetTitle(csTitle);
            xTEST_DIFF(false, m_bRes);

            #if 1 && xOS_ENV_WIN
                m_sRes = cnConsole.sGetTitle();
                xTEST_EQ(m_sRes, csTitle);
            #endif
        #endif
    }

    //--------------------------------------------------
    //bCenterWindow
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE && xOS_ENV_WIN
            CxConsole cnConsole;

            m_bRes = cnConsole.bCenterWindow();
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bSetFullScreen
    xTEST_CASE(cullBlockLoops)
    {
        #if xTEST_IGNORE && xOS_ENV_WIN
            CxConsole cnConsole;

            m_bRes = cnConsole.bSetFullScreen();
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bEnableClose
    xTEST_CASE(cullBlockLoops)
    {
        #if 0 && xOS_ENV_WIN
            CxConsole cnConsole;

            m_bRes = cnConsole.bEnableClose(false);
            xTEST_DIFF(false, m_bRes);

            m_bRes = cnConsole.bEnableClose(true);
            xTEST_DIFF(false, m_bRes);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
