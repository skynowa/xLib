/**
 * \file   Test_Ram.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Ram)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Ram::unit()
{
	info::Ram sysInfo;

    xTEST_CASE("total")
    {
        m_ullRv = sysInfo.total();
        xTEST_GR(m_ullRv, 0ULL);
    }

    xTEST_CASE("available")
    {
        m_ullRv = sysInfo.available();
        xTEST_GR(m_ullRv, 0ULL);
    }

    xTEST_CASE("usage")
    {
        for (size_t i = 0; i < 5; ++ i) {
            m_ulRv = sysInfo.usage();
            xTEST_NA(m_ulRv);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
