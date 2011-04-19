/****************************************************************************
* Class name:  CxTest_CxEvent
* Description: test CxEvent
* File name:   CxTest_CxEvent.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxEventH
#define CxTest_CxEventH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxEvent.h>
//---------------------------------------------------------------------------
class CxTest_CxEvent : public CxTest {
	public:
		CxTest_CxEvent();
	   ~CxTest_CxEvent();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//TODO: + CxTest_CxEvent (constructor)
CxTest_CxEvent::CxTest_CxEvent() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxEvent (destructor)
CxTest_CxEvent::~CxTest_CxEvent() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxEvent::bUnit() {
	//-------------------------------------
	//bManualReset == TRUE
	{
		CxEvent objEvent;

		g_bRes = objEvent.bCreate(0, TRUE, FALSE, NULL);
		xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bIsSignaled(); 
		xASSERT(FALSE == g_bRes);

		g_hRes = objEvent.hGetHandle();
		xASSERT(NULL != g_hRes);

		////g_bRes = objEvent.bOpen(0, FALSE, NULL);
		////xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bPulse();
		xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bReset();
		xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bIsSignaled(); 
		xASSERT(FALSE == g_bRes);

		g_bRes = objEvent.bSet();
		xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bIsSignaled(); 
		xASSERT(TRUE == g_bRes);

		g_bRes = objEvent.bWait(5000);
		xASSERT(FALSE != g_bRes);
	}
	//-------------------------------------
	//bManualReset == FALSE
	{
		CxEvent objEvent;

		g_bRes = objEvent.bCreate(0, FALSE, TRUE, _T("XLib_CxEvent_25_01_2010"));
		xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bIsSignaled(); 
		xASSERT(TRUE == g_bRes);

		g_hRes = objEvent.hGetHandle();
		xASSERT(NULL != g_hRes);

		////g_bRes = objEvent.bOpen(0, FALSE, _T("XLib_CxEvent_25_01_2010"));
		////xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bPulse();
		xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bReset();
		xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bIsSignaled(); 
		xASSERT(FALSE == g_bRes);

		g_bRes = objEvent.bSet();
		xASSERT(FALSE != g_bRes);

		g_bRes = objEvent.bIsSignaled(); 
		xASSERT(TRUE == g_bRes);

		g_bRes = objEvent.bSet();
		xASSERT(FALSE != g_bRes)

		g_bRes = objEvent.bWait(5000);
		xASSERT(FALSE != g_bRes);
	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxEventH

