/****************************************************************************
* Class name:  CxTest_CxCriticalSection
* Description: test CxCriticalSection
* File name:   CxTest_CxCriticalSection.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCriticalSectionH
#define CxTest_CxCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxTest_CxCriticalSection :
    public CxTest
{
	public:
		CxTest_CxCriticalSection();
		virtual     ~CxTest_CxCriticalSection();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCriticalSectionH
