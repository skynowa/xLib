/****************************************************************************
* Class name:  CxCpuUsage
* Description: cpu usage
* File name:   CxCpuUsage.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.02.2011 21:57:45
*
*****************************************************************************/


///////////////////////////////////////////////////////////////////
//
//        GetCpuUsage uses the performance counters to retrieve the
//        system cpu usage.
//        The cpu usage counter is of type PERF_100NSEC_TIMER_INV
//        which as the following calculation:
//
//        Element        Value
//        =======        ===========
//        X            CounterData
//        Y            100NsTime
//        Data Size    8 Bytes
//        Time base    100Ns
//        Calculation 100*(1-(X1-X0)/(Y1-Y0))
//
//      where the denominator (Y) represents the total elapsed time of the
//      sample interval and the numerator (X) represents the time during
//      the interval when the monitored components were inactive.
//
//
//        Note:
//        ====
//        On windows NT, cpu usage counter is '% Total processor time'
//        under 'System' object. However, in Win2K/XP Microsoft moved
//        that counter to '% processor time' under '_Total' instance
//        of 'Processor' object.
//        Read 'INFO: Percent Total Performance Counter Changes on Windows 2000'
//        Q259390 in MSDN.
//
///////////////////////////////////////////////////////////////////


#include <xLib/Common/Win/CxCpuUsage.h>


#if defined(xOS_WIN)
#include <xVCL/xCommon.h>
#include <ATLBASE.H>    // for CRegKey use

#pragma pack(push,8)
#include <xLib/Common/Win/CxPerfCounters.h>
#pragma pack(pop)

#define SYSTEM_OBJECT_INDEX                    2        // 'System' object
#define PROCESS_OBJECT_INDEX                230        // 'Process' object
#define PROCESSOR_OBJECT_INDEX                238        // 'Processor' object
#define TOTAL_PROCESSOR_TIME_COUNTER_INDEX    240        // '% Total processor time' counter (valid in WinNT under 'System' object)
#define PROCESSOR_TIME_COUNTER_INDEX        6        // '% processor time' counter (for Win2K/XP)


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: FUNCTION_NAME (COMMENTS)
enum EPlarform {
    WINNT,
    WIN2K_XP,
    WIN9X,
    UNKNOWN
};

