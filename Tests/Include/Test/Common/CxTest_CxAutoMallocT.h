/****************************************************************************
* Class name:  CxTest_CxAutoMallocT
* Description: test CxAutoMallocT
* File name:   CxTest_CxAutoMallocT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAutoMallocTH
#define CxTest_CxAutoMallocTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxAutoMallocT.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoMallocT :
    public CxTest
{
	public:
                     CxTest_CxAutoMallocT();
		virtual     ~CxTest_CxAutoMallocT();

	    virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoMallocTH
