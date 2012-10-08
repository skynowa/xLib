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
    xTEST_CASE(CxCurrentProcess::ulGetCurrId, cullCaseLoops)
    {
        CxProcess::id_t ulRv = CxCurrentProcess::ulGetId();
        xTEST_LESS(0UL, (ulong_t)ulRv);
    }

    xTEST_CASE(CxCurrentProcess::ulGetCurrParentId, cullCaseLoops)
    {
        CxProcess::id_t ulRv = CxCurrentProcess::ulGetParentId();
        xTEST_LESS(0UL, (ulong_t)ulRv);
    }
}
//---------------------------------------------------------------------------
