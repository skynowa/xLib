/**
 * \file  Net.h
 * \brief Network information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Net
    /// Network information
{
public:
///\name ctors, dtor
///\{
			 Net() = default;
	virtual ~Net() = default;

	xNO_COPY_ASSIGN(Net)
///\}

	bool_t isVpnActive() const;
		///< detect VPN

xPLATFORM_IMPL:
    bool_t _isVpnActive_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
