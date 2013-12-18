/**
 * \file   CxTest_CxGuid.cpp
 * \brief  test CxGuid
 */


#include <Test/Crypt/CxTest_CxGuid.h>


//---------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxGuid::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxGuid::create", a_caseLoops)
    {
        CxGuid::cExType data[] = {
            CxGuid::tpRandomBased
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            CxGuid guid;

            m_sRv = guid.create(data[i]);
            xTEST_EQ(false, m_sRv.empty());
        }
    }
}
//---------------------------------------------------------------------------
