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
	PowerSupply sysInfo;

    xTEST_CASE("isPowerSupply, powerSupplyLevel")
    {
		if ( sysInfo.isPowerSupply() ) {
			m_stRv = sysInfo.powerSupplyLevel();
			xTEST_GR(m_stRv, 0ULL);

			PowerSupply::cPowerSupplyStatus psRv = sysInfo.powerSupplyStatus();
			xTEST_DIFF((int)psRv, (int)PowerSupply::PowerSupplyStatus::Unknown);
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
