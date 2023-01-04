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

	ulonglong_t ramTotal() const;
		///< get total RAM (bytes)
	ulonglong_t ramAvailable() const;
		///< get available RAM (bytes)
	ulong_t     ramUsage() const;
		///< get RAM usage (percentage)

xPLATFORM_IMPL:
    ulonglong_t _ramTotal_impl() const;
    ulonglong_t _ramAvailable_impl() const;
    ulong_t     _ramUsage_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
