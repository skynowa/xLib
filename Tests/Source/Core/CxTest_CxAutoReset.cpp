/**
 * \file   CxTest_CxAutoReset.cpp
 * \brief  test CxAutoReset
 */


#include <Test/Core/CxTest_CxAutoReset.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxAutoReset::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxAutoReset::CxAutoReset", a_caseLoops)
    {
        bool_t data[] = {true, false, true};

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            bool_t origin = data[i];

            {
                CxAutoReset<bool_t> reseter(&data[i], false);
                xTEST_EQ(data[i], origin);
            }

            xTEST_EQ(data[i], false);
        }

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            bool_t origin = data[i];

            {
                CxAutoReset<bool_t> reseter(&data[i], true);
                xTEST_EQ(data[i], origin);
            }

            xTEST_EQ(data[i], true);
        }
    }
}
//-------------------------------------------------------------------------------------------------
