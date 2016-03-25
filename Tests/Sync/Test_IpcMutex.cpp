/**
 * \file   Test_IpcMutex.cpp
 * \brief
 */


#include "Test_IpcMutex.h"

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_IpcMutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_IpcMutex::unit()
{
    std::ctstring_t csName = xT("mutex_name_a");


    xTEST_CASE("handle")
    {
        IpcMutex mtMutex;

        IpcMutex::handle_t hRv;

        hRv = mtMutex.handle();
        xUNUSED(hRv);
        ////xTEST_EQ(false, hRv.bIsValid());
    }

    xTEST_CASE("create")
    {
        IpcMutex mtMutex;

        mtMutex.create(csName);
    }

    xTEST_CASE("open")
    {
        IpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.open(csName);
    }

    xTEST_CASE("lock unlock")
    {
        culong_t culTimeout = 1000UL;

        IpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.lock(culTimeout);
        mtMutex.unlock();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
