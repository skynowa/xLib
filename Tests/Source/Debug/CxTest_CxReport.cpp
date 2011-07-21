/****************************************************************************
* Class name:  CxTest_CxReport
* Description: test CxReport
* File name:   CxTest_CxReport.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Debug/CxTest_CxReport.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxReport
CxTest_CxReport::CxTest_CxReport() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxReport
CxTest_CxReport::~CxTest_CxReport() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxReport::bUnit() {
    //--------------------------------------------------
    //CxReport
    {
std::cout << 0 << std::endl;
        tString f  = xFILE;
        tString fu = xFUNCTION;
        ULONG   l  = xLINE;
        tString d  = xDATE;
        tString t  = xTIME;

        std::cout << f  << std::endl;
        std::cout << fu << std::endl;
        std::cout << l  << std::endl;
        std::cout << d  << std::endl;
        std::cout << t  << std::endl;

        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), f, l, fu, d, t, xT("Simple comment: %s"), xT("comment"));
std::cout << 1 << std::endl;
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }
std::cout << 2 << std::endl;
    //--------------------------------------------------
    //CxReport
    {
        tString f  = xFILE;
        tString fu = xFUNCTION;
        ULONG   l  = xLINE;
        tString d  = xDATE;
        tString t  = xTIME;

        std::cout << f  << std::endl;
        std::cout << fu << std::endl;
        std::cout << l  << std::endl;
        std::cout << d  << std::endl;
        std::cout << t  << std::endl;
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), f, l, fu, d, t, tString(xT("Simple comment")));
std::cout << 3 << std::endl;
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }
std::cout << 4 << std::endl;
    return TRUE;
}
//---------------------------------------------------------------------------

