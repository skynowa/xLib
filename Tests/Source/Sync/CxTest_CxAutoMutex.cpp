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
    const std::tstring_t csName = xT("mutex_name_a");

    //-------------------------------------
    //CxAutoMutex
    xTEST_CASE(cullCaseLoops)
    {
        CxMutex mtMutex;

        CxAutoMutex objAutoMutex(mtMutex, csName);
    }

    return true;
}
//---------------------------------------------------------------------------
