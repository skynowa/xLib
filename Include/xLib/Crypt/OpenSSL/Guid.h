/**
 * \file   Guid.h
 * \brief  GUID (globally unique identifier), Version 4 UUID
 *
 * Refer Section 4.2 of RFC-4122
 * https://tools.ietf.org/html/rfc4122#section-4.2
 */


#pragma once

#include <xLib/Core/Core.h>
//---------------------------------------------------------------------------
namespace xl::crypt
{

class Guid
    /// GUID (globally unique identifier)
{
public:
///@name ctors, dtor
///@{
			 Guid() = default;
	virtual ~Guid() = default;

	xNO_COPY_ASSIGN(Guid)
///@}

	std::tstring_t str() const;
		///< generate GUID string
};

} // namespace
//---------------------------------------------------------------------------
