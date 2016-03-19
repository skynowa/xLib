/**
 * \file   Test_IpcMutex.cpp
 * \brief
 */


#include <Test/Sync/Test_IpcMutex.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_IpcMutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_IpcMutex::unit(
    std::csize_t &a_caseLoops
)
{
    std::ctstring_t csName = xT("mutex_name_a");


    xTEST_CASE("handle", a_caseLoops)
    {
        IpcMutex mtMutex;

        IpcMutex::handle_t hRv;

        hRv = mtMutex.handle();
        xUNUSED(hRv);
        ////xTEST_EQ(false, hRv.bIsValid());
    }

    xTEST_CASE("create", 1)
    {
        IpcMutex mtMutex;

        mtMutex.create(csName);
    }

    xTEST_CASE("open", 1)
    {
        IpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.open(csName);
    }

    xTEST_CASE("lock unlock", a_caseLoops)
    {
        culong_t culTimeout = 1000UL;

        IpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.lock(culTimeout);
        mtMutex.unlock();
    }
}
//-------------------------------------------------------------------------------------------------
