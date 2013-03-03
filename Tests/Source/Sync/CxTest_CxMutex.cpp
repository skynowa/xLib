/**
 * \file   CxTest_CxMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxMutex.h>


//------------------------------------------------------------------------------
CxTest_CxMutex::CxTest_CxMutex() {

}
//------------------------------------------------------------------------------
CxTest_CxMutex::~CxTest_CxMutex() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxMutex::unit(
    culonglong_t &cullCaseLoops
)
{
    size_t uiVal = 0;

    xTEST_CASE("CxMutex::lock CxMutex::unlock", cullCaseLoops)
    {
        CxMutex csCS;

        csCS.create();
        csCS.lock();

        ++ uiVal;

        csCS.unlock();
    }

    xTEST_CASE("CxMutex::tryLock CxMutex::unlock", cullCaseLoops)
    {
        CxMutex csCS;

        csCS.create();

        m_bRv = csCS.tryLock();
        xTEST_EQ(true, m_bRv);

        ++ uiVal;

        csCS.unlock();
    }

    xTEST_CASE("CxMutex::lock CxMutex::unlock", cullCaseLoops)
    {
        CxMutex csCS;

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

    xTEST_CASE("CxMutex::tryLock CxMutex::unlock", cullCaseLoops)
    {
        CxMutex csCS;

        std::csize_t cuiLocks = 10;

        csCS.create();

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRv = csCS.tryLock();
            xTEST_EQ(true, m_bRv);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            csCS.unlock();
        }
    }
}
//------------------------------------------------------------------------------
