/****************************************************************************
* Class name:  CxTest_CxTcpClientSocket
* Description: test CxTcpClientSocket
* File name:   CxTest_CxTcpClientSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTcpClientSocketH
#define CxTest_CxTcpClientSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxTcpClientSocket.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxTcpClientSocket :
    public CxTest
{
	public:
		CxTest_CxTcpClientSocket();
		virtual     ~CxTest_CxTcpClientSocket();

	   virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTcpClientSocketH
