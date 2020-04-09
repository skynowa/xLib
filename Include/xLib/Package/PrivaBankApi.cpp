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

	curl::DataIn dataIn;
	{
	   /**
		* HTTP GET request:
		*
		* https://api.privatbank.ua/p24api/exchange_rates?date=01.12.2014
		*/

		dataIn.url            = xT("https://api.privatbank.ua/p24api/exchange_rates");
		dataIn.accept         = "application/xml";
		dataIn.acceptEncoding = "gzip, deflate";
		dataIn.acceptLanguage = "en-us,en";
		dataIn.acceptCharset  = "UTF-8";

		// dataIn.request
		{
			cbool_t is_xml {true};

			const std::map_tstring_t request
			{
				{"date",               a_date},
				{is_xml ? "" : "json", ""}
			};

			for (auto &[param, value] : request) {
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
		std::tcout
			<< xTRACE_VAR(dataIn)  << "\n"
			<< xTRACE_VAR(dataOut) << std::endl;
		return;
	}

	xTEST(!dataOut.headers.empty());
	xTEST(!dataOut.body.empty());

#if 0
	std::tcout
		<< xTRACE_VAR(dataIn)  << "\n"
		<< xTRACE_VAR(dataOut) << std::endl;
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
