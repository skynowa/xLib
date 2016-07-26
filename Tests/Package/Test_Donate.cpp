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

		xTEST_EQ(donate.get().payPal, data.payPal);
		xTEST_EQ(donate.get().webMoney, data.webMoney);
		xTEST_EQ(donate.get().yandexMoney, data.yandexMoney);
		xTEST_EQ(donate.get().private24, data.private24);
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
