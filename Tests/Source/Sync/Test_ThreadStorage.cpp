/**
 * \file   Test_ThreadStorage.cpp
 * \brief
 */


#include <Test/Sync/Test_ThreadStorage.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_ThreadStorage)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_ThreadStorage::unit()
{
    xTEST_CASE("setValue, value")
    {
        culong_t data[] = {0, 1, 2, 777};


        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            culong_t culData  = data[i];
            ulong_t *pulValue = new ulong_t(culData);

            ThreadStorage tls;

            m_bRv = tls.isValid();
            xTEST_EQ(m_bRv, true);

            m_bRv = tls.isSet();
            xTEST_EQ(m_bRv, false);

            tls.setValue(reinterpret_cast<void_t **>(&pulValue));

            m_bRv = tls.isSet();
            xTEST_EQ(m_bRv, true);

            ulong_t *pulRes = static_cast<ulong_t *>( tls.value() );
            xTEST_PTR(pulRes);
            xTEST_EQ(culData, ulong_t(*pulRes));

            m_bRv = tls.isSet();
            xTEST_EQ(m_bRv, true);

            m_bRv = tls.isValid();
            xTEST_EQ(m_bRv, true);

            delete pulRes;
        }
    }
}
//-------------------------------------------------------------------------------------------------
