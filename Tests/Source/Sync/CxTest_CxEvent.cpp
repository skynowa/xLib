/****************************************************************************
* Class name:  CxTest_CxEvent
* Description: test CxEvent
* File name:   CxTest_CxEvent.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxEvent (constructor)
CxTest_CxEvent::CxTest_CxEvent() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxEvent (destructor)
CxTest_CxEvent::~CxTest_CxEvent() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxEvent::bUnit() {
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
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bIsSignaled
		{
			m_bRes = objEvent.bIsSignaled();
			xASSERT(FALSE == m_bRes);
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
			////xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bPulse
		{
			m_bRes = objEvent.bPulse();
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bReset
		{
			m_bRes = objEvent.bReset();
			xASSERT(FALSE != m_bRes);
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
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bIsSignaled
		{
			m_bRes = objEvent.bIsSignaled();
			xASSERT(TRUE == m_bRes);
		}

		//-------------------------------------
		//bWait
		{
			m_bRes = objEvent.bWait(5000);
			xASSERT(FALSE != m_bRes);
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
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bIsSignaled
		{
			m_bRes = objEvent.bIsSignaled();
			xASSERT(TRUE == m_bRes);
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
			////xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bPulse
		{
			m_bRes = objEvent.bPulse();
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bReset
		{
			m_bRes = objEvent.bReset();
			xASSERT(FALSE != m_bRes);
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
			xASSERT(FALSE != m_bRes);
		}

		//-------------------------------------
		//bIsSignaled
		{
			m_bRes = objEvent.bIsSignaled();
			xASSERT(TRUE == m_bRes);
		}

		//-------------------------------------
		//bSet
		{
			m_bRes = objEvent.bSet();
			xASSERT(FALSE != m_bRes)
		}

		//-------------------------------------
		//bWait
		{
			m_bRes = objEvent.bWait(5000);
			xASSERT(FALSE != m_bRes);
		}
	}

    return TRUE;
}
//---------------------------------------------------------------------------
