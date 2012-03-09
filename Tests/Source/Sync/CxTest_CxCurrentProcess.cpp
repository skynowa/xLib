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
/*virtual*/
bool
CxTest_CxCurrentProcess::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //ulGetCurrId
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::TxId ulRes = CxCurrentProcess::ulGetId();
        xTEST_LESS(0UL, (ulong_t)ulRes);
    }

    //--------------------------------------------------
    //ulGetCurrParentId
    xTEST_CASE(cullCaseLoops)
    {
        CxProcess::TxId ulRes = CxCurrentProcess::ulGetParentId();
        xTEST_LESS(0UL, (ulong_t)ulRes);
    }

    return true;
}
//---------------------------------------------------------------------------
