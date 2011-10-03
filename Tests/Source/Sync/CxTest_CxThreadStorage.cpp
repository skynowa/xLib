/****************************************************************************
* Class name:  CxTest_CxThreadStorage
* Description: test CxThreadStorage
* File name:   CxTest_CxThreadStorage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Sync/CxTest_CxThreadStorage.h>


//---------------------------------------------------------------------------
CxTest_CxThreadStorage::CxTest_CxThreadStorage() {

}
//---------------------------------------------------------------------------
CxTest_CxThreadStorage::~CxTest_CxThreadStorage() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxThreadStorage::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bSetValue, pvGetValue
    xTEST_BLOCK(cullBlockLoops)
    {
        CxThreadStorage tlsTls;

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
