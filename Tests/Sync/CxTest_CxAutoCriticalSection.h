/****************************************************************************
* Class name:  CxTest_CxAutoCriticalSection
* Description: test CxAutoCriticalSection
* File name:   CxTest_CxAutoCriticalSection.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxAutoCriticalSectionH
#define CxTest_CxAutoCriticalSectionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxAutoCriticalSection.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoCriticalSection : public CxTest {
	public:
		CxTest_CxAutoCriticalSection();
	   ~CxTest_CxAutoCriticalSection();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxAutoCriticalSection (constructor)
CxTest_CxAutoCriticalSection::CxTest_CxAutoCriticalSection() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxAutoCriticalSection (destructor)
CxTest_CxAutoCriticalSection::~CxTest_CxAutoCriticalSection() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxAutoCriticalSection::bUnit() {
	//-------------------------------------
	//
	{
		////CxAutoCriticalSection objCxCriticalSectionLocker;
	}

	//-------------------------------------
	//
	{
		////CxAutoCriticalSection objCxCriticalSectionLocker(10000);
	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoCriticalSectionH
