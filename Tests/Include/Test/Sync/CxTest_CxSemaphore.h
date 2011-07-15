/****************************************************************************
* Class name:  CxTest_CxSemaphore
* Description: test CxSemaphore
* File name:   CxTest_CxSemaphore.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSemaphoreH
#define CxTest_CxSemaphoreH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxSemaphore.h>
//---------------------------------------------------------------------------
class CxTest_CxSemaphore :
    public CxTest
{
	public:
                     CxTest_CxSemaphore();
		virtual     ~CxTest_CxSemaphore();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSemaphoreH
