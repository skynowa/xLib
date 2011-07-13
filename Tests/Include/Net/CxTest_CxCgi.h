/****************************************************************************
* Class name:  CxTest_CxCgi
* Description: test CxCgi
* File name:   CxTest_CxCgi.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCgiH
#define CxTest_CxCgiH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxCgi.h>
//---------------------------------------------------------------------------
class CxTest_CxCgi :
    public CxTest
{
	public:
		CxTest_CxCgi();
		virtual     ~CxTest_CxCgi();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCgiH
