/****************************************************************************
* Class name:  CxTest_CxSocket
* Description: test CxSocket
* File name:   CxTest_CxSocket.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSocketH
#define CxTest_CxSocketH
//---------------------------------------------------------------------------
#include <xLib/Net/CxSocket.h>
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_CxSocket :
    public CxTest
{
	public:
                     CxTest_CxSocket();
		virtual     ~CxTest_CxSocket();

		virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSocketH
