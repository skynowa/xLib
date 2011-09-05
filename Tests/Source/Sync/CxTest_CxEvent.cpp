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
CxTest_CxEvent::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //bManualReset == TRUE
    {
        CxEvent objEvent;

        //-------------------------------------
        //hGetHandle
        {
            #if xTODO
                m_hRes = objEvent.hGetHandle();
                xASSERT(NULL == m_hRes);
            #endif
        }

        //-------------------------------------
        //bCreate
        {
            m_bRes = objEvent.bCreate(/*0, TRUE, FALSE, xT("")*/);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //hGetHandle
        {
            #if xTODO
                m_hRes = objEvent.hGetHandle();
                xASSERT(NULL != m_hRes);
            #endif
        }

        //-------------------------------------
        //bOpen
        {
            ////m_bRes = objEvent.bOpen(0, FALSE, NULL);
            ////xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bPulse
        {
#if xTEMP_DISABLED
            m_bRes = objEvent.bPulse();
            xASSERT_NOT_EQ(FALSE, m_bRes);
#endif
        }

        //-------------------------------------
        //bReset
        {
            m_bRes = objEvent.bReset();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bSet
        {
            m_bRes = objEvent.bSet();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bWait
        {
            m_bRes = objEvent.bWait(5000);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    //-------------------------------------
    //bManualReset == FALSE
    {
        CxEvent objEvent;

        //-------------------------------------
        //bCreate
        {
            m_bRes = objEvent.bCreate(/*0, FALSE, TRUE, xT("XLib_CxEvent_25_01_2010")*/);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
#if xDEPRECIATE
            xASSERT_NOT_EQ(FALSE, m_bRes);
#else
            xASSERT_NOT_EQ(TRUE, m_bRes);
#endif
        }

        //-------------------------------------
        //hGetHandle
        {
            #if xTODO
                m_hRes = objEvent.hGetHandle();
                xASSERT(NULL != m_hRes);
            #endif
        }

        //-------------------------------------
        //bOpen
        {
#if xTEMP_DISABLED
            m_bRes = objEvent.bOpen(0, FALSE, xT("XLib_CxEvent_25_01_2010"));
            xASSERT_NOT_EQ(FALSE, m_bRes);
#endif
        }

        //-------------------------------------
        //bPulse
        {
#if xTEMP_DISABLED
            m_bRes = objEvent.bPulse();
            xASSERT_NOT_EQ(FALSE, m_bRes);
#endif
        }

        //-------------------------------------
        //bReset
        {
            m_bRes = objEvent.bReset();
            xASSERT_NOT_EQ(FALSE, m_bRes);
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
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bIsSignaled
        {
            m_bRes = objEvent.bIsSignaled();
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }

        //-------------------------------------
        //bSet
        {
            m_bRes = objEvent.bSet();
            xASSERT_NOT_EQ(FALSE, m_bRes)
        }

        //-------------------------------------
        //bWait
        {
            m_bRes = objEvent.bWait(5000UL);
            xASSERT_NOT_EQ(FALSE, m_bRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
