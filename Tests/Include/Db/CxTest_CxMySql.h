/****************************************************************************
* Class name:  CxTest_CxMySql
* Description: test CxMySql
* File name:   CxTest_CxMySql.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxMySqlH
#define CxTest_CxMySqlH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Db/CxMySql.h>
//---------------------------------------------------------------------------
class CxTest_CxMySql :
    public CxTest
{
	public:
		CxTest_CxMySql();
		virtual     ~CxTest_CxMySql();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxMySqlH
