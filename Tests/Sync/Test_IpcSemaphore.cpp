/**
 * \file   Test_IpcSemaphore.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_IpcSemaphore)
xTEST_UNIT(Test_IpcSemaphore)
//-------------------------------------------------------------------------------------------------
namespace
{

std::size_t valuesNum {50};

}
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_IpcSemaphore::unit()
{
	{
		// TODO: Test_IpcSemaphore - fix tests
		xTRACE_NOT_IMPLEMENTED

		return true;
	}

	struct Worker
	{
	#if   xENV_WIN
		using rv_exec_t = uint_t;
	#elif xENV_UNIX
		using rv_exec_t = void_t *;
	#endif

		static rv_exec_t xSTDCALL
		exec(void_t *param)
		{
			auto *sem = static_cast<IpcSemaphore *>(param);
			xTEST_PTR(sem);

			for (size_t i = 0; i < ::valuesNum; i ++) {
				sem->wait(xTIMEOUT_INFINITE);
			}

			return 0;
		}
	};

	IpcSemaphore semaphore;

    xTEST_CASE("create")
    {
        std::ctstring_t name = Format::str(xT("{}-SemaName"), getData().name);
        /// std::ctstring_t name = xT("sema_name");

		semaphore.create(4, name);
		xTEST_PTR(semaphore.handle());

	#if   xENV_WIN
		uintptr_t puiRv = ::_beginthreadex(nullptr, 0, &Worker::exec, &semaphore, 0, nullptr);
		xTEST_PTR(puiRv);
	#elif xENV_UNIX
		pthread_t id {};
		int_t iRv = ::pthread_create(&id, nullptr, &Worker::exec, &semaphore);
		xTEST_EQ(iRv, 0);
	#endif

		Thread::currentSleep(10);
    }

    xTEST_CASE("post")
    {
        for (size_t i = 0; i < ::valuesNum; ++ i) {
            Thread::currentSleep(1);

            semaphore.post();
            semaphore.post();
        }
    }

    xTEST_CASE("dtor")
    {
    }

	Thread::currentSleep(10);

    return true;
}
//-------------------------------------------------------------------------------------------------
