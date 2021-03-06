/**
 * \file   Test_Mutex.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Mutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Mutex::unit()
{
    size_t uiVal = 0;

    xTEST_CASE("lock, unlock")
    {
        Mutex csCS;

        csCS.create();
        csCS.lock();

        ++ uiVal;

        csCS.unlock();
    }

    xTEST_CASE("tryLock, unlock")
    {
        Mutex csCS;

        csCS.create();

        m_bRv = csCS.tryLock();
        xTEST(m_bRv);

        ++ uiVal;

        csCS.unlock();
    }

    xTEST_CASE("lock, unlock")
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

    xTEST_CASE("tryLock, unlock")
    {
        Mutex csCS;

        std::csize_t cuiLocks = 10;

        csCS.create();

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRv = csCS.tryLock();
            xTEST(m_bRv);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            csCS.unlock();
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