EPlarform
GetPlatform() {
    OSVERSIONINFO osvi = {};
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (!GetVersionEx(&osvi))
        return UNKNOWN;

    switch (osvi.dwPlatformId) {
        case VER_PLATFORM_WIN32_WINDOWS:
            return WIN9X;

        case VER_PLATFORM_WIN32_NT:
            if (4 == osvi.dwMajorVersion) {
                return WINNT;
            } else {
                return WIN2K_XP;
            }
    }

    return UNKNOWN;
}
//---------------------------------------------------------------------------
//TODO: FUNCTION_NAME (COMMENTS)
CxCpuUsage::CxCpuUsage() {
    m_bFirstTime = true;
    m_lnOldValue = 0;
    memset(&m_OldPerfTime100nSec, 0, sizeof(m_OldPerfTime100nSec));
}
//---------------------------------------------------------------------------
//TODO: FUNCTION_NAME (COMMENTS)
/*virtual*/
CxCpuUsage::~CxCpuUsage() {

}
//---------------------------------------------------------------------------
//TODO: FUNCTION_NAME (COMMENTS)
BOOL
CxCpuUsage::EnablePerformaceCounters(BOOL bEnable) {
    if (GetPlatform() != WIN2K_XP)
        return TRUE;


    std::auto_ptr<TRegistry> regKey(new TRegistry(KEY_ALL_ACCESS));
    /*DEBUG*/xASSERT(NULL != regKey.get());

    regKey->RootKey = HKEY_LOCAL_MACHINE;

    if (regKey->OpenKey("SYSTEM\\CurrentControlSet\\Services\\PerfOS\\Performance", true) != ERROR_SUCCESS)
        return FALSE;

    regKey->WriteBool("Disable Performance Counters", !bEnable);
    regKey->CloseKey();

    regKey->RootKey = HKEY_LOCAL_MACHINE;
    if (regKey->OpenKey("SYSTEM\\CurrentControlSet\\Services\\PerfProc\\Performance", true) != ERROR_SUCCESS)
        return FALSE;

    regKey->WriteBool("Disable Performance Counters", !bEnable);
    regKey->CloseKey();

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - FUNCTION_NAME (COMMENTS)
//
//    GetCpuUsage returns the system-wide cpu usage.
//    Since we calculate the cpu usage by two samplings, the first
//    call to GetCpuUsage() returns 0 and keeps the values for the next
//    sampling.
//  Read the comment at the beginning of this file for the formula.
//
INT
CxCpuUsage::GetCpuUsage() {
    static EPlarform Platform = GetPlatform();

    if (m_bFirstTime)
        EnablePerformaceCounters();

    // Cpu usage counter is 8 byte length.
    CxPerfCounters<LONGLONG> PerfCounters;
    TCHAR/*char*/ szInstance[256] = {0};

//        Note:
//        ====
//        On windows NT, cpu usage counter is '% Total processor time'
//        under 'System' object. However, in Win2K/XP Microsoft moved
//        that counter to '% processor time' under '_Total' instance
//        of 'Processor' object.
//        Read 'INFO: Percent Total Performance Counter Changes on Windows 2000'
//        Q259390 in MSDN.

    DWORD dwObjectIndex;
    DWORD dwCpuUsageIndex;
    switch (Platform) {
        case WINNT:
            dwObjectIndex = SYSTEM_OBJECT_INDEX;
            dwCpuUsageIndex = TOTAL_PROCESSOR_TIME_COUNTER_INDEX;
            break;

        case WIN2K_XP:
            dwObjectIndex = PROCESSOR_OBJECT_INDEX;
            dwCpuUsageIndex = PROCESSOR_TIME_COUNTER_INDEX;
            wcscpy(szInstance, xT("_Total"));
            break;

        default:
            return - 1;
    }

    INT                CpuUsage = 0;
    LONGLONG        lnNewValue = 0;
    PPERF_DATA_BLOCK pPerfData = NULL;
    LARGE_INTEGER    NewPerfTime100nSec = {0};

    //T GetCounterValue(PERF_DATA_BLOCK **pPerfData, DWORD dwObjectIndex, DWORD dwCounterIndex, LPCTSTR pInstanceName = NULL)
    lnNewValue = PerfCounters.GetCounterValue(&pPerfData, dwObjectIndex, dwCpuUsageIndex, szInstance);
    NewPerfTime100nSec = pPerfData->PerfTime100nSec;

    if (m_bFirstTime) {
        m_bFirstTime = false;
        m_lnOldValue = lnNewValue;
        m_OldPerfTime100nSec = NewPerfTime100nSec;
        return 0;
    }

    LONGLONG lnValueDelta = lnNewValue - m_lnOldValue;
    double DeltaPerfTime100nSec = (double)NewPerfTime100nSec.QuadPart - (double)m_OldPerfTime100nSec.QuadPart;

    m_lnOldValue = lnNewValue;
    m_OldPerfTime100nSec = NewPerfTime100nSec;

    double a = (double)lnValueDelta / DeltaPerfTime100nSec;

    double f = (1.0 - a) * 100.0;
    CpuUsage = (INT)(f + 0.5);    // rounding the result
    if (CpuUsage < 0)
        return 0;
    return CpuUsage;
}
//---------------------------------------------------------------------------
//TODO: - FUNCTION_NAME (COMMENTS)
INT
CxCpuUsage::GetCpuUsage(LPCTSTR pProcessName) {
    static EPlarform Platform = GetPlatform();

    if (m_bFirstTime)
        EnablePerformaceCounters();

    // Cpu usage counter is 8 byte length.
    CxPerfCounters<LONGLONG> PerfCounters;
    TCHAR/*char*/ szInstance[256] = {0};


    DWORD dwObjectIndex = PROCESS_OBJECT_INDEX;
    DWORD dwCpuUsageIndex = PROCESSOR_TIME_COUNTER_INDEX;
    wcscpy(szInstance,pProcessName);

    INT                CpuUsage = 0;
    LONGLONG        lnNewValue = 0;
    PPERF_DATA_BLOCK pPerfData = NULL;
    LARGE_INTEGER    NewPerfTime100nSec = {0};

    lnNewValue = PerfCounters.GetCounterValue(&pPerfData, dwObjectIndex, dwCpuUsageIndex, szInstance);
    NewPerfTime100nSec = pPerfData->PerfTime100nSec;

    if (m_bFirstTime) {
        m_bFirstTime = false;
        m_lnOldValue = lnNewValue;
        m_OldPerfTime100nSec = NewPerfTime100nSec;
        return 0;
    }

    LONGLONG lnValueDelta = lnNewValue - m_lnOldValue;
    double DeltaPerfTime100nSec = (double)NewPerfTime100nSec.QuadPart - (double)m_OldPerfTime100nSec.QuadPart;

    m_lnOldValue = lnNewValue;
    m_OldPerfTime100nSec = NewPerfTime100nSec;

    double a = (double)lnValueDelta / DeltaPerfTime100nSec;

    CpuUsage = (INT) (a*100);
    if (CpuUsage < 0)
        return 0;
    return CpuUsage;
}
//---------------------------------------------------------------------------
//TODO: - FUNCTION_NAME (COMMENTS)
INT
CxCpuUsage::GetCpuUsage(DWORD dwProcessID) {
    static EPlarform Platform = GetPlatform();

    if (m_bFirstTime)
        EnablePerformaceCounters();

    // Cpu usage counter is 8 byte length.
    CxPerfCounters<LONGLONG> PerfCounters;


    DWORD dwObjectIndex = PROCESS_OBJECT_INDEX;
    DWORD dwCpuUsageIndex = PROCESSOR_TIME_COUNTER_INDEX;

    INT                CpuUsage = 0;
    LONGLONG        lnNewValue = 0;
    PPERF_DATA_BLOCK pPerfData = NULL;
    LARGE_INTEGER    NewPerfTime100nSec = {0};

    lnNewValue = PerfCounters.GetCounterValueForProcessID(&pPerfData, dwObjectIndex, dwCpuUsageIndex, dwProcessID);
    NewPerfTime100nSec = pPerfData->PerfTime100nSec;

    if (m_bFirstTime) {
        m_bFirstTime = false;
        m_lnOldValue = lnNewValue;
        m_OldPerfTime100nSec = NewPerfTime100nSec;
        return 0;
    }

    LONGLONG lnValueDelta = lnNewValue - m_lnOldValue;
    double DeltaPerfTime100nSec = (double)NewPerfTime100nSec.QuadPart - (double)m_OldPerfTime100nSec.QuadPart;

    m_lnOldValue = lnNewValue;
    m_OldPerfTime100nSec = NewPerfTime100nSec;

    double a = (double)lnValueDelta / DeltaPerfTime100nSec;

    CpuUsage = (INT) (a*100);
    if (CpuUsage < 0)
        return 0;

    return CpuUsage;
}
//---------------------------------------------------------------------------

#elif defined(xOS_LINUX)

#endif
