/**
 * \file   CxTest_CxStackTrace.cpp
 * \brief  test CxStackTrace
 */


#include <Test/Debug/CxTest_CxStackTrace.h>


//---------------------------------------------------------------------------
CxTest_CxStackTrace::CxTest_CxStackTrace() {

}
//---------------------------------------------------------------------------
CxTest_CxStackTrace::~CxTest_CxStackTrace() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxStackTrace::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxStackTrace::get", cullCaseLoops)
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

    xTEST_CASE("CxStackTrace::toString", cullCaseLoops)
    {
        CxStackTrace stStack;

        m_sRv = stStack.toString();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxStackTrace::toString", cullCaseLoops)
    {
        #if xTEST_IGNORE
            xTEST_FAIL;
        #endif
    }
}
//---------------------------------------------------------------------------
