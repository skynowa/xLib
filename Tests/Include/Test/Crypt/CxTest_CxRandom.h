/****************************************************************************
* Class name:  CxTest_CxRandom
* Description: test CxRandom
* File name:   CxTest_CxRandom.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxRandomH
#define CxTest_CxRandomH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Crypt/CxRandom.h>
//---------------------------------------------------------------------------
class CxTest_CxRandom :
    public CxTest
{
	public:
                     CxTest_CxRandom();
		virtual     ~CxTest_CxRandom();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxRandomH
