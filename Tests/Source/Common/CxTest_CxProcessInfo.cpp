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
        m_ulRv = CxProcessInfo::ulGetCpuUsage(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetCpuUsage
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetCpuUsage(): %lu"), m_ulRv);
        #endif

    }

    //--------------------------------------------------
    // ulGetRamUsage
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulGetRamUsage(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetRamUsage
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetRamUsage(): %lu"), m_ulRv);
        #endif
    }

    //--------------------------------------------------
    // ulGetIOBytes
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulGetIOBytes(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetIOBytes
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetIOBytes(): %lu"), m_ulRv);
        #endif
    }

    //--------------------------------------------------
    // sGetExeName
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxProcessInfo::sGetExeName( CxCurrentProcess::ulGetId() );
        xTEST_EQ(true,  CxFile::bIsExists(m_sRv));
        xTEST_EQ(m_sRv, CxPath::sGetExe());
    }

    //--------------------------------------------------
    // ulGetParentId
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulGetParentId( CxCurrentProcess::ulGetId() );
        // TODO: CxProcessInfo::ulGetParentId
        // xTEST_DIFF(0UL, m_ulRv);
    }

    //--------------------------------------------------
    // CxProcessInfo::sGetArgs
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxProcessInfo::sGetArgs(CxCurrentProcess::ulGetId());
        // TODO: test CxProcessInfo::sGetArgs
    }

    return true;
}
//---------------------------------------------------------------------------
