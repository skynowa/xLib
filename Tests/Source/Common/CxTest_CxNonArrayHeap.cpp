/**
 * \file   CxTest_CxNonArrayHeap.cpp
 * \brief  test CxNonArrayHeap
 */


#include <Test/Common/CxTest_CxNonArrayHeap.h>


//---------------------------------------------------------------------------
class A : 
    public CxNonArrayHeap 
{

};
//---------------------------------------------------------------------------
CxTest_CxNonArrayHeap::CxTest_CxNonArrayHeap() {

}
//---------------------------------------------------------------------------
CxTest_CxNonArrayHeap::~CxTest_CxNonArrayHeap() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxNonArrayHeap::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxNonArrayHeap::CxNonArrayHeap", cullCaseLoops)
    {
        A a[10];
    }

    xTEST_CASE("CxNonArrayHeap::CxNonArrayHeap", cullCaseLoops)
    {
        #if xNOT_COMPILE
            A *a = new A[10];
        #endif
    }
}
//---------------------------------------------------------------------------
