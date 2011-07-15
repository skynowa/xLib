/****************************************************************************
* Class name:  CxTest_CxUri
* Description: test CxUri
* File name:   CxTest_CxUri.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxUriH
#define CxTest_CxUriH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxUri.h>
//---------------------------------------------------------------------------
class CxTest_CxUri :
    public CxTest
{
	public:
                     CxTest_CxUri();
		virtual     ~CxTest_CxUri();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxUriH
