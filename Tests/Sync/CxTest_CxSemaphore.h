/****************************************************************************
* Class name:  CxTest_CxSemaphore
* Description: test CxSemaphore
* File name:   CxTest_CxSemaphore.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSemaphoreH
#define CxTest_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxSemaphore.h>
//---------------------------------------------------------------------------
class CxTest_CxSemaphore : public CxTest {
	public:
		CxTest_CxSemaphore();
	   ~CxTest_CxSemaphore();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
BOOL g_bRes = FALSE;
CxSemaphore m_Semaphore; 
//---------------------------------------------------------------------------
unsigned __stdcall vTest( void* pArguments ) {
	BOOL bRes = FALSE;
	
	/*LOG*/std::cout << "Start" << std::endl;

	for (int i = 1; i < 100; i ++) {
		bRes = m_Semaphore.bWait(INFINITE);
		xASSERT(FALSE != bRes);

		/*LOG*/std::cout << i << std::endl;
	}

	/*LOG*/std::cout << "Stop" << std::endl;
	
	return 0;
}
//---------------------------------------------------------------------------
//TODO: + CxTest_CxSemaphore (constructor)
CxTest_CxSemaphore::CxTest_CxSemaphore() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxSemaphore (destructor)
CxTest_CxSemaphore::~CxTest_CxSemaphore() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxSemaphore::bUnit() {
	g_bRes = m_Semaphore.bCreate(NULL, 4, 2048, NULL);
	xASSERT(FALSE != g_bRes);

	if (NULL == _beginthreadex(0, 0, &vTest, 0, NULL, NULL)) {
		std::cout << "Error begin thread " << std::endl;
	}

	//-------------------------------------
	//bRelease
	for (int i = 0; i < 100; ++ i) {
		::Sleep(2000);
	
		for (int x = 0; x < 2; x ++) {
			g_bRes = m_Semaphore.bRelease(1, NULL);
			xASSERT(FALSE != g_bRes);
		}
	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxSemaphoreH

