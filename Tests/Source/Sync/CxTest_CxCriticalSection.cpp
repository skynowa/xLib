/****************************************************************************
* Class name:  CxTest_CxCriticalSection
* Description: test CxCriticalSection
* File name:   CxTest_CxCriticalSection.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxCriticalSection.h>


//---------------------------------------------------------------------------
CxTest_CxCriticalSection::CxTest_CxCriticalSection() {

}
//---------------------------------------------------------------------------
CxTest_CxCriticalSection::~CxTest_CxCriticalSection() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxCriticalSection::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    size_t uiVal = 0;


    //--------------------------------------------------
    //bLock, bUnlock
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCriticalSection csCS;

        m_bRes = csCS.bLock();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        ++ uiVal;

        m_bRes = csCS.bUnlock();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bTryLock, bUnlock
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCriticalSection csCS;

        m_bRes = csCS.bTryLock();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        ++ uiVal;

        m_bRes = csCS.bUnlock();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bLock, bUnlock
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCriticalSection csCS;

        const size_t cuiLocks = 10;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRes = csCS.bLock();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRes = csCS.bUnlock();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //--------------------------------------------------
    //bTryLock, bUnlock
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCriticalSection csCS;

        const size_t cuiLocks = 10;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRes = csCS.bTryLock();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        ++ uiVal;

        for (size_t i = 0; i < cuiLocks; ++ i) {
            m_bRes = csCS.bUnlock();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
