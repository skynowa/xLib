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
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //CxReport
    xTEST_CASE(cullCaseLoops)
    {
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT("Simple comment: %s"), xT("comment"));
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    //--------------------------------------------------
    //CxReport
    xTEST_CASE(cullCaseLoops)
    {
        CxReport rpReport(CxReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), std::tstring_t(xT("Simple comment")));
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    return true;
}
//---------------------------------------------------------------------------
