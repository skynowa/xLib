/****************************************************************************
* Class name:  CxTest_CxFileLog
* Description: test CxFileLog
* File name:   CxFileLog.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#ifndef CxTest_CxFileLogH
#define CxTest_CxFileLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Log/CxFileLog.h>
//---------------------------------------------------------------------------
class CxTest_CxFileLog :
    public CxTest
{
	public:
		         CxTest_CxFileLog();
	    virtual ~CxTest_CxFileLog();

	    virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileLogH
