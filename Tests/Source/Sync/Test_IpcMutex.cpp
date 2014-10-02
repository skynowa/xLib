/**
 * \file   Test_IpcMutex.cpp
 * \brief
 */


#include <Test/Sync/Test_IpcMutex.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_IpcMutex::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t csName = xT("mutex_name_a");


    xTEST_CASE("IpcMutex::handle", a_caseLoops)
    {
        IpcMutex mtMutex;

        IpcMutex::handle_t hRv;

        hRv = mtMutex.handle();
        xUNUSED(hRv);
        ////xTEST_EQ(false, hRv.bIsValid());
    }

    xTEST_CASE("IpcMutex::create", 1)
    {
        IpcMutex mtMutex;

        mtMutex.create(csName);
    }

    xTEST_CASE("IpcMutex::open", 1)
    {
        IpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.open(csName);
    }

    xTEST_CASE("IpcMutex::lock unlock", a_caseLoops)
    {
        culong_t culTimeout = 1000UL;

        IpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.lock(culTimeout);
        mtMutex.unlock();
    }
}
//-------------------------------------------------------------------------------------------------
