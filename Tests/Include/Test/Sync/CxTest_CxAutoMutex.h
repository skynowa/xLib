/****************************************************************************
* Class name:  CxTest_CxAutoMutex
* Description: test CxAutoMutex
* File name:   CxTest_CxAutoMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAutoMutexH
#define CxTest_CxAutoMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxAutoMutex.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoMutex :
    public CxTest
{
	public:
		CxTest_CxAutoMutex();
		virtual     ~CxTest_CxAutoMutex();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoMutexH
