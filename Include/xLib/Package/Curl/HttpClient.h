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

    bool_t request(cRequestType type, BaseDataIn &baseDataIn, BaseDataOut *baseDataOut);

private:
    xNO_COPY_ASSIGN(HttpClient)
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
