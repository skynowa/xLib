/**
 * \file   Test_Condition.cpp
 * \brief  test Condition
 */


#include "Test_Condition.h"

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Condition)
//-------------------------------------------------------------------------------------------------
#if xENV_UNIX

std::csize_t    threadsNum   = 3;
std::csize_t    counterMax   = 12;
size_t          counter      = 0;
size_t          jobLoops     = 10;

pthread_mutex_t mtMutex      = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cndCondition = PTHREAD_COND_INITIALIZER;

#endif // xENV_UNIX
//-------------------------------------------------------------------------------------------------
#if xENV_UNIX

static
void_t *
watch(
    void_t *a_param
)
{
    int_t iRv  = - 1;

    clong_t id = *(static_cast<long_t *>( a_param ));
    xUNUSED(id);

    Trace() << Format::str(xT("watch(): starting thread {}"), id);

   /**
    * Lock mutex and wait for signal.  Note that the pthread_cond_wait
    * routine will automatically and atomically unlock mutex while it waits.
    * Also, note that if COUNT_LIMIT is reached before this routine is run by
    * the waiting thread, the loop will be skipped to prevent pthread_cond_wait
    * from never returning.
    */

    iRv = ::pthread_mutex_lock(&::mtMutex);
    xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

    {
        while (::counter < ::counterMax) {
            iRv = ::pthread_cond_wait(&::cndCondition, &::mtMutex);
            xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

            Trace() << Format::str(xT("watch(): thread: {} Condition signal received"), id);

            ::counter += 125;

            Trace() << Format::str(xT("watch(): thread: {} counter: {}"), id, ::counter);
        }
    }

    iRv = ::pthread_mutex_unlock(&::mtMutex);
    xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

    return xPTR_NULL;
}

#endif // xENV_UNIX
//-------------------------------------------------------------------------------------------------
#if xENV_UNIX

static
void_t *
job(
    void_t *a_param
)
{
    int_t iRv  = - 1;

    clong_t id = *(static_cast<long_t *>( a_param ));
    xUNUSED(id);

    for (size_t i = 0; i < ::jobLoops; ++ i) {
        iRv = ::pthread_mutex_lock(&::mtMutex);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        {
            ++ ::counter;

            // Check the value of count and signal waiting thread when condition is reached
            if (::counter == ::counterMax) {
                iRv = ::pthread_cond_signal(&::cndCondition);
                xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

                Trace() << Format::str(xT("job(): thread: {} counter: {} threshold reached"), id, ::counter);
            }

            Trace() << Format::str(xT("job(): thread: {} counter: {} unlocking mutex"), id, ::counter);
        }

        iRv = ::pthread_mutex_unlock(&::mtMutex);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        // do some "work" so threads can alternate on mutex lock
        {
           ::sleep(1);
        }
    }

    return xPTR_NULL;
}

#endif // xENV_UNIX
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Condition::unit()
{
#if xENV_UNIX
    int_t iRv = - 1;

    pthread_t threads[3] = {0};
    clong_t   id1        = 1L;
    clong_t   id2        = 2L;
    clong_t   id3        = 3L;

    // initialize
    {
        iRv = ::pthread_mutex_init(&::mtMutex, xPTR_NULL);   // mutex not recursive
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        iRv = ::pthread_cond_init(&::cndCondition, xPTR_NULL);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        // for portability, explicitly create threads in a joinable state
        pthread_attr_t attr;

        iRv = ::pthread_attr_init(&attr);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        iRv = ::pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        iRv = ::pthread_create(&threads[0], &attr, watch, (void_t *)&id1);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        iRv = ::pthread_create(&threads[1], &attr, job,   (void_t *)&id2);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        iRv = ::pthread_create(&threads[2], &attr, job,   (void_t *)&id3);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        iRv = ::pthread_attr_destroy(&attr);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));
    }

    // wait for all threads to complete
	{
		Trace() << Format::str(xT("Main(): waited on {} threads..."), ::threadsNum);

		for (size_t i = 0; i < ::threadsNum; ++ i) {
			iRv = ::pthread_join(threads[i], xPTR_NULL);
			xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));
		}

		Trace() << Format::str(xT("Main(): waited on {} threads. Done"), ::threadsNum);
	}

    // clean up
    {
        iRv = ::pthread_cond_destroy(&::cndCondition);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));

        iRv = ::pthread_mutex_destroy(&::mtMutex);
        xTEST_EQ_MSG(0, iRv, NativeError::format(iRv));
    }

    // ::exit(0);

#if xTEMP_DISABLED
    Condition cond;

    cond.mutex();
    cond.handle();
    cond.create();
    cond.wait(5000UL);
    cond.signal();
    cond.broadcast();
#endif

#endif // xENV_UNIX

    return true;
}
//-------------------------------------------------------------------------------------------------
