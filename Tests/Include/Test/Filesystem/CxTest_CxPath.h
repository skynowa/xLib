/****************************************************************************
* Class name:  CxTest_CxPath
* Description: test CxPath
* File name:   CxTest_CxPath.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxPathH
#define CxTest_CxPathH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxPath.h>
//---------------------------------------------------------------------------
class CxTest_CxPath :
    public CxTest
{
	public:
		             CxTest_CxPath();
	    virtual     ~CxTest_CxPath();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxPathH
