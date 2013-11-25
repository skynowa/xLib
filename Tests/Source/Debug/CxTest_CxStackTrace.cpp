/**
 * \file   CxTest_CxStackTrace.cpp
 * \brief  test CxStackTrace
 */


#include <Test/Debug/CxTest_CxStackTrace.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxStackTrace::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxStackTrace::get", a_caseLoops)
    {
        CxStackTrace                    stStack;
        std::vector<std::vec_tstring_t> vvsStack;

        stStack.get(&vvsStack);
        xTEST_EQ(false, vvsStack.empty());

        #if xTEST_IGNORE && 0
            std::tcout << xT("stack trace:") << std::endl;
            std::tcout << vvsStack           << std::endl;
        #endif
    }

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
//------------------------------------------------------------------------------
