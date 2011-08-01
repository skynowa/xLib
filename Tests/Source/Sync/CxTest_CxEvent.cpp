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
//DONE: CxTest_CxEvent
CxTest_CxEvent::CxTest_CxEvent() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxEvent
CxTest_CxEvent::~CxTest_CxEvent() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxEvent::bUnit() {
#if defined(xOS_WIN)
    //-------------------------------------
    //bManualReset == TRUE
    {
        CxEvent objEvent;

        //-------------------------------------
        //hGetHandle
        {
            m_hRes = objEvent.hGetHandle();
            xASSERT(NULL == m_hRes);
        }

        //-------------------------------------
        //bCreate
        {
            m_bRes = objEvent.bCreate(0, TRUE, FALSE, xT(""));
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //hGetHandle
        {
            m_hRes = objEvent.hGetHandle();
            xASSERT(NULL != m_hRes);
        }

        //-------------------------------------
        //bOpen
        {
            ////m_bRes = objEvent.bOpen(0, FALSE, NULL);
            ////xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bPulse
        {
            m_bRes = objEvent.bPulse();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bReset
        {
            m_bRes = objEvent.bReset();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bSet
        {
            m_bRes = objEvent.bSet();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bWait
        {
            m_bRes = objEvent.bWait(5000);
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bManualReset == FALSE
    {
        CxEvent objEvent;

        //-------------------------------------
        //bCreate
        {
            m_bRes = objEvent.bCreate(0, FALSE, TRUE, xT("XLib_CxEvent_25_01_2010"));
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //hGetHandle
        {
            m_hRes = objEvent.hGetHandle();
            xASSERT(NULL != m_hRes);
        }

        //-------------------------------------
        //bOpen
        {
            ////m_bRes = objEvent.bOpen(0, FALSE, xT("XLib_CxEvent_25_01_2010"));
            ////xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bPulse
        {
            m_bRes = objEvent.bPulse();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bReset
        {
            m_bRes = objEvent.bReset();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT(FALSE == m_bRes);
        }

        //-------------------------------------
        //bSet
        {
            m_bRes = objEvent.bSet();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }

        //-------------------------------------
        //bSet
        {
            m_bRes = objEvent.bSet();
            xASSERT_NOT_EQUAL(FALSE, m_bRes)
        }

        //-------------------------------------
        //bWait
        {
            m_bRes = objEvent.bWait(5000);
            xASSERT_NOT_EQUAL(FALSE, m_bRes);
        }
    }
#elif defined(xOS_LINUX)

#endif

    return TRUE;
}
//---------------------------------------------------------------------------
