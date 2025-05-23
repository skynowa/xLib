/**
 * \file  IRestClient.h
 * \brief REST API client
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Fs/Config.h>
#include <xLib/Log/FileLog.h>
#include <xLib/Package/Curl/HttpClient.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

class IRestClient
    /// REST API client
{
public:
///\name ctors, dtor
///\{
			 IRestClient() = default;
	virtual ~IRestClient() = default;

	xNO_COPY_ASSIGN(IRestClient);
///\}

protected:
	std::size_t        _version {};
	std::map_tstring_t _credentials;
	fs::Config         _config;
	/// log::FileLog       _log;
	std::tstring_t     _dirTmp;
	curl::HttpClient   _http {false};
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * \file IRestClient.h
 * \todo
 *
 * - DbClient
 * - IRequest / IResponse
 * - Json/Xml/Csv
 * - MailClient / SlackClient
 * - ErrorReport
 */
