/**
 * \file  Test_PrivatBankApi.cpp
 * \brief test PrivatBankApi
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_PrivatBankApi)
xTEST_UNIT(Test_PrivatBankApi)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_PrivatBankApi::unit()
{
	xTEST_CASE("getExchangeRatesArchive")
	{
		if (false) {
			std::ctstring_t               date = DateTime().current().format(xT("%d.%m.%Y"), xT(""));
			PrivatBankApi::exchange_rate_t data;

			PrivatBankApi api;
			api.getExchangeRatesArchive(date, &data);

			auto eurSale = data[date]["EUR"]["PbRateSale"];
			Cout() << xTRACE_VAR(eurSale) << std::endl;

			auto eurPurchase = data[date]["EUR"]["PbRatePurchase"];
			Cout() << xTRACE_VAR(eurPurchase) << std::endl;
		}
	}

	xTEST_CASE("getExchangeRatesArchive")
	{
		DateTime dateNow = DateTime().current();

		std::vec_tstring_t dates;
		dates.push_back( dateNow.format(xT("%d.%m.%Y"), xT("")) );

		for (size_t i = 1; i <= 7; ++ i) {
			DateTime date = dateNow - DateTime(1000 * 60 * 60 * 24 * i);

			dates.push_back( date.format(xT("%d.%m.%Y"), xT("")) );
		}

		PrivatBankApi::exchange_rates_t datas;

		PrivatBankApi api;
		api.getExchangeRatesArchive(dates, &datas);

		for (size_t i = 0; i < dates.size(); ++ i) {
			std::ctstring_t &it_date = dates[i];
			auto            &it_data = datas[i];

			const auto eurSale     = it_data[it_date]["EUR"]["PbRateSale"];
			const auto eurPurchase = it_data[it_date]["EUR"]["PbRatePurchase"];

			Cout() << xTRACE_VAR_3(it_date, eurSale, eurPurchase) << std::endl;
		} // for
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
