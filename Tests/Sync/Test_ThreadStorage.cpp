/**
 * \file   Test_ThreadStorage.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_ThreadStorage)
xTEST_UNIT(Test_ThreadStorage)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
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
            xTEST(m_bRv);

            m_bRv = tls.isSet();
            xTEST(!m_bRv);

            tls.setValue(reinterpret_cast<void_t **>(&pulValue));

            m_bRv = tls.isSet();
            xTEST(m_bRv);

            ulong_t *pulRes = static_cast<ulong_t *>( tls.value() );
            xTEST_PTR(pulRes);
            xTEST_EQ(culData, ulong_t(*pulRes));

            m_bRv = tls.isSet();
            xTEST(m_bRv);

            m_bRv = tls.isValid();
            xTEST(m_bRv);

            delete pulRes;
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
