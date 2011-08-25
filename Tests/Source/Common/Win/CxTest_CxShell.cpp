/****************************************************************************
* Class name:  CxTest_CxShell
* Description: test CxShell
* File name:   CxTest_CxShell.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/Win/CxTest_CxShell.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxShell
CxTest_CxShell::CxTest_CxShell() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxShell
CxTest_CxShell::~CxTest_CxShell() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxShell::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

#if defined(xOS_WIN)
    //-------------------------------------
    //bFindExecutable
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxShell::bFindExecutable(xT("win.ini"), xT("C:"));
        xASSERT_EQ(false, m_sRes.empty());
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
        //m_bRes = CxShell::bExecute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, INT iShowCmd);
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
            xASSERT_EQ(std::tstring(xT("C:\\WINDOWS\\Fonts")), m_sRes);
        #endif //xWIN32_2K
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
