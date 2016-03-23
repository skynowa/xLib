/**
 * \file   Test_Shell.cpp
 * \brief
 */


#include <Test/System/Test_Shell.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Shell)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Shell::unit()
{
    xTEST_CASE("isAvailable")
    {
        m_bRv = Shell().isAvailable();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("execute")
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
    xTEST_CASE("findExecutable")
    {
        #if xTEST_IGNORE
            m_sRv = Shell().findExecutable(xT("win.ini"), xT("C:"));
            xTEST_EQ(false, m_sRv.empty());
        #endif
    }

    xTEST_CASE("executeEx")
    {
        #if xTEST_IGNORE
            SHELLEXECUTEINFO execInfo = {0};
            Shell().executeEx(execInfo);
        #endif
    }

    xTEST_CASE("execute")
    {
        #if xTEST_IGNORE
            Shell().execute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, int_t iShowCmd);
        #endif
    }

    xTEST_CASE("executeHttp")
    {
        #if xTEST_IGNORE
            Shell().executeHttp(xT(" http://www.google.ru/ "));
        #endif
    }

    xTEST_CASE("executeFtp")
    {
        #if xTEST_IGNORE
            Shell().executeFtp(xT(" ftp://ftp.drweb.com/ "));
        #endif
    }

    xTEST_CASE("executeEmail")
    {
        #if xTEST_IGNORE
            Shell().executeEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
        #endif
    }

    xTEST_CASE("specialDirPath")
    {
        m_sRv = Shell().specialDirPath(Shell::sfFonts, xPTR_NULL);
        xTEST_EQ(std::tstring_t(xT("C:\\WINDOWS\\Fonts")), m_sRv);
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
