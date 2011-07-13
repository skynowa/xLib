/****************************************************************************
* Class name:  CxTest_CxAutoMutex
* Description: test CxAutoMutex
* File name:   CxTest_CxAutoMutex.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxAutoMutex (constructor)
CxTest_CxAutoMutex::CxTest_CxAutoMutex() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxAutoMutex (destructor)
CxTest_CxAutoMutex::~CxTest_CxAutoMutex() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxAutoMutex::bUnit() {
	//-------------------------------------
	//CxAutoMutex
	{
    	CxMutex mtMutex;

		CxAutoMutex objAutoMutex(mtMutex);
	}

    return TRUE;
}
//---------------------------------------------------------------------------
