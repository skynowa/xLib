/****************************************************************************
* Class name:  CxTest_CxSocketInit
* Description: test CxSocketInit
* File name:   CxTest_CxSocketInit.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Net/CxTest_CxSocketInit.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxSocketInit
CxTest_CxSocketInit::CxTest_CxSocketInit() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxSocketInit
CxTest_CxSocketInit::~CxTest_CxSocketInit() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL 
CxTest_CxSocketInit::bUnit() {
	/*DEBUG*/

	//-------------------------------------
	//CxSocketInit
	{
		CxSocketInit siInit10(1, 0);
		CxSocketInit siInit11(1, 1);
		CxSocketInit siInit20(2, 0);
		CxSocketInit siInit21(2, 1);
		CxSocketInit siInit22(2, 2);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
