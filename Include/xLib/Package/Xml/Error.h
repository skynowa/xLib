/**
 * \file  Error.h
 * \brief LibXml2 wrapper
 */

#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/IError.h>

#include "Common.h"
//-------------------------------------------------------------------------------------------------
namespace xl::package::xml
{

class Error final :
	public xl::interface_::IError<int_t>
{
public:
///\name ctors, dtor
///\{
    explicit Error(const xmlErrorPtr error);
	virtual ~Error() = default;

	xNO_DEFAULT_CONSTRUCT(Error);
	xNO_COPY_ASSIGN(Error);
///\}

///\name Overrides
///\{
	int_t          code() const final;
	bool_t         isOk() const final;
	std::tstring_t category() const final;
	std::tstring_t message() const final;
///\}

private:
	const xmlErrorPtr _error {}; ///< XML error
};

} // namespace
//-------------------------------------------------------------------------------------------------
