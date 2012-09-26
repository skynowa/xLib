/**
 * \file   CxTest_CxSystemInfo.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxSystemInfo.h>

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
bool
CxTest_CxSystemInfo::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    // osGetOS
    xTEST_CASE(cullCaseLoops)
    {
        const CxSystemInfo::ExOsType otType = CxSystemInfo::osGetOS();
        xTEST_DIFF(CxSystemInfo::otUnknown, otType);

        #if xOS_ENV_WIN
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

    //-------------------------------------
    // sFormatOsType
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
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

    //--------------------------------------------------
    // oaGetOsArch
    xTEST_CASE(cullCaseLoops)
    {
        CxSystemInfo::ExOsArch oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo::oaGetOsArch();
        xTEST_DIFF(CxSystemInfo::oaUnknown, oaRes);
    }

    //--------------------------------------------------
    // sFormatOsArch
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sFormatOsArch(CxSystemInfo::oaUnknown);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxSystemInfo::sFormatOsArch(CxSystemInfo::oa32bit);
        xTEST_EQ(false, m_sRv.empty());

        m_sRv = CxSystemInfo::sFormatOsArch(CxSystemInfo::oa64bit);
        xTEST_EQ(false, m_sRv.empty());
    }

    //-------------------------------------
    // sGetHostName
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sGetHostName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sGetHostName(): %s"), m_sRv.c_str());
        #endif
    }

    //--------------------------------------------------
    // bIsUserAnAdmin
    xTEST_CASE(cullCaseLoops)
    {
        m_bRv = CxSystemInfo::bIsUserAnAdmin();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::bIsUserAnAdmin(): %s"), CxString::sBoolToStr(m_bRv).c_str());
        #endif
    }

    //-------------------------------------
    //sGetUserName
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sGetUserName();
        xTEST_EQ(false, m_sRv.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sGetUserName(): %s"), m_sRv.c_str());
        #endif
    }

    //-------------------------------------
    // sGetUseHomeDir
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sGetUseHomeDir();
        xTEST_EQ(false, m_sRv.empty());
        xTEST_EQ(true,  CxDir::bIsExists(m_sRv));
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sGetUseHomeDir(): %s"), m_sRv.c_str());
        #endif
    }

    //-------------------------------------
    // ulGetNumOfCpus
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::ulGetNumOfCpus();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::ulGetNumOfCpus: %lu"), m_ulRv);
        #endif
        xTEST_LESS(0UL, m_ulRv);
    }

    //-------------------------------------
    // ulGetCurrentCpuNum
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::ulGetCurrentCpuNum();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::ulGetCurrentCpuNum: %lu"), m_ulRv);
        #endif
        xTEST_EQ(true, CxSystemInfo::ulGetNumOfCpus() > m_ulRv);
    }

    //--------------------------------------------------
    // cvGetCpuVendor
    xTEST_CASE(cullCaseLoops)
    {
        CxSystemInfo::ExCpuVendor cvType = CxSystemInfo::cvGetCpuVendor();
        xTEST_EQ(true, CxSystemInfo::cvIntel == cvType || CxSystemInfo::cvAmd == cvType);
    }

    //--------------------------------------------------
    // sGetCpuModel
    xTEST_CASE(cullCaseLoops)
    {
        m_sRv = CxSystemInfo::sGetCpuModel();
        xTEST_EQ(false, m_sRv.empty());

        #if xTEST_IGNORE
            xTRACEV(xT("\tCPU model: %s"), m_sRv.c_str());
        #endif
    }

    //--------------------------------------------------
    // ulGetCpuSpeed
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::ulGetCpuSpeed();
        xTEST_LESS(0UL, m_ulRv);

        #if xTEST_IGNORE
            xTRACEV(xT("\tCPU speed: %ld"), m_ulRv);
        #endif
    }

    //--------------------------------------------------
    // ullGetRamTotal
    {
        m_ullRv = CxSystemInfo::ullGetRamTotal();
        xTEST_LESS(0ULL, m_ullRv);
    }

    //--------------------------------------------------
    // ullGetRamAvailable
    {
        m_ullRv = CxSystemInfo::ullGetRamAvailable();
        xTEST_LESS(0ULL, m_ullRv);
    }

    //--------------------------------------------------
    // ulGetCpuUsage
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = CxSystemInfo::ulGetCpuUsage();
            xDEBUG_VAR_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tCPU usage: %ld"), m_ulRv);

                CxCurrentThread::bSleep(1000UL);
            #endif
        }
    }

    //--------------------------------------------------
    // ulGetRamUsage
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < 10; ++ i) {
            m_ulRv = CxSystemInfo::ulGetRamUsage();
            xDEBUG_VAR_NA(m_ulRv);

            #if xTEST_IGNORE
                xTRACEV(xT("\tMemory usage: %ld"), m_ulRv);

                CxCurrentThread::bSleep(1000UL);
            #endif
        }
    }

    //--------------------------------------------------
    // ulGetPageSize
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRv = CxSystemInfo::ulGetPageSize();
        xTEST_LESS(0UL, m_ulRv);
    }

    return true;
}
//---------------------------------------------------------------------------
