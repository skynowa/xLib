/****************************************************************************
* Class name:  CxTest_CxVolume
* Description: test CxVolume
* File name:   CxTest_CxVolume.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxVolumeH
#define CxTest_CxVolumeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxVolume.h>
//---------------------------------------------------------------------------
class CxTest_CxVolume : public CxTest {
	public:
		CxTest_CxVolume();
		virtual     ~CxTest_CxVolume();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxVolume (constructor)
CxTest_CxVolume::CxTest_CxVolume() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxVolume (destructor)
CxTest_CxVolume::~CxTest_CxVolume() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxVolume::bUnit() {
    #if xCAN_REMOVE
        const tString  g_csFilePath                   = xT("C:\\Test.txt");
        const tString  g_csNewFilePath                = xT("C:\\New.Test.txt");
        const tString  g_csBakFilePath                = xT("C:\\Test_Static.txt.bak");
        const tString  g_csFilePathSt                 = xT("C:\\Test_Static.txt");
    #endif

	//-------------------------------------
	//bIsReady
    {
        //TRUE
        {
            #if defined(xOS_WIN)
                const tString  g_csVolumePathWithSlash     = xT("C:\\");
                const tString  g_csVolumeePathWithoutSlash = xT("C:");
            #elif defined(xOS_LINUX)
                const tString  g_csVolumePathWithSlash     = xT("/");
                const tString  g_csVolumeePathWithoutSlash = xT("/");
            #endif

            m_bRes = CxVolume::bIsReady(g_csVolumePathWithSlash);
            xASSERT(FALSE != m_bRes);

            m_bRes = CxVolume::bIsReady(g_csVolumeePathWithoutSlash);
            xASSERT(FALSE != m_bRes);
        }

        //FALSE
        {
            #if defined(xOS_WIN)
                const tString  g_csVolumePathWithSlash     = xT("B:\\");
                const tString  g_csVolumeePathWithoutSlash = xT("B:");
            #elif defined(xOS_LINUX)
                const tString  g_csVolumePathWithSlash     = xT("/mnqwioe54oq389cp3qm49/");
                const tString  g_csVolumeePathWithoutSlash = xT("/mnqwioe54oq389cp3qm49");
            #endif

            m_bRes = CxVolume::bIsReady(g_csVolumePathWithSlash);
            xASSERT(FALSE == m_bRes);

            m_bRes = CxVolume::bIsReady(g_csVolumeePathWithoutSlash);
            xASSERT(FALSE == m_bRes);
        }
    }

	//-------------------------------------
	//bIsEmpty
	{
        //TRUE
        {
            #if xTODO
                #if defined(xOS_WIN)
                    const tString  g_csVolumePathWithSlash     = xT("B:\\");
                    const tString  g_csVolumeePathWithoutSlash = xT("B:");
                #elif defined(xOS_LINUX)
                    const tString  g_csVolumePathWithSlash     = xT("/home/mnqwioe54oq389cp3qm49/");
                    const tString  g_csVolumeePathWithoutSlash = xT("/home/mnqwioe54oq389cp3qm49");
                #endif

                m_bRes = CxVolume::bIsEmpty(g_csVolumePathWithSlash);
                xASSERT(TRUE == m_bRes);

                m_bRes = CxVolume::bIsEmpty(g_csVolumeePathWithoutSlash);
                xASSERT(TRUE == m_bRes);
            #endif
        }

        //FALSE
        {
            #if defined(xOS_WIN)
                const tString  g_csVolumePathWithSlash     = xT("C:\\");
                const tString  g_csVolumeePathWithoutSlash = xT("C:");
            #elif defined(xOS_LINUX)
                const tString  g_csVolumePathWithSlash     = xT("/");
                const tString  g_csVolumeePathWithoutSlash = xT("/FLASH_4GB/");
            #endif

            #if xTEMP_DISABLED
                m_bRes = CxVolume::bIsEmpty(g_csVolumePathWithSlash);
                xASSERT(FALSE == m_bRes);

                m_bRes = CxVolume::bIsEmpty(g_csVolumeePathWithoutSlash);
                xASSERT(FALSE == m_bRes);
            #endif
        }
    }

	//-------------------------------------
	//bGetFreeSpace
	{
        #if defined(xOS_WIN)
            const tString  csVolumePathWithSlash     = xT("C:\\");
            const tString  csVolumeePathWithoutSlash = xT("C:");
        #elif defined(xOS_LINUX)
            const tString  csVolumePathWithSlash     = xT("/");
            const tString  csVolumeePathWithoutSlash = xT("//");
        #endif

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, &ullAvailable, &ullTotal, &ullFree);
            xASSERT(FALSE != m_bRes);
            xASSERT(0     <  ullAvailable);
            xASSERT(0     <  ullTotal);
            xASSERT(0     <  ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, NULL, NULL, NULL);
            xASSERT(FALSE != m_bRes);
            xASSERT(0     == ullAvailable);
            xASSERT(0     == ullTotal);
            xASSERT(0     == ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(xT("/media/FLASH_4GB/xxx")/*CxConst::xSTR_EMPTY*/, &ullAvailable, &ullTotal, &ullFree);
            xASSERT(FALSE != m_bRes);
            xASSERT(0     <  ullAvailable);
            xASSERT(0     <  ullTotal);
            xASSERT(0     <  ullFree);

            //xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(CxConst::xSTR_EMPTY, &ullAvailable, &ullTotal, &ullFree);
            xASSERT(FALSE != m_bRes);
            xASSERT(0     <  ullAvailable);
            xASSERT(0     <  ullTotal);
            xASSERT(0     <  ullFree);

            //xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
        }
	}

	//-------------------------------------
	//dtGetType
    #if defined(xOS_WIN)
        CxVolume::EType g_dtRes = CxVolume::dtGetType(g_csDrivePathWithoutSlash);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
    #endif

	//-------------------------------------
	//dtGetType
    #if defined(xOS_WIN)
    	tString szVolumeName;
        ULONG   ulVolumeSerialNumber     = 0;
        ULONG   ulMaximumComponentLength = 0;
        ULONG   ulFileSystemFlags        = 0;
        tString sFileSystemName;

        m_bRes = CxVolume::bGetInfo(
                            g_csDrivePathWithoutSlash,
                            &szVolumeName,
                            &ulVolumeSerialNumber,
                            &ulMaximumComponentLength,
                            &ulFileSystemFlags,
                            &sFileSystemName);
        xASSERT(TRUE == m_bRes);
    #elif defined(xOS_LINUX)
        //TODO: xOS_LINUX
    #endif

	//-------------------------------------
	//bGetLogicalDrives
	{
        #if defined(xOS_WIN)
            std::vector<tString> vecsDrives;

            m_bRes = CxVolume::bGetLogicalDrives(&vecsDrives);
            xASSERT(TRUE == m_bRes);
        #elif defined(xOS_LINUX)
            //TODO: xOS_LINUX
        #endif
	}

	//-------------------------------------
	//bGetLogicalDrives2
	{
        #if defined(xOS_WIN)
            std::vector<tString> vecsDrives;

            m_bRes = CxVolume::bGetLogicalDrives(&vecsDrives, CxVolume::dtFixed);
            xASSERT(TRUE == m_bRes);
        #elif defined(xOS_LINUX)
            //TODO: xOS_LINUX
        #endif
	}

	//-------------------------------------
	//bDefineDosDevice
	{

	}

	//-------------------------------------
	//bDeleteVolumeMountPoint
	{

	}

	//-------------------------------------
	//hFindFirstVolume
	{

	}

	//-------------------------------------
	//hFindFirstVolumeMountPoint
	{

	}

	//-------------------------------------
	//sFindNextVolume
	{

	}

	//-------------------------------------
	//bFindNextVolumeMountPoint
	{

	}

	//-------------------------------------
	//bFindVolumeClose
	{

	}

	//-------------------------------------
	//bFindVolumeMountPointClose
	{

	}

	//-------------------------------------
	//sGetLogicalStrings
	{

	}

	//-------------------------------------
	//sGetVolumeNameForVolumeMountPoint
	{

	}

	//-------------------------------------
	//sGetVolumePathName
	{

	}

	//-------------------------------------
	//sGetVolumePathNamesForVolumeName
	{

	}

	//-------------------------------------
	//sQueryDosDevice

	//-------------------------------------
	//bSetVolumeLabel
	{

	}

	//-------------------------------------
	//bSetVolumeMountPoint
	{

	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxVolumeH

