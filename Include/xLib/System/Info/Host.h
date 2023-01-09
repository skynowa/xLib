/**
 * \file  Host.h
 * \brief Host information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Host
    /// Host information
{
public:
///\name ctors, dtor
///\{
			 Host() = default;
	virtual ~Host() = default;

	xNO_COPY_ASSIGN(Host)
///\}

	std::tstring_t name() const;
		///< get the NetBIOS name of the local computer

xPLATFORM_IMPL:
    std::tstring_t _name_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
