/**
 * \file   CxTest_CxSocketInit.cpp
 * \brief
 */


#include <Test/Net/CxTest_CxSocketInit.h>


//---------------------------------------------------------------------------
CxTest_CxSocketInit::CxTest_CxSocketInit() {

}
//---------------------------------------------------------------------------
CxTest_CxSocketInit::~CxTest_CxSocketInit() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxSocketInit::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    //-------------------------------------
    //CxSocketInit
    xTEST_BLOCK(cullBlockLoops)
    {
        CxSocketInit siInit10(1, 0);
        CxSocketInit siInit11(1, 1);
        CxSocketInit siInit20(2, 0);
        CxSocketInit siInit21(2, 1);
        CxSocketInit siInit22(2, 2);
    }

    return true;
}
//---------------------------------------------------------------------------
