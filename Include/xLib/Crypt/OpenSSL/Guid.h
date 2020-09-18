/**
 * \file   Guid.h
 * \brief  GUID (globally unique identifier), Version 4 UUID
 */


#pragma once

#include <xLib/Core/Core.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, crypt)

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

xNAMESPACE_END2(xl, crypt)
//---------------------------------------------------------------------------
