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
//TODO: + CxTest_CxSystemInfo (constructor)
CxTest_CxSystemInfo::CxTest_CxSystemInfo() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxSystemInfo (destructor)
CxTest_CxSystemInfo::~CxTest_CxSystemInfo() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
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
        //#define xWIN32_NT4       	   0x0400	//Windows NT 4.0
        //#define xWIN32_2K     	   0x0500	//Windows 2000
        //#define xWIN32_XP    	       0x0501	//Windows Server 2003, Windows XP
        //#define xWIN32_S03      	   0x0502	//Windows Server 2003 with SP1, Windows XP with SP2
        //#define xWIN32_WIN6     	   0x0600	//
        //#define xWIN32_VISTA     	   0x0600	//Windows Vista, Windows Server 2008
        //#define xWIN32_S08      	   0x0600	//
        //#define xWIN32_LONGHORN  	   0x0600	//
        //#define xWIN32_7      	   0x0601	//Windows 7

        m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otWindowsNT);
        xASSERT(xT("Win NT 4.0") == m_sRes);

        m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otWindows2000);
        xASSERT(xT("Win 2000") == m_sRes);

        m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otWindowsXP);
        xASSERT(xT("Win Server 2003, Win XP") == m_sRes);

        m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otWindowsServer2003);
        xASSERT(xT("Win Server 2003 SP1, Win XP SP2") == m_sRes);

        //m_sRes = CxSystemInfo::sFormatOsType(xWIN32_WIN6);
        //xASSERT(xT("Windows Vista, Windows Server 2008") == m_sRes);

        m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otWindowsVista);
        xASSERT(xT("Win Vista, Win Server 2008") == m_sRes);

        //m_sRes = CxSystemInfo::sFormatOsType(xWIN32_S08);
        //xASSERT(xT("Windows Vista, Windows Server 2008") == m_sRes);

        //m_sRes = CxSystemInfo::sFormatOsType(xWIN32_LONGHORN);
        //xASSERT(xT("Windows Vista, Windows Server 2008") == m_sRes);

        m_sRes = CxSystemInfo::sFormatOsType(CxSystemInfo::otWindowsServer2008R2);
        xASSERT(xT("Win 7, Win Server 2008 R2") == m_sRes);
        #elif defined(xOS_LINUX)
        m_sRes = CxSystemInfo::sFormatOsType( CxSystemInfo::osGetOS() );
        xASSERT(false == m_sRes.empty());
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
        xASSERT(xT("user") == m_sRes);
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

