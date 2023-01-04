/**
 * \file  Cpu.h
 * \brief system information
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system::info
{

class Cpu
    /// system information
{
public:
///\name ctors, dtor
///\{
			 Cpu() = default;
	virtual ~Cpu() = default;

	xNO_COPY_ASSIGN(Cpu)
///\}

    enum class CpuVendor
        /// CPU type
    {
        Unknown,
        Intel,
        Amd
    };
    xUSING_CONST(CpuVendor);

	ulong_t        cpusNum() const;
		///< get num of CPUs
	ulong_t        currentCpuNum() const;
		///< get the number of the processor the current thread was running on during
		///< the call to this function
	CpuVendor      cpuVendor() const;
		///< get CPU vendor
	std::tstring_t cpuModel() const;
		///< get CPU model name
	ulong_t        cpuSpeed() const;
		///< get CPU speed (MHz)
	ulong_t        cpuUsage() const;
		///< get CPU usage (percentage)

xPLATFORM_IMPL:
    ulong_t        _cpusNum_impl() const;
    ulong_t        _currentCpuNum_impl() const;
    std::tstring_t _cpuVendor_impl() const;
    std::tstring_t _cpuModel_impl() const;
    ulong_t        _cpuSpeed_impl() const;
    ulong_t        _cpuUsage_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
