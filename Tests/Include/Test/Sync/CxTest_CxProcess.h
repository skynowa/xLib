/****************************************************************************
* Class name:  CxTest_CxProcess
* Description: test CxTest_CxProcess
* File name:   CxTest_CxProcess.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTest_CxProcessH
#define CxTest_CxTest_CxProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxProcess.h>
//---------------------------------------------------------------------------
class CxTest_CxProcess :
    public CxTest
{
	public:
                     CxTest_CxProcess();
		virtual     ~CxTest_CxProcess();

	    virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTest_CxProcessH
