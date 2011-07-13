/****************************************************************************
* Class name:  CxTest_CxTls
* Description: test CxTls
* File name:   CxTest_CxTls.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxTlsH
#define CxTest_CxTlsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxTls.h>
//---------------------------------------------------------------------------
class CxTest_CxTls :
    public CxTest
{
	public:
		CxTest_CxTls();
		virtual     ~CxTest_CxTls();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxTlsH
