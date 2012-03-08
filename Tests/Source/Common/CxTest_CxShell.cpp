/**
 * \file   CxTest_CxShell.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxShell.h>


//---------------------------------------------------------------------------
CxTest_CxShell::CxTest_CxShell() {

}
//---------------------------------------------------------------------------
CxTest_CxShell::~CxTest_CxShell() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxShell::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    /*DEBUG*/

    //-------------------------------------
    //bIsAvailable
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxShell::bIsAvailable();
        xTEST_EQ(true, m_bRes);
    }

    //-------------------------------------
    //bExecute
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t casData[][2] = {
            { xT("cd"), xT("./") },
            { xT("cd"), xT(".")  },
            { xT("cd"), xT("")   },
            { xT(""),   xT("")   }

        #if   xOS_ENV_WIN

        #elif xOS_ENV_UNIX

        #endif
        };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            const std::tstring_t csFilePath = casData[i][0];
            const std::tstring_t csParams   = casData[i][1];

            m_bRes = CxShell::bExecute(csFilePath, csParams);
            xTEST_EQ(true, m_bRes);
        }
    }

#if xOS_ENV_WIN
    //-------------------------------------
    //bFindExecutable
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxShell::bFindExecutable(xT("win.ini"), xT("C:"));
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //bExecuteEx
    xTEST_CASE(cullCaseLoops)
    {
        //SHELLEXECUTEINFO eiExecInfo = {0};
        //m_bRes = CxShell::bExecuteEx(&eiExecInfo);
    }

    //-------------------------------------
    //bExecute
    xTEST_CASE(cullCaseLoops)
    {
        //m_bRes = CxShell::bExecute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, int iShowCmd);
    }

    //-------------------------------------
    //bExecuteHttp
    xTEST_CASE(cullCaseLoops)
    {
        ////m_bRes = CxShell::bExecuteHttp(xT(" http://www.google.ru/ "));
    }

    //-------------------------------------
    //bExecuteFtp
    xTEST_CASE(cullCaseLoops)
    {
        ////m_bRes = CxShell::bExecuteFtp(xT(" ftp://ftp.drweb.com/ "));
    }

    //-------------------------------------
    //bExecuteEmail
    xTEST_CASE(cullCaseLoops)
    {
        ////m_bRes = CxShell::bExecuteEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
    }

    //-------------------------------------
    //sGetSpecialDirPath
    xTEST_CASE(cullCaseLoops) {
        #if (xWINVER >= xOS_WIN_2K)
            m_sRes = CxShell::sGetSpecialDirPath(CxShell::sfFonts, NULL);
            xTEST_EQ(std::tstring_t(xT("C:\\WINDOWS\\Fonts")), m_sRes);
        #endif //xOS_WIN_2K
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
