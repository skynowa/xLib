/**
 * \file   CxTest_CxSocketInit.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxSocketInit.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSocketInit::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxSocketInit::CxSocketInit", a_caseLoops)
    {
        CxSocketInit siInit10(1, 0);
        CxSocketInit siInit11(1, 1);
        CxSocketInit siInit20(2, 0);
        CxSocketInit siInit21(2, 1);
        CxSocketInit siInit22(2, 2);
    }
}
//-------------------------------------------------------------------------------------------------
