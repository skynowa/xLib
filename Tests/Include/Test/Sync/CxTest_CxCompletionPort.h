/****************************************************************************
* Class name:  CxTest_CxCompletionPort
* Description: test CxCompletionPort
* File name:   CxTest_CxCompletionPort.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCompletionPortH
#define CxTest_CxCompletionPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxCompletionPort.h>
//---------------------------------------------------------------------------
class CxTest_CxCompletionPort :
    public CxTest
{
	public:
                     CxTest_CxCompletionPort();
		virtual     ~CxTest_CxCompletionPort();

		virtual     BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCompletionPortH
