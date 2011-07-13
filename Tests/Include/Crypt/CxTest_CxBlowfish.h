/****************************************************************************
* Class name:  CxTest_CxBlowfish
* Description: test CxBlowfish
* File name:   CxTest_CxBlowfish.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxBlowfishH
#define CxTest_CxBlowfishH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Crypt/OpenSSL/CxBlowfish.h>
//---------------------------------------------------------------------------
class CxTest_CxBlowfish :
    public CxTest
{
	public:
		CxTest_CxBlowfish();
		virtual     ~CxTest_CxBlowfish();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxBlowfishH
