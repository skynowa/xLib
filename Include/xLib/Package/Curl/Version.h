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
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

class Version
    /// Client version
{
public:
                   Version() = default;
                  ~Version() = default;

    std::tstring_t version() const;
    std::tstring_t info(cCURLversion version) const;
    std::tstring_t infoCurrent() const;
    void_t         protocols(std::vec_tstring_t *values) const;

private:
    xNO_COPY_ASSIGN(Version)
};

} // namespace
//-------------------------------------------------------------------------------------------------
