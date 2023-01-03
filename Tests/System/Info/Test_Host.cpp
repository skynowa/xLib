/**
 * \file   Test_Host.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Host)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SystemInfo::unit()
{
	Host sysInfo;

    xTEST_CASE("hostName")
    {
        m_sRv = sysInfo.hostName();
        xTEST(!m_sRv.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
