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
		std::ctstring_t               date = DateTime().current().format(xT("%d.%m.%Y"), xT(""));
		PrivaBankApi::exchange_rate_t data;

		PrivaBankApi api;
		api.getExchangeRates(date, &data);

		auto dataByDate = data[date]["EUR"];
		Cout() << xTRACE_VAR(dataByDate);
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
