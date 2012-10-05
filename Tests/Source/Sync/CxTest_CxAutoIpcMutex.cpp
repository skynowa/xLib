/**
 * \file   CxTest_CxAutoIpcMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAutoIpcMutex.h>

#include <xLib/Sync/CxIpcMutex.h>


//---------------------------------------------------------------------------
CxTest_CxAutoIpcMutex::CxTest_CxAutoIpcMutex() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoIpcMutex::~CxTest_CxAutoIpcMutex() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxAutoIpcMutex::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csName = xT("mutex_name_a");

    //-------------------------------------
    //CxAutoIpcMutex
    xTEST_CASE(cullCaseLoops)
    {
        CxIpcMutex mtMutex;

        CxAutoIpcMutex objAutoMutex(mtMutex, csName);
    }
}
//---------------------------------------------------------------------------
