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
/* virtual */
void
CxTest_CxProcessInfo::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxProcessInfo::ulGetCpuUsage, cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulGetCpuUsage(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetCpuUsage
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetCpuUsage(): %lu"), m_ulRv);
        #endif

    }

    xTEST_CASE(CxProcessInfo::ulGetRamUsage, cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulGetRamUsage(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetRamUsage
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetRamUsage(): %lu"), m_ulRv);
        #endif
    }

    xTEST_CASE(CxProcessInfo::ulGetIOBytes, cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulGetIOBytes(CxCurrentProcess::ulGetId());
        // TODO: CxProcessInfo::ulGetIOBytes
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulGetIOBytes(): %lu"), m_ulRv);
        #endif
    }

    xTEST_CASE(CxProcessInfo::sGetExeName, cullCaseLoops)
    {
        m_sRv = CxProcessInfo::sGetExeName( CxCurrentProcess::ulGetId() );
        xTEST_EQ(true,  CxFile::bIsExists(m_sRv));
        xTEST_EQ(m_sRv, CxPath::sGetExe());
    }

    xTEST_CASE(CxProcessInfo::ulGetParentId, cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulGetParentId( CxCurrentProcess::ulGetId() );
        // TODO: CxProcessInfo::ulGetParentId
        // xTEST_DIFF(0UL, m_ulRv);
    }

    xTEST_CASE(CxProcessInfo::sGetArgs, cullCaseLoops)
    {
        m_sRv = CxProcessInfo::sGetArgs(CxCurrentProcess::ulGetId());
        // TODO: test CxProcessInfo::sGetArgs
    }
}
//---------------------------------------------------------------------------
