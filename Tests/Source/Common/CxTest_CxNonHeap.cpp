/**
 * \file   CxTest_CxNonHeap.cpp
 * \brief  test CxNonHeap
 */


#include <Test/Common/CxTest_CxNonHeap.h>


//---------------------------------------------------------------------------
class A : 
    public CxNonHeap 
{

};
//---------------------------------------------------------------------------
CxTest_CxNonHeap::CxTest_CxNonHeap() {

}
//---------------------------------------------------------------------------
CxTest_CxNonHeap::~CxTest_CxNonHeap() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxNonHeap::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxNonHeap::CxNonHeap", cullCaseLoops)
    {
        A a;
    }

    xTEST_CASE("CxNonHeap::CxNonHeap", cullCaseLoops)
    {
        #if xNOT_COMPILE
            A *a = new A;
        #endif
    }
}
//---------------------------------------------------------------------------
