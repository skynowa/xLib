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

	enum class PowerSupplyStatus
		/// Power supply status
	{
		Unknown     = 0,///< Unknown
		Discharging = 1,///< Discharging
		Charging    = 2,///< Charging
		Full        = 3 ///< Full
	};
    xUSING_CONST(PowerSupplyStatus);

	bool_t            isPowerSupply() const;
		///< Check for power supply
	std::size_t       powerSupplyLevel() const;
		///< get level (pct) of power supply
	PowerSupplyStatus powerSupplyStatus() const;
		///< get status of power supply

xPLATFORM_IMPL:
    bool_t         _isPowerSupply_impl() const;
    std::size_t    _powerSupplyLevel_impl() const;
    PowerSupplyStatus _powerSupplyStatus_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
