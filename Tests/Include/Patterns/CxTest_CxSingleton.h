/****************************************************************************
* Class name:  CxTest_CxSingleton
* Description: test CxSingleton
* File name:   CxTest_CxSingleton.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSingletonH
#define CxTest_CxSingletonH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Patterns/CxSingleton.h>
//---------------------------------------------------------------------------
class CxTest_CxSingleton :
    public CxTest
{
	public:
		CxTest_CxSingleton();
		virtual     ~CxTest_CxSingleton();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSingletonH
