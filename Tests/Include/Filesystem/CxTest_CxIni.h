/****************************************************************************
* Class name:  CxTest_CxIni
* Description: test CxIni
* File name:   CxIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#ifndef CxTest_CxIniH
#define CxTest_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxIni.h>
//---------------------------------------------------------------------------
class CxTest_CxIni :
    public CxTest
{
	public:
		         CxTest_CxIni();
	    virtual ~CxTest_CxIni();

	    virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxIniH
