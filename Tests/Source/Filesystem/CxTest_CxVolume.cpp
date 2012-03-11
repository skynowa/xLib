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
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //bIsReady
    xTEST_CASE(cullCaseLoops)
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
    xTEST_CASE(cullCaseLoops)
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
    xTEST_CASE(cullCaseLoops)
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
    //bMount, bUnMount
    xTEST_CASE(cullCaseLoops)
    {
#if xTEST_IGNORE
        #if xOS_ENV_WIN
            const std::tstring_t csSourcePath = xT("\\\\KSF\\Files\\INSTALL");
            const std::tstring_t csDestPath   = xT("T:");
        #elif xOS_ENV_UNIX
            const std::tstring_t csSourcePath = xT("~");
            const std::tstring_t csDestPath   = xT("~\test_volume");
        #endif

        m_bRes = CxVolume::bMount(csSourcePath, csDestPath);
        xTEST_EQ(true, m_bRes);

        m_bRes = CxVolume::bUnMount(csDestPath, true);
        xTEST_EQ(true, m_bRes);
#endif
    }

    //-------------------------------------
    //dtGetType
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t csVolumePath = xT("C:");

            CxVolume::EType dtRes = CxVolume::dtGetType(csVolumePath);
            xTEST_EQ(CxVolume::dtFixed, dtRes);
        #endif
    }

    //-------------------------------------
    //bGetLogicalDrives
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            std::vector<std::tstring_t> vsDrives;

            m_bRes = CxVolume::bGetLogicalDrives(&vsDrives);
            xTEST_EQ(true, m_bRes);

            #if xTEST_IGNORE
                std::tcout << vsDrives << std::endl;
            #endif
        #endif
    }

    //-------------------------------------
    //bIsValidDriveLetter
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            {
                std::tstring_t sDataTrue = xT("qwertyuiopasdfghjklzxcvbnm");

                for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                    m_bRes = CxVolume::bIsValidDriveLetter( sDataTrue.at(i) );
                    xTEST_EQ(true, m_bRes);
                }
            }

            {
                std::tstring_t sDataFalse = xT("1234567890-=/*-+!@#$%^&*()_+:\"<>?|");

                for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                    m_bRes = CxVolume::bIsValidDriveLetter( sDataFalse.at(i) );
                    xTEST_EQ(false, m_bRes);
                }
            }
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
