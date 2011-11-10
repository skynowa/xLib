/**
 * \file   CxTest_CxAutoMallocT.cpp
 * \brief
 */


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
