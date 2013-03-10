/**
 * \file   CxTest_CxThreadStorage.cpp
 * \brief
 */


#include <Test/Sync/CxTest_CxThreadStorage.h>


//------------------------------------------------------------------------------
CxTest_CxThreadStorage::CxTest_CxThreadStorage() {

}
//------------------------------------------------------------------------------
CxTest_CxThreadStorage::~CxTest_CxThreadStorage() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxThreadStorage::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxThreadStorage::setValue CxThreadStorage::value", a_cullCaseLoops)
    {
        culong_t caulData[] = {0, 1, 2, 777};


        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            CxThreadStorage tlsTls;

            culong_t culData = caulData[i];

            ulong_t *pulValue = new ulong_t(culData);

            m_bRv = tlsTls.isSet();
            xTEST_EQ(false, m_bRv);

            tlsTls.setValue(static_cast<void_t *>( pulValue ));

            m_bRv = tlsTls.isSet();
            xTEST_EQ(true, m_bRv);

            ulong_t *pulRes = static_cast<ulong_t *>( tlsTls.value() );
            xTEST_PTR(pulRes);
            xTEST_EQ(culData, ulong_t(*pulRes));

            m_bRv = tlsTls.isSet();
            xTEST_EQ(true, m_bRv);

            delete pulRes;
        }
    }
}
//------------------------------------------------------------------------------
