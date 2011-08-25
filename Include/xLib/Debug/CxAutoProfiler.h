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
{
    public:
                   CxAutoProfiler(const std::tstring &csFilePath, const CxProfiler::EMode cpmMode, LPCTSTR pcszComment, ...);
        virtual   ~CxAutoProfiler();

    private:
        CxProfiler _m_pfProfiler;
        std::tstring    _m_sComment;
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxAutoProfilerH
