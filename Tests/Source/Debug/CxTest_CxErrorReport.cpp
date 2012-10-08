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
/* virtual */
void
CxTest_CxErrorReport::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxErrorReport::CxErrorReport, cullCaseLoops)
    {
        ulong_t ulLastError = CxLastError::ulGet();

        ulong_t val1 = 10;
        ulong_t val2 = 20;

        CxErrorReport rpReport(CxErrorReport::rtMsgboxPlain, val1, val2, "val1", "val2", xT("=="),
                               ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME,
                               CxStackTrace().sGet(), xT(""));
    }
}
//---------------------------------------------------------------------------
