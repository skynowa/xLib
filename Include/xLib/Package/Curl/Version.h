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
#include "Types.h"
#include "Buffer.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN3(xl, package, curl)

class Version
    ///< client
{
public:
                   Version() = default;
        ///< constructor
                  ~Version() = default;
        ///< destructor

    std::tstring_t version() const;
    std::tstring_t info(cCURLversion version) const;
    std::tstring_t infoCurrent() const;
    void_t         protocols(std::vec_tstring_t *values) const;

private:
    xNO_COPY_ASSIGN(Version)
};

xNAMESPACE_END3(xl, package, curl)
//-------------------------------------------------------------------------------------------------
