/**
 * \file  Cpu.h
 * \brief CPU information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Cpu
    /// CPU information
{
public:
///\name ctors, dtor
///\{
			 Cpu() = default;
	virtual ~Cpu() = default;

	xNO_COPY_ASSIGN(Cpu)
///\}

    enum class Vendor
        /// Vendor
    {
        Unknown,
        Intel,
        Amd
    };
    xUSING_CONST(Vendor);

	ulong_t        num() const;
		///< get num of CPUs
	ulong_t        currentNum() const;
		///< get the number of the processor the current thread was running on during
		///< the call to this function
	Vendor         vendor() const;
		///< get CPU vendor
	std::tstring_t model() const;
		///< get CPU model name
	ulong_t        speed() const;
		///< get CPU speed (MHz)
	ulong_t        usage() const;
		///< get CPU usage (percentage)

xPLATFORM_IMPL:
    ulong_t        _num_impl() const;
    ulong_t        _currentNum_impl() const;
    std::tstring_t _vendor_impl() const;
    std::tstring_t _model_impl() const;
    ulong_t        _speed_impl() const;
    ulong_t        _usage_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
