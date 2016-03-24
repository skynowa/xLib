/**
 * \file   Test_AutoReset.cpp
 * \brief  test AutoReset
 */


#include <Test/Core/Test_AutoReset.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_AutoReset)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_AutoReset::unit()
{
    xTEST_CASE("AutoReset")
    {
        cbool_t data[] = {true, false, true};

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            bool_t origin = data[i];

            {
                AutoReset<bool_t> reseter(&origin, false);
                xTEST_EQ(origin, data[i]);
            }

            xTEST_EQ(origin, false);
        }

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            bool_t origin = data[i];

            {
                AutoReset<bool_t> reseter(&origin, true);
                xTEST_EQ(origin, data[i]);
            }

            xTEST_EQ(origin, true);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
