/**
 * \file   CxTest_CxAutoMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAutoMutex.h>

#include <xLib/Sync/CxMutex.h>


//---------------------------------------------------------------------------
CxTest_CxAutoMutex::CxTest_CxAutoMutex() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoMutex::~CxTest_CxAutoMutex() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxAutoMutex::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //CxAutoMutex
    xTEST_CASE(cullCaseLoops)
    {
        CxMutex mtMutex;

        CxAutoMutex objAutoMutex(mtMutex);
    }

    return true;
}
//---------------------------------------------------------------------------
