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
class CxAutoProfiler :
    public CxNonCopyable
    /// auto code profiling
{
    public:
                     CxAutoProfiler(const std::tstring &csFilePath, const CxProfiler::EMode cpmMode, const TCHAR *pcszComment, ...);
            ///< constructor
        virtual     ~CxAutoProfiler();
            ///< destructor

    private:
        CxProfiler   _m_pfProfiler; ///< profiler
        std::tstring _m_sComment;   ///< comment
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxAutoProfilerH
