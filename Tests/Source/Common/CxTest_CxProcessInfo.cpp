/**
 * \file   CxTest_CxProcessInfo.cpp
 * \brief  test CxProcessInfo
 */


#include <Test/Common/CxTest_CxProcessInfo.h>

#include <xLib/Sync/CxCurrentProcess.h>

//---------------------------------------------------------------------------
CxTest_CxProcessInfo::CxTest_CxProcessInfo() {

}
//---------------------------------------------------------------------------
CxTest_CxProcessInfo::~CxTest_CxProcessInfo() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxProcessInfo::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //var
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxProcessInfo::ulGetCpuUsage(CxCurrentProcess::ulGetId());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetCpuUsage(): %lu"), m_ulRes);
        #endif

    }

    //--------------------------------------------------
    //var
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxProcessInfo::ulGetRamUsage(CxCurrentProcess::ulGetId());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetRamUsage(): %lu"), m_ulRes);
        #endif
    }

    //--------------------------------------------------
    //var
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxProcessInfo::ulGetIOBytes(CxCurrentProcess::ulGetId());
        #if xTEST_IGNORE || 1
            xTRACEV(xT("\tCxProcessInfo::ulGetIOBytes(): %lu"), m_ulRes);
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
