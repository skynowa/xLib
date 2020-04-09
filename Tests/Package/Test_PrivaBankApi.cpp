/**
 * \file  Test_PrivaBankApi.cpp
 * \brief test PrivaBankApi
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_PrivaBankApi)
xTEST_UNIT(Test_PrivaBankApi)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_PrivaBankApi::unit()
{
	xTEST_CASE("getExchangeRates")
	{
		std::ctstring_t               date = xT("01.12.2014");
		PrivaBankApi::exchange_rate_t data;

		PrivaBankApi api;
		api.getExchangeRates(date, &data);
		Cout() << xTRACE_VAR(data);
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
