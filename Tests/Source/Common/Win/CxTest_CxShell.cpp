/**
 * \file   CxTest_CxShell.cpp
 * \brief
 */


#include <Test/Common/Win/CxTest_CxShell.h>


//---------------------------------------------------------------------------
CxTest_CxShell::CxTest_CxShell() {

}
//---------------------------------------------------------------------------
CxTest_CxShell::~CxTest_CxShell() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxShell::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

#if defined(xOS_ENV_WIN)
    //-------------------------------------
    //bFindExecutable
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxShell::bFindExecutable(xT("win.ini"), xT("C:"));
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //bExecuteEx
    xTEST_BLOCK(cullBlockLoops)
    {
        //SHELLEXECUTEINFO eiExecInfo = {0};
        //m_bRes = CxShell::bExecuteEx(&eiExecInfo);
    }

    //-------------------------------------
    //bExecute
    xTEST_BLOCK(cullBlockLoops)
    {
        //m_bRes = CxShell::bExecute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, int iShowCmd);
    }

    //-------------------------------------
    //bExecuteHttp
    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_bRes = CxShell::bExecuteHttp(xT(" http://www.google.ru/ "));
    }

    //-------------------------------------
    //bExecuteFtp
    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_bRes = CxShell::bExecuteFtp(xT(" ftp://ftp.drweb.com/ "));
    }

    //-------------------------------------
    //bExecuteEmail
    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_bRes = CxShell::bExecuteEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
    }

    //-------------------------------------
    //sGetSpecialDirPath
    xTEST_BLOCK(cullBlockLoops) {
        #if (xWINVER >= xWIN32_2K)
            m_sRes = CxShell::sGetSpecialDirPath(CxShell::sfFonts, NULL);
            xTEST_EQ(std::string_t(xT("C:\\WINDOWS\\Fonts")), m_sRes);
        #endif //xWIN32_2K
    }
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
