/**
 * \file   CxTest_CxSystemInfo.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxSystemInfo.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Sync/CxCurrentThread.h>


//---------------------------------------------------------------------------
CxTest_CxSystemInfo::CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
CxTest_CxSystemInfo::~CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxSystemInfo::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    xTEST_CASE(CxSystemInfo::osOS, cullCaseLoops)
    {
        const CxSystemInfo::ExOsType otType = CxSystemInfo::osOS();
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

    xTEST_CASE(CxSystemInfo::sFormatOsType, cullCaseLoops)
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
                m_sRv = CxSystemInfo::sFormatOsType((*it).first);
                xTEST_EQ((*it).second, m_sRv);
            }
        #elif xOS_ENV_UNIX
            m_sRv = CxSystemInfo::sFormatOsType(CxSystemInfo::otLinux);
            xTEST_EQ(false, m_sRv.empty());

            m_sRv = CxSystemInfo::sFormatOsType(CxSystemInfo::otFreeBSD);
            xTEST_EQ(false, m_sRv.empty());
        #endif
    }

    xTEST_CASE(CxSystemInfo::oaOsArch, cullCaseLoops)
    {
        CxSystemInfo::ExOsArch oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo::oaOsArch();
        xTEST_DIFF(CxSystemInfo::oaUnknown, oaRes);
    }

    xTEST_CASE(CxSystemInfo::sFormatOsArch, cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sFormatOsArch(CxSystemInfo::oaUnknown);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxSystemInfo::sFormatOsArch(CxSystemInfo::oa32bit);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxSystemInfo::sFormatOsArch(CxSystemInfo::oa64bit);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE(CxSystemInfo::sHostName, cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sHostName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sHostName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE(CxSystemInfo::bIsUserAnAdmin, cullCaseLoops)
    {
        m_bRv = CxSystemInfo::bIsUserAnAdmin();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::bIsUserAnAdmin(): %s"), CxString::sBoolToStr(m_bRv).c_str());
        #endif
    }

    xTEST_CASE(CxSystemInfo::sUserName, cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sUserName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sUserName(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE(CxSystemInfo::sUseHomeDir, cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sUseHomeDir();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  CxDir::bIsExists(m_sRv));
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sUseHomeDir(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE(CxSystemInfo::sUserShellPath, cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sUserShellPath();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  CxFile::bIsExists(m_sRv));
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sUserShellPath(): %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE(CxSystemInfo::ulNumOfCpus, cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::ulNumOfCpus();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::ulNumOfCpus: %lu"), m_ulRv);
        #endif
        xTEST_LESS(0UL, m_ulRv);
    }

    xTEST_CASE(CxSystemInfo::ulCurrentCpuNum, cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::ulCurrentCpuNum();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::ulCurrentCpuNum: %lu"), m_ulRv);
        #endif
        xTEST_EQ(true, CxSystemInfo::ulNumOfCpus() > m_ulRv);
    }

    xTEST_CASE(CxSystemInfo::cvCpuVendor, cullCaseLoops)
    {
        CxSystemInfo::ExCpuVendor cvType = CxSystemInfo::cvCpuVendor();
        xTEST_EQ(true, CxSystemInfo::cvIntel == cvType || CxSystemInfo::cvAmd == cvType);
    }

    xTEST_CASE(CxSystemInfo::sCpuModel, cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sCpuModel();
        xTEST_EQ(false, m_sRv.empty());

        #if xTEST_IGNORE
            xTRACEV(xT("\tCPU model: %s"), m_sRv.c_str());
        #endif
    }

    xTEST_CASE(CxSystemInfo::ulCpuSpeed, cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::ulCpuSpeed();
        xTEST_LESS(0UL, m_ulRv);

        #if xTEST_IGNORE
            xTRACEV(xT("\tCPU speed: %ld"), m_ulRv);
        #endif
    }

    xTEST_CASE(CxSystemInfo::ullRamTotal, cullCaseLoops)
    {
        m_ullRv = CxSystemInfo::ullRamTotal();
        xTEST_LESS(0ULL, m_ullRv);
    }

    xTEST_CASE(CxSystemInfo::ullRamAvailable, cullCaseLoops)
    {
        m_ullRv = CxSystemInfo::ullRamAvailable();
        xTEST_LESS(0ULL, m_ullRv);
    }

    xTEST_CASE(CxSystemInfo::ulCpuUsage, cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = CxSystemInfo::ulCpuUsage();
            xTEST_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tCPU usage: %ld"), m_ulRv);

                CxCurrentThread::vSleep(1000UL);
            #endif
        }
    }

    xTEST_CASE(CxSystemInfo::ulRamUsage, cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = CxSystemInfo::ulRamUsage();
            xTEST_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tMemory usage: %ld"), m_ulRv);

                CxCurrentThread::vSleep(1000UL);
            #endif
        }
    }

    xTEST_CASE(CxSystemInfo::ulPageSize, cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::ulPageSize();
        xTEST_LESS(0UL, m_ulRv);
    }
}
//---------------------------------------------------------------------------
