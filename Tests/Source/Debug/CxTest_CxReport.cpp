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
CxTest_CxReport::CxTest_CxReport() {

}
//---------------------------------------------------------------------------
CxTest_CxReport::~CxTest_CxReport() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxReport::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //CxReport
    xTEST_BLOCK(cullBlockLoops)
    {
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT("Simple comment: %s"), xT("comment"));
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    //--------------------------------------------------
    //CxReport
    xTEST_BLOCK(cullBlockLoops)
    {
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), std::tstring(xT("Simple comment")));
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
