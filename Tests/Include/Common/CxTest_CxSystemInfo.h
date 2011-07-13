/****************************************************************************
* Class name:  CxTest_CxSystemInfo
* Description: test CxSystemInfo
* File name:   CxTest_CxSystemInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSystemInfoH
#define CxTest_CxSystemInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxSystemInfo.h>
//---------------------------------------------------------------------------
class CxTest_CxSystemInfo :
    public CxTest
{
	public:
		CxTest_CxSystemInfo();
		virtual     ~CxTest_CxSystemInfo();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSystemInfoH
