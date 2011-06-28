/****************************************************************************
* Class name:  CWorkThread
* Description: ������� �����
* File name:   CWorkThread.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.12.2009 22:10:16
*
*****************************************************************************/


#ifndef CWorkThreadH
#define CWorkThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
#include <xLib/Log/CxFileLog.h>
//---------------------------------------------------------------------------
#define WM_TEST_MSG_1  (WM_USER + 100)
//---------------------------------------------------------------------------
class CWorkThread :
    public CxThread
{
	public:
		size_t       m_uiIndex;

				     CWorkThread(BOOL bAutoDelete);
		virtual     ~CWorkThread();

	protected:
		virtual UINT uiOnRun    (VOID *pData);	/*overload*/
		virtual VOID vOnEnter   ();			    /*overload*/
		virtual VOID vOnExit    ();			    /*overload*/


	private:
		CxConsoleLog _m_clLog;
};
//---------------------------------------------------------------------------


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CWorkThread
CWorkThread::CWorkThread(BOOL bAutoDelete) :
	CxThread (bAutoDelete),
	m_uiIndex(0),
	_m_clLog (FALSE)
{
}
//---------------------------------------------------------------------------
//TODO: ~CWorkThread
CWorkThread::~CWorkThread() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*    protected
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: uiOnRun
UINT CWorkThread::uiOnRun(VOID *pData) {
	//xTRACEV(xT("Start thread: #%i\n"), m_uiIndex);

	UINT uiRes = 0;
	BOOL bRes  = FALSE;

	for (size_t i = 0; i < /**piParam*/10; ++ i, ++ uiRes) {
		bRes = bIsTimeToExit();
		xCHECK_DO(TRUE == bRes, break);

		for (int i = 0; i < 20; i ++) {
			//xTRACEV(xT("*\n"));
			::Sleep(1000);
		}
	}

	//xTRACEV(xT("End thread: #%i\n"), m_uiIndex);

	return uiRes;
}
//---------------------------------------------------------------------------
//TODO: vOnEnter
VOID CWorkThread::vOnEnter() {
	//LOG("vOnEnter");
}
//---------------------------------------------------------------------------
//TODO: vOnExit
VOID CWorkThread::vOnExit() {
	//LOG("vOnExit");

	BOOL bRes = FALSE;

	////bRes = thpTP->bPushTask(NULL);	//if (TRUE == bRes)		//bRelease
	/////*DEBUG*/xASSERT_DO(FALSE != bRes, return);
}
//---------------------------------------------------------------------------
#endif	//CWorkThreadH

