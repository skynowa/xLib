/**
 * \file   CxTest_CxSystemInfo.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxSystemInfo.h>

#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Sync/CxCurrentThread.h>


//------------------------------------------------------------------------------
CxTest_CxSystemInfo::CxTest_CxSystemInfo() {

}
//------------------------------------------------------------------------------
CxTest_CxSystemInfo::~CxTest_CxSystemInfo() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxSystemInfo::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxSystemInfo::os", a_cullCaseLoops)
    {
        const CxSystemInfo::ExOsType otType = CxSystemInfo::os();
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

    xTEST_CASE("CxSystemInfo::formatOsType", a_cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            typedef std::map<CxSystemInfo::ExOsType, std::tstring_t> TData;

            TData mapData;

            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindows3,               xT("Windows 3.1")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindows95,              xT("Windows 95")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindows98,              xT("Windows 98")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsNT,              xT("Windows NT 4.0")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindows2000,            xT("Windows 2000")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsXP,              xT("Windows XP")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsXPProx64Edition, xT("Windows XP Pro x64 Edition")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsServer2003,      xT("Windows Server 2003")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsHomeServer,      xT("Windows Home Server")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsServer2003R2,    xT("Windows Server 2003 R2")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsVista,           xT("Windows Vista")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsServer2008,      xT("Windows Server 2008")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindowsServer2008R2,    xT("Windows Server 2008 R2")) );
            mapData.insert( std::pair<CxSystemInfo::ExOsType, std::tstring_t>(CxSystemInfo::otWindows7,               xT("Windows 7")) );

            xFOREACH_CONST(TData, it, mapData) {
                m_sRv = CxSystemInfo::formatOsType((*it).first);
                xTEST_EQ((*it).second, m_sRv);
            }
        #elif xOS_ENV_UNIX
            m_sRv = CxSystemInfo::formatOsType(CxSystemInfo::otLinux);
            xTEST_EQ(false, m_sRv.empty());

            m_sRv = CxSystemInfo::formatOsType(CxSystemInfo::otFreeBSD);
            xTEST_EQ(false, m_sRv.empty());
        #endif
    }

    xTEST_CASE("CxSystemInfo::osArch", a_cullCaseLoops)
    {
        CxSystemInfo::ExOsArch oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo::osArch();
        xTEST_DIFF(CxSystemInfo::oaUnknown, oaRes);
    }

    xTEST_CASE("CxSystemInfo::formatOsArch", a_cullCaseLoops)
    {
        m_sRv = CxSystemInfo::formatOsArch(CxSystemInfo::oaUnknown);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxSystemInfo::formatOsArch(CxSystemInfo::oa32bit);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxSystemInfo::formatOsArch(CxSystemInfo::oa64bit);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxSystemInfo::hostName", a_cullCaseLoops)
    {
        m_sRv = CxSystemInfo::hostName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::hostName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::isUserAdmin", a_cullCaseLoops)
    {
        m_bRv = CxSystemInfo::isUserAdmin();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::isUserAdmin(): %s"), CxString::boolToStr(m_bRv).c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::userName", a_cullCaseLoops)
    {
        m_sRv = CxSystemInfo::userName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::userName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::useHomeDir", a_cullCaseLoops)
    {
        m_sRv = CxSystemInfo::useHomeDir();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  CxDir(m_sRv).isExists());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::useHomeDir(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::userShellPath", a_cullCaseLoops)
    {
        m_sRv = CxSystemInfo::userShellPath();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  CxFile::isExists(m_sRv));
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::userShellPath(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::numOfCpus", a_cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::numOfCpus();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::numOfCpus: %lu"), m_ulRv);
        #endif
        xTEST_LESS(0UL, m_ulRv);
    }

    xTEST_CASE("CxSystemInfo::currentCpuNum", a_cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::currentCpuNum();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::currentCpuNum: %lu"), m_ulRv);
        #endif
        xTEST_EQ(true, CxSystemInfo::numOfCpus() > m_ulRv);
    }

    xTEST_CASE("CxSystemInfo::cpuVendor", a_cullCaseLoops)
    {
        CxSystemInfo::ExCpuVendor cvType = CxSystemInfo::cpuVendor();
        xTEST_EQ(true, CxSystemInfo::cvIntel == cvType || CxSystemInfo::cvAmd == cvType);
    }

    xTEST_CASE("CxSystemInfo::cpuModel", a_cullCaseLoops)
    {
        m_sRv = CxSystemInfo::cpuModel();
        xTEST_EQ(false, m_sRv.empty());

        #if xTEST_IGNORE
            xTRACEV(xT("\tcpuModel: %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE("CxSystemInfo::cpuSpeed", a_cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::cpuSpeed();
        xTEST_LESS(0UL, m_ulRv);

        #if xTEST_IGNORE
            xTRACEV(xT("\tcpuSpeed: %ld"), m_ulRv);
        #endif
    }

    xTEST_CASE("CxSystemInfo::ramTotal", a_cullCaseLoops)
    {
        m_ullRv = CxSystemInfo::ramTotal();
        xTEST_LESS(0ULL, m_ullRv);
    }

    xTEST_CASE("CxSystemInfo::ramAvailable", a_cullCaseLoops)
    {
        m_ullRv = CxSystemInfo::ramAvailable();
        xTEST_LESS(0ULL, m_ullRv);
    }

    xTEST_CASE("CxSystemInfo::cpuUsage", a_cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = CxSystemInfo::cpuUsage();
            xTEST_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tcpuUsage: %ld"), m_ulRv);

                CxCurrentThread::sleep(1000UL);
            #endif
        }
    }

    xTEST_CASE("CxSystemInfo::ramUsage", a_cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = CxSystemInfo::ramUsage();
            xTEST_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tramUsage: %ld"), m_ulRv);

                CxCurrentThread::sleep(1000UL);
            #endif
        }
    }

    xTEST_CASE("CxSystemInfo::pageSize", a_cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::pageSize();
        xTEST_LESS(0UL, m_ulRv);
    }
}
//------------------------------------------------------------------------------
