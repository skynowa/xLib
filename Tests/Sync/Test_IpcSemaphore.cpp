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
/* virtual */
bool_t
Test_IpcSemaphore::unit()
{
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

			for (int_t i = 0; i < 50; i ++) {
				sem->wait(xTIMEOUT_INFINITE);
			}

			return 0;
		}
	};

	IpcSemaphore semaphore;

    xTEST_CASE("create")
    {
		semaphore.create(4, xT("sema_name"));
		xTEST_PTR(semaphore.handle());

	#if   xENV_WIN
		uintptr_t puiRv = ::_beginthreadex(nullptr, 0, &Worker::exec, &semaphore, 0, nullptr);
		xTEST_PTR(puiRv);
	#elif xENV_UNIX
		pthread_t id {};
		int_t iRv = ::pthread_create(&id, nullptr, &Worker::exec, &semaphore);
		xTEST_EQ(iRv, 0);
	#endif

		Thread::currentSleep(50);
    }

    xTEST_CASE("post")
    {
        for (size_t i = 0; i < 50; ++ i) {
            Thread::currentSleep(1);

            for (int_t x = 0; x < 2; x ++) {
                semaphore.post();
            }
        }
    }

    xTEST_CASE("dtor")
    {
    }

	Thread::currentSleep(10);

    return true;
}
//-------------------------------------------------------------------------------------------------
