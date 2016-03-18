/**
 * \file   Test_AutoIpcMutex.cpp
 * \brief
 */


#include <Test/Sync/Test_AutoIpcMutex.h>

#include <xLib/Sync/IpcMutex.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_AutoIpcMutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_AutoIpcMutex::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t csName = xT("mutex_name_a");

    xTEST_CASE("AutoIpcMutex", a_caseLoops)
    {
        IpcMutex mtMutex;

        AutoIpcMutex objAutoMutex(mtMutex, csName);
    }
}
//-------------------------------------------------------------------------------------------------
