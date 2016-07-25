/**
 * \file   Test_Donate.cpp
 * \brief  test Donate
 */


#include "Test_Donate.h"


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Donate)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Donate::unit()
{
	xTEST_CASE("data")
	{
		DonateData data;
		data.payPal      = xT("[PAY_PAL]");
		data.webMoney    = xT("[WEB_MONEY]");
		data.yandexMoney = xT("[YANDEX_MONEY]");
		data.private24   = xT("[PRIVATE_24]");

		Donate donate(data);

		xTEST_EQ(donate.data().payPal.empty(), false);
		xTEST_EQ(donate.data().webMoney.empty(), false);
		xTEST_EQ(donate.data().yandexMoney.empty(), false);
		xTEST_EQ(donate.data().private24.empty(), false);
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
