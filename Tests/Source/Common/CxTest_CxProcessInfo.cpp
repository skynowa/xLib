/**
 * \file   CxTest_CxProcessInfo.cpp
 * \brief  test CxProcessInfo
 */


#include <Test/Common/CxTest_CxProcessInfo.h>

#include <xLib/Sync/CxCurrentProcess.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>


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
    // ulGetCpuUsage
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxProcessInfo::ulGetCpuUsage(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetCpuUsage
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetCpuUsage(): %lu"), m_ulRes);
        #endif

    }

    //--------------------------------------------------
    // ulGetRamUsage
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxProcessInfo::ulGetRamUsage(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetRamUsage
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetRamUsage(): %lu"), m_ulRes);
        #endif
    }

    //--------------------------------------------------
    // ulGetIOBytes
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxProcessInfo::ulGetIOBytes(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetIOBytes
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetIOBytes(): %lu"), m_ulRes);
        #endif
    }

    //--------------------------------------------------
    // sGetExeName
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxProcessInfo::sGetExeName( CxCurrentProcess::ulGetId() );
        xTEST_EQ(true,   CxFile::bIsExists(m_sRes));
        xTEST_EQ(m_sRes, CxPath::sGetExe());
    }

    //--------------------------------------------------
    // ulGetParentId
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxProcessInfo::ulGetParentId( CxCurrentProcess::ulGetId() );
        // TODO: CxProcessInfo::ulGetParentId
        // xTEST_DIFF(0UL, m_ulRes);
    }

    return true;
}
//---------------------------------------------------------------------------
