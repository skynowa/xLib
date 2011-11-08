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
        const ULONG caulData[] = {0, 1, 2, 777};


        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
	        CxThreadStorage tlsTls;
	
	        const ULONG culData = caulData[i];
	
	        ULONG *pulValue = new ULONG(culData);
	
	        m_bRes = tlsTls.bIsSet();
	        xTEST_EQ(FALSE, m_bRes);
	
	        m_bRes = tlsTls.bSetValue(static_cast<void *>( pulValue ));
	        xTEST_DIFF(FALSE, m_bRes);
	
	        m_bRes = tlsTls.bIsSet();
	        xTEST_DIFF(FALSE, m_bRes);
	
	        ULONG *pulRes = static_cast<ULONG *>( tlsTls.pvGetValue() );
	        xTEST_PTR(pulRes);
	        xTEST_EQ(culData, ULONG(*pulRes));
	
	        m_bRes = tlsTls.bIsSet();
	        xTEST_DIFF(FALSE, m_bRes);
	
	        delete pulRes;
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
