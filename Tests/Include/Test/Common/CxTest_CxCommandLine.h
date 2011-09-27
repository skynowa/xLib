/****************************************************************************
* Class name:  CxTest_CxCommandLine
* Description: test CxCommandLine
* File name:   CxTest_CxCommandLine.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxCommandLineH
#define CxTest_CxCommandLineH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxCommandLine.h>
//---------------------------------------------------------------------------
class CxTest_CxCommandLine :
    public CxTest
{
	public:
                     CxTest_CxCommandLine();
		virtual     ~CxTest_CxCommandLine();

	    virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCommandLineH
