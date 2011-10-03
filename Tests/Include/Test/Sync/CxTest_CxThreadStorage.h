/****************************************************************************
* Class name:  CxTest_CxThreadStorage
* Description: test CxThreadStorage
* File name:   CxTest_CxThreadStorage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxThreadStorageH
#define CxTest_CxThreadStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxThreadStorage.h>
//---------------------------------------------------------------------------
class CxTest_CxThreadStorage :
    public CxTest
{
	public:
                     CxTest_CxThreadStorage();
		virtual     ~CxTest_CxThreadStorage();

	    virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxThreadStorageH
