/**
 * \file   Version.h
 * \brief  CURL client
 *
 * https://curl.haxx.se/libcurl/c/allfuncs.html
 * https://curl.haxx.se/libcurl/c/example.html
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "CurlTypes.h"
#include "CurlBuffer.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xl, package, curl)

class Version
    ///< client
{
public:
    explicit       Version();
        ///< constructor
    virtual       ~Version();
        ///< destructor

    std::tstring_t version();
    std::tstring_t versionInfo(cCURLversion version);
    std::tstring_t versionInfoCurrent();

private:
    xNO_COPY_ASSIGN(Version)
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
