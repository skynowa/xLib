/**
 * \file  CxAutoProfiler.h
 * \brief auto code profiling
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxProfiler.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAutoProfiler :
    private CxNonCopyable
    /// auto code profiling
{
public:
                   CxAutoProfiler(std::ctstring_t &csFilePath, ctchar_t *pcszComment, ...);
        ///< constructor
    virtual       ~CxAutoProfiler();
        ///< destructor

private:
    CxProfiler     _m_pfProfiler; ///< profiler
    std::tstring_t _m_sComment;   ///< comment
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
