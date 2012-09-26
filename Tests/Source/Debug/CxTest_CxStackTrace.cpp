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
bool
CxTest_CxStackTrace::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    // bGet
    xTEST_CASE(cullCaseLoops)
    {
        CxStackTrace                    stStack;
        std::vector<std::vec_tstring_t> vvsStack;

        m_bRv = stStack.bGet(&vvsStack);
        xTEST_EQ(true,  m_bRv);
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
    // xASSERT
    xTEST_CASE(cullCaseLoops)
    {
        #if xTEST_IGNORE
            xASSERT(false);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
