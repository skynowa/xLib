/****************************************************************************
* Class name:  CxTest_CxDnsClient
* Description: test CxDnsClient
* File name:   CxTest_CxDnsClient.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxDnsClientH
#define CxTest_CxDnsClientH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxDnsClient :
    public CxTest
{
	public:
                     CxTest_CxDnsClient();
		virtual     ~CxTest_CxDnsClient();

		virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDnsClientH
