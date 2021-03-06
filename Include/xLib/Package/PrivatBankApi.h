/**
 * \file  PrivatBankApi.h
 * \brief PrivaBank API
 *
 * https://api.privatbank.ua/#p24/exchangeArchive
 * https://api.privatbank.ua/#p24/exchange
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Package/IRestClient.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

class PrivatBankApi
	/// PrivaBank API
{
public:
///@name ctors, dtor
///@{
			 PrivatBankApi();
	virtual ~PrivatBankApi();

	xNO_COPY_ASSIGN(PrivatBankApi)
///@}

	using exchange_rate_t  = std::map<std::tstring_t, std::map<std::tstring_t, std::map_tstring_t>>;
	using exchange_rates_t = std::vector<exchange_rate_t>;

	void_t getExchangeRatesArchive(std::ctstring_t &date, exchange_rate_t *data)
				const;
		///< API позволяет получить информацию о наличных курсах валют ПриватБанка и НБУ
		///< на выбранную дату. Архив хранит данные за последние 4 года
	void_t getExchangeRatesArchive(std::cvec_tstring_t &dates, exchange_rates_t *datas)
				const;

private:
	void_t _parseExchangeRatesArchive(std::ctstring_t &date, std::ctstring_t &response,
				exchange_rate_t *data) const;
		///< parse response
};

} // namespace
//-------------------------------------------------------------------------------------------------
