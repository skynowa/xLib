/**
 * \file   CxTest_CxSocketInit.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxSocketInit.h>


//------------------------------------------------------------------------------
CxTest_CxSocketInit::CxTest_CxSocketInit() {

}
//------------------------------------------------------------------------------
CxTest_CxSocketInit::~CxTest_CxSocketInit() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxSocketInit::unit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE("CxSocketInit::CxSocketInit", cullCaseLoops)
    {
        CxSocketInit siInit10(1, 0);
        CxSocketInit siInit11(1, 1);
        CxSocketInit siInit20(2, 0);
        CxSocketInit siInit21(2, 1);
        CxSocketInit siInit22(2, 2);
    }
}
//------------------------------------------------------------------------------
