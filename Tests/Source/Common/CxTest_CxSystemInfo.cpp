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
CxTest_CxSystemInfo::bUnit() {
    //--------------------------------------------------
    //osGetOS
    {
        CxSystemInfo::EOsType otType = CxSystemInfo::otUnknown;

        otType = CxSystemInfo::osGetOS();
        #if defined(xOS_WIN)
            xASSERT(CxSystemInfo::otWindowsXP == otType);
        #elif defined(xOS_LINUX)
            #if defined(xOS_FREEBSD)
                xASSERT(CxSystemInfo::otFreeBSD == otType);
            #else
                xASSERT(CxSystemInfo::otLinux == otType);
            #endif
        #endif
    }

    //-------------------------------------
    //sFormatOsType
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
                xASSERT((*it).second == m_sRes);
            }
        #elif defined(xOS_LINUX)
            m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otLinux);
            xASSERT(false == m_sRes.empty());

            m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otFreeBSD);
            xASSERT(false == m_sRes.empty());
        #endif
    }

    //--------------------------------------------------
    //oaGetOsArchitecture
    {
        CxSystemInfo::EOsArch oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo::oaGetOsArch();
        xASSERT(CxSystemInfo::oaUnknown != oaRes);
    }

    //-------------------------------------
    //sGetComputerName
    {
        m_sRes = CxSystemInfo::sGetComputerName();
        xASSERT(false == m_sRes.empty());
    }

    //--------------------------------------------------
    //bIsUserAnAdmin
    {
        m_bRes = CxSystemInfo::bIsUserAnAdmin();
        #if defined(xOS_WIN)
            xASSERT(TRUE == m_bRes);
        #elif defined(xOS_LINUX)
            #if defined(xOS_FREEBSD)
                xASSERT(TRUE == m_bRes);
            #else
                xASSERT(FALSE == m_bRes);
            #endif
        #endif
    }

    //-------------------------------------
    //sGetUserName
    {
        m_sRes = CxSystemInfo::sGetUserName();
        xASSERT(false == m_sRes.empty());
    }

    //-------------------------------------
    //ulGetNumOfCPUs
    {
        m_ulRes = CxSystemInfo::ulGetNumOfCPUs();
        xTRACEV(xT("    CxSystemInfo::ulGetNumOfCPUs: %li"), m_ulRes);
        xASSERT(0 < m_ulRes);
    }

    //-------------------------------------
    //ulGetCurrentCpuNum
    {
        m_ulRes = CxSystemInfo::ulGetCurrentCpuNum();
        xTRACEV(xT("    CxSystemInfo::ulGetCurrentCpuNum: %li"), m_ulRes);
        xASSERT(static_cast<ULONG>( - 1 ) != m_ulRes);
        xASSERT(0 <= m_ulRes && CxSystemInfo::ulGetNumOfCPUs() > m_ulRes);
    }

    //-------------------------------------
    //bIsUnicodeOS - Vista
    {
        m_bRes = CxSystemInfo::bIsUnicodeOS();
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //TODO: ullGetCpuSpeed
    {
        ////m_iRes = CxSystemInfo::ullGetCpuSpeed();
        ////xASSERT( == m_iRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
