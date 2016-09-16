/**
 * \file   Test_Guid.cpp
 * \brief  test Guid
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_Guid)
xTEST_UNIT(Test_Guid)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Guid::unit()
{
    xTEST_CASE("create")
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

    return true;
}
//-------------------------------------------------------------------------------------------------
