/****************************************************************************
* Class name:  CxTest_CxAutoCriticalSection
* Description: test CxAutoCriticalSection
* File name:   CxTest_CxAutoCriticalSection.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAutoCriticalSectionH
#define CxTest_CxAutoCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxAutoCriticalSection.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoCriticalSection :
    public CxTest
{
	public:
		CxTest_CxAutoCriticalSection();
		virtual     ~CxTest_CxAutoCriticalSection();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoCriticalSectionH
