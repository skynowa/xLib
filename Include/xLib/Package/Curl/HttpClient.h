/**
 * \file   HttpClient.h
 * \brief  HTTP client
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

private:
    xNO_COPY_ASSIGN(HttpClient)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
