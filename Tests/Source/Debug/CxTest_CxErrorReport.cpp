/**
 * \file   CxTest_CxErrorReport.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxErrorReport.h>


//---------------------------------------------------------------------------
CxTest_CxErrorReport::CxTest_CxErrorReport() {

}
//---------------------------------------------------------------------------
CxTest_CxErrorReport::~CxTest_CxErrorReport() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxErrorReport::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //CxErrorReport
    xTEST_CASE(cullCaseLoops)
    {
        CxErrorReport rpReport(CxErrorReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), xT("Simple comment: %s"), xT("comment"));
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    //--------------------------------------------------
    //CxErrorReport
    xTEST_CASE(cullCaseLoops)
    {
        CxErrorReport rpReport(CxErrorReport::rtMsgboxPlain, xT("Expression"), CxLastError::ulGet(), xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().sGet(), std::tstring_t(xT("Simple comment")));
        m_sRes = rpReport.sGetReport();
        //xTRACE(m_sRes);
    }

    return true;
}
//---------------------------------------------------------------------------
