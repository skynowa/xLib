/**
 * \file   CxTest_CxSystemInfo.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxSystemInfo.h>


//---------------------------------------------------------------------------
CxTest_CxSystemInfo::CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
CxTest_CxSystemInfo::~CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxSystemInfo::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //osGetOS
    xTEST_BLOCK(cullBlockLoops)
    {
        CxSystemInfo::EOsType otType = CxSystemInfo::otUnknown;

        otType = CxSystemInfo::osGetOS();
        #if defined(xOS_ENV_WIN)
            xTEST_EQ(CxSystemInfo::otWindowsXP, otType);
        #elif defined(xOS_ENV_UNIX)
            #if defined(xOS_FREEBSD)
                xTEST_EQ(CxSystemInfo::otFreeBSD, otType);
            #else
                xTEST_EQ(CxSystemInfo::otLinux, otType);
            #endif
        #endif
    }

    //-------------------------------------
    //sFormatOsType
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            std::map<CxSystemInfo::EOsType, std::string_t> mapData;

            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindows3,               xT("Windows 3.1")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindows95,              xT("Windows 95")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindows98,              xT("Windows 98")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsNT,              xT("Windows NT 4.0")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindows2000,            xT("Windows 2000")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsXP,              xT("Windows XP")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsXPProx64Edition, xT("Windows XP Pro x64 Edition")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsServer2003,      xT("Windows Server 2003")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsHomeServer,      xT("Windows Home Server")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsServer2003R2,    xT("Windows Server 2003 R2")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsVista,           xT("Windows Vista")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsServer2008,      xT("Windows Server 2008")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindowsServer2008R2,    xT("Windows Server 2008 R2")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, std::string_t>(CxSystemInfo::otWindows7,               xT("Windows 7")) );

            std::map<CxSystemInfo::EOsType, std::string_t>::const_iterator it;
            for (it = mapData.begin(); it != mapData.end(); ++ it) {
                m_sRes = CxSystemInfo::sFormatOsType((*it).first);
                xTEST_EQ((*it).second, m_sRes);
            }
        #elif defined(xOS_ENV_UNIX)
            m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otLinux);
            xTEST_EQ(false, m_sRes.empty());

            m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otFreeBSD);
            xTEST_EQ(false, m_sRes.empty());
        #endif
    }

    //--------------------------------------------------
    //oaGetOsArchitecture
    xTEST_BLOCK(cullBlockLoops)
    {
        CxSystemInfo::EOsArch oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo::oaGetOsArch();
        xTEST_DIFF(CxSystemInfo::oaUnknown, oaRes);
    }

    //-------------------------------------
    //sGetComputerName
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxSystemInfo::sGetComputerName();
        xTEST_EQ(false, m_sRes.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sGetComputerName(): %s"), m_sRes.c_str());
        #endif
    }

    //--------------------------------------------------
    //bIsUserAnAdmin
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxSystemInfo::bIsUserAnAdmin();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::bIsUserAnAdmin(): %s"), CxString::sBoolToStr(m_bRes).c_str());
        #endif
    }

    //-------------------------------------
    //sGetUserName
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxSystemInfo::sGetUserName();
        xTEST_EQ(false, m_sRes.empty());
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::sGetUserName(): %s"), m_sRes.c_str());
        #endif
    }

    //-------------------------------------
    //ulGetNumOfCpus
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = CxSystemInfo::ulGetNumOfCpus();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::ulGetNumOfCpus: %li"), m_ulRes);
        #endif
        xTEST_LESS(0UL, m_ulRes);
    }

    //-------------------------------------
    //ulGetCurrentCpuNum
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = CxSystemInfo::ulGetCurrentCpuNum();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxSystemInfo::ulGetCurrentCpuNum: %li"), m_ulRes);
        #endif
        xTEST_DIFF(static_cast<ULONG>( - 1 ), m_ulRes);
        xTEST_EQ(true, 0 <= m_ulRes && CxSystemInfo::ulGetNumOfCpus() > m_ulRes);
    }

    //-------------------------------------
    //bIsUnicodeOS - Vista
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxSystemInfo::bIsUnicodeOS();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //TODO: ullGetCpuSpeed
    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_iRes = CxSystemInfo::ullGetCpuSpeed();
        ////xTEST_LESS(0, m_iRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
