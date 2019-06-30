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
xNAMESPACE_BEGIN2(xl, package)

class IRestClient
    ///< REST API client
{
public:
             IRestClient();
        ///< constructor
    virtual ~IRestClient();
        ///< destructor

protected:
	std::size_t        _version {};
	std::map_tstring_t _credentials;
	fs::Config         _config;
	log::FileLog       _log;
	std::tstring_t     _dirTmp;
	curl::HttpClient   _http;
	/// TODO: DbClient
	/// TODO: IRequest / IResponse
	/// TODO: Json/Xml/Csv
	/// TODO: MailClient / SlackClient
	/// TODO: ErrorReport

private:
    xNO_COPY_ASSIGN(IRestClient)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
