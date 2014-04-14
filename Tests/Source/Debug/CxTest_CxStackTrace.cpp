/**
 * \file   CxTest_CxStackTrace.cpp
 * \brief  test CxStackTrace
 */


#include <Test/Debug/CxTest_CxStackTrace.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxStackTrace::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxStackTrace::toString", a_caseLoops)
    {
        CxStackTrace stStack;

        m_sRv = stStack.toString();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxStackTrace::toString", a_caseLoops)
    {
        #if xTEST_IGNORE
            xTEST_FAIL;
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
