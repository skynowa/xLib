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
void
CxTest_CxNonHeap::unit(
    culonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxNonHeap::CxNonHeap", cullCaseLoops)
    {
        CNonHeap a;
        xUNUSED(a);
    }

    xTEST_CASE("CxNonHeap::CxNonHeap", cullCaseLoops)
    {
        #if xNOT_COMPILE
            CNonHeap *a = new CNonHeap;
        #endif
    }
}
//------------------------------------------------------------------------------
