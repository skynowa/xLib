/****************************************************************************
* Class name:  CxTest_CxAutoCriticalSection
* Description: test CxAutoCriticalSection
* File name:   CxTest_CxAutoCriticalSection.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxAutoCriticalSection.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxAutoCriticalSection
CxTest_CxAutoCriticalSection::CxTest_CxAutoCriticalSection() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxAutoCriticalSection
CxTest_CxAutoCriticalSection::~CxTest_CxAutoCriticalSection() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
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
