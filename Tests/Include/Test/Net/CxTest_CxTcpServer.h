/****************************************************************************
* Class name:  CxTest_CxTcpServer
* Description: test CxTcpServer
* File name:   CxTest_CxTcpServer.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTcpServerH
#define CxTest_CxTcpServerH
//---------------------------------------------------------------------------
#include <xLib/Net/CxTcpServer.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxTcpServer :
    public CxTest
{
	public:
                     CxTest_CxTcpServer();
		virtual     ~CxTest_CxTcpServer();

		virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTcpServerH
