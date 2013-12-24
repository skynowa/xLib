/**
 * \file   CxTracer.h
 * \brief  tracer
 */


#pragma once

#ifndef xLib_CxTracerH
#define xLib_CxTracerH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include "IxLog.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxString;

class CxTracer :
    public IxLog
    /// tracing
{
public:
                   CxTracer() {}
        ///< constructor
    virtual       ~CxTracer();
        ///< destructor

    template<class T>
    CxTracer &     operator << (const T &valueT)
    {
        _oss << valueT;

        return *this;
    }
        ///< operator <<

    virtual void_t write(ctchar_t *format, ...) const xOVERRIDE;
        ///< tracing to debugger, std::cout
    virtual void_t write(const ExLevel &level, ctchar_t *format, ...) const xOVERRIDE;
        ///< tracing to debugger, std::cout

private:
    std::tostringstream_t _oss; ///< string stream

    void_t         _write(std::ctstring_t &msg) const;
        ///< tracing to debugger, std::cout
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxTracer.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxTracerH
