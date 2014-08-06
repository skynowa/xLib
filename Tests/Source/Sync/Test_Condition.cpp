/**
 * \file   Test_Condition.cpp
 * \brief  test Condition
 */


#include <Test/Sync/Test_Condition.h>


//-------------------------------------------------------------------------------------------------
#if xENV_UNIX

std::csize_t    g_cuiThreadsNum = 3;
std::csize_t    g_cuiCounterMax = 12;
size_t          g_uiCounter     = 0;

pthread_mutex_t g_mtMutex      = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  g_cndCondition = PTHREAD_COND_INITIALIZER;

#endif // xENV_UNIX
//-------------------------------------------------------------------------------------------------
#if xENV_UNIX && xTODO

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
        Tracer() << "Starting pvWatch(): thread " << liId;
    #endif

    /*
    Lock mutex and wait for signal.  Note that the pthread_cond_wait
    routine will automatically and atomically unlock mutex while it waits.
    Also, note that if COUNT_LIMIT is reached before this routine is run by
    the waiting thread, the loop will be skipped to prevent pthread_cond_wait
    from never returning.
    */

    iRv = ::pthread_mutex_lock(&g_mtMutex);
    xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

    {
        while (g_uiCounter < g_cuiCounterMax) {
            iRv = ::pthread_cond_wait(&g_cndCondition, &g_mtMutex);
            xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

            #if 0
                Tracer() << xT("pvCountWatch(): thread: ") << liId << xT(" Condition signal received");
            #endif

            g_uiCounter += 125;

            #if 0
                Tracer() << xT("pvCountWatch(): thread: ") << liId << xT(" g_uiCounter: ") << g_uiCounter;
            #endif
        }
    }

    iRv = ::pthread_mutex_unlock(&g_mtMutex);
    xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

    return xPTR_NULL;
}

#endif // xENV_UNIX
//-------------------------------------------------------------------------------------------------
#if xENV_UNIX && xTODO

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
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        {
            ++ g_uiCounter;

            // Check the value of count and signal waiting thread when condition is reached
            if (g_uiCounter == g_cuiCounterMax) {
                iRv = ::pthread_cond_signal(&g_cndCondition);
                xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

                #if 0
                    Tracer() << xT("pvJob(): thread: ") << liId << xT(" g_uiCounter: ")  << g_uiCounter << xT(" threshold reached");
                #endif
            }
            #if 0
                Tracer() << xT("pvJob(): thread: ") << liId << xT(" g_uiCounter: ") << g_uiCounter << xT(" unlocking mutex");
            #endif
        }

        iRv = ::pthread_mutex_unlock(&g_mtMutex);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        // do some "work" so threads can alternate on mutex lock
        {
            uint_t uiRv = ::sleep(1);
            xUNUSED(uiRv);
        }
    }

    return xPTR_NULL;
}

#endif // xENV_UNIX
//-------------------------------------------------------------------------------------------------
/*virtual*/
void_t
Test_Condition::unit(
    culonglong_t &a_caseLoops
)
{
    xUNUSED(a_caseLoops);

#if xENV_UNIX && xTODO
    int_t          iRv          = - 1;
    pthread_t    thThreads[3] = {0};
    clong_t liId1        = 1L;
    clong_t liId2        = 2L;
    clong_t liId3        = 3L;

    // initialize
    {
        iRv = ::pthread_mutex_init(&g_mtMutex, xPTR_NULL);   // mutex not recursive
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        iRv = ::pthread_cond_init(&g_cndCondition, xPTR_NULL);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        // for portability, explicitly create threads in a joinable state
        pthread_attr_t atAttr /* = {{0}} */;

        iRv = ::pthread_attr_init(&atAttr);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        iRv = ::pthread_attr_setdetachstate(&atAttr, PTHREAD_CREATE_JOINABLE);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        iRv = ::pthread_create(&thThreads[0], &atAttr, pvWatch, (void_t *)&liId1);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        iRv = ::pthread_create(&thThreads[1], &atAttr, pvJob,   (void_t *)&liId2);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        iRv = ::pthread_create(&thThreads[2], &atAttr, pvJob,   (void_t *)&liId3);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        iRv = ::pthread_attr_destroy(&atAttr);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));
    }

    // wait for all threads to complete
    for (size_t i = 0; i < g_cuiThreadsNum; ++ i) {
        iRv = ::pthread_join(thThreads[i], xPTR_NULL);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));
    }

    #if 0
        Tracer() << xT("Main(): waited on ") << g_cuiThreadsNum << xT(" threads. Done");
    #endif

    // clean up
    {
        iRv = ::pthread_cond_destroy(&g_cndCondition);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));

        iRv = ::pthread_mutex_destroy(&g_mtMutex);
        xTEST_MSG_EQ(0, iRv, LastError::format(iRv));
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
}
//-------------------------------------------------------------------------------------------------
