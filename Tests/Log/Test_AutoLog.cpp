/**
 * \file   Test_Trace.cpp
 * \brief  test Trace
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Trace)
xTEST_UNIT(Test_Trace)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Trace::unit()
{
    cbool_t isEnabled = true;

    xTEST_CASE("AutoTrace")
    {
        AutoTrace autoLog(xT("AutoTrace"), isEnabled);
    }

    xTEST_CASE("AutoFileLog")
    {
        AutoTrace autoLog(xT("AutoFileLog"), isEnabled);
    }

    xTEST_CASE("AutoSystemLog")
    {
        AutoTrace autoLog(xT("AutoSystemLog"), isEnabled);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
