/**
 * \file   Test_Trace.cpp
 * \brief  test Trace
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Trace)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Trace::unit()
{
    cbool_t isEnabled {true};

    xTEST_CASE("AutoTrace")
    {
        AutoTrace autoLog(xT("AutoTrace"), isEnabled);
    }

    xTEST_CASE("AutoFileLog")
    {
        AutoFileLog autoLog(xT("AutoFileLog"), isEnabled);
    }

    xTEST_CASE("AutoSystemLog")
    {
        AutoSystemLog autoLog(xT("AutoSystemLog"), isEnabled);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
