/**
 * \file  Trace.h
 * \brief Tracing to debugger, std::cout
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
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

///\name operators
///\{
	template<typename T>
	Trace &  operator << (const T &valueT);
///\}

///\name Overrides
///\{
	void_t write(cLevel level, cptr_ctchar_t format, ...) const final;
///\}

private:
    OStream _oss;

xPLATFORM_IMPL:
    void_t _write_impl(std::ctstring_t &msg) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Trace.inl"
