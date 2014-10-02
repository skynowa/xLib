/**
 * \file  AutoProfiler.h
 * \brief auto code profiling
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Debug/Profiler.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, debug)

class AutoProfiler
    /// auto code profiling
{
public:
                   AutoProfiler(std::ctstring_t &filePath, ctchar_t *comment, ...);
        ///< constructor
    virtual       ~AutoProfiler();
        ///< destructor

private:
    Profiler     _profiler;   ///< profiler
    std::tstring_t _comment;    ///< comment

    xNO_COPY_ASSIGN(AutoProfiler)
};

xNAMESPACE_END2(xlib, debug)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "AutoProfiler.cpp"
#endif
