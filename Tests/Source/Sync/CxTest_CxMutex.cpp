/**
 * \file   CxTest_CxMutex.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxMutex.h>


//---------------------------------------------------------------------------
CxTest_CxMutex::CxTest_CxMutex() {

}
//---------------------------------------------------------------------------
CxTest_CxMutex::~CxTest_CxMutex() {

}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest_CxMutex::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    size_t uiVal = 0;


    //--------------------------------------------------
    // bLock, bUnlock
    xTEST_CASE(cullCaseLoops)
    {
        CxMutex csCS;

        m_bRv = csCS.bCreate();
        xTEST_EQ(true, m_bRv);

        m_bRv = csCS.bLock();
        xTEST_EQ(true, m_bRv);

        ++ uiVal;

        m_bRv = csCS.bUnlock();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    // bTryLock, bUnlock
    xTEST_CASE(cullCaseLoops)
    {
        CxMutex csCS;

        m_bRv = csCS.bCreate();
        xTEST_EQ(true, m_bRv);

        m_bRv = csCS.bTryLock();
        xTEST_EQ(true, m_bRv);

        ++ uiVal;

        m_bRv = csCS.bUnlock();
        xTEST_EQ(true, m_bRv);
    }

    //--------------------------------------------------
    // bLock, bUnlock
    xTEST_CASE(cullCaseLoops)
    {
        CxMutex csCS;

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
    // bTryLock, bUnlock
    xTEST_CASE(cullCaseLoops)
    {
        CxMutex csCS;

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
