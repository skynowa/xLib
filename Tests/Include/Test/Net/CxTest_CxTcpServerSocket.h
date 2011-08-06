/****************************************************************************
* Class name:  CxTest_CxTcpServerSocket
* Description: test CxTcpServerSocket
* File name:   CxTest_CxTcpServerSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTcpServerSocketH
#define CxTest_CxTcpServerSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxTcpServerSocket.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxTcpServerSocket :
    public CxTest
{
	public:
                     CxTest_CxTcpServerSocket();
		virtual     ~CxTest_CxTcpServerSocket();

		virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTcpServerSocketH
