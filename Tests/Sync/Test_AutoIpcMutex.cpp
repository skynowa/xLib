/**
 * \file   Test_AutoIpcMutex.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_AutoIpcMutex)
xTEST_UNIT(Test_AutoIpcMutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_AutoIpcMutex::unit()
{
    std::ctstring_t csName = xT("mutex_name_a");

    xTEST_CASE("AutoIpcMutex")
    {
        IpcMutex mtMutex;

        AutoIpcMutex objAutoMutex(mtMutex, csName);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
