/**
 * \file   CxTest_CxNonHeap.cpp
 * \brief  test CxNonHeap
 */


#include <Test/Common/CxTest_CxNonHeap.h>


//------------------------------------------------------------------------------
class CNonHeap :
    public CxNonHeap
{

};
//------------------------------------------------------------------------------
CxTest_CxNonHeap::CxTest_CxNonHeap() {

}
//------------------------------------------------------------------------------
CxTest_CxNonHeap::~CxTest_CxNonHeap() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxNonHeap::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxNonHeap::CxNonHeap", a_cullCaseLoops)
    {
        CNonHeap a;
        xUNUSED(a);
    }

    xTEST_CASE("CxNonHeap::CxNonHeap", a_cullCaseLoops)
    {
        #if xNOT_COMPILE
            CNonHeap *a = new CNonHeap;
        #endif
    }
}
//------------------------------------------------------------------------------
