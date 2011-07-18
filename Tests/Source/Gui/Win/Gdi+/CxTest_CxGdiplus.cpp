/****************************************************************************
* Class name:  CxTest_CxGdiplus
* Description: test CxGdiplus
* File name:   CxTest_CxGdiplus.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Gui/Win/Gdi+/CxTest_CxGdiplus.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxGdiplus
CxTest_CxGdiplus::CxTest_CxGdiplus() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxGdiplus
CxTest_CxGdiplus::~CxTest_CxGdiplus() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL 
CxTest_CxGdiplus::bUnit() {
	/*DEBUG*/

    CxGdiplus gpGdiPlus;

	return TRUE;
}
//---------------------------------------------------------------------------
