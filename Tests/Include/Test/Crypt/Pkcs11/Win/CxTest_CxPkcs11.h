/****************************************************************************
* Class name:  CxTest_CxPkcs11
* Description: test CxPkcs11
* File name:   CxTest_CxPkcs11.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxPkcs11H
#define CxTest_CxPkcs11H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>

#if defined(xOS_ENV_WIN)
    #include <xLib/Crypt/Pkcs11/Win/All.h>
#endif
//---------------------------------------------------------------------------
class CxTest_CxPkcs11 :
    public CxTest
{
	public:
                     CxTest_CxPkcs11();
		virtual     ~CxTest_CxPkcs11();

		virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxPkcs11H
