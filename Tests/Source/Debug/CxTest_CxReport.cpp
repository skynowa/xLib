/**
 * \file   CxTest_CxReport.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxReport.h>


//---------------------------------------------------------------------------
CxTest_CxReport::CxTest_CxReport() {

}
//---------------------------------------------------------------------------
CxTest_CxReport::~CxTest_CxReport() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxReport::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //CxReport
    xTEST_CASE(cullBlockLoops)
    {
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT("Simple comment: %s"), xT("comment"));
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    //--------------------------------------------------
    //CxReport
    xTEST_CASE(cullBlockLoops)
    {
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), std::tstring(xT("Simple comment")));
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    return true;
}
//---------------------------------------------------------------------------
