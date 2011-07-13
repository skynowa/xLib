/****************************************************************************
* Class name:  CxTest_CxSocketInit
* Description: test CxSocketInit
* File name:   CxTest_CxSocketInit.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSocketInitH
#define CxTest_CxSocketInitH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocketInit.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxSocketInit :
    public CxTest
{
	public:
		CxTest_CxSocketInit();
		virtual     ~CxTest_CxSocketInit();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSocketInitH
