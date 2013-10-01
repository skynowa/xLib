/**
 * \file   CxTest_CxNonArrayHeap.cpp
 * \brief  test CxNonArrayHeap
 */


#include <Test/Core/CxTest_CxNonArrayHeap.h>


//------------------------------------------------------------------------------
class CNonArrayHeap :
    public CxNonArrayHeap
{
    public:
        int_t m_a;
};
//------------------------------------------------------------------------------
CxTest_CxNonArrayHeap::CxTest_CxNonArrayHeap() {

}
//------------------------------------------------------------------------------
CxTest_CxNonArrayHeap::~CxTest_CxNonArrayHeap() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxNonArrayHeap::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxNonArrayHeap::CxNonArrayHeap", a_cullCaseLoops)
    {
        CNonArrayHeap a[2];
        xUNUSED(a[0].m_a);
        xUNUSED(a[1].m_a);
    }

    xTEST_CASE("CxNonArrayHeap::CxNonArrayHeap", a_cullCaseLoops)
    {
        #if xNOT_COMPILE
            CNonArrayHeap *a = new CNonArrayHeap[10];
        #endif
    }
}
//------------------------------------------------------------------------------
