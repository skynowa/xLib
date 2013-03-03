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
void_t
CxTest_CxAutoIpcMutex::unit(
    culonglong_t &cullCaseLoops
)
{
    std::ctstring_t csName = xT("mutex_name_a");

    xTEST_CASE("CxAutoIpcMutex::CxAutoIpcMutex", cullCaseLoops)
    {
        CxIpcMutex mtMutex;

        CxAutoIpcMutex objAutoMutex(mtMutex, csName);
    }
}
//------------------------------------------------------------------------------
