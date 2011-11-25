/**
 * \file   CxTest_CxThreadStorage.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxThreadStorage.h>


//---------------------------------------------------------------------------
CxTest_CxThreadStorage::CxTest_CxThreadStorage() {

}
//---------------------------------------------------------------------------
CxTest_CxThreadStorage::~CxTest_CxThreadStorage() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxThreadStorage::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    //--------------------------------------------------
    //bSetValue, pvGetValue
    xTEST_CASE(cullBlockLoops)
    {
        const ulong_t caulData[] = {0, 1, 2, 777};


        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            CxThreadStorage tlsTls;

            const ulong_t culData = caulData[i];

            ulong_t *pulValue = new ulong_t(culData);

            m_bRes = tlsTls.bIsSet();
            xTEST_EQ(false, m_bRes);

            m_bRes = tlsTls.bSetValue(static_cast<void *>( pulValue ));
            xTEST_EQ(true, m_bRes);

            m_bRes = tlsTls.bIsSet();
            xTEST_EQ(true, m_bRes);

            ulong_t *pulRes = static_cast<ulong_t *>( tlsTls.pvGetValue() );
            xTEST_PTR(pulRes);
            xTEST_EQ(culData, ulong_t(*pulRes));

            m_bRes = tlsTls.bIsSet();
            xTEST_EQ(true, m_bRes);

            delete pulRes;
        }
    }

    return true;
}
//---------------------------------------------------------------------------
