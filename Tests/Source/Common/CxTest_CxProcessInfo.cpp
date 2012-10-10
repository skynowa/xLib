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
    xTEST_CASE(CxProcessInfo::ulCpuUsage, cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulCpuUsage(CxCurrentProcess::ulId());
        // TODO: CxProcessInfo::ulCpuUsage
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulCpuUsage(): %lu"), m_ulRv);
        #endif

    }

    xTEST_CASE(CxProcessInfo::ulRamUsage, cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulRamUsage(CxCurrentProcess::ulId());
        // TODO: CxProcessInfo::ulRamUsage
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulRamUsage(): %lu"), m_ulRv);
        #endif
    }

    xTEST_CASE(CxProcessInfo::ulIOBytes, cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulIOBytes(CxCurrentProcess::ulId());
        // TODO: CxProcessInfo::ulIOBytes
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxProcessInfo::ulIOBytes(): %lu"), m_ulRv);
        #endif
    }

    xTEST_CASE(CxProcessInfo::sExeName, cullCaseLoops)
    {
        m_sRv = CxProcessInfo::sExeName( CxCurrentProcess::ulId() );
        xTEST_EQ(true,  CxFile::bIsExists(m_sRv));
        xTEST_EQ(m_sRv, CxPath::sExe());
    }

    xTEST_CASE(CxProcessInfo::ulParentId, cullCaseLoops)
    {
        m_ulRv = CxProcessInfo::ulParentId( CxCurrentProcess::ulId() );
        // TODO: CxProcessInfo::ulParentId
        // xTEST_DIFF(0UL, m_ulRv);
    }

    xTEST_CASE(CxProcessInfo::sArgs, cullCaseLoops)
    {
        m_sRv = CxProcessInfo::sArgs(CxCurrentProcess::ulId());
        // TODO: test CxProcessInfo::sArgs
    }
}
//---------------------------------------------------------------------------
