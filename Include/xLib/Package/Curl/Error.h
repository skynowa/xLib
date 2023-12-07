/**
 * \file  Error.h
 * \brief CURL error
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
#include <xLib/Interface/ILastError.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "Types.h"
//-------------------------------------------------------------------------------------------------
namespace xl::package::curl
{

class Error :
	public xl::interface_::ILastError<CURLcode>
    /// CURL connection
{
public:
///\name ctors, dtor
///\{
	/* explicit */ Error(cCURLcode code);
	virtual ~Error() = default;

	xNO_DEFAULT_CONSTRUCT(Error)
	xNO_COPY_ASSIGN(Error)
///\}

///\name Overrides
///\{
	CURLcode       code() const final;
		///< error code for the most recently invoked API function that can succeed or fail
	bool_t         isOk() const final;
		///<
	std::tstring_t category() const final;
		///<
	std::tstring_t message() const final;
		///< error message for the most recently invoked API function that failed
///\}

private:
	CURLcode _code {CURLE_OK};    ///< Error code
};

} // namespace
//-------------------------------------------------------------------------------------------------

/**
 * TODO:
 *
 * - Tests
 */
