/**
 * \file   Test_Mutex.cpp
 * \brief
 */


#include <Test/Sync/Test_Mutex.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Mutex::unit(
    culonglong_t &a_caseLoops
)
{
    size_t uiVal = 0;

    xTEST_CASE("lock unlock", a_caseLoops)
    {
        Mutex csCS;

        csCS.create();
        csCS.lock();

        ++ uiVal;

        csCS.unlock();
    }

    xTEST_CASE("tryLock unlock", a_caseLoops)
    {
        Mutex csCS;

        csCS.create();

        m_bRv = csCS.tryLock();
        xTEST_EQ(m_bRv, true);

        ++ uiVal;

        csCS.unlock();
    }

    xTEST_CASE("lock unlock", a_caseLoops)
    {
        Mutex csCS;

        std::csize_t cuiLocks = 10;

        csCS.create();

        for (size_t i = 0; i < cuiLocks; ++ i) {
            csCS.lock();
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            csCS.unlock();
        }
    }

    xTEST_CASE("tryLock unlock", a_caseLoops)
    {
        Mutex csCS;

        std::csize_t cuiLocks = 10;

        csCS.create();

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRv = csCS.tryLock();
            xTEST_EQ(m_bRv, true);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            csCS.unlock();
        }
    }
}
//-------------------------------------------------------------------------------------------------
