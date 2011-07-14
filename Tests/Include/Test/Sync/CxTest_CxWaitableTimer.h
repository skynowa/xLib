/****************************************************************************
* Class name:  CxTest_CxWaitableTimer
* Description: test CxWaitableTimer
* File name:   CxTest_CxWaitableTimer.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxWaitableTimerH
#define CxTest_CxWaitableTimerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxWaitableTimer.h>
//---------------------------------------------------------------------------
class CxTest_CxWaitableTimer :
    public CxTest
{
	public:
		CxTest_CxWaitableTimer();
		virtual     ~CxTest_CxWaitableTimer();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxWaitableTimerH
