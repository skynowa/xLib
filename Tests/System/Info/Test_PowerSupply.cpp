/**
 * \file   Test_PowerSupply.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_PowerSupply)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_PowerSupply::unit()
{
	info::PowerSupply sysInfo;

    xTEST_CASE("isExists, level")
    {
		if ( sysInfo.isExists() ) {
			m_stRv = sysInfo.level();
			xTEST_GR(m_stRv, 0ULL);

			info::PowerSupply::cStatus psRv = sysInfo.status();
			xTEST_DIFF((int)psRv, (int)info::PowerSupply::Status::Unknown);
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
