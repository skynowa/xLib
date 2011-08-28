/****************************************************************************
* Class name:  CxTest_CxBase64
* Description: test CxBase64
* File name:   CxTest_CxBase64.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxBase64H
#define CxTest_CxBase64H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Crypt/OpenSSL/CxBase64.h>
//---------------------------------------------------------------------------
class CxTest_CxBase64 :
    public CxTest
{
	public:
                     CxTest_CxBase64();
		virtual     ~CxTest_CxBase64();

	    virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxBase64H
