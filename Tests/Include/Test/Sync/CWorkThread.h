/****************************************************************************
* Class name:  CWorkThread
* Description: work thread
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
class CWorkThread :
    public CxThread
{
	public:
		size_t       m_uiIndex;

				     CWorkThread(const BOOL cbAutoDelete);
		virtual     ~CWorkThread();

	protected:
		virtual UINT uiOnRun    (VOID *pData);
		virtual VOID vOnEnter   ();
		virtual VOID vOnExit    ();

	private:
		CxConsoleLog _m_clLog;
};
//---------------------------------------------------------------------------
#endif	//CWorkThreadH
