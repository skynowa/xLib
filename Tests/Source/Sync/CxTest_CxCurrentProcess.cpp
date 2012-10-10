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
    xTEST_CASE(CxCurrentProcess::ulCurrId, cullCaseLoops)
    {
        CxProcess::id_t ulRv = CxCurrentProcess::ulId();
        xTEST_LESS(0UL, (ulong_t)ulRv);
    }

    xTEST_CASE(CxCurrentProcess::ulCurrParentId, cullCaseLoops)
    {
        CxProcess::id_t ulRv = CxCurrentProcess::ulParentId();
        xTEST_LESS(0UL, (ulong_t)ulRv);
    }
}
//---------------------------------------------------------------------------
