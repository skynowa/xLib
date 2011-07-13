/****************************************************************************
* Class name:  CxTest_CxAutoMallocT
* Description: test CxAutoMallocT
* File name:   CxTest_CxAutoMallocT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Common/CxTest_CxAutoMallocT.h>


//---------------------------------------------------------------------------
//test struct
typedef struct {
    INT x;
    INT y;
} SMy, *PSMy;

//---------------------------------------------------------------------------
//DONE: CxTest_CxAutoMallocT (constructor)
CxTest_CxAutoMallocT::CxTest_CxAutoMallocT() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxAutoMallocT (destructor)
CxTest_CxAutoMallocT::~CxTest_CxAutoMallocT() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxAutoMallocT::bUnit() {


    //-------------------------------------
	//CxAutoMallocT
	{
	    CxAutoMallocT<PSMy> stM(sizeof(SMy));
	}

    return TRUE;
}
//---------------------------------------------------------------------------
