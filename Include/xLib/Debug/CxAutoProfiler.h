/****************************************************************************
* Class name:  CxAutoProfiler
* Description: auto code profiling
* File name:   CxAutoProfiler.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     05.07.2010 16:27:50
*
*****************************************************************************/


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
                   CxAutoProfiler(const tString &csFilePath, const CxProfiler::EMode cpmMode, LPCTSTR pcszComment, ...);
        virtual   ~CxAutoProfiler();

    private:
        CxProfiler _m_pfProfiler;
        tString    _m_sComment;
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxAutoProfilerH
