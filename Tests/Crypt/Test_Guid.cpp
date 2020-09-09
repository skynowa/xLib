/**
 * \file   Test_Guid.cpp
 * \brief  test Guid
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Guid)
xTEST_UNIT(Test_Guid)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Guid::unit()
{
    xTEST_CASE("str")
    {
        Guid::cType data[]
        {
            Guid::Type::RandomBased
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            Guid guid(data[i]);
            m_sRv = guid.str();
            xTEST(!m_sRv.empty());
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
