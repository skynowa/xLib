/****************************************************************************
* Class name:  CxTest_CxPop3
* Description: test CxPop3
* File name:   CxTest_CxPop3.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxPop3H
#define CxTest_CxPop3H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxPop3.h>
//---------------------------------------------------------------------------
class CxTest_CxPop3 :
    public CxTest
{
	public:
		CxTest_CxPop3();
		virtual     ~CxTest_CxPop3();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxPop3H
