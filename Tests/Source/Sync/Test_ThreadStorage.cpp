/**
 * \file   Test_ThreadStorage.cpp
 * \brief
 */


#include <Test/Sync/Test_ThreadStorage.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_ThreadStorage::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("ThreadStorage::setValue value", a_caseLoops)
    {
        culong_t caulData[] = {0, 1, 2, 777};


        for (size_t i = 0; i < xARRAY_SIZE(caulData); ++ i) {
            ThreadStorage tlsTls;

            culong_t culData = caulData[i];

            ulong_t *pulValue = new ulong_t(culData);

            m_bRv = tlsTls.isSet();
            xTEST_EQ(m_bRv, false);

            tlsTls.setValue(static_cast<void_t *>( pulValue ));

            m_bRv = tlsTls.isSet();
            xTEST_EQ(m_bRv, true);

            ulong_t *pulRes = static_cast<ulong_t *>( tlsTls.value() );
            xTEST_PTR(pulRes);
            xTEST_EQ(culData, ulong_t(*pulRes));

            m_bRv = tlsTls.isSet();
            xTEST_EQ(m_bRv, true);

            delete pulRes;
        }
    }
}
//-------------------------------------------------------------------------------------------------
