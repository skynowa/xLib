/**
 * \file   CxTest_CxCriticalSection.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxCriticalSection.h>


//---------------------------------------------------------------------------
CxTest_CxCriticalSection::CxTest_CxCriticalSection() {

}
//---------------------------------------------------------------------------
CxTest_CxCriticalSection::~CxTest_CxCriticalSection() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxCriticalSection::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    size_t uiVal = 0;


    //--------------------------------------------------
    //bLock, bUnlock
    xTEST_CASE(cullBlockLoops)
    {
        CxCriticalSection csCS;

        m_bRes = csCS.bLock();
        xTEST_EQ(true, m_bRes);

        ++ uiVal;

        m_bRes = csCS.bUnlock();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bTryLock, bUnlock
    xTEST_CASE(cullBlockLoops)
    {
        CxCriticalSection csCS;

        m_bRes = csCS.bTryLock();
        xTEST_EQ(true, m_bRes);

        ++ uiVal;

        m_bRes = csCS.bUnlock();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bLock, bUnlock
    xTEST_CASE(cullBlockLoops)
    {
        CxCriticalSection csCS;

        const size_t cuiLocks = 10;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRes = csCS.bLock();
            xTEST_EQ(true, m_bRes);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRes = csCS.bUnlock();
            xTEST_EQ(true, m_bRes);
        }
    }

    //--------------------------------------------------
    //bTryLock, bUnlock
    xTEST_CASE(cullBlockLoops)
    {
        CxCriticalSection csCS;

        const size_t cuiLocks = 10;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRes = csCS.bTryLock();
            xTEST_EQ(true, m_bRes);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRes = csCS.bUnlock();
            xTEST_EQ(true, m_bRes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
