/**
 * \file   Test_SystemInfo.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_SystemInfo)
xTEST_UNIT(Test_SystemInfo)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_SystemInfo::unit()
{
    xTEST_CASE("os")
    {
        const SystemInfo::OsType otType = SystemInfo().os();
        xTEST_DIFF((int)SystemInfo::OsType::otUnknown, (int)otType);

        #if   xENV_WIN
            m_bRv =
                otType == SystemInfo::OsType::otWindows3 ||
                otType == SystemInfo::OsType::otWindows95 ||
                otType == SystemInfo::OsType::otWindows98 ||
                otType == SystemInfo::OsType::otWindowsNT ||
                otType == SystemInfo::OsType::otWindows2000 ||
                otType == SystemInfo::OsType::otWindowsXP ||
                otType == SystemInfo::OsType::otWindowsXPProx64Edition ||
                otType == SystemInfo::OsType::otWindowsServer2003 ||
                otType == SystemInfo::OsType::otWindowsHomeServer ||
                otType == SystemInfo::OsType::otWindowsServer2003R2 ||
                otType == SystemInfo::OsType::otWindowsVista ||
                otType == SystemInfo::OsType::otWindowsServer2008 ||
                otType == SystemInfo::OsType::otWindowsServer2008R2 ||
                otType == SystemInfo::OsType::otWindows7;

            xTEST_EQ(m_bRv, true);
        #elif xENV_UNIX
            #if xOS_FREEBSD
                xTEST_EQ((int)SystemInfo::OsType::otFreeBSD, (int)otType);
            #else
                xTEST_EQ((int)SystemInfo::OsType::otLinux, (int)otType);
            #endif
        #endif
    }

    xTEST_CASE("formatOs")
    {
        m_sRv = SystemInfo().formatOs();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("distro")
    {
        m_sRv = SystemInfo().distro();
        xTEST_EQ(m_sRv.empty(), false);
    }

    xTEST_CASE("osArch")
    {
        SystemInfo::OsArch oaRes = SystemInfo::OsArch::oaUnknown;

        oaRes = SystemInfo().osArch();
        xTEST_DIFF((int)SystemInfo::OsArch::oaUnknown, (int)oaRes);
    }

    xTEST_CASE("formatOsArch")
    {
        m_sRv = SystemInfo().formatOsArch();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("hostName")
    {
        m_sRv = SystemInfo().hostName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tSystemInfo::hostName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("numOfCpus")
    {
        m_ulRv = SystemInfo().numOfCpus();
        #if xTEST_IGNORE
            xTRACEV(xT("\tSystemInfo::numOfCpus: %lu"), m_ulRv);
        #endif
        xTEST_LESS(0UL, m_ulRv);
    }

    xTEST_CASE("currentCpuNum")
    {
        m_ulRv = SystemInfo().currentCpuNum();
        #if xTEST_IGNORE
            xTRACEV(xT("\tSystemInfo::currentCpuNum: %lu"), m_ulRv);
        #endif
        xTEST_EQ(true, SystemInfo().numOfCpus() > m_ulRv);
    }

    xTEST_CASE("cpuVendor")
    {
        SystemInfo::CpuVendor cvType = SystemInfo().cpuVendor();
        xTEST_EQ(true, SystemInfo::CpuVendor::cvIntel == cvType || SystemInfo::CpuVendor::cvAmd == cvType);
    }

    xTEST_CASE("cpuModel")
    {
        m_sRv = SystemInfo().cpuModel();
        xTEST_EQ(false, m_sRv.empty());

        #if xTEST_IGNORE
            xTRACEV(xT("\tcpuModel: %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("cpuSpeed")
    {
        m_ulRv = SystemInfo().cpuSpeed();
        xTEST_LESS(0UL, m_ulRv);

        #if xTEST_IGNORE
            xTRACEV(xT("\tcpuSpeed: %ld"), m_ulRv);
        #endif
    }

    xTEST_CASE("ramTotal")
    {
        m_ullRv = SystemInfo().ramTotal();
        xTEST_LESS(0ULL, m_ullRv);
    }

    xTEST_CASE("ramAvailable")
    {
        m_ullRv = SystemInfo().ramAvailable();
        xTEST_LESS(0ULL, m_ullRv);
    }

    xTEST_CASE("cpuUsage")
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = SystemInfo().cpuUsage();
            xTEST_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tcpuUsage: %ld"), m_ulRv);

                Thread::currentSleep(1000UL);
            #endif
        }
    }

    xTEST_CASE("ramUsage")
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = SystemInfo().ramUsage();
            xTEST_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tramUsage: %ld"), m_ulRv);

                Thread::currentSleep(1000UL);
            #endif
        }
    }

    xTEST_CASE("pageSize")
    {
        m_ulRv = SystemInfo().pageSize();
        xTEST_LESS(0UL, m_ulRv);
    }

#if xENV_UNIX
    xTEST_CASE("glibcVersion")
    {
        m_sRv = SystemInfo().glibcVersion();
        xTEST_EQ(m_sRv.empty(), false);

        // Trace() << xTRACE_VAR(m_sRv);
    }
#endif

#if xENV_UNIX
    xTEST_CASE("libPthreadVersion")
    {
        m_sRv = SystemInfo().libPthreadVersion();
        xTEST_EQ(m_sRv.empty(), false);

        // Trace() << xTRACE_VAR(m_sRv);
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
