/**
 * \file   CxTest_CxCurrentProcess.cpp
 * \brief  test CxCurrentProcess
 */


#include <Test/Sync/CxTest_CxCurrentProcess.h>


//---------------------------------------------------------------------------
CxTest_CxCurrentProcess::CxTest_CxCurrentProcess() {

}
//---------------------------------------------------------------------------
CxTest_CxCurrentProcess::~CxTest_CxCurrentProcess() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxCurrentProcess::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    //--------------------------------------------------
    //ulGetCurrId
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::id_t ulRv = CxCurrentProcess::ulGetId();
        xTEST_LESS(0UL, (ulong_t)ulRv);
    }

    //--------------------------------------------------
    //ulGetCurrParentId
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::id_t ulRv = CxCurrentProcess::ulGetParentId();
        xTEST_LESS(0UL, (ulong_t)ulRv);
    }
}
//---------------------------------------------------------------------------
