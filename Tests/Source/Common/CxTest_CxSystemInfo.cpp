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
    try {
        int     c  = xCOUNTER;
        tString f  = xFILE;
        tString fu = xFUNCTION;
        int     l  = xLINE;

        std::cout << c  << std::endl;
        std::cout << f  << std::endl;
        std::cout << fu << std::endl;
        std::cout << l  << std::endl;

        CxDebugger::bTrace("Point: %i (file: %s, function: %s, line: %i)", c, f.c_str(), fu.c_str(), l);
        std::cout << "after bTrace" << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "!!!!!!!!" << std::endl;
    }

//xTRACE_POINT;
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxSystemInfo
CxTest_CxSystemInfo::~CxTest_CxSystemInfo() {
xTRACE_POINT;
}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxSystemInfo::bUnit() {
std::cout << "CxTest_CxSystemInfo::bUnit()_0" << std::endl;
//    #if xTEMP_DISABLED
//        //--------------------------------------------------
//        //osGetOS
//        {
//            CxSystemInfo::EOsType otType = CxSystemInfo::otUnknown;
//
//            #if defined(xOS_WIN)
//                otType = CxSystemInfo::osGetOS();
//                xASSERT(CxSystemInfo::otWindowsXP == otType);
//            #elif defined(xOS_LINUX)
//                otType = CxSystemInfo::osGetOS();
//                xASSERT(CxSystemInfo::otLinux == otType);
//            #endif
//        }
//        xTRACE_POINT;
//        //-------------------------------------
//        //sFormatOsType
//        {
//            #if defined(xOS_WIN)
//            std::map<CxSystemInfo::EOsType, tString> mapData;
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows3,               xT("Windows 3.1")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows95,              xT("Windows 95")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows98,              xT("Windows 98")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsNT,              xT("Windows NT 4.0")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows2000,            xT("Windows 2000")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsXP,              xT("Windows XP")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsXPProx64Edition, xT("Windows XP Pro x64 Edition")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsServer2003,      xT("Windows Server 2003")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsHomeServer,      xT("Windows Home Server")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsServer2003R2,    xT("Windows Server 2003 R2")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsVista,           xT("Windows Vista")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsServer2008,      xT("Windows Server 2008")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindowsServer2008R2,    xT("Windows Server 2008 R2")) );
//            mapData.insert( std::pair<CxSystemInfo::EOsType, tString>(CxSystemInfo::otWindows7,               xT("Windows 7")) );
//
//            std::map<CxSystemInfo::EOsType, tString>::const_iterator it;
//            for (it = mapData.begin(); it != mapData.end(); ++ it) {
//                m_sRes = CxSystemInfo::sFormatOsType((*it).first);
//                xASSERT((*it).second == m_sRes);
//            }
//            #endif
//        }
//        xTRACE_POINT;
//        //--------------------------------------------------
//        //oaGetOsArchitecture
//        {
//            CxSystemInfo::EOsArchitecture oaRes = CxSystemInfo::oaUnknown;
//
//            oaRes = CxSystemInfo::oaGetOsArchitecture();
//            xASSERT(CxSystemInfo::oa32bit == oaRes);
//        }
//        xTRACE_POINT;
//        //-------------------------------------
//        //sGetComputerName
//        {
//            m_sRes = CxSystemInfo::sGetComputerName();
//            xASSERT(false == m_sRes.empty());
//        }
//        xTRACE_POINT;
//        //--------------------------------------------------
//        //bIsUserAnAdmin
//        {
//            m_bRes = CxSystemInfo::bIsUserAnAdmin();
//            #if defined(xOS_WIN)
//                xASSERT(TRUE == m_bRes);
//            #elif defined(xOS_LINUX)
//                #if defined(xOS_FREEBSD)
//                    xASSERT(TRUE == m_bRes);
//                #else
//                    xASSERT(FALSE == m_bRes);
//                #endif
//            #endif
//        }
//        xTRACE_POINT;
//        //-------------------------------------
//        //sGetUserName
//        {
//            m_sRes = CxSystemInfo::sGetUserName();
//            xASSERT(false == m_sRes.empty());
//        }
//        xTRACE_POINT;
//        //-------------------------------------
//        //ulGetNumOfCPUs
//        {
//            m_ulRes = CxSystemInfo::ulGetNumOfCPUs();
//            xTRACEV(xT("    CxSystemInfo::ulGetNumOfCPUs: %ld"), m_ulRes);
//            xASSERT(0 < m_ulRes);
//        }
//        xTRACE_POINT;
//        //-------------------------------------
//        //ulGetCurrentCpuNum
//        {
//            m_ulRes = CxSystemInfo::ulGetCurrentCpuNum();
//            xTRACEV(xT("    CxSystemInfo::ulGetCurrentCpuNum: %ld"), m_ulRes);
//            xASSERT(static_cast<ULONG>( - 1 ) != m_ulRes);
//            xASSERT(0 <= m_ulRes && CxSystemInfo::ulGetNumOfCPUs() > m_ulRes);
//        }
//        xTRACE_POINT;
//        //-------------------------------------
//        //bIsUnicodeOS - Vista
//        {
//            m_bRes = CxSystemInfo::bIsUnicodeOS();
//            xASSERT(FALSE != m_bRes);
//        }
//        xTRACE_POINT;
//        //--------------------------------------------------
//        //iGetCpuSpeed
//        {
//            ////m_iRes = CxSystemInfo::iGetCpuSpeed();
//            ////xASSERT( == m_iRes);
//        }
//    #endif
std::cout << "CxTest_CxSystemInfo::bUnit()_1" << std::endl;
    return TRUE;
}
//---------------------------------------------------------------------------
