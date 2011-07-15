/****************************************************************************
* Class name:  CxTest_CxHttpClient
* Description: test CxHttpClient
* File name:   CxTest_CxHttpClient.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxHttpClientH
#define CxTest_CxHttpClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxHttpClient.h>
//---------------------------------------------------------------------------
class CxTest_CxHttpClient :
    public CxTest
{
	public:
                     CxTest_CxHttpClient();
		virtual     ~CxTest_CxHttpClient();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxHttpClientH
