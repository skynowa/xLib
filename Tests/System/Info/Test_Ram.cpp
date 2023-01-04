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

    xTEST_CASE("ramTotal")
    {
        m_ullRv = sysInfo.ramTotal();
        xTEST_GR(m_ullRv, 0ULL);
    }

    xTEST_CASE("ramAvailable")
    {
        m_ullRv = sysInfo.ramAvailable();
        xTEST_GR(m_ullRv, 0ULL);
    }

    xTEST_CASE("ramUsage")
    {
        for (size_t i = 0; i < 5; ++ i) {
            m_ulRv = sysInfo.ramUsage();
            xTEST_NA(m_ulRv);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
