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
BOOL
CxTest_CxStackTrace::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bGet
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStackTrace stStack;
        std::vector<std::tstring> vsStack;

        m_bRes = stStack.bGet(&vsStack);
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_EQ(false, vsStack.empty());
    }

    //--------------------------------------------------
    //sGet
    xTEST_BLOCK(cullBlockLoops)
    {
        CxStackTrace stStack;
        std::tstring sStack;

        sStack = stStack.sGet();
        xTEST_EQ(false, sStack.empty());
    }

    return TRUE;
}
//---------------------------------------------------------------------------
