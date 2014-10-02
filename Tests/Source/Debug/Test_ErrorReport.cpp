/**
 * \file   Test_ErrorReport.cpp
 * \brief
 */


#include <Test/Debug/Test_ErrorReport.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_ErrorReport::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("ErrorReport::ErrorReport", a_caseLoops)
    {
        ulong_t nativeError = NativeError::get();

        ulong_t val1 = 10UL;
        ulong_t val2 = 20UL;

        ErrorReport rpReport(ErrorReport::rtMsgbox, xT("val1"), xT("val2"), val1, val2,
            xT("=="), nativeError, xFILE, xLINE, xFUNCTION, StackTrace().toString(), xT(""));
    }
}
//-------------------------------------------------------------------------------------------------
