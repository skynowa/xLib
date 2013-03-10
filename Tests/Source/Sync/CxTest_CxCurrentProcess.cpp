/**
 * \file   CxTest_CxCurrentProcess.cpp
 * \brief  test CxCurrentProcess
 */


#include <Test/Sync/CxTest_CxCurrentProcess.h>


//------------------------------------------------------------------------------
CxTest_CxCurrentProcess::CxTest_CxCurrentProcess() {

}
//------------------------------------------------------------------------------
CxTest_CxCurrentProcess::~CxTest_CxCurrentProcess() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxCurrentProcess::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxCurrentProcess::id", a_cullCaseLoops)
    {
        CxProcess::id_t ulRv = CxCurrentProcess::id();
        xTEST_LESS(0UL, (ulong_t)ulRv);
    }

    xTEST_CASE("CxCurrentProcess::parentId", a_cullCaseLoops)
    {
        CxProcess::id_t ulRv = CxCurrentProcess::parentId();
        xTEST_LESS(0UL, (ulong_t)ulRv);
    }
}
//------------------------------------------------------------------------------
