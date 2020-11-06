/**
 * \file   Trace.h
 * \brief  tracer
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

class Trace :
    public ILog
    /// tracing
{
public:
///@name ctors, dtor
///@{
			 Trace() = default;
	virtual ~Trace();
///@}

///@name operators
///@{
	template<typename T>
	Trace &  operator << (const T &valueT);
///@}

    virtual void_t write(cptr_ctchar_t format, ...) const override;
        ///< tracing to debugger, std::cout
    virtual void_t write(cLevel level, cptr_ctchar_t format, ...) const override;
        ///< tracing to debugger, std::cout

xPLATFORM_IMPL:
    void_t         _write_impl(std::ctstring_t &msg) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Trace.inl"
