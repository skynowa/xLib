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
        m_bRv = CxShell::bIsAvailable();
        xTEST_EQ(true, m_bRv);
    }

    //-------------------------------------
    //bExecute
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t casData[][2] = {
            { xT("cd"), xT("./") },
            { xT("cd"), xT(".")  },
            { xT(""),   xT("")   }

        #if   xOS_ENV_WIN

        #elif xOS_ENV_UNIX

        #endif
        };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            const std::tstring_t csFilePath = casData[i][0];
            const std::tstring_t csParams   = casData[i][1];

            m_bRv = CxShell::bExecute(csFilePath, csParams);
            xTEST_EQ(true, m_bRv);
        }
    }

#if xOS_ENV_WIN
    //-------------------------------------
    //bFindExecutable
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxShell::bFindExecutable(xT("win.ini"), xT("C:"));
        xTEST_EQ(false, m_sRv.empty());
    }

    //-------------------------------------
    //bExecuteEx
    xTEST_CASE(cullCaseLoops)
    {
        //SHELLEXECUTEINFO eiExecInfo = {0};
        //m_bRv = CxShell::bExecuteEx(&eiExecInfo);
    }

    //-------------------------------------
    //bExecute
    xTEST_CASE(cullCaseLoops)
    {
        //m_bRv = CxShell::bExecute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, int iShowCmd);
    }

    //-------------------------------------
    //bExecuteHttp
    xTEST_CASE(cullCaseLoops)
    {
        ////m_bRv = CxShell::bExecuteHttp(xT(" http://www.google.ru/ "));
    }

    //-------------------------------------
    //bExecuteFtp
    xTEST_CASE(cullCaseLoops)
    {
        ////m_bRv = CxShell::bExecuteFtp(xT(" ftp://ftp.drweb.com/ "));
    }

    //-------------------------------------
    //bExecuteEmail
    xTEST_CASE(cullCaseLoops)
    {
        ////m_bRv = CxShell::bExecuteEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
    }

    //-------------------------------------
    //sGetSpecialDirPath
    xTEST_CASE(cullCaseLoops) {
        #if (xWINVER >= xOS_WIN_2K)
            m_sRv = CxShell::sGetSpecialDirPath(CxShell::sfFonts, NULL);
            xTEST_EQ(std::tstring_t(xT("C:\\WINDOWS\\Fonts")), m_sRv);
        #endif //xOS_WIN_2K
    }
#endif

    return true;
}
//---------------------------------------------------------------------------
