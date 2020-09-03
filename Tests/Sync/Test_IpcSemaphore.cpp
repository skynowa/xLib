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
    xTEST_CASE("IpcSemaphore")
    {
        struct _Functor
        {
        #if   xENV_WIN
            static uint_t   xSTDCALL
        #elif xENV_UNIX
            static void_t * xSTDCALL
        #endif
            worker(void_t *param)
            {
                auto *semaphore = static_cast<IpcSemaphore *>(param);
                xTEST_PTR(semaphore);

                for (int_t i = 0; i < 50; i ++) {
                    semaphore->wait(xTIMEOUT_INFINITE);
                }

                return 0;
            }
        };

        // create
        IpcSemaphore semaphore;
        semaphore.create(4, xT("sema_name"));

    #if   xENV_WIN
        uintptr_t puiRv = ::_beginthreadex(nullptr, 0U, &_Functor::worker, &semaphore, 0U, nullptr);
        #if xARCH_BITS_32
            xTEST_DIFF(puiRv, uintptr_t(0));
        #else
            xTEST_PTR(puiRv);
        #endif
    #elif xENV_UNIX
        pthread_t id {};
        int_t iRv = ::pthread_create(&id, nullptr, &_Functor::worker, &semaphore);
        xTEST_EQ(iRv, 0);
    #endif

        // post
        for (size_t i = 0; i < 50; ++ i) {
            Thread::currentSleep(1);
            for (int_t x = 0; x < 2; x ++) {
                semaphore.post();
            }
        }

        Thread::currentSleep(10);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
