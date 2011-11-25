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
/*virtual*/
bool
CxTest_CxStackTrace::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    //--------------------------------------------------
    //bGet
    xTEST_CASE(cullBlockLoops)
    {
        CxStackTrace stStack;
        std::vector<std::tstring_t> vsStack;

        m_bRes = stStack.bGet(&vsStack);
        xTEST_EQ(true, m_bRes);
        xTEST_EQ(false, vsStack.empty());
    }

    //--------------------------------------------------
    //sGet
    xTEST_CASE(cullBlockLoops)
    {
        CxStackTrace stStack;
        std::tstring_t sStack;

        sStack = stStack.sGet();
        xTEST_EQ(false, sStack.empty());
    }

    return true;
}
//---------------------------------------------------------------------------
