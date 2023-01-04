/**
 * \file  PowerSupply.h
 * \brief system information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class PowerSupply
    /// system information
{
public:
///\name ctors, dtor
///\{
			 PowerSupply() = default;
	virtual ~PowerSupply() = default;

	xNO_COPY_ASSIGN(PowerSupply)
///\}

	enum class Status
		/// Status
	{
		Unknown     = 0,///< Unknown
		Discharging = 1,///< Discharging
		Charging    = 2,///< Charging
		Full        = 3 ///< Full
	};
    xUSING_CONST(Status);

	bool_t      isExists() const;
		///< Check for power supply
	std::size_t level() const;
		///< get level (pct) of power supply
	Status      status() const;
		///< get status of power supply

xPLATFORM_IMPL:
    bool_t      _isExists_impl() const;
    std::size_t _level_impl() const;
    Status      _status_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
