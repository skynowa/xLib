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
        CxEvent objEvent(TRUE, TRUE);

        #if defined(xOS_ENV_WIN)
            xASSERT_DIFF(FALSE, objEvent.hGet().bIsValid())
        #elif defined(xOS_ENV_UNIX)
            //TODO: hRes
        #endif
    }

    //-------------------------------------
    //bIsSignaled
    {
        {
            CxEvent objEvent(TRUE, TRUE);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_DIFF(FALSE, m_bRes);
        }

        {
            CxEvent objEvent(TRUE, FALSE);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bSet
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent(TRUE, TRUE);

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bReset();
            xASSERT_DIFF(FALSE, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(FALSE, m_bRes);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bSet();
            xASSERT_DIFF(FALSE, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_DIFF(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bReset
    {
        const size_t cuiSpinCount = 3;


        CxEvent objEvent(TRUE, TRUE);

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bSet();
            xASSERT_DIFF(FALSE, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_DIFF(FALSE, m_bRes);
        }

        for (size_t i = 0; i < cuiSpinCount; ++ i) {
            m_bRes = objEvent.bReset();
            xASSERT_DIFF(FALSE, m_bRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bWait
    {
        {
            const BOOL cbIsAutoReset  = FALSE;
            const BOOL cbInitialState = FALSE;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(cbInitialState, m_bRes);

            CxEvent::EObjectState osRes = objEvent.osWait(5);
            xASSERT_EQ((ULONG)CxEvent::osTimeout, (ULONG)osRes);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(cbInitialState, m_bRes);
        }

        {
            const BOOL cbIsAutoReset  = TRUE;
            const BOOL cbInitialState = TRUE;


            CxEvent objEvent(cbIsAutoReset, cbInitialState);

            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(cbInitialState, m_bRes);

            CxEvent::EObjectState osRes = objEvent.osWait(5);
            xASSERT_EQ((ULONG)CxEvent::osSignaled, (ULONG)osRes);   //LINUX   - osSignaled
                                                                    //Windows - osTimeout
            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(FALSE, m_bRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
