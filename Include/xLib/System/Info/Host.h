/**
 * \file  Host.h
 * \brief system information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Host
    /// system information
{
public:
///\name ctors, dtor
///\{
			 Host() = default;
	virtual ~Host() = default;

	xNO_COPY_ASSIGN(Host)
///\}

	std::tstring_t hostName() const;
		///< get the NetBIOS name of the local computer

xPLATFORM_IMPL:
    std::tstring_t _hostName_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
