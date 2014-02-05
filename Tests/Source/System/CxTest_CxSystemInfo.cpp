/**
 * \file   CxTest_CxSystemInfo.cpp
 * \brief
 */


#include <Test/System/CxTest_CxSystemInfo.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Sync/CxThread.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSystemInfo::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxSystemInfo::os", a_caseLoops)
    {
        const CxSystemInfo::ExOsType otType = CxSystemInfo().os();
        xTEST_DIFF(CxSystemInfo::otUnknown, otType);

        #if   xOS_ENV_WIN
            m_bRv =
                otType == CxSystemInfo::otWindows3 ||
                otType == CxSystemInfo::otWindows95 ||
                otType == CxSystemInfo::otWindows98 ||
                otType == CxSystemInfo::otWindowsNT ||
                otType == CxSystemInfo::otWindows2000 ||
                otType == CxSystemInfo::otWindowsXP ||
                otType == CxSystemInfo::otWindowsXPProx64Edition ||
                otType == CxSystemInfo::otWindowsServer2003 ||
                otType == CxSystemInfo::otWindowsHomeServer ||
                otType == CxSystemInfo::otWindowsServer2003R2 ||
                otType == CxSystemInfo::otWindowsVista ||
                otType == CxSystemInfo::otWindowsServer2008 ||
                otType == CxSystemInfo::otWindowsServer2008R2 ||
                otType == CxSystemInfo::otWindows7;

            xTEST_EQ(true, m_bRv);
        #elif xOS_ENV_UNIX
            #if xOS_FREEBSD
                xTEST_EQ(CxSystemInfo::otFreeBSD, otType);
            #else
                xTEST_EQ(CxSystemInfo::otLinux, otType);
            #endif
        #endif
    }

    xTEST_CASE("CxSystemInfo::formatOsType", a_caseLoops)
    {
        m_sRv = CxSystemInfo().formatOsType();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxSystemInfo::osArch", a_caseLoops)
    {
        CxSystemInfo::ExOsArch oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo().osArch();
        xTEST_DIFF(CxSystemInfo::oaUnknown, oaRes);
    }

    xTEST_CASE("CxSystemInfo::formatOsArch", a_caseLoops)
    {
        m_sRv = CxSystemInfo().formatOsArch();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxSystemInfo::hostName", a_caseLoops)
    {
        m_sRv = CxSystemInfo().hostName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::hostName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::isUserAdmin", a_caseLoops)
    {
        m_bRv = CxSystemInfo().isUserAdmin();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::isUserAdmin(): %s"), CxString::castBool(m_bRv).c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::userName", a_caseLoops)
    {
        m_sRv = CxSystemInfo().userName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::userName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::loginUserName", a_caseLoops)
    {
        m_sRv = CxSystemInfo().loginUserName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::loginUserName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::userHomeDir", a_caseLoops)
    {
        m_sRv = CxSystemInfo().userHomeDir();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  CxDir(m_sRv).isExists());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::userHomeDir(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::userShellPath", a_caseLoops)
    {
        m_sRv = CxSystemInfo().userShellPath();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  CxFile::isExists(m_sRv));
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::userShellPath(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::numOfCpus", a_caseLoops)
    {
        m_ulRv = CxSystemInfo().numOfCpus();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::numOfCpus: %lu"), m_ulRv);
        #endif
        xTEST_LESS(0UL, m_ulRv);
    }

    xTEST_CASE("CxSystemInfo::currentCpuNum", a_caseLoops)
    {
        m_ulRv = CxSystemInfo().currentCpuNum();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::currentCpuNum: %lu"), m_ulRv);
        #endif
        xTEST_EQ(true, CxSystemInfo().numOfCpus() > m_ulRv);
    }

    xTEST_CASE("CxSystemInfo::cpuVendor", a_caseLoops)
    {
        CxSystemInfo::ExCpuVendor cvType = CxSystemInfo().cpuVendor();
        xTEST_EQ(true, CxSystemInfo::cvIntel == cvType || CxSystemInfo::cvAmd == cvType);
    }

    xTEST_CASE("CxSystemInfo::cpuModel", a_caseLoops)
    {
        m_sRv = CxSystemInfo().cpuModel();
        xTEST_EQ(false, m_sRv.empty());

        #if xTEST_IGNORE
            xTRACEV(xT("\tcpuModel: %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::cpuSpeed", a_caseLoops)
    {
        m_ulRv = CxSystemInfo().cpuSpeed();
        xTEST_LESS(0UL, m_ulRv);

        #if xTEST_IGNORE
            xTRACEV(xT("\tcpuSpeed: %ld"), m_ulRv);
        #endif
    }

    xTEST_CASE("CxSystemInfo::ramTotal", a_caseLoops)
    {
        m_ullRv = CxSystemInfo().ramTotal();
        xTEST_LESS(0ULL, m_ullRv);
    }

    xTEST_CASE("CxSystemInfo::ramAvailable", a_caseLoops)
    {
        m_ullRv = CxSystemInfo().ramAvailable();
        xTEST_LESS(0ULL, m_ullRv);
    }

    xTEST_CASE("CxSystemInfo::cpuUsage", a_caseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = CxSystemInfo().cpuUsage();
            xTEST_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tcpuUsage: %ld"), m_ulRv);

                CxThread::currentSleep(1000UL);
            #endif
        }
    }

    xTEST_CASE("CxSystemInfo::ramUsage", a_caseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = CxSystemInfo().ramUsage();
            xTEST_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tramUsage: %ld"), m_ulRv);

                CxThread::currentSleep(1000UL);
            #endif
        }
    }

    xTEST_CASE("CxSystemInfo::pageSize", a_caseLoops)
    {
        m_ulRv = CxSystemInfo().pageSize();
        xTEST_LESS(0UL, m_ulRv);
    }

#if xOS_ENV_UNIX
    xTEST_CASE("CxSystemInfo::glibcVersion", a_caseLoops)
    {
        m_sRv = CxSystemInfo().glibcVersion();
        xTEST_EQ(m_sRv.empty(), false);

        // CxTrace() << xTRACE_VAR(m_sRv);
    }
#endif

#if xOS_ENV_UNIX
    xTEST_CASE("CxSystemInfo::libPthreadVersion", a_caseLoops)
    {
        m_sRv = CxSystemInfo().libPthreadVersion();
        xTEST_EQ(m_sRv.empty(), false);

        // CxTrace() << xTRACE_VAR(m_sRv);
    }
#endif
}
//-------------------------------------------------------------------------------------------------
