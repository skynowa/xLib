/****************************************************************************
* Class name:  CxTest_CxAutoMallocT
* Description: test CxAutoMallocT
* File name:   CxTest_CxAutoMallocT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxAutoMallocTH
#define CxTest_CxAutoMallocTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxAutoMallocT.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoMallocT : public CxTest {
	public:
		CxTest_CxAutoMallocT();
		virtual     ~CxTest_CxAutoMallocT();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//test struct
typedef struct {
    INT x;
    INT y;
} SMy, *PSMy;

//---------------------------------------------------------------------------
//TODO: + CxTest_CxAutoMallocT (constructor)
CxTest_CxAutoMallocT::CxTest_CxAutoMallocT() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxAutoMallocT (destructor)
CxTest_CxAutoMallocT::~CxTest_CxAutoMallocT() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
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
#endif //CxTest_CxAutoMallocTH
