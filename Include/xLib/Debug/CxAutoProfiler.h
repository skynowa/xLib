/**
 * \file  CxAutoProfiler.h
 * \brief auto code profiling
 */


#pragma once

#ifndef xLib_CxAutoProfilerH
#define xLib_CxAutoProfilerH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Debug/CxProfiler.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, debug)

class CxAutoProfiler
    /// auto code profiling
{
public:
                   CxAutoProfiler(std::ctstring_t &filePath, ctchar_t *comment, ...);
        ///< constructor
    virtual       ~CxAutoProfiler();
        ///< destructor

private:
    CxProfiler     _profiler;   ///< profiler
    std::tstring_t _comment;    ///< comment

    xNO_COPY_ASSIGN(CxAutoProfiler)
};

xNAMESPACE2_END(xlib, debug)
//-------------------------------------------------------------------------------------------------
#include "CxAutoProfiler.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxAutoProfilerH
