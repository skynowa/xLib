/**
 * \file   Test_IpcMutex.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_IpcMutex)
xTEST_UNIT(Test_IpcMutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_IpcMutex::unit()
{
    std::ctstring_t name = Format::str(xT("{}-MutexName"), getData().name);

    xTEST_CASE("handle")
    {
        IpcMutex mutex;
        IpcMutex::handle_t hRv;
        hRv = mutex.handle();
        xTEST(hRv == nullptr);
    }

    xTEST_CASE("create")
    {
        IpcMutex mutex;
        mutex.create(name);
    }

    xTEST_CASE("open")
    {
        IpcMutex mutex;
        mutex.create(name);
        mutex.open(name);
    }

    xTEST_CASE("lock / unlock")
    {
        culong_t timeoutMsec {1000UL};

        IpcMutex mutex;
        mutex.create(name);
        mutex.lock(timeoutMsec);
        mutex.unlock();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
