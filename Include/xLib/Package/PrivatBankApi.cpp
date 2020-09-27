/**
 * \file  PrivatBankApi.cpp
 * \brief PrivaBank API
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Package/Curl/HttpClient.h>
#include <xLib/Package/PrivatBankApi.h>
#include <xLib/Package/Xml.h>


namespace xl::package
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
PrivatBankApi::PrivatBankApi()
{
}
//-------------------------------------------------------------------------------------------------
PrivatBankApi::~PrivatBankApi()
{
}
//-------------------------------------------------------------------------------------------------
void_t
PrivatBankApi::getExchangeRatesArchive(
	std::ctstring_t  &a_date,
	exchange_rate_t  *out_data
) const
{
	xTEST(!a_date.empty());
	xTEST(out_data->empty());

	out_data->clear();

	bool_t bRv {};

	curl::HttpClient http;

	curl::DataIn dataIn;
	{
	   /**
		* HTTP GET request:
		*
		* https://api.privatbank.ua/p24api/exchange_rates?date=01.12.2014
		*/

		dataIn.url            = xT("https://api.privatbank.ua/p24api/exchange_rates");
		dataIn.accept         = xT("application/xml");
		dataIn.acceptEncoding = xT("gzip, deflate");
		dataIn.acceptLanguage = xT("en-us,en");
		dataIn.acceptCharset  = xT("UTF-8");

		// dataIn.request
		{
			cbool_t is_xml {true};

			const std::map_tstring_t request
			{
				{"date",               a_date},
				{is_xml ? "" : "json", ""}
			};

			for (const auto &[param, value] : request) {
				if ( param.empty() ) {
					continue;
				}

				dataIn.request += param + "=" + http.escape(value);
				dataIn.request += "&";
			}

			dataIn.request = String::trimRightChars(dataIn.request, "&");
		}
	}

	curl::DataOut dataOut;
	bRv = http.request(curl::HttpClient::Request::Get, dataIn, &dataOut);
	xTEST(bRv);
	if ( !http.isSuccess(dataOut) ) {
		core::OStream()
			<< xTRACE_VAR(dataIn)  << "\n"
			<< xTRACE_VAR(dataOut) << "\n";
		return;
	}

	xTEST(!dataOut.headers.empty());
	xTEST(!dataOut.body.empty());

#if 1
	// TODO: core::Cout()
	core::OStream()
		<< xTRACE_VAR(dataIn)  << "\n"
		<< xTRACE_VAR(dataOut) << "\n";
#endif

	 _parseExchangeRatesArchive(a_date, dataOut.body, out_data);
}
//-------------------------------------------------------------------------------------------------
void_t
PrivatBankApi::getExchangeRatesArchive(
	std::cvec_tstring_t &a_dates,
	exchange_rates_t    *out_datas
) const
{
	out_datas->clear();
	out_datas->reserve(a_dates.size());

	for (const auto &it_date : a_dates) {
		exchange_rate_t out_data;
		getExchangeRatesArchive(it_date, &out_data);

		out_datas->emplace_back(out_data);
	} // for (a_dates)
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
PrivatBankApi::_parseExchangeRatesArchive(
	std::ctstring_t &a_date,		///<
	std::ctstring_t &a_response,	///<
	exchange_rate_t *out_data		///< [out]
) const
{
	XmlDoc doc("UTF-8");
	doc.parse(a_response, true /* isNss */);

	XmlNode root;
	doc.getRootNode(root);

	XmlNode exchangeRate;
	root.node("/exchangerates", exchangeRate);

	std::ctstring_t &date         = exchangeRate.attribute("date"); 			// 01.12.2014
	std::ctstring_t &bank         = exchangeRate.attribute("bank"); 			// PB (PrivatBank)
	std::ctstring_t &currencyFrom = exchangeRate.attribute("BaseCurrencyLit");	// UAH

	// tests
	{
		xTEST(!date.empty());
		xTEST_EQ(bank, std::tstring_t("PB"));
		xTEST(!currencyFrom.empty());
	}

	std::vector<XmlNode> exchangeRates;
	exchangeRate.nodes("exchangerate", exchangeRates);

	for (const auto &it_exchangeRate : exchangeRates) {
		const std::tstring_t &currencyBase = it_exchangeRate.attribute("baseCurrency");	// UAH
		const std::tstring_t &currency     = it_exchangeRate.attribute("currency");		// AUD

		// out
		(*out_data)[a_date][currency]["NbRateSale"]     = it_exchangeRate.attribute("saleRateNB");		// 12.8319250
		(*out_data)[a_date][currency]["NbRatePurchase"] = it_exchangeRate.attribute("purchaseRateNB");	// 12.8319250
		(*out_data)[a_date][currency]["PbRateSale"]     = it_exchangeRate.attribute("saleRate");		// 20.0000000
		(*out_data)[a_date][currency]["PbRatePurchase"] = it_exchangeRate.attribute("purchaseRate");	// 19.2000000
	} // for (exchangeRates)
}
//-------------------------------------------------------------------------------------------------

} // namespace
