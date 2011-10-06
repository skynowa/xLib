/****************************************************************************
* Class name:  CxTest_CxTcpClient
* Description: test CxTcpClient
* File name:   CxTest_CxTcpClient.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTcpClientH
#define CxTest_CxTcpClientH
//---------------------------------------------------------------------------
#include <xLib/Net/CxTcpClient.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxTcpClient :
    public CxTest
{
	public:
                     CxTest_CxTcpClient();
        virtual     ~CxTest_CxTcpClient();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTcpClientH
