/**
 * \file  CxAutoProfiler.h
 * \brief auto code profiling
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Debug/CxProfiler.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAutoProfiler :
    private CxNonCopyable
    /// auto code profiling
{
public:
                   CxAutoProfiler(std::ctstring_t &filePath, ctchar_t *comment, ...);
        ///< constructor
    virtual       ~CxAutoProfiler();
        ///< destructor

private:
    CxProfiler     _profiler; ///< profiler
    std::tstring_t _comment;   ///< comment
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif
