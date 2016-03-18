/**
 * \file   Test_StackTrace.cpp
 * \brief  test StackTrace
 */


#include <Test/Debug/Test_StackTrace.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_StackTrace)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_StackTrace::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("toString", a_caseLoops)
    {
        StackTrace stStack;

        m_sRv = stStack.toString();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("toString", a_caseLoops)
    {
        #if xTEST_IGNORE
            xTEST_FAIL;
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
