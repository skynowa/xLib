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
BOOL
CxTest_CxConsole::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bSetTextColor
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTODO
            CxConsole cnConsole;

            const std::string_t     csText;
            const EForeground cfgForeground;
            const BOOL        cbIsBold;
            const BOOL        cbIsUnderline;
            const EBackground cbgBackground;
            const BOOL        cbIsBlink;

            m_sRes = cnConsole.bSetTextColor(csText, cfgForeground, cbIsBold, cbIsUnderline, cbgBackground, cbIsBlink);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //sRead
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_sRes = cnConsole.sRead();
            // n/a
        #endif
    }

    //--------------------------------------------------
    //bWrite
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::string_t csStr = xT("\tConsole_test_string");


            CxConsole cnConsole;

            m_bRes = cnConsole.bWrite(csStr);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bWriteLine
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::string_t csStr = xT("\tConsole_test_line");


            CxConsole cnConsole;

            m_bRes = cnConsole.bWriteLine(csStr);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bWriteErrLine
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::string_t csStr = xT("\tConsole_test_error");


            CxConsole cnConsole;

            m_bRes = cnConsole.bWriteLine(csStr);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //iMsgBox
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::string_t csText  = xT("iMsgBox_text");
            const std::string_t csTitle = xT("iMsgBox_title");
            const UINT    cuiType = 0U;


            CxConsole cnConsole;

            CxConsole::EModalResult mrRes = cnConsole.iMsgBox(csText, csTitle, cuiType);
            xUNUSED(mrRes);
        #endif
    }

    //--------------------------------------------------
    //bPrompt
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::string_t csPrompt    = xT("bPrompt_simple_prompt");
            const BOOL    cbIsVisible = TRUE;
            std::string_t       sAnswer     = xT("sAnswer_bla-bla-bla");


            CxConsole cnConsole;

            m_bRes = cnConsole.bPrompt(csPrompt, cbIsVisible, &sAnswer);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bPause
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_bRes = cnConsole.bPause();
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            CxConsole cnConsole;

            m_bRes = cnConsole.bClear();
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //sGetTitle
    xTEST_BLOCK(cullBlockLoops)
    {
        #if 1 && xOS_ENV_WIN
            std::string_t csTitle = xT("Title1");


            CxConsole cnConsole;

            m_bRes = cnConsole.bSetTitle(csTitle);
            xTEST_DIFF(FALSE, m_bRes);

            m_sRes = cnConsole.sGetTitle();
            xTEST_EQ(m_sRes, csTitle);
        #endif
    }

    //--------------------------------------------------
    //bSetTitle
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE
            const std::string_t csTitle = xT("Title1");


            CxConsole cnConsole;

            m_bRes = cnConsole.bSetTitle(csTitle);
            xTEST_DIFF(FALSE, m_bRes);

            #if 1 && xOS_ENV_WIN
                m_sRes = cnConsole.sGetTitle();
                xTEST_EQ(m_sRes, csTitle);
            #endif
        #endif
    }

    //--------------------------------------------------
    //bCenterWindow
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE && xOS_ENV_WIN
            CxConsole cnConsole;

            m_bRes = cnConsole.bCenterWindow();
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bSetFullScreen
    xTEST_BLOCK(cullBlockLoops)
    {
        #if xTEST_IGNORE && xOS_ENV_WIN
            CxConsole cnConsole;

            m_bRes = cnConsole.bSetFullScreen();
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    //--------------------------------------------------
    //bEnableClose
    xTEST_BLOCK(cullBlockLoops)
    {
        #if 0 && xOS_ENV_WIN
            CxConsole cnConsole;

            m_bRes = cnConsole.bEnableClose(FALSE);
            xTEST_DIFF(FALSE, m_bRes);

            m_bRes = cnConsole.bEnableClose(TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
