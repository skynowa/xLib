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
#include "Common.h"
#include "Types.h"
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

class Version
    /// Client version
{
public:
///\name ctors, dtor
///\{
	Version() = default;
	~Version() = default;

	xNO_COPY_ASSIGN(Version)
///\}

	CURLversion    version() const;
    std::tstring_t info() const;
    void_t         protocols(std::vec_tstring_t *values) const;

private:
    cCURLversion _version {CURLVERSION_NOW};
};

} // namespace
//-------------------------------------------------------------------------------------------------
