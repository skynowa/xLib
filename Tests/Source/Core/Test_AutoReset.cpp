/**
 * \file   Test_AutoReset.cpp
 * \brief  test AutoReset
 */


#include <Test/Core/Test_AutoReset.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_AutoReset::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("AutoReset", a_caseLoops)
    {
        bool_t data[] = {true, false, true};

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            bool_t origin = data[i];

            {
                AutoReset<bool_t> reseter(&data[i], false);
                xTEST_EQ(data[i], origin);
            }

            xTEST_EQ(data[i], false);
        }

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            bool_t origin = data[i];

            {
                AutoReset<bool_t> reseter(&data[i], true);
                xTEST_EQ(data[i], origin);
            }

            xTEST_EQ(data[i], true);
        }
    }
}
//-------------------------------------------------------------------------------------------------
