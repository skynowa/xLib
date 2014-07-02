/**
 * \file   Test_Shell.cpp
 * \brief
 */


#include <Test/System/Test_Shell.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Shell::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Shell::isAvailable", a_caseLoops)
    {
        m_bRv = Shell().isAvailable();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("Shell::execute", a_caseLoops)
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

            Shell().execute(csFilePath, csParams);
        }
    }

#if   xENV_WIN
    xTEST_CASE("Shell::findExecutable", a_caseLoops)
    {
        #if xTEST_IGNORE
            m_sRv = Shell().findExecutable(xT("win.ini"), xT("C:"));
            xTEST_EQ(false, m_sRv.empty());
        #endif
    }

    xTEST_CASE("Shell::executeEx", a_caseLoops)
    {
        #if xTEST_IGNORE
            SHELLEXECUTEINFO execInfo = {0};
            Shell().executeEx(execInfo);
        #endif
    }

    xTEST_CASE("Shell::execute", a_caseLoops)
    {
        #if xTEST_IGNORE
            Shell().execute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, int_t iShowCmd);
        #endif
    }

    xTEST_CASE("Shell::executeHttp", a_caseLoops)
    {
        #if xTEST_IGNORE
            Shell().executeHttp(xT(" http://www.google.ru/ "));
        #endif
    }

    xTEST_CASE("Shell::executeFtp", a_caseLoops)
    {
        #if xTEST_IGNORE
            Shell().executeFtp(xT(" ftp://ftp.drweb.com/ "));
        #endif
    }

    xTEST_CASE("Shell::executeEmail", a_caseLoops)
    {
        #if xTEST_IGNORE
            Shell().executeEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
        #endif
    }

    xTEST_CASE("Shell::specialDirPath", a_caseLoops)
    {
        m_sRv = Shell().specialDirPath(Shell::sfFonts, NULL);
        xTEST_EQ(std::tstring_t(xT("C:\\WINDOWS\\Fonts")), m_sRv);
    }
#endif
}
//-------------------------------------------------------------------------------------------------
