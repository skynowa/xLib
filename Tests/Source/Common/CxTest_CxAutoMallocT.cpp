/****************************************************************************
* Class name:  CxTest_CxAutoMallocT
* Description: test CxAutoMallocT
* File name:   CxTest_CxAutoMallocT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxAutoMallocT.h>


//---------------------------------------------------------------------------
//test struct
typedef struct {
    int x;
    int y;
} SMy, *PSMy;
//---------------------------------------------------------------------------
CxTest_CxAutoMallocT::CxTest_CxAutoMallocT() {

}
//---------------------------------------------------------------------------
CxTest_CxAutoMallocT::~CxTest_CxAutoMallocT() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxAutoMallocT::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //-------------------------------------
    //CxAutoMallocT
    xTEST_BLOCK(cullBlockLoops)
    {
        CxAutoMallocT<PSMy> stM(sizeof(SMy));
    }

    return TRUE;
}
//---------------------------------------------------------------------------
