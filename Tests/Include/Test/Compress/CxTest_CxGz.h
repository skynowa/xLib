/****************************************************************************
* Class name:  CxTest_CxGz
* Description: test CxGz
* File name:   CxTest_CxGz.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxGzH
#define CxTest_CxGzH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Compress/Linux/CxGz.h>
//---------------------------------------------------------------------------
class CxTest_CxGz :
    public CxTest
{
	public:
                     CxTest_CxGz();
		virtual     ~CxTest_CxGz();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxGzH
