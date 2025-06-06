/**
 * \file  Trace.h
 * \brief Tracing to debugger, std::cout
 */


#pragma once

#include <xLib/Core/Core.h>
#include "ILog.h"
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

class String;

} // namespace

namespace xl::log
{

class Trace final :
    public ILog
    /// Tracing to debugger, std::cout
{
public:
///\name ctors, dtor
///\{
			 Trace() = default;
	virtual ~Trace();
///\}

protected:
///\name Overrides
///\{
	void_t write(cLevel level, std::ctstring_t &msg) const final;
///\}

xPLATFORM_IMPL:
    void_t _write_impl(std::ctstring_t &msg) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
