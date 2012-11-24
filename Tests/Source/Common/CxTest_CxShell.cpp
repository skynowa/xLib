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
/* virtual */
void
CxTest_CxShell::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxShell::bIsAvailable", cullCaseLoops)
    {
        m_bRv = CxShell::bIsAvailable();
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxShell::vExecute", cullCaseLoops)
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

            CxShell::vExecute(csFilePath, csParams);
        }
    }

#if   xOS_ENV_WIN

    xTEST_CASE("CxShell::sFindExecutable", cullCaseLoops)
    {
        m_sRv = CxShell::sFindExecutable(xT("win.ini"), xT("C:"));
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxShell::vExecuteEx", cullCaseLoops)
    {
        // SHELLEXECUTEINFO eiExecInfo = {0};
        // CxShell::vExecuteEx(&eiExecInfo);
    }

    xTEST_CASE("CxShell::vExecute", cullCaseLoops)
    {
        // CxShell::vExecute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, int iShowCmd);
    }

    xTEST_CASE("CxShell::vExecuteHttp", cullCaseLoops)
    {
        // CxShell::vExecuteHttp(xT(" http://www.google.ru/ "));
    }

    xTEST_CASE("CxShell::", cullCaseLoops)
    {
        // CxShell::vExecuteFtp(xT(" ftp://ftp.drweb.com/ "));
    }

    xTEST_CASE("CxShell::vExecuteEmail", cullCaseLoops)
    {
        // CxShell::vExecuteEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
    }

    xTEST_CASE("CxShell::sGetSpecialDirPath", cullCaseLoops) {
        #if (xWINVER >= xOS_WIN_2K)
            m_sRv = CxShell::sGetSpecialDirPath(CxShell::sfFonts, NULL);
            xTEST_EQ(std::tstring_t(xT("C:\\WINDOWS\\Fonts")), m_sRv);
        #endif //xOS_WIN_2K
    }
#endif
}
//---------------------------------------------------------------------------
