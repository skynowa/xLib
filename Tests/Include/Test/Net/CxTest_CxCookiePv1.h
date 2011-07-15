/****************************************************************************
* Class name:  CxTest_CxCookiePv1
* Description: test CxCookiePv1
* File name:   CxTest_CxCookiePv1.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCookiePv1H
#define CxTest_CxCookiePv1H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxCookiePv1.h>
//---------------------------------------------------------------------------
class CxTest_CxCookiePv1 :
    public CxTest
{
	public:
                     CxTest_CxCookiePv1();
		virtual     ~CxTest_CxCookiePv1();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCookiePv1H
