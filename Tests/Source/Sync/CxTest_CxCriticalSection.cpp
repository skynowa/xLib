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
    const ulonglong_t cullCaseLoops
)
{
    size_t uiVal = 0;


    //--------------------------------------------------
    //bLock, bUnlock
    xTEST_CASE(cullCaseLoops)
    {
        CxCriticalSection csCS;

        m_bRv = csCS.bCreate();
        xTEST_EQ(true, m_bRv);

        m_bRv = csCS.bLock();
        xTEST_EQ(true, m_bRv);

        ++ uiVal;

        m_bRv = csCS.bUnlock();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bTryLock, bUnlock
    xTEST_CASE(cullCaseLoops)
    {
        CxCriticalSection csCS;

        m_bRv = csCS.bCreate();
        xTEST_EQ(true, m_bRv);

        m_bRv = csCS.bTryLock();
        xTEST_EQ(true, m_bRv);

        ++ uiVal;

        m_bRv = csCS.bUnlock();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    //bLock, bUnlock
    xTEST_CASE(cullCaseLoops)
    {
        CxCriticalSection csCS;

        const size_t cuiLocks = 10;

        m_bRv = csCS.bCreate();
        xTEST_EQ(true, m_bRv);

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRv = csCS.bLock();
            xTEST_EQ(true, m_bRv);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRv = csCS.bUnlock();
            xTEST_EQ(true, m_bRv);
        }
    }

    //--------------------------------------------------
    //bTryLock, bUnlock
    xTEST_CASE(cullCaseLoops)
    {
        CxCriticalSection csCS;

        const size_t cuiLocks = 10;

        m_bRv = csCS.bCreate();
        xTEST_EQ(true, m_bRv);

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRv = csCS.bTryLock();
            xTEST_EQ(true, m_bRv);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRv = csCS.bUnlock();
            xTEST_EQ(true, m_bRv);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
