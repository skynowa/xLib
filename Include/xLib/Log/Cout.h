/**
 * \file  Cout.h
 * \brief Tracing to debugger, std::cout
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/System/Console.h>
#include "ILog.h"
//-------------------------------------------------------------------------------------------------
namespace xl::log
{

class Cout final :
    public ILog
    /// Tracing to debugger, std::cout
{
public:
///\name ctors, dtor
///\{
			 Cout() = default;
	virtual ~Cout();
///\}

///\name Overrides
///\{
	void_t write(cLevel level, std::ctstring_t &msg) const final;
///\}

private:
	cbool_t _isColorSupport {true};

	Console _console;

xPLATFORM_IMPL:
    void_t _write_impl(std::ctstring_t &msg) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
