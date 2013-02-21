/**
 * \file   CxTest_CxAutoIpcMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAutoIpcMutex.h>

#include <xLib/Sync/CxIpcMutex.h>


//------------------------------------------------------------------------------
CxTest_CxAutoIpcMutex::CxTest_CxAutoIpcMutex() {

}
//------------------------------------------------------------------------------
CxTest_CxAutoIpcMutex::~CxTest_CxAutoIpcMutex() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxAutoIpcMutex::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csName = xT("mutex_name_a");

    xTEST_CASE("CxAutoIpcMutex::CxAutoIpcMutex", cullCaseLoops)
    {
        CxIpcMutex mtMutex;

        CxAutoIpcMutex objAutoMutex(mtMutex, csName);
    }
}
//------------------------------------------------------------------------------
