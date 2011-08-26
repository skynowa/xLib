/**
 * \file  CxCpuUsage.h
 * \brief cpu usage
 */


#ifndef xLib_Common_Win_CxCpuUsageH
#define xLib_Common_Win_CxCpuUsageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxCpuUsage :
    public CxNonCopyable
    /// cpu usage
{
    public:
                      CxCpuUsage ();
        virtual      ~CxCpuUsage ();

        INT           GetCpuUsage();
        INT           GetCpuUsage(LPCTSTR pProcessName);
        INT           GetCpuUsage(DWORD dwProcessID);

        BOOL          EnablePerformaceCounters(BOOL bEnable = TRUE);

    private:
        bool          m_bFirstTime;
        LONGLONG      m_lnOldValue;
        LARGE_INTEGER m_OldPerfTime100nSec;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxCpuUsageH

