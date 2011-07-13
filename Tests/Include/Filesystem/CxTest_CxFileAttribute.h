/****************************************************************************
* Class name:  CxTest_CxFileAttribute
* Description: test CxFileAttribute
* File name:   CxFileAttribute.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.05.2011
*
*****************************************************************************/


#ifndef CxTest_CxFileAttributeH
#define CxTest_CxFileAttributeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxFileAttribute.h>
//---------------------------------------------------------------------------
class CxTest_CxFileAttribute :
    public CxTest
{
	public:
		         CxTest_CxFileAttribute();
	    virtual ~CxTest_CxFileAttribute();

	    virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileAttributeH
