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
	info::PowerSupply powerSupply;

    xTEST_CASE("isExists, level, status")
    {
		if ( powerSupply.isExists() ) {
			m_stRv = powerSupply.level();
			xTEST_GR(m_stRv, 0ULL);

			info::PowerSupply::cStatus psRv = powerSupply.status();
			xTEST_DIFF((int)psRv, (int)info::PowerSupply::Status::Unknown);
		}
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
