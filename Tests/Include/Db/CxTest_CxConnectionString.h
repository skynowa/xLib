/****************************************************************************
* Class name:  CxTest_CxConnectionString
* Description: test CxConnectionString
* File name:   CxTest_CxConnectionString.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxConnectionStringH
#define CxTest_CxConnectionStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Db/CxConnectionString.h>
//---------------------------------------------------------------------------
class CxTest_CxConnectionString :
    public CxTest
{
	public:
		CxTest_CxConnectionString();
		virtual     ~CxTest_CxConnectionString();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxConnectionStringH
