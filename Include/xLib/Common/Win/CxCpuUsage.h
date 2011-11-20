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

xNAMESPACE_BEGIN(NxLib)

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

        bool          EnablePerformaceCounters(bool bEnable = true);

    private:
        bool          m_bFirstTime;
        LONGLONG      m_lnOldValue;
        LARGE_INTEGER m_OldPerfTime100nSec;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxCpuUsageH

