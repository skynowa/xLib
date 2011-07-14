/****************************************************************************
* Class name:  CxTest_CxMutex
* Description: test CxMutex
* File name:   CxTest_CxMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxMutexH
#define CxTest_CxMutexH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxMutex.h>
//---------------------------------------------------------------------------
class CxTest_CxMutex :
    public CxTest
{
	public:
		CxTest_CxMutex();
		virtual     ~CxTest_CxMutex();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxMutexH
