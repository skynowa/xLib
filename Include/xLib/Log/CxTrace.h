/**
 * \file   CxTrace.h
 * \brief  tracer
 */


#pragma once

#ifndef xLib_CxTraceH
#define xLib_CxTraceH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include "IxLog.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxString;

class CxTrace :
    public IxLog
    /// tracing
{
public:
                   CxTrace() {}
        ///< constructor
    virtual       ~CxTrace();
        ///< destructor

    template<class T>
    CxTrace &      operator << (const T &valueT);
        ///< operator <<

    virtual void_t write(ctchar_t *format, ...) const xOVERRIDE;
        ///< tracing to debugger, std::cout
    virtual void_t write(const ExLevel &level, ctchar_t *format, ...) const xOVERRIDE;
        ///< tracing to debugger, std::cout
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxTrace.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxTraceH
