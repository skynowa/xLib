/****************************************************************************
* Class name:  CxTest_CxEvent
* Description: test CxEvent
* File name:   CxTest_CxEvent.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxEvent.h>


//---------------------------------------------------------------------------
CxTest_CxEvent::CxTest_CxEvent() {

}
//---------------------------------------------------------------------------
CxTest_CxEvent::~CxTest_CxEvent() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxEvent::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //hGet
    {
        CxEvent objEvent;

        CxEvent::TxHandle hRes;

        hRes = objEvent.hGet();
        #if defined(xOS_WIN)
            xASSERT_NOT_EQ((ULONG)NULL, (ULONG)hRes);
        #elif defined(xOS_LINUX)
            //TODO: hRes
        #endif
    }

    //-------------------------------------
    //bIsSignaled
    {
        CxEvent objEvent;

        m_bRes = objEvent.bIsSignaled();
        xASSERT_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bSet
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent;

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bReset();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(FALSE, m_bRes);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bSet();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bReset
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent;

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bSet();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bReset();
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bWait
    {
        CxEvent objEvent;

        m_bRes = objEvent.bIsSignaled();
        xASSERT_EQ(FALSE, m_bRes);

        CxEvent::EObjectState osRes = objEvent.osWait(5);
        xASSERT_EQ((ULONG)CxEvent::osTimeout, (ULONG)osRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
