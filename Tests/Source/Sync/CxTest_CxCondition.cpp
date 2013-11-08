/**
 * \file   CxTest_CxCondition.cpp
 * \brief  test CxCondition
 */


#include <Test/Sync/CxTest_CxCondition.h>


//--------------------------------------------------------------------------
#if xOS_ENV_UNIX

std::csize_t    g_cuiThreadsNum = 3;
std::csize_t    g_cuiCounterMax = 12;
size_t          g_uiCounter     = 0;

pthread_mutex_t g_mtMutex      = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  g_cndCondition = PTHREAD_COND_INITIALIZER;

#endif // xOS_ENV_UNIX
//------------------------------------------------------------------------------
#if xOS_ENV_UNIX

static
void_t *
pvWatch(
    void_t *a_pvParam
)
{
    int_t    iRv  = - 1;
    long_t liId = *(static_cast<long *>( a_pvParam ));
    xUNUSED(liId);

    #if 0
        CxTracer() << "Starting pvWatch(): thread " << liId;
    #endif

    /*
    Lock mutex and wait for signal.  Note that the pthread_cond_wait
    routine will automatically and atomically unlock mutex while it waits.
    Also, note that if COUNT_LIMIT is reached before this routine is run by
    the waiting thread, the loop will be skipped to prevent pthread_cond_wait
    from never returning.
    */

    iRv = ::pthread_mutex_lock(&g_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    {
        while (g_uiCounter < g_cuiCounterMax) {
            iRv = ::pthread_cond_wait(&g_cndCondition, &g_mtMutex);
            xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

            #if 0
                CxTracer() << xT("pvCountWatch(): thread: ") << liId << xT(" Condition signal received");
            #endif

            g_uiCounter += 125;

            #if 0
                CxTracer() << xT("pvCountWatch(): thread: ") << liId << xT(" g_uiCounter: ") << g_uiCounter;
            #endif
        }
    }

    iRv = ::pthread_mutex_unlock(&g_mtMutex);
    xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

    return NULL;
}

#endif // xOS_ENV_UNIX
//------------------------------------------------------------------------------
#if xOS_ENV_UNIX

static
void_t *
pvJob(
    void_t *a_pvParam
)
{
    int_t    iRv  = - 1;
    long_t liId = *(static_cast<long *>( a_pvParam ));
    xUNUSED(liId);

    for (size_t i = 0; i < 10 /* g_cuiJobLoops */; ++ i) {
        iRv = ::pthread_mutex_lock(&g_mtMutex);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        {
            ++ g_uiCounter;

            // Check the value of count and signal waiting thread when condition is reached
            if (g_uiCounter == g_cuiCounterMax) {
                iRv = ::pthread_cond_signal(&g_cndCondition);
                xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

                #if 0
                    CxTracer() << xT("pvJob(): thread: ") << liId << xT(" g_uiCounter: ")  << g_uiCounter << xT(" threshold reached");
                #endif
            }
            #if 0
                CxTracer() << xT("pvJob(): thread: ") << liId << xT(" g_uiCounter: ") << g_uiCounter << xT(" unlocking mutex");
            #endif
        }

        iRv = ::pthread_mutex_unlock(&g_mtMutex);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        // do some "work" so threads can alternate on mutex lock
        {
            uint_t uiRv = ::sleep(1);
            xUNUSED(uiRv);
        }
    }

    return NULL;
}

#endif // xOS_ENV_UNIX
//------------------------------------------------------------------------------
/*virtual*/
void_t
CxTest_CxCondition::unit(
    culonglong_t &a_cullCaseLoops
)
{
#if xOS_ENV_UNIX
    int_t          iRv          = - 1;
    pthread_t    thThreads[3] = {0};
    clong_t liId1        = 1L;
    clong_t liId2        = 2L;
    clong_t liId3        = 3L;

    // initialize
    {
        iRv = ::pthread_mutex_init(&g_mtMutex, NULL);   // mutex not recursive
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        iRv = ::pthread_cond_init(&g_cndCondition, NULL);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        // for portability, explicitly create threads in a joinable state
        pthread_attr_t atAttr /* = {{0}} */;

        iRv = ::pthread_attr_init(&atAttr);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        iRv = ::pthread_attr_setdetachstate(&atAttr, PTHREAD_CREATE_JOINABLE);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        iRv = ::pthread_create(&thThreads[0], &atAttr, pvWatch, (void_t *)&liId1);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        iRv = ::pthread_create(&thThreads[1], &atAttr, pvJob,   (void_t *)&liId2);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        iRv = ::pthread_create(&thThreads[2], &atAttr, pvJob,   (void_t *)&liId3);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        iRv = ::pthread_attr_destroy(&atAttr);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    // wait for all threads to complete
    for (size_t i = 0; i < g_cuiThreadsNum; ++ i) {
        iRv = ::pthread_join(thThreads[i], NULL);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    #if 0
        CxTracer() << xT("Main(): waited on ") << g_cuiThreadsNum << xT(" threads. Done");
    #endif

    // clean up
    {
        iRv = ::pthread_cond_destroy(&g_cndCondition);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));

        iRv = ::pthread_mutex_destroy(&g_mtMutex);
        xTEST_MSG_EQ(0, iRv, CxLastError::format(iRv));
    }

    // ::exit(0);

#if xTEMP_DISABLED
    CxCondition cond;

    cond.mutex();
    cond.handle();
    cond.create();
    cond.wait(5000UL);
    cond.signal();
    cond.broadcast();
#endif

#endif // xOS_ENV_UNIX
}
//------------------------------------------------------------------------------
