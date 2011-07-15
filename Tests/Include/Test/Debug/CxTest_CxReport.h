/****************************************************************************
* Class name:  CxTest_CxReport
* Description: test CxReport
* File name:   CxTest_CxReport.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxReportH
#define CxTest_CxReportH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxReport.h>
//---------------------------------------------------------------------------
class CxTest_CxReport :
    public CxTest
{
	public:
                     CxTest_CxReport();
		virtual     ~CxTest_CxReport();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxReportH
