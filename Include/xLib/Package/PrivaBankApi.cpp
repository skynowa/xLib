/**
 * \file  PrivaBankApi.cpp
 * \brief PrivaBank API
 */


#include "PrivaBankApi.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Package/Curl/HttpClient.h>
#include <xLib/Package/Xml.h>


xNAMESPACE_BEGIN2(xl, package)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
PrivaBankApi::PrivaBankApi()
{
}
//-------------------------------------------------------------------------------------------------
PrivaBankApi::~PrivaBankApi()
{
}
//-------------------------------------------------------------------------------------------------
void
PrivaBankApi::getExchangeRates(
	std::ctstring_t  &a_date,
	exchange_rate_t  *out_data
) const
{
    xTEST(!a_date.empty());
    xTEST(out_data->empty());

	out_data->clear();

    bool_t bRv {};

	curl::HttpClient http;

	curl::DataIn baseDataIn;
	{
	   /**
		* HTTP GET request:
		*
		* https://api.privatbank.ua/p24api/exchange_rates?date=01.12.2014
		*/

		baseDataIn.url            = xT("https://api.privatbank.ua/p24api/exchange_rates");
		baseDataIn.accept         = "application/xml";
		// baseDataIn.acceptEncoding = "gzip, deflate";
		baseDataIn.acceptLanguage = "en-us,en";
		baseDataIn.acceptCharset  = "UTF-8";

		// baseDataIn.request
		{
			cbool_t is_xml {true};

			const std::map_tstring_t request
			{
				{"date",               a_date},
				{is_xml ? "" : "json", ""}
			};

			for (auto &it_request_data : request) {
				baseDataIn.request += it_request_data.first + "=" + http.escape(it_request_data.second);
				baseDataIn.request += "&";
			}

			baseDataIn.request = String::trimRightChars(baseDataIn.request, "&");
		}
	}

	curl::DataOut dataOut;
	bRv = http.request(curl::HttpClient::RequestType::Get, baseDataIn, &dataOut);
	xTEST(bRv);
	if ( !http.isSuccess(dataOut) ) {
		Cout()
			<< xTRACE_VAR(baseDataIn.request)   << std::endl
			<< xT("\n")
			<< xTRACE_VAR(dataOut.contentType)  << std::endl
			<< xTRACE_VAR(dataOut.effectiveUrl) << std::endl
			<< xTRACE_VAR(dataOut.responseCode) << std::endl
			<< xTRACE_VAR(dataOut.totalTimeSec) << std::endl
			<< xT("\n")
			<< xTRACE_VAR(dataOut.headers)      << std::endl
			<< xTRACE_VAR(dataOut.body.size())  << std::endl
			<< xTRACE_VAR(dataOut.body)         << std::endl;

		return;
	}

	xTEST(!dataOut.headers.empty());
	xTEST(!dataOut.body.empty());

#if 0
	Cout()
		<< xTRACE_VAR(baseDataIn.request)   << std::endl
		<< xT("\n")
		<< xTRACE_VAR(dataOut.contentType)  << std::endl
		<< xTRACE_VAR(dataOut.effectiveUrl) << std::endl
		<< xTRACE_VAR(dataOut.responseCode) << std::endl
		<< xTRACE_VAR(dataOut.totalTimeSec) << std::endl
		<< xT("\n")
		<< xTRACE_VAR(dataOut.headers)      << std::endl
		<< xTRACE_VAR(dataOut.body.size())  << std::endl
		<< xTRACE_VAR(dataOut.body)         << std::endl;
#endif

     _parseExchangeRates(a_date, dataOut.body, out_data);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
PrivaBankApi::_parseExchangeRates(
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

xNAMESPACE_END2(xl, package)
