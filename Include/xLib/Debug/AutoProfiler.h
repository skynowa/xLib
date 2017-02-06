/**
 * \file  AutoProfiler.h
 * \brief auto code profiling
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Debug/Profiler.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, debug)

class AutoProfiler
    /// auto profiling code
{
public:
                   AutoProfiler(std::ctstring_t &filePath, cptr_ctchar_t comment, ...);
        ///< constructor
    virtual       ~AutoProfiler();
        ///< destructor

private:
    Profiler       _profiler;   ///< profiler
    std::tstring_t _comment;    ///< comment

    xNO_COPY_ASSIGN(AutoProfiler)
};

xNAMESPACE_END2(xl, debug)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "AutoProfiler.cpp"
#endif
