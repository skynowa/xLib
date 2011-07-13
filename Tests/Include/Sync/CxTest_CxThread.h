/****************************************************************************
* Class name:  CxTest_CxThread
* Description: test CxThread
* File name:   CxTest_CxThread.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxThreadH
#define CxTest_CxThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxThread.h>

#if xTODO
    #include "CWorkThread.h"
#endif
//---------------------------------------------------------------------------
class CxTest_CxThread :
    public CxTest
{
	public:
		CxTest_CxThread();
		virtual     ~CxTest_CxThread();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxThreadH
