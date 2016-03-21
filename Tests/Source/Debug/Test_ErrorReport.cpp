/**
 * \file   Test_ErrorReport.cpp
 * \brief
 */


#include <Test/Debug/Test_ErrorReport.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_ErrorReport)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_ErrorReport::unit()
{
    xTEST_CASE("ErrorReport")
    {
        ulong_t nativeError = NativeError::get();

        ulong_t val1 = 10UL;
        ulong_t val2 = 20UL;

        ErrorReport rpReport(ErrorReport::rtMsgbox, xT("val1"), xT("val2"), val1, val2,
            xT("=="), nativeError, xSOURCE_INFO, StackTrace().toString(), xT(""));
    }
}
//-------------------------------------------------------------------------------------------------
