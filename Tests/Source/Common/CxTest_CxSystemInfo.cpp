/**
 * \file   CxTest_CxSystemInfo.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxSystemInfo.h>

#include <xLib/Sync/CxCurrentThread.h>


//---------------------------------------------------------------------------
CxTest_CxSystemInfo::CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
CxTest_CxSystemInfo::~CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxSystemInfo::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //osGetOS
    xTEST_CASE(cullCaseLoops)
    {
        CxSystemInfo::EOsType otType = CxSystemInfo::otUnknown;

        otType = CxSystemInfo::osGetOS();
        #if xOS_ENV_WIN
            xTEST_DIFF(CxSystemInfo::otLinux,   otType);
            xTEST_DIFF(CxSystemInfo::otFreeBSD, otType);
        #elif xOS_ENV_UNIX
            #if xOS_FREEBSD
                xTEST_EQ(CxSystemInfo::otFreeBSD, otType);
            #else
                xTEST_EQ(CxSystemInfo::otLinux, otType);
            #endif
        #endif
    }

    //-------------------------------------
    //sFormatOsType
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            std::map<CxSystemInfo::EOsType, std::tstring_t> mapData;

            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindows3,               xT("Windows 3.1")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindows95,              xT("Windows 95")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindows98,              xT("Windows 98")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsNT,              xT("Windows NT 4.0")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindows2000,            xT("Windows 2000")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsXP,              xT("Windows XP")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsXPProx64Edition, xT("Windows XP Pro x64 Edition")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsServer2003,      xT("Windows Server 2003")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsHomeServer,      xT("Windows Home Server")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsServer2003R2,    xT("Windows Server 2003 R2")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsVista,           xT("Windows Vista")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsServer2008,      xT("Windows Server 2008")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindowsServer2008R2,    xT("Windows Server 2008 R2")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::tstring_t>(CxSystemInfo::otWindows7,               xT("Windows 7")) );

            std::map<CxSystemInfo::EOsType, std::tstring_t>::const_iterator it;
            for (it = mapData.begin(); it != mapData.end(); ++ it) {
                m_sRes = CxSystemInfo::sFormatOsType((*it).first);
                xTEST_EQ((*it).second, m_sRes);
            }
        #elif xOS_ENV_UNIX
            m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otLinux);
            xTEST_EQ(false, m_sRes.empty());

            m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otFreeBSD);
            xTEST_EQ(false, m_sRes.empty());
        #endif
    }

    //--------------------------------------------------
    //oaGetOsArch
    xTEST_CASE(cullCaseLoops)
    {
        CxSystemInfo::EOsArch oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo::oaGetOsArch();
        xTEST_DIFF(CxSystemInfo::oaUnknown, oaRes);
    }

    //--------------------------------------------------
    //sFormatOsArch
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxSystemInfo::sFormatOsArch(CxSystemInfo::oaUnknown);
        xTEST_EQ(false, m_sRes.empty());

        m_sRes = CxSystemInfo::sFormatOsArch(CxSystemInfo::oa32bit);
        xTEST_EQ(false, m_sRes.empty());

        m_sRes = CxSystemInfo::sFormatOsArch(CxSystemInfo::oa64bit);
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //sGetComputerName
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxSystemInfo::sGetComputerName();
        xTEST_EQ(false, m_sRes.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sGetComputerName(): %s"), m_sRes.c_str());
        #endif
    }

    //--------------------------------------------------
    //bIsUserAnAdmin
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = CxSystemInfo::bIsUserAnAdmin();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::bIsUserAnAdmin(): %s"), CxString::sBoolToStr(m_bRes).c_str());
        #endif
    }

    //-------------------------------------
    //sGetUserName
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxSystemInfo::sGetUserName();
        xTEST_EQ(false, m_sRes.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sGetUserName(): %s"), m_sRes.c_str());
        #endif
    }

    //-------------------------------------
    //ulGetNumOfCpus
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxSystemInfo::ulGetNumOfCpus();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::ulGetNumOfCpus: %lu"), m_ulRes);
        #endif
        xTEST_LESS(0UL, m_ulRes);
    }

    //-------------------------------------
    //ulGetCurrentCpuNum
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxSystemInfo::ulGetCurrentCpuNum();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::ulGetCurrentCpuNum: %lu"), m_ulRes);
        #endif
        xTEST_EQ(true, 0 <= m_ulRes);
        xTEST_EQ(true, CxSystemInfo::ulGetNumOfCpus() > m_ulRes);
    }

    //--------------------------------------------------
    //ulGetCpuSpeed
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxSystemInfo::ulGetCpuSpeed();
        xTEST_LESS(0UL, m_ulRes);

        #if xTEST_IGNORE
            xTRACEV(xT("CPU speed: %ld"), m_ulRes);
        #endif
    }

    //--------------------------------------------------
    //ulGetCpuUsage
    xTEST_CASE(cullCaseLoops)
    {
        for (size_t i = 0; i < 1000; ++ i) {
            m_ulRes = CxSystemInfo::ulGetCpuUsage();
            xDEBUG_VAR_NA(m_ulRes);

            #if xTEST_IGNORE
                xTRACEV(xT("CPU usage: %ld"), m_ulRes);

                CxCurrentThread::bSleep(1000UL);
            #endif
        }
    }

    //--------------------------------------------------
    //ulGetPageSize
    xTEST_CASE(cullCaseLoops)
    {
        m_ulRes = CxSystemInfo::ulGetPageSize();
        xTEST_LESS(0UL, m_ulRes);
    }

    return true;
}
//---------------------------------------------------------------------------
