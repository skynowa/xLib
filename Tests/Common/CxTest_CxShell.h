/****************************************************************************
* Class name:  CxTest_CxShell
* Description: test CxShell
* File name:   CxTest_CxShell.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxShellH
#define CxTest_CxShellH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/Win/CxShell.h>
//---------------------------------------------------------------------------
class CxTest_CxShell :
    public CxTest
{
    public:
        CxTest_CxShell();
        virtual     ~CxTest_CxShell();

        virtual     BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxShell (comment)
CxTest_CxShell::CxTest_CxShell() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxShell (comment)
CxTest_CxShell::~CxTest_CxShell() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL CxTest_CxShell::bUnit() {
    /*DEBUG*/

    //-------------------------------------
    //bFindExecutable
    {
        m_sRes = CxShell::bFindExecutable(xT("win.ini"), xT("C:"));
        xASSERT(false == m_sRes.empty());
    }

    //-------------------------------------
    //bExecuteEx
    {
        //SHELLEXECUTEINFO eiExecInfo = {0};
        //m_bRes = CxShell::bExecuteEx(&eiExecInfo);
    }

    //-------------------------------------
    //bExecute
    {
        //m_bRes = CxShell::bExecute(HWND hWnd, LPCTSTR pcszOperation, LPCTSTR pcszFile, LPCTSTR pcszParams, LPCTSTR pcszDirectory, INT iShowCmd);
    }

    //-------------------------------------
    //bExecuteHttp
    {
        ////m_bRes = CxShell::bExecuteHttp(xT(" http://www.google.ru/ "));
    }

    //-------------------------------------
    //bExecuteFtp
    {
        ////m_bRes = CxShell::bExecuteFtp(xT(" ftp://ftp.drweb.com/ "));
    }

    //-------------------------------------
    //bExecuteEmail
    {
        ////m_bRes = CxShell::bExecuteEmail(xT("  Sky_Nova@mail.ru "), xT("  Subject"), xT("  Body  "));
    }

    //-------------------------------------
    //sGetSpecialDirPath
    #if (xWINVER >= xWIN32_2K)
        m_sRes = CxShell::sGetSpecialDirPath(CxShell::sfFonts, NULL);
        xASSERT(xT("C:\\WINDOWS\\Fonts") == m_sRes);
    #endif //xWIN32_2K

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxShellH
