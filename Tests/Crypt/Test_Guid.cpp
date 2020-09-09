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

        for (auto &it_data : data) {
            Guid guid(it_data);
            m_sRv = guid.str();
            xTEST(!m_sRv.empty());
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
