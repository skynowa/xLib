/**
 * \file  Storage.h
 * \brief system information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Storage
    /// system information
{
public:
///\name ctors, dtor
///\{
			 Storage() = default;
	virtual ~Storage() = default;

	xNO_COPY_ASSIGN(Storage)
///\}

	ulong_t pageSize() const;
		///< get Size of a page (bytes)

xPLATFORM_IMPL:
    ulong_t _pageSize_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
