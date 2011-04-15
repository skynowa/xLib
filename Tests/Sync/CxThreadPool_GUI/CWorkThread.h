/****************************************************************************
* Class name:  CWorkThread
* Description: рабочий поток
* File name:   CWorkThread.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     10.12.2009 22:10:16
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CWorkThreadH
#define CWorkThreadH
//---------------------------------------------------------------------------
#include <XLib/xCommon.h>
#include <XLib/Sync/CxCriticalSection.h>
#include <XLib/Sync/CxAutoCriticalSection.h>
#include <XLib/Sync/CxThread.h>
#include <XLib/Log/CxConsoleLog.h>
#include <XLib/Log/CxTraceLog.h>
#include <XLib/Log/CxFileLog.h>
#include <XLib/Log/CxWndLog.h>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
class CWorkThread : public CxThread {
	public:
		size_t       m_uiIndex;

				     CWorkThread(BOOL bIsPaused, BOOL bAutoDelete);
			        ~CWorkThread();
	protected:
		virtual UINT uiOnRun    (VOID *pData);	/*overload*/
		virtual VOID vOnEnter   ();			    /*overload*/
		virtual VOID vOnExit    ();			    /*overload*/

	private:
		CxTraceLog   _m_clLog;
};
//---------------------------------------------------------------------------
#endif	//CWorkThreadH