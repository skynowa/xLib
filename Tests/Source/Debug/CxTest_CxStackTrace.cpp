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
    //--------------------------------------------------
    // bGet
    xTEST_CASE(cullCaseLoops)
    {
        CxStackTrace                    stStack;
        std::vector<std::vec_tstring_t> vvsStack;

        stStack.vGet(&vvsStack);
        xTEST_EQ(false, vvsStack.empty());

        #if xTEST_IGNORE
            std::tcout << xT("stack trace:") << std::endl;
            std::tcout << vsStack            << std::endl;
        #endif
    }

    //--------------------------------------------------
    // sGet
    xTEST_CASE(cullCaseLoops)
    {
        CxStackTrace stStack;

        m_sRv = stStack.sGet();
        xTEST_EQ(false, m_sRv.empty());
    }

    //--------------------------------------------------
    // xTEST_FAIL
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            xTEST_FAIL;
        #endif
    }
}
//---------------------------------------------------------------------------
