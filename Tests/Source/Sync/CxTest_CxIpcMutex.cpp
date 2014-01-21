/**
 * \file   CxTest_CxIpcMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxIpcMutex.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxIpcMutex::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t csName = xT("mutex_name_a");


    xTEST_CASE("CxIpcMutex::handle", a_caseLoops)
    {
        CxIpcMutex mtMutex;

        CxIpcMutex::handle_t hRv;

        hRv = mtMutex.handle();
        xUNUSED(hRv);
        ////xTEST_EQ(false, hRv.bIsValid());
    }

    xTEST_CASE("CxIpcMutex::create", 1)
    {
        CxIpcMutex mtMutex;

        mtMutex.create(csName);
    }

    xTEST_CASE("CxIpcMutex::open", 1)
    {
        CxIpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.open(csName);
    }

    xTEST_CASE("CxIpcMutex::lock CxIpcMutex::unlock", a_caseLoops)
    {
        culong_t culTimeout = 1000UL;

        CxIpcMutex mtMutex;

        mtMutex.create(csName);
        mtMutex.lock(culTimeout);
        mtMutex.unlock();
    }
}
//-------------------------------------------------------------------------------------------------
