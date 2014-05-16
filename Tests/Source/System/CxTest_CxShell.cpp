/**
 * \file   CxTest_CxShell.cpp
 * \brief
 */


#include <Test/System/CxTest_CxShell.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxShell::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxShell::isAvailable", a_caseLoops)
    {
        m_bRv = CxShell().isAvailable();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("CxShell::execute", a_caseLoops)
    {
        std::ctstring_t casData[][2] = {
            { xT("cd"), xT("./") },
            { xT("cd"), xT(".")  },
            { xT(""),   xT("")   }

        #if   xENV_WIN

        #elif xENV_UNIX

        #endif
        };

        for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
            std::ctstring_t csFilePath = casData[i][0];
            std::ctstring_t csParams   = casData[i][1];

            CxShell().execute(csFilePath, csParams);
        }
    }

#if   xENV_WIN
    xTEST_CASE("CxShell::findExecutable", a_caseLoops)
    {
        #if xTEST_IGNORE
            m_sRv = CxShell().findExecutable(xT("win.ini"), xT("C:"));
            xTEST_EQ(false, m_sRv.empty());
        #endif
    }

    xTEST_CASE("CxShell::executeEx", a_caseLoops)
    {
        #if xTEST_IGNORE
            SHELLEXECUTEINFO execInfo = {0};
            CxShell().executeEx(execInfo);
        #endif
    }

    xTEST_CASE("CxShell::execute", a_caseLoops)
    {
        #if xTEST_IGNORE
            CxShell().execute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, int_t iShowCmd);
        #endif
    }

    xTEST_CASE("CxShell::executeHttp", a_caseLoops)
    {
        #if xTEST_IGNORE
            CxShell().executeHttp(xT(" http://www.google.ru/ "));
        #endif
    }

    xTEST_CASE("CxShell::executeFtp", a_caseLoops)
    {
        #if xTEST_IGNORE
            CxShell().executeFtp(xT(" ftp://ftp.drweb.com/ "));
        #endif
    }

    xTEST_CASE("CxShell::executeEmail", a_caseLoops)
    {
        #if xTEST_IGNORE
            CxShell().executeEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
        #endif
    }

    xTEST_CASE("CxShell::specialDirPath", a_caseLoops)
    {
        m_sRv = CxShell().specialDirPath(CxShell::sfFonts, NULL);
        xTEST_EQ(std::tstring_t(xT("C:\\WINDOWS\\Fonts")), m_sRv);
    }
#endif
}
//-------------------------------------------------------------------------------------------------
