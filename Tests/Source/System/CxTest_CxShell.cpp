/**
 * \file   CxTest_CxShell.cpp
 * \brief
 */


#include <Test/System/CxTest_CxShell.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxShell::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxShell::isAvailable", a_cullCaseLoops)
    {
        m_bRv = CxShell::isAvailable();
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxShell::execute", a_cullCaseLoops)
    {
        std::ctstring_t casData[][2] = {
            { xT("cd"), xT("./") },
            { xT("cd"), xT(".")  },
            { xT(""),   xT("")   }

        #if   xOS_ENV_WIN

        #elif xOS_ENV_UNIX

        #endif
        };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            std::ctstring_t csFilePath = casData[i][0];
            std::ctstring_t csParams   = casData[i][1];

            CxShell::execute(csFilePath, csParams);
        }
    }

#if   xOS_ENV_WIN

    xTEST_CASE("CxShell::findExecutable", a_cullCaseLoops)
    {
        m_sRv = CxShell::findExecutable(xT("win.ini"), xT("C:"));
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxShell::executeEx", a_cullCaseLoops)
    {
        // SHELLEXECUTEINFO eiExecInfo = {0};
        // CxShell::executeEx(&eiExecInfo);
    }

    xTEST_CASE("CxShell::execute", a_cullCaseLoops)
    {
        // CxShell::execute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, int_t iShowCmd);
    }

    xTEST_CASE("CxShell::executeHttp", a_cullCaseLoops)
    {
        // CxShell::executeHttp(xT(" http://www.google.ru/ "));
    }

    xTEST_CASE("CxShell::executeFtp", a_cullCaseLoops)
    {
        // CxShell::executeFtp(xT(" ftp://ftp.drweb.com/ "));
    }

    xTEST_CASE("CxShell::executeEmail", a_cullCaseLoops)
    {
        // CxShell::executeEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
    }

    xTEST_CASE("CxShell::specialDirPath", a_cullCaseLoops) {
        #if (xWINVER >= xOS_WIN_2K)
            m_sRv = CxShell::specialDirPath(CxShell::sfFonts, NULL);
            xTEST_EQ(std::tstring_t(xT("C:\\WINDOWS\\Fonts")), m_sRv);
        #endif //xOS_WIN_2K
    }
#endif
}
//------------------------------------------------------------------------------
