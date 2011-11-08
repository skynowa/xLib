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
CxTest_CxVolume::CxTest_CxVolume() {

}
//---------------------------------------------------------------------------
CxTest_CxVolume::~CxTest_CxVolume() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxVolume::bUnit(
    const ULONGLONG cullBlockLoops
)
{
	//-------------------------------------
	//bIsReady
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            #if defined(xOS_ENV_WIN)
                const std::tstring  g_csVolumePathWithSlash     = xT("C:\\");
                const std::tstring  g_csVolumeePathWithoutSlash = xT("C:");
            #elif defined(xOS_ENV_UNIX)
                const std::tstring  g_csVolumePathWithSlash     = xT("/");
                const std::tstring  g_csVolumeePathWithoutSlash = xT("/");
            #endif

            m_bRes = CxVolume::bIsReady(g_csVolumePathWithSlash);
            xASSERT_DIFF(FALSE, m_bRes);

            m_bRes = CxVolume::bIsReady(g_csVolumeePathWithoutSlash);
            xASSERT_DIFF(FALSE, m_bRes);
        }

        //FALSE
        {
            #if defined(xOS_ENV_WIN)
                const std::tstring  g_csVolumePathWithSlash     = xT("B:\\");
                const std::tstring  g_csVolumeePathWithoutSlash = xT("B:");
            #elif defined(xOS_ENV_UNIX)
                const std::tstring  g_csVolumePathWithSlash     = xT("/mnqwioe54oq389cp3qm49/");
                const std::tstring  g_csVolumeePathWithoutSlash = xT("/mnqwioe54oq389cp3qm49");
            #endif

            m_bRes = CxVolume::bIsReady(g_csVolumePathWithSlash);
            xASSERT_EQ(FALSE, m_bRes);

            m_bRes = CxVolume::bIsReady(g_csVolumeePathWithoutSlash);
            xASSERT_EQ(FALSE, m_bRes);
        }
    }

	//-------------------------------------
	//bIsEmpty
    xTEST_BLOCK(cullBlockLoops)
	{
        //TRUE
        {
            #if xTODO
                #if defined(xOS_ENV_WIN)
                    const std::tstring  g_csVolumePathWithSlash     = xT("B:\\");
                    const std::tstring  g_csVolumeePathWithoutSlash = xT("B:");
                #elif defined(xOS_ENV_UNIX)
                    const std::tstring  g_csVolumePathWithSlash     = xT("/home/mnqwioe54oq389cp3qm49/");
                    const std::tstring  g_csVolumeePathWithoutSlash = xT("/home/mnqwioe54oq389cp3qm49");
                #endif

                m_bRes = CxVolume::bIsEmpty(g_csVolumePathWithSlash);
                xASSERT_DIFF(FALSE, m_bRes);

                m_bRes = CxVolume::bIsEmpty(g_csVolumeePathWithoutSlash);
                xASSERT_DIFF(FALSE, m_bRes);
            #endif
        }

        //FALSE
        {
            #if defined(xOS_ENV_WIN)
                const std::tstring  g_csVolumePathWithSlash     = xT("C:\\");
                const std::tstring  g_csVolumeePathWithoutSlash = xT("C:");
            #elif defined(xOS_ENV_UNIX)
                const std::tstring  g_csVolumePathWithSlash     = xT("/");
                const std::tstring  g_csVolumeePathWithoutSlash = xT("/FLASH_4GB/");
            #endif

            #if xTEMP_DISABLED
                m_bRes = CxVolume::bIsEmpty(g_csVolumePathWithSlash);
                xASSERT_EQ(FALSE, m_bRes);

                m_bRes = CxVolume::bIsEmpty(g_csVolumeePathWithoutSlash);
                xASSERT_EQ(FALSE, m_bRes);
            #endif
        }
    }

	//-------------------------------------
	//bGetFreeSpace
    xTEST_BLOCK(cullBlockLoops)
	{
        #if defined(xOS_ENV_WIN)
            const std::tstring  csVolumePathWithSlash     = xT("C:\\");
            const std::tstring  csVolumeePathWithoutSlash = xT("C:");
        #elif defined(xOS_ENV_UNIX)
            const std::tstring  csVolumePathWithSlash     = xT("/");
            const std::tstring  csVolumeePathWithoutSlash = xT("//");
        #endif

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, &ullAvailable, &ullTotal, &ullFree);
            xASSERT_DIFF(FALSE, m_bRes);
            xASSERT_LESS(0ULL, ullAvailable);
            xASSERT_LESS(0ULL, ullTotal);
            xASSERT_LESS(0ULL, ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, NULL, NULL, NULL);
            xASSERT_DIFF(FALSE, m_bRes);
            xASSERT_EQ(0ULL, ullAvailable);
            xASSERT_EQ(0ULL, ullTotal);
            xASSERT_EQ(0ULL, ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, &ullAvailable, &ullTotal, &ullFree);
            xASSERT_DIFF(FALSE, m_bRes);
            xASSERT_LESS(0ULL, ullAvailable);
            xASSERT_LESS(0ULL, ullTotal);
            xASSERT_LESS(0ULL, ullFree);

            //xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
        }

        {
            ULONGLONG ullAvailable = 0;
            ULONGLONG ullTotal     = 0;
            ULONGLONG ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(CxConst::xSTR_EMPTY, &ullAvailable, &ullTotal, &ullFree);
            xASSERT_DIFF(FALSE, m_bRes);
            xASSERT_LESS(0ULL, ullAvailable);
            xASSERT_LESS(0ULL, ullTotal);
            xASSERT_LESS(0ULL, ullFree);

            //xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
        }
	}

	//-------------------------------------
	//dtGetType
    xTEST_BLOCK(cullBlockLoops)
    {
	    #if defined(xOS_ENV_WIN)
	        const std::tstring csVolumePath = xT("C:");

	        CxVolume::EType dtRes = CxVolume::dtGetType(csVolumePath);
	        xASSERT_EQ(CxVolume::dtFixed, dtRes);
	    #elif defined(xOS_ENV_UNIX)
	        //TODO: xOS_ENV_UNIX
	    #endif
    }

	//-------------------------------------
	//bGetInfo
    xTEST_BLOCK(cullBlockLoops)
    {
	    #if defined(xOS_ENV_WIN)
	        const std::tstring csVolumePath = xT("C:");
	    	std::tstring szVolumeName;
	        ULONG   ulVolumeSerialNumber     = 0;
	        ULONG   ulMaximumComponentLength = 0;
	        ULONG   ulFileSystemFlags        = 0;
	        std::tstring sFileSystemName;

	        m_bRes = CxVolume::bGetInfo(
	                            csVolumePath,
	                            &szVolumeName,
	                            &ulVolumeSerialNumber,
	                            &ulMaximumComponentLength,
	                            &ulFileSystemFlags,
	                            &sFileSystemName);
	        xASSERT_DIFF(FALSE, m_bRes);
	    #elif defined(xOS_ENV_UNIX)
	        //TODO: xOS_ENV_UNIX
	    #endif
    }

	//-------------------------------------
	//bGetLogicalDrives
    xTEST_BLOCK(cullBlockLoops)
	{
        #if defined(xOS_ENV_WIN)
            std::vector<std::tstring> vsDrives;

            m_bRes = CxVolume::bGetLogicalDrives(&vsDrives);
            xASSERT_DIFF(FALSE, m_bRes);
        #elif defined(xOS_ENV_UNIX)
            //TODO: xOS_ENV_UNIX
        #endif
	}

	//-------------------------------------
	//bGetLogicalDrives2
    xTEST_BLOCK(cullBlockLoops)
	{
        #if defined(xOS_ENV_WIN)
            std::vector<std::tstring> vsDrives;

            m_bRes = CxVolume::bGetLogicalDrives(&vsDrives, CxVolume::dtFixed);
            xASSERT_DIFF(FALSE, m_bRes);
        #elif defined(xOS_ENV_UNIX)
            //TODO: xOS_ENV_UNIX
        #endif
	}

	//-------------------------------------
	//bDefineDosDevice
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//bDeleteVolumeMountPoint
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//hFindFirstVolume
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//hFindFirstVolumeMountPoint
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//sFindNextVolume
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//bFindNextVolumeMountPoint
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//bFindVolumeClose
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//bFindVolumeMountPointClose
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//sGetLogicalStrings
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//sGetVolumeNameForVolumeMountPoint
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//sGetVolumePathName
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//sGetVolumePathNamesForVolumeName
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//sQueryDosDevice
    xTEST_BLOCK(cullBlockLoops)
    {

    }

	//-------------------------------------
	//bSetVolumeLabel
    xTEST_BLOCK(cullBlockLoops)
	{

	}

	//-------------------------------------
	//bSetVolumeMountPoint
    xTEST_BLOCK(cullBlockLoops)
	{

	}

    return TRUE;
}
//---------------------------------------------------------------------------
