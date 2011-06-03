/****************************************************************************
* Class name:  CxTest_CxSleeper
* Description: test CxSleeper
* File name:   CxTest_CxSleeper.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSleeperH
#define CxTest_CxSleeperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxSleeper.h>
//---------------------------------------------------------------------------
class CxTest_CxSleeper :
    public CxTest
{
	public:
		CxTest_CxSleeper();
		virtual     ~CxTest_CxSleeper();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxSleeper (constructor)
CxTest_CxSleeper::CxTest_CxSleeper() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxSleeper (destructor)
CxTest_CxSleeper::~CxTest_CxSleeper() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxSleeper::bUnit() {
	BOOL bRes = FALSE;

	{
		CxSleeper objSleeper;

		bRes = objSleeper.bIsSleeping();
		xASSERT(FALSE == bRes);

		for (INT i = 0; i < 10000; i ++) {
			std::cout << "Start sleeping....." << std::endl;
			objSleeper.bSleep(200);

			bRes = objSleeper.bIsSleeping();
			xASSERT(FALSE == bRes);
		}

		std::cout << "Stop sleeping"       << std::endl;
	}

	//bIsSleeping

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxSleeperH

