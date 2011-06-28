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
//DONE: CxTest_CxSleeper
CxTest_CxSleeper::CxTest_CxSleeper() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxSleeper
CxTest_CxSleeper::~CxTest_CxSleeper() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxSleeper::bUnit() {
	CxSleeper objSleeper;

    m_bRes = objSleeper.bIsSleeping();
    xASSERT(FALSE == m_bRes);

	for (size_t i = 0; i < 10; ++ i) {
        m_bRes = objSleeper.bSleep(10);
        xASSERT(FALSE != m_bRes);

		m_bRes = objSleeper.bIsSleeping();
		xASSERT(FALSE == m_bRes);

        m_bRes = objSleeper.bIsSleeping();
		xASSERT(FALSE == m_bRes);

        #if xTODO
            m_bRes = objSleeper.bWakeUp();
	        //xASSERT(FALSE != m_bRes);
        #endif
	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxSleeperH

