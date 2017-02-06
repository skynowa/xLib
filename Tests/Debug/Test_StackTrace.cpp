/**
 * \file   Test_StackTrace.cpp
 * \brief  test StackTrace
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_StackTrace)
xTEST_UNIT(Test_StackTrace)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_StackTrace::unit()
{
    xTEST_CASE("toString")
    {
        StackTrace stStack;

        m_sRv = stStack.toString();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("toString")
    {
        #if xTEST_IGNORE
            xTEST_FAIL;
        #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
