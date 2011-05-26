/****************************************************************************
* Class name:  CxTest_CxSystemInfo
* Description: test CxSystemInfo
* File name:   CxTest_CxSystemInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxSystemInfoH
#define CxTest_CxSystemInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxSystemInfo.h>
//---------------------------------------------------------------------------
class CxTest_CxSystemInfo : public CxTest {
	public:
		CxTest_CxSystemInfo();
		virtual     ~CxTest_CxSystemInfo();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxSystemInfo (constructor)
CxTest_CxSystemInfo::CxTest_CxSystemInfo() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxSystemInfo (destructor)
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

        #if defined(xOS_WIN)
        otType = CxSystemInfo::osGetOS();
        xASSERT(CxSystemInfo::otWindowsXP == otType);
        #elif defined(xOS_LINUX)
        otType = CxSystemInfo::osGetOS();
        xASSERT(CxSystemInfo::otLinux == otType);
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
        #endif
	}

    //--------------------------------------------------
    //oaGetOsArchitecture
    {
        CxSystemInfo::EOsArchitecture oaRes = CxSystemInfo::oaUnknown;

        oaRes = CxSystemInfo::oaGetOsArchitecture();
        xASSERT(CxSystemInfo::oa32bit == oaRes);
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
        xASSERT(FALSE == m_bRes);
        #endif
    }

    //-------------------------------------
    //sGetUserName
    {
        m_sRes = CxSystemInfo::sGetUserName();
        #if defined(xOS_WIN)
        xASSERT(false == m_sRes.empty());
        #elif defined(xOS_LINUX)
        xASSERT_EQUAL(tString(xT("user")), m_sRes);
        #endif
    }

	//-------------------------------------
	//ulGetNumOfCPUs
	{
		m_ulRes = CxSystemInfo::ulGetNumOfCPUs();
        #if defined(xOS_WIN)
        xASSERT(4 == m_ulRes);
        #elif defined(xOS_LINUX)
        xASSERT(2 == m_ulRes);
        #endif
	}

	//-------------------------------------
	//ulGetCurrentCpuNum
	{
		m_ulRes = CxSystemInfo::ulGetCurrentCpuNum();
		//xTRACEV(xT("m_ulRes: %i"), (INT)m_ulRes);
		xASSERT(0 <= m_ulRes && CxSystemInfo::ulGetNumOfCPUs() > m_ulRes);
	}

	//-------------------------------------
	//bIsUnicodeOS - Vista
	{
		m_bRes = CxSystemInfo::bIsUnicodeOS();
		xASSERT(FALSE != m_bRes);
	}

	//--------------------------------------------------
    //iGetCpuSpeed
    {
        ////m_iRes = CxSystemInfo::iGetCpuSpeed();
        ////xASSERT( == m_iRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxSystemInfoH

