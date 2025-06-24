/**
 * \file   Test_IpcSemaphore.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
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
        std::ctstring_t name = Format::str(xT("{}-SemaName"), option().name);
        /// std::ctstring_t name = xT("sema_name");

		semaphore.create(4, name);
		xTEST_PTR(semaphore.handle());

	#if   xENV_WIN
		HANDLE puiRv = (HANDLE)::_beginthreadex(nullptr, 0, &Worker::exec, &semaphore, 0, nullptr);
		xTEST(puiRv != 0);
	#elif xENV_UNIX
		pthread_t id {};
		int_t iRv = ::pthread_create(&id, nullptr, &Worker::exec, &semaphore);
		xTEST_EQ(iRv, 0);
	#endif

		ThreadCurrent::sleep(10);
    }

    xTEST_CASE("post")
    {
        for (size_t i = 0; i < ::valuesNum; ++ i) {
        	ThreadCurrent::sleep(1);

            semaphore.post();
            semaphore.post();
        }
    }

    xTEST_CASE("dtor")
    {
    }

    ThreadCurrent::sleep(10);

    return true;
}
//-------------------------------------------------------------------------------------------------
