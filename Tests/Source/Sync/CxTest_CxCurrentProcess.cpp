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
BOOL
CxTest_CxCurrentProcess::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //ulGetCurrId
    xTEST_BLOCK(cullBlockLoops)
    {
        CxProcess::TxId ulRes = CxCurrentProcess::ulGetId();
        xTEST_LESS_EQ(0UL, (ULONG)ulRes);
    }

    //--------------------------------------------------
    //ulGetCurrParentId
    xTEST_BLOCK(cullBlockLoops)
    {
        CxProcess::TxId ulRes = CxCurrentProcess::ulGetParentId();
        xTEST_LESS_EQ(0UL, (ULONG)ulRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
