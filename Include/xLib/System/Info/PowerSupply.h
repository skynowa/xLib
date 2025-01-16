/**
 * \file  PowerSupply.h
 * \brief Power supply information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class PowerSupply
    /// Power supply information
{
public:
///\name ctors, dtor
///\{
			 PowerSupply() = default;
	virtual ~PowerSupply() = default;

	xNO_COPY_ASSIGN(PowerSupply);
///\}

	enum class Status
		/// Status
	{
		Unknown     = 0, ///< Unknown
		Discharging = 1, ///< Discharging
		Charging    = 2, ///< Charging
		Full        = 3  ///< Full
	};
    xUSING_CONST(Status);

	bool_t      isExists() const;
		///< Check existance
	std::size_t level() const;
		///< get level (pct)
	Status      status() const;
		///< get status

xPLATFORM_IMPL:
    bool_t      _isExists_impl() const;
    std::size_t _level_impl() const;
    Status      _status_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
