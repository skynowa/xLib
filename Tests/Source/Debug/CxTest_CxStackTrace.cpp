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
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //bGet
    xTEST_CASE(cullCaseLoops)
    {
        CxStackTrace stStack;
        std::vector<std::tstring_t> vsStack;

        m_bRv = stStack.bGet(&vsStack);
        //xTEST_EQ(true, m_bRv);
        //xTEST_EQ(false, vsStack.empty());
    }

    //--------------------------------------------------
    //sGet
    xTEST_CASE(cullCaseLoops)
    {
        CxStackTrace stStack;
        std::tstring_t sStack;

        sStack = stStack.sGet();
        //xTEST_EQ(false, sStack.empty());
    }

    /*****************************************************************************/
    #if xTEMP_DISABLED
        std::vector<std::string> vsStack;

        CxStackTrace stStack;

        stStack.bGet(&vsStack, 64);

        std::tcerr << "stack trace:" << std::endl;
        std::tcerr << vsStack        << std::endl;
    #endif
    /*****************************************************************************/

    return true;
}
//---------------------------------------------------------------------------
