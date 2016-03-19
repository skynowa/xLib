/**
 * \file   Test_Guid.cpp
 * \brief  test Guid
 */


#include <Test/Crypt/Test_Guid.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Guid)
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Guid::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("create", a_caseLoops)
    {
        Guid::cExType data[] = {
            Guid::tpRandomBased
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            Guid guid;

            m_sRv = guid.create(data[i]);
            xTEST_EQ(m_sRv.empty(), false);
        }
    }
}
//-------------------------------------------------------------------------------------------------
