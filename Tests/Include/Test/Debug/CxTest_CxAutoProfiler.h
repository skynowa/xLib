/****************************************************************************
* Class name:  CxTest_CxAutoProfiler
* Description: test CxAutoProfiler
* File name:   CxTest_CxAutoProfiler.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAutoProfilerH
#define CxTest_CxAutoProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxAutoProfiler.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoProfiler :
    public CxTest
{
	public:
                     CxTest_CxAutoProfiler();
		virtual     ~CxTest_CxAutoProfiler();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoProfilerH
