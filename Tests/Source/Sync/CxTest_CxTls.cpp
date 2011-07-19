/****************************************************************************
* Class name:  CxTest_CxTls
* Description: test CxTls
* File name:   CxTest_CxTls.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxTls.h>


//---------------------------------------------------------------------------
CxTest_CxTls::CxTest_CxTls() {

}
//---------------------------------------------------------------------------
CxTest_CxTls::~CxTest_CxTls() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxTls::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bSetValue, pvGetValue
    xTEST_BLOCK(cullBlockLoops)
    {
        CxTls tlsTls;

        const ULONG culData = 777;

        ULONG *pulValue = new ULONG(culData);

        _m_bRes = tlsTls.bSetValue(static_cast<VOID *>( pulValue ));
        xASSERT_NOT_EQ(FALSE, _m_bRes);

        ULONG *pulRes = static_cast<ULONG *>( tlsTls.pvGetValue() );
        xASSERT_PTR(pulRes);
        xASSERT_EQ(culData, ULONG(*pulRes));

        delete pulRes;
    }

    return TRUE;
}
//---------------------------------------------------------------------------
