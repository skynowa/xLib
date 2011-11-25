/**
 * \file   CxTest_CxVolume.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxVolume.h>


//---------------------------------------------------------------------------
CxTest_CxVolume::CxTest_CxVolume() {

}
//---------------------------------------------------------------------------
CxTest_CxVolume::~CxTest_CxVolume() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxVolume::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    //-------------------------------------
    //bIsReady
    xTEST_CASE(cullBlockLoops)
    {
        //true
        {
            #if xOS_ENV_WIN
                const std::tstring_t  g_csVolumePathWithSlash     = xT("C:\\");
                const std::tstring_t  g_csVolumeePathWithoutSlash = xT("C:");
            #elif xOS_ENV_UNIX
                const std::tstring_t  g_csVolumePathWithSlash     = xT("/");
                const std::tstring_t  g_csVolumeePathWithoutSlash = xT("/");
            #endif

            m_bRes = CxVolume::bIsReady(g_csVolumePathWithSlash);
            xTEST_EQ(true, m_bRes);

            m_bRes = CxVolume::bIsReady(g_csVolumeePathWithoutSlash);
            xTEST_EQ(true, m_bRes);
        }

        //false
        {
            #if xOS_ENV_WIN
                const std::tstring_t  g_csVolumePathWithSlash     = xT("B:\\");
                const std::tstring_t  g_csVolumeePathWithoutSlash = xT("B:");
            #elif xOS_ENV_UNIX
                const std::tstring_t  g_csVolumePathWithSlash     = xT("/mnqwioe54oq389cp3qm49/");
                const std::tstring_t  g_csVolumeePathWithoutSlash = xT("/mnqwioe54oq389cp3qm49");
            #endif

            m_bRes = CxVolume::bIsReady(g_csVolumePathWithSlash);
            xTEST_EQ(false, m_bRes);

            m_bRes = CxVolume::bIsReady(g_csVolumeePathWithoutSlash);
            xTEST_EQ(false, m_bRes);
        }
    }

    //-------------------------------------
    //bIsEmpty
    xTEST_CASE(cullBlockLoops)
    {
        //true
        {
            #if xTODO
                #if xOS_ENV_WIN
                    const std::tstring_t  g_csVolumePathWithSlash     = xT("B:\\");
                    const std::tstring_t  g_csVolumeePathWithoutSlash = xT("B:");
                #elif xOS_ENV_UNIX
                    const std::tstring_t  g_csVolumePathWithSlash     = xT("/home/mnqwioe54oq389cp3qm49/");
                    const std::tstring_t  g_csVolumeePathWithoutSlash = xT("/home/mnqwioe54oq389cp3qm49");
                #endif

                m_bRes = CxVolume::bIsEmpty(g_csVolumePathWithSlash);
                xTEST_EQ(true, m_bRes);

                m_bRes = CxVolume::bIsEmpty(g_csVolumeePathWithoutSlash);
                xTEST_EQ(true, m_bRes);
            #endif
        }

        //false
        {
            #if xOS_ENV_WIN
                const std::tstring_t  g_csVolumePathWithSlash     = xT("C:\\");
                const std::tstring_t  g_csVolumeePathWithoutSlash = xT("C:");
            #elif xOS_ENV_UNIX
                const std::tstring_t  g_csVolumePathWithSlash     = xT("/");
                const std::tstring_t  g_csVolumeePathWithoutSlash = xT("/FLASH_4GB/");
            #endif

            #if xTEMP_DISABLED
                m_bRes = CxVolume::bIsEmpty(g_csVolumePathWithSlash);
                xTEST_EQ(false, m_bRes);

                m_bRes = CxVolume::bIsEmpty(g_csVolumeePathWithoutSlash);
                xTEST_EQ(false, m_bRes);
            #endif
        }
    }

    //-------------------------------------
    //bGetFreeSpace
    xTEST_CASE(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t  csVolumePathWithSlash     = xT("C:\\");
            const std::tstring_t  csVolumeePathWithoutSlash = xT("C:");
        #elif xOS_ENV_UNIX
            const std::tstring_t  csVolumePathWithSlash     = xT("/");
            const std::tstring_t  csVolumeePathWithoutSlash = xT("//");
        #endif

        {
            ulonglong_t ullAvailable = 0;
            ulonglong_t ullTotal     = 0;
            ulonglong_t ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, &ullAvailable, &ullTotal, &ullFree);
            xTEST_EQ(true, m_bRes);
            xTEST_LESS(0ULL, ullAvailable);
            xTEST_LESS(0ULL, ullTotal);
            xTEST_LESS(0ULL, ullFree);
        }

        {
            ulonglong_t ullAvailable = 0;
            ulonglong_t ullTotal     = 0;
            ulonglong_t ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, NULL, NULL, NULL);
            xTEST_EQ(true, m_bRes);
            xTEST_EQ(0ULL, ullAvailable);
            xTEST_EQ(0ULL, ullTotal);
            xTEST_EQ(0ULL, ullFree);
        }

        {
            ulonglong_t ullAvailable = 0;
            ulonglong_t ullTotal     = 0;
            ulonglong_t ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(csVolumePathWithSlash, &ullAvailable, &ullTotal, &ullFree);
            xTEST_EQ(true, m_bRes);
            xTEST_LESS(0ULL, ullAvailable);
            xTEST_LESS(0ULL, ullTotal);
            xTEST_LESS(0ULL, ullFree);

            //xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
        }

        {
            ulonglong_t ullAvailable = 0;
            ulonglong_t ullTotal     = 0;
            ulonglong_t ullFree      = 0;

            m_bRes = CxVolume::bGetFreeSpace(CxConst::xSTR_EMPTY, &ullAvailable, &ullTotal, &ullFree);
            xTEST_EQ(true, m_bRes);
            xTEST_LESS(0ULL, ullAvailable);
            xTEST_LESS(0ULL, ullTotal);
            xTEST_LESS(0ULL, ullFree);

            //xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
        }
    }

    //-------------------------------------
    //dtGetType
    xTEST_CASE(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t csVolumePath = xT("C:");

            CxVolume::EType dtRes = CxVolume::dtGetType(csVolumePath);
            xTEST_EQ(CxVolume::dtFixed, dtRes);
        #elif xOS_ENV_UNIX
            //TODO: xOS_ENV_UNIX
        #endif
    }

    //-------------------------------------
    //bGetInfo
    xTEST_CASE(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t csVolumePath = xT("C:");
            std::tstring_t szVolumeName;
            ulong_t   ulVolumeSerialNumber     = 0;
            ulong_t   ulMaximumComponentLength = 0;
            ulong_t   ulFileSystemFlags        = 0;
            std::tstring_t sFileSystemName;

            m_bRes = CxVolume::bGetInfo(
                                csVolumePath,
                                &szVolumeName,
                                &ulVolumeSerialNumber,
                                &ulMaximumComponentLength,
                                &ulFileSystemFlags,
                                &sFileSystemName);
            xTEST_EQ(true, m_bRes);
        #elif xOS_ENV_UNIX
            //TODO: xOS_ENV_UNIX
        #endif
    }

    //-------------------------------------
    //bGetLogicalDrives
    xTEST_CASE(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            std::vector<std::tstring_t> vsDrives;

            m_bRes = CxVolume::bGetLogicalDrives(&vsDrives);
            xTEST_EQ(true, m_bRes);
        #elif xOS_ENV_UNIX
            //TODO: xOS_ENV_UNIX
        #endif
    }

    //-------------------------------------
    //bGetLogicalDrives2
    xTEST_CASE(cullBlockLoops)
    {
        #if xOS_ENV_WIN
            std::vector<std::tstring_t> vsDrives;

            m_bRes = CxVolume::bGetLogicalDrives(&vsDrives, CxVolume::dtFixed);
            xTEST_EQ(true, m_bRes);
        #elif xOS_ENV_UNIX
            //TODO: xOS_ENV_UNIX
        #endif
    }

    //-------------------------------------
    //bDefineDosDevice
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //bDeleteVolumeMountPoint
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //hFindFirstVolume
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //hFindFirstVolumeMountPoint
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //sFindNextVolume
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //bFindNextVolumeMountPoint
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //bFindVolumeClose
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //bFindVolumeMountPointClose
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //sGetLogicalStrings
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //sGetVolumeNameForVolumeMountPoint
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //sGetVolumePathName
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //sGetVolumePathNamesForVolumeName
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //sQueryDosDevice
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //bSetVolumeLabel
    xTEST_CASE(cullBlockLoops)
    {

    }

    //-------------------------------------
    //bSetVolumeMountPoint
    xTEST_CASE(cullBlockLoops)
    {

    }

    return true;
}
//---------------------------------------------------------------------------
