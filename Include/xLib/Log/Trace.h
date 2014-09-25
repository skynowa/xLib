/**
 * \file   Trace.h
 * \brief  tracer
 */


#pragma once

#include <xLib/Core/Core.h>
#include "ILog.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)
    class String;
xNAMESPACE_END2(xlib, core)

xNAMESPACE_BEGIN2(xlib, log)

class Trace :
    public ILog
    /// tracing
{
public:
                   Trace() {}
        ///< constructor
    virtual       ~Trace();
        ///< destructor

    template<class T>
    Trace &        operator << (const T &valueT);
        ///< operator <<

    virtual void_t write(ctchar_t *format, ...) const xOVERRIDE;
        ///< tracing to debugger, std::cout
    virtual void_t write(cExLevel &level, ctchar_t *format, ...) const xOVERRIDE;
        ///< tracing to debugger, std::cout

xPLATFORM:
    void_t         _write_impl(std::ctstring_t &msg) const;
};

xNAMESPACE_END2(xlib, log)
//-------------------------------------------------------------------------------------------------
#include "Trace.inl"

#if xOPTION_HEADER_ONLY
    #include "Trace.cpp"
#endif
