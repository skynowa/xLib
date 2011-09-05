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
    //-------------------------------------
    //CxCriticalSection
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCriticalSection objCriticalSection;

        {
            m_ulRes = objCriticalSection.ulSetSpinCount(10000);
            xASSERT_LESS_EQ(0UL, m_ulRes);

            m_bRes = objCriticalSection.bEnter();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = objCriticalSection.bLeave();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        {
            m_ulRes = objCriticalSection.ulSetSpinCount(1000);
            xASSERT_LESS_EQ(0UL, m_ulRes);

            m_bRes = objCriticalSection.bTryEnter();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = objCriticalSection.bLeave();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        {
            const size_t cuiLocks = 10;

            m_ulRes = objCriticalSection.ulSetSpinCount(1000);
            xASSERT_LESS_EQ(0UL, m_ulRes);

            for (size_t i = 0; i < cuiLocks; ++ i) {
                m_bRes = objCriticalSection.bEnter();
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }

            for (size_t i = 0; i < cuiLocks; ++ i) {
                m_bRes = objCriticalSection.bLeave();
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        {
            const size_t cuiLocks = 10;

            m_ulRes = objCriticalSection.ulSetSpinCount(1000);
            xASSERT_LESS_EQ(0UL, m_ulRes);

            for (size_t i = 0; i < cuiLocks; ++ i) {
                m_bRes = objCriticalSection.bTryEnter();
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }

            for (size_t i = 0; i < cuiLocks; ++ i) {
                m_bRes = objCriticalSection.bLeave();
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }
    }

    //-------------------------------------
    //CxCriticalSection(const ULONG culSpinCount);
    xTEST_BLOCK(cullBlockLoops)
    {
        CxCriticalSection objCriticalSection(1000);

        {
            m_ulRes = objCriticalSection.ulSetSpinCount(10000);
            xASSERT_LESS_EQ(0UL, m_ulRes);

            m_bRes = objCriticalSection.bEnter();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = objCriticalSection.bLeave();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        {
            m_ulRes = objCriticalSection.ulSetSpinCount(4000);
            xASSERT_LESS_EQ(0UL, m_ulRes);

            m_bRes = objCriticalSection.bTryEnter();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = objCriticalSection.bLeave();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
