/**
 * \file   Test_Guid.cpp
 * \brief  test Guid
 */


#include <Test/Crypt/Test_Guid.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Guid::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Guid::create", a_caseLoops)
    {
        Guid::cExType data[] = {
            Guid::tpRandomBased
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            Guid guid;

            m_sRv = guid.create(data[i]);
            xTEST_EQ(false, m_sRv.empty());
        }
    }
}
//-------------------------------------------------------------------------------------------------
