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
        ulong_t lastError = CxLastError::get();

        ulong_t val1 = 10UL;
        ulong_t val2 = 20UL;

        CxErrorReport rpReport(CxErrorReport::rtMsgbox, xT("val1"), xT("val2"), val1, val2,
            xT("=="), lastError, xFILE, xLINE, xFUNCTION, xDATE, xTIME, CxStackTrace().toString(),
            xT(""));
    }
}
//------------------------------------------------------------------------------
