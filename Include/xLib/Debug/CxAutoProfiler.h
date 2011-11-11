/**
 * \file  CxAutoProfiler.h
 * \brief auto code profiling
 */


#ifndef xLib_Debug_CxAutoProfilerH
#define xLib_Debug_CxAutoProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxProfiler.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAutoProfiler :
    public CxNonCopyable
    /// auto code profiling
{
    public:
                     CxAutoProfiler(const std::string_t &csFilePath, const CxProfiler::EMode cpmMode, const char_t *pcszComment, ...);
            ///< constructor
        virtual     ~CxAutoProfiler();
            ///< destructor

    private:
        CxProfiler   _m_pfProfiler; ///< profiler
        std::string_t _m_sComment;   ///< comment
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxAutoProfilerH
