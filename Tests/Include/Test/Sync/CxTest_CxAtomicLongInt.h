/****************************************************************************
* Class name:  CxTest_CxAtomicLongInt
* Description: test CxAtomicLongInt
* File name:   CxTest_CxAtomicLongInt.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAtomicLongIntH
#define CxTest_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxAtomicLongInt.h>
//---------------------------------------------------------------------------
class CxTest_CxAtomicLongInt :
    public CxTest
{
	public:
                     CxTest_CxAtomicLongInt();
		virtual     ~CxTest_CxAtomicLongInt();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxAtomicLongIntH
