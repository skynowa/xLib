/**
 * \file   Test_Net.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Net)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Net::unit()
{
	info::Net sysInfo;

    xTEST_CASE("isVpnActive")
    {
        m_bRv = sysInfo.isVpnActive();
        xTEST_NA(m_bRv);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
