/****************************************************************************
* Class name:  CxTest_CxWaitableTimer
* Description: test CxWaitableTimer
* File name:   CxTest_CxWaitableTimer.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxWaitableTimerH
#define CxTest_CxWaitableTimerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxWaitableTimer.h>
//---------------------------------------------------------------------------
class CxTest_CxWaitableTimer : public CxTest {
	public:
		CxTest_CxWaitableTimer();
	   ~CxTest_CxWaitableTimer();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxWaitableTimer (constructor)
CxTest_CxWaitableTimer::CxTest_CxWaitableTimer() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxWaitableTimer (destructor)
CxTest_CxWaitableTimer::~CxTest_CxWaitableTimer() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxWaitableTimer::bUnit() {
	BOOL bRes = FALSE;
	
	CxWaitableTimer WT;

	//-------------------------------------
	//создаем
	bRes = WT.bCreate(FALSE, NULL, NULL);
	if (FALSE == bRes) {
		printf("CreateWaitableTimer failed (%d)\n", GetLastError());
		return 1;
	}
	printf("CreateWaitableTimer success (%d)\n", GetLastError());

	//-------------------------------------
	//Устанавливаем
	WT.bSet(/*-30000000LL*/0, 2000, NULL, NULL, 0);
	if (FALSE == bRes) {
		printf("SetWaitableTimer failed (%d)\n", GetLastError());
		return 2;
	}
	printf("SetWaitableTimer success (%d)\n", GetLastError());


	while (true) {
		//-------------------------------------
		//ждем
		BOOL bRes = WT.bWait(INFINITE);
		printf("ulWait success (%d)\n", GetLastError());
		
		if (FALSE == bRes) {
			printf("ulWait failed (%d)\n", GetLastError());
		} else {
			printf("Timer was signaled.\n");
		}

	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxWaitableTimerH

