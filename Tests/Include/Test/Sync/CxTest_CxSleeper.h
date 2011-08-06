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

	    virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSleeperH
