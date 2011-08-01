/****************************************************************************
* Class name:  CxTest_CxVolume
* Description: test CxVolume
* File name:   CxTest_CxVolume.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxVolume.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxVolume
CxTest_CxVolume::CxTest_CxVolume() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxVolume
CxTest_CxVolume::~CxTest_CxVolume() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxVolume::bUnit() {
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
            xASSERT_EQUAL(TRUE, m_bRes);

            m_bRes = CxVolume::bIsReady(g_csVolumeePathWithoutSlash);
            xASSERT_EQUAL(TRUE, m_bRes);
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
            xASSERT_EQUAL(FALSE, m_bRes);

            m_bRes = CxVolume::bIsReady(g_csVolumeePathWithoutSlash);
            xASSERT_EQUAL(FALSE, m_bRes);
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
                xASSERT_EQUAL(TRUE, m_bRes);

                m_bRes = CxVolume::bIsEmpty(g_csVolumeePathWithoutSlash);
                xASSERT_EQUAL(TRUE, m_bRes);
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
                xASSERT_EQUAL(FALSE, m_bRes);

                m_bRes = CxVolume::bIsEmpty(g_csVolumeePathWithoutSlash);
                xASSERT_EQUAL(FALSE, m_bRes);
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
            xASSERT_EQUAL(TRUE, m_bRes);
            xASSERT_LESS(0, ullAvailable);
            xASSERT_LESS(0, ullTotal);
            xASSERT_LESS(0, ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, NULL, NULL, NULL);
            xASSERT_EQUAL(TRUE, m_bRes);
            xASSERT_EQUAL(0, ullAvailable);
            xASSERT_EQUAL(0, ullTotal);
            xASSERT_EQUAL(0, ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, &ullAvailable, &ullTotal, &ullFree);
            xASSERT_EQUAL(TRUE, m_bRes);
            xASSERT_LESS(0, ullAvailable);
            xASSERT_LESS(0, ullTotal);
            xASSERT_LESS(0, ullFree);

            //xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(CxConst::xSTR_EMPTY, &ullAvailable, &ullTotal, &ullFree);
            xASSERT_EQUAL(TRUE, m_bRes);
            xASSERT_LESS(0, ullAvailable);
            xASSERT_LESS(0, ullTotal);
            xASSERT_LESS(0, ullFree);

            //xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
        }
	}

	//-------------------------------------
	//dtGetType
    {
	    #if defined(xOS_WIN)
	        const tString csVolumePath = xT("C:");

	        CxVolume::EType dtRes = CxVolume::dtGetType(csVolumePath);
	        xASSERT_EQUAL(CxVolume::dtFixed, dtRes);
	    #elif defined(xOS_LINUX)
	        //TODO: xOS_LINUX
	    #endif
    }

	//-------------------------------------
	//bGetInfo
    {
	    #if defined(xOS_WIN)
	        const tString csVolumePath = xT("C:");
	    	tString szVolumeName;
	        ULONG   ulVolumeSerialNumber     = 0;
	        ULONG   ulMaximumComponentLength = 0;
	        ULONG   ulFileSystemFlags        = 0;
	        tString sFileSystemName;

	        m_bRes = CxVolume::bGetInfo(
	                            csVolumePath,
	                            &szVolumeName,
	                            &ulVolumeSerialNumber,
	                            &ulMaximumComponentLength,
	                            &ulFileSystemFlags,
	                            &sFileSystemName);
	        xASSERT_EQUAL(TRUE, m_bRes);
	    #elif defined(xOS_LINUX)
	        //TODO: xOS_LINUX
	    #endif
    }

	//-------------------------------------
	//bGetLogicalDrives
	{
        #if defined(xOS_WIN)
            std::vector<tString> vecsDrives;

            m_bRes = CxVolume::bGetLogicalDrives(&vecsDrives);
            xASSERT_EQUAL(TRUE, m_bRes);
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
            xASSERT_EQUAL(TRUE, m_bRes);
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
