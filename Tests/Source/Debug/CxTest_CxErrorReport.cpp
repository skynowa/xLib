/**
 * \file   CxTest_CxErrorReport.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxErrorReport.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxErrorReport::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxErrorReport::CxErrorReport", a_caseLoops)
    {
        ulong_t ulLastError = CxLastError::get();

        ulong_t val1 = 10;
        ulong_t val2 = 20;

        CxErrorReport rpReport(CxErrorReport::rtMsgboxPlain, xT("val1"), xT("val2"), val1, val2, xT("=="),
                               ulLastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME,
                               CxStackTrace().toString(), xT(""));
    }
}
//------------------------------------------------------------------------------
