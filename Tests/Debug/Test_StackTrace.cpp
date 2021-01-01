/**
 * \file   Test_StackTrace.cpp
 * \brief  test StackTrace
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_StackTrace)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_StackTrace::unit()
{
    xTEST_CASE("str")
    {
        StackTrace stack;

        m_sRv = stack.str();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
