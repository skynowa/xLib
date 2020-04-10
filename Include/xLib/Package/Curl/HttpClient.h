/**
 * \file   HttpClient.h
 * \brief  HTTP client
 *
 * https://www.tutorialspoint.com/http/http_methods.htm
 */


#pragma once

#include <xLib/Package/Curl/BaseClient.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xl, package, curl)

class HttpClient :
	public BaseClient
    ///< HTTP client
{
public:
             HttpClient() = default;
        ///< constructor
    virtual ~HttpClient() = default;
        ///< destructor

	enum class Request
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
	xUSING_CONST(Request);

    bool_t request(cRequest type, DataIn &dataIn, DataOut *dataOut);
		///<

   /**
	* HTTP response code
	*
	* 1xx - Transient code, a new one follows
	* 2xx - Things are OK
	* 3xx - The content is somewhere else
	* 4xx - Failed because of a client problem
	* 5xx - Failed because of a server problem
	*/
    bool_t isSuccess(cDataOut &dataOut) const;
		///<

private:
    xNO_COPY_ASSIGN(HttpClient)
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
