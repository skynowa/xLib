/****************************************************************************
* Class name:  CxTest_CxLastError
* Description: test CxLastError
* File name:   CxTest_CxLastError.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxLastErrorH
#define CxTest_CxLastErrorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxLastError.h>
//---------------------------------------------------------------------------
class CxTest_CxLastError :
    public CxTest
{
	public:
                     CxTest_CxLastError();
		virtual     ~CxTest_CxLastError();

	    virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxLastErrorH
