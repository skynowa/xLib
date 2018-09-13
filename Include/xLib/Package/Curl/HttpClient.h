/**
 * \file   HttpClient.h
 * \brief  HTTP client
 *
 * https://www.tutorialspoint.com/http/http_methods.htm
 */


#pragma once

#include <xLib/Package/Curl/CurlBase.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class HttpClient :
	private CurlBase
    ///< HTTP client
{
public:
             HttpClient();
        ///< constructor
    virtual ~HttpClient();
        ///< destructor

	enum class RequestType
	{
		Unknown = 0,
			///< unknown
		Get     = 1,
			///< Retrieve information from the given server using a given URI.
			///< Requests using GET should only retrieve data and should have no other effect
			///< on the data.
		Head    = 2,
			///< Same as GET, but transfers the status line and header section only
		Post    = 3,
			///< Send data to the server, for example, customer information, file upload, etc.
			///< using HTML forms.
		Put     = 4,
			///< Replaces all current representations of the target resource with uploaded content
		Delete  = 5,
			///< Removes all current representations of the target resource given by a URI
		Connect = 6,
			///< Establishes a tunnel to the server identified by a given URI
		Options = 7,
			///< Describes the communication options for the target resource.
		Trace   = 8
			///< Performs a message loop-back test along the path to the target resource.
	};
	xTYPEDEF_CONST(RequestType);

    bool_t request(cRequestType type, std::ctstring_t &url, std::ctstring_t &request,
				std::tstring_t *responseHeader, std::tstring_t *responseBody);

private:

    xNO_COPY_ASSIGN(HttpClient)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
