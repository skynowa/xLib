/****************************************************************************
* Class name:  CxTest_CxSystemInfo
* Description: test CxSystemInfo
* File name:   CxTest_CxSystemInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxSystemInfo.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxSystemInfo
CxTest_CxSystemInfo::CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxSystemInfo
CxTest_CxSystemInfo::~CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
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
        #if defined(xOS_WIN)
            xASSERT_EQUAL(CxSystemInfo::otWindowsXP, otType);
        #elif defined(xOS_LINUX)
            #if defined(xOS_FREEBSD)
                xASSERT_EQUAL(CxSystemInfo::otFreeBSD, otType);
            #else
                xASSERT_EQUAL(CxSystemInfo::otLinux, otType);
            #endif
        #endif
    }

    //-------------------------------------
    //sFormatOsType
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_WIN)
            std::map<CxSystemInfo::EOsType, tString> mapData;

            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows3,               xT("Windows 3.1")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows95,              xT("Windows 95")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows98,              xT("Windows 98")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsNT,              xT("Windows NT 4.0")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows2000,            xT("Windows 2000")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsXP,              xT("Windows XP")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsXPProx64Edition, xT("Windows XP Pro x64 Edition")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsServer2003,      xT("Windows Server 2003")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsHomeServer,      xT("Windows Home Server")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsServer2003R2,    xT("Windows Server 2003 R2")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsVista,           xT("Windows Vista")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsServer2008,      xT("Windows Server 2008")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsServer2008R2,    xT("Windows Server 2008 R2")) );
            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows7,               xT("Windows 7")) );

            std::map<CxSystemInfo::EOsType, tString>::const_iterator it;
            for (it = mapData.begin(); it != mapData.end(); ++ it) {
                m_sRes = CxSystemInfo::sFormatOsType((*it).first);
                xASSERT_EQUAL((*it).second, m_sRes);
            }
        #elif defined(xOS_LINUX)
            m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otLinux);
            xASSERT_EQUAL(false, m_sRes.empty());

            m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otFreeBSD);
            xASSERT_EQUAL(false, m_sRes.empty());
        #endif
    }

    //--------------------------------------------------
    //oaGetOsArchitecture
    xTEST_BLOCK(cullBlockLoops)
    {
        CxSystemInfo::EOsArch oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo::oaGetOsArch();
        xASSERT_NOT_EQUAL(CxSystemInfo::oaUnknown, oaRes);
    }

    //-------------------------------------
    //sGetComputerName
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxSystemInfo::sGetComputerName();
        xASSERT_EQUAL(false, m_sRes.empty());
        xTRACEV(xT("\tCxSystemInfo::sGetComputerName(): %s"), m_sRes.c_str());
    }

    //--------------------------------------------------
    //bIsUserAnAdmin
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxSystemInfo::bIsUserAnAdmin();
        xTRACEV(xT("\tCxSystemInfo::bIsUserAnAdmin(): %s"), CxString::sBoolToStr(m_bRes).c_str());
    }

    //-------------------------------------
    //sGetUserName
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxSystemInfo::sGetUserName();
        xASSERT_EQUAL(false, m_sRes.empty());
        xTRACEV(xT("\tCxSystemInfo::sGetUserName(): %s"), m_sRes.c_str());
    }

    //-------------------------------------
    //ulGetNumOfCPUs
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = CxSystemInfo::ulGetNumOfCPUs();
        xTRACEV(xT("\tCxSystemInfo::ulGetNumOfCPUs: %li"), m_ulRes);
        xASSERT_LESS(0UL, m_ulRes);
    }

    //-------------------------------------
    //ulGetCurrentCpuNum
    xTEST_BLOCK(cullBlockLoops)
    {
        m_ulRes = CxSystemInfo::ulGetCurrentCpuNum();
        xTRACEV(xT("\tCxSystemInfo::ulGetCurrentCpuNum: %li"), m_ulRes);
        xASSERT_NOT_EQUAL(static_cast<ULONG>( - 1 ), m_ulRes);
        xASSERT_EQUAL(true, 0 <= m_ulRes && CxSystemInfo::ulGetNumOfCPUs() > m_ulRes);
    }

    //-------------------------------------
    //bIsUnicodeOS - Vista
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxSystemInfo::bIsUnicodeOS();
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //TODO: ullGetCpuSpeed
    xTEST_BLOCK(cullBlockLoops)
    {
        ////m_iRes = CxSystemInfo::ullGetCpuSpeed();
        ////xASSERT_LESS(0, m_iRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
