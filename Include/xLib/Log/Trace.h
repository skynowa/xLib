/**
 * \file   Trace.h
 * \brief  tracer
 */


#pragma once

#include <xLib/Core/Core.h>
#include "ILog.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class String;

xNAMESPACE_END2(xl, core)

xNAMESPACE_BEGIN2(xl, log)

class Trace :
    public ILog
    /// tracing
{
public:
                   Trace() {}
        ///< constructor
    virtual       ~Trace();
        ///< destructor

    template<typename T>
    Trace &        operator << (const T &valueT);
        ///< operator <<

    virtual void_t write(cptr_ctchar_t format, ...) const xOVERRIDE;
        ///< tracing to debugger, std::cout
    virtual void_t write(cLevel &level, cptr_ctchar_t format, ...) const xOVERRIDE;
        ///< tracing to debugger, std::cout

xPLATFORM_IMPL:
    void_t         _write_impl(std::ctstring_t &msg) const;
};

xNAMESPACE_END2(xl, log)
//-------------------------------------------------------------------------------------------------
#include "Trace.inl"
