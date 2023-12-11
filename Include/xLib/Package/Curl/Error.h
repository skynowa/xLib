/**
 * \file  Error.h
 * \brief CURL error
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
#include <xLib/Interface/IError.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "Types.h"
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

class Error :
	public xl::interface_::IError<CURLcode>
    /// CURL error
{
public:
///\name ctors, dtor
///\{
             Error(cCURLcode code);
    virtual ~Error() = default;

	xNO_DEFAULT_CONSTRUCT(Error)
	xNO_COPY_ASSIGN(Error)
///\}

///\name Overrides
///\{
	CURLcode       code() const final;
	bool_t         isOk() const final;
	std::tstring_t category() const final;
	std::tstring_t message() const final;
///\}

private:
	cCURLcode _code {CURLE_OK};    ///< Error code
};

} // namespace
//-------------------------------------------------------------------------------------------------

/**
 * TODO:
 *
 * - Tests
 */
