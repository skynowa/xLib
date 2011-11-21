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
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bGet
    xTEST_CASE(cullBlockLoops)
    {
        CxStackTrace stStack;
        std::vector<std::tstring> vsStack;

        m_bRes = stStack.bGet(&vsStack);
        xTEST_DIFF(false, m_bRes);
        xTEST_EQ(false, vsStack.empty());
    }

    //--------------------------------------------------
    //sGet
    xTEST_CASE(cullBlockLoops)
    {
        CxStackTrace stStack;
        std::tstring sStack;

        sStack = stStack.sGet();
        xTEST_EQ(false, sStack.empty());
    }

    return true;
}
//---------------------------------------------------------------------------
