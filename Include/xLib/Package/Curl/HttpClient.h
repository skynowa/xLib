/**
 * \file   HttpClient.h
 * \brief  HTTP client
 *
 * https://www.tutorialspoint.com/http/http_methods.htm
 */


#pragma once

#include <xLib/Package/Curl/Base.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xl, package, curl)

class HttpClient :
	public CurlBase
    ///< HTTP client
{
public:
             HttpClient() = default;
        ///< constructor
    virtual ~HttpClient() = default;
        ///< destructor

	enum class HttpCode
	{
		Unknown              = 0,

		// 1xx: Informational
		Continue             = 100,
		SwitchingProtocols   = 101,
		Processing           = 102,

		// 2xx: Success
		OK                   = 200,
		Created              = 201,
		Accepted             = 202,
		NoContent            = 204,

		// 3xx: Redirection
		MovedPermanently     = 301,
		Found                = 302,
		SeeOther             = 303,
		NotModified          = 304,
		TemporaryRedirect    = 307,

		// 4xx: Client Error
		BadRequest           = 400,
		Unauthorized         = 401,
		Forbidden            = 403,
		NotFound             = 404,
		MethodNotAllowed     = 405,
		NotAcceptable        = 406,
		PreconditionFailed   = 412,
		UnsupportedMediaType = 415,

		// 5xx: Server Error
		InternalServerError  = 500,
		NotImplemented       = 501
	};

	enum class RequestType
	{
		Unknown = 0,
		Get     = 1,
		Head    = 2,
		Post    = 3,
		Put     = 4,
		Delete  = 5,
		Connect = 6,
		Options = 7,
		Trace   = 8
	};
	xUSING_CONST(RequestType);

    bool_t request(cRequestType type, DataIn &dataIn, DataOut *dataOut);

private:
    xNO_COPY_ASSIGN(HttpClient)
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
