/****************************************************************************
* Class name:  CxTest_CxUrlCoder
* Description: test CxUrlCoder
* File name:   CxTest_CxUrlCoder.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxUrlCoderH
#define CxTest_CxUrlCoderH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxUrlCoder.h>
//---------------------------------------------------------------------------
class CxTest_CxUrlCoder :
    public CxTest
{
	public:
		CxTest_CxUrlCoder();
		virtual     ~CxTest_CxUrlCoder();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxUrlCoderH
