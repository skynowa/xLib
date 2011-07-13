/****************************************************************************
* Class name:  CxTest_CxQueryList
* Description: test CxQueryList
* File name:   CxTest_CxQueryList.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxQueryListH
#define CxTest_CxQueryListH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxQueryList.h>
//---------------------------------------------------------------------------
class CxTest_CxQueryList :
    public CxTest
{
	public:
		CxTest_CxQueryList();
		virtual     ~CxTest_CxQueryList();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxQueryListH
