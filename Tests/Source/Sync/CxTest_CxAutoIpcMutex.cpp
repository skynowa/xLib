/**
 * \file   CxTest_CxAutoIpcMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxAutoIpcMutex.h>

#include <xLib/Sync/CxIpcMutex.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxAutoIpcMutex::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t csName = xT("mutex_name_a");

    xTEST_CASE("CxAutoIpcMutex::CxAutoIpcMutex", a_caseLoops)
    {
        CxIpcMutex mtMutex;

        CxAutoIpcMutex objAutoMutex(mtMutex, csName);
    }
}
//-------------------------------------------------------------------------------------------------
