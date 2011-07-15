/****************************************************************************
* Class name:  CxTest_CxDebugger
* Description: test CxDebugger
* File name:   CxTest_CxDebugger.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxDebuggerH
#define CxTest_CxDebuggerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxDebugger.h>
//---------------------------------------------------------------------------
class CxTest_CxDebugger :
    public CxTest
{
	public:
                     CxTest_CxDebugger();
		virtual     ~CxTest_CxDebugger();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxDebuggerH
