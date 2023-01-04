/**
 * \file  Ram.h
 * \brief system information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Ram
    /// system information
{
public:
///\name ctors, dtor
///\{
			 Ram() = default;
	virtual ~Ram() = default;

	xNO_COPY_ASSIGN(Ram)
///\}

	ulonglong_t total() const;
		///< get total RAM (bytes)
	ulonglong_t available() const;
		///< get available RAM (bytes)
	ulong_t     usage() const;
		///< get RAM usage (percentage)

xPLATFORM_IMPL:
    ulonglong_t _total_impl() const;
    ulonglong_t _available_impl() const;
    ulong_t     _usage_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
