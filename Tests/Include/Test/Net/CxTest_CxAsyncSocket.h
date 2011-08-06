/****************************************************************************
* Class name:  CxTest_CxAsyncSocket
* Description: test CxAsyncSocket
* File name:   CxTest_CxAsyncSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAsyncSocketH
#define CxTest_CxAsyncSocketH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxAsyncSocket.h>
//---------------------------------------------------------------------------
class CxTest_CxAsyncSocket :
    public CxTest
{
	public:
                     CxTest_CxAsyncSocket();
		virtual     ~CxTest_CxAsyncSocket();

	    virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAsyncSocketH
