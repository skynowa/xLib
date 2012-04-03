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
    // bIsValid
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            std::vector<std::tstring_t> vsData;

            m_bRes = CxVolume::bGetPaths(&vsData);

            xFOREACH(std::vector<std::tstring_t>, it, vsData) {
                m_bRes = CxVolume::bIsValid(*it);
                xTEST_EQ(true, m_bRes);
            }
        }

        //false
        {
            const std::tstring_t csData[] = {
                #if   xOS_ENV_WIN
                    xT("1"),
                    xT("0"),
                    xT("xxxxxx"),
                    xT("-C:"),
                    xT("*T")
                #elif xOS_ENV_UNIX
                    xT("1"),
                    xT("0"),
                    xT("xxxxxx"),
                    xT("-/etc"),
                    xT("*/home")
                #endif
            };

            for (size_t i = 0; i < xARRAY_SIZE(csData); ++ i) {
                m_bRes = CxVolume::bIsValid(csData[i]);
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //-------------------------------------
    // bIsReady
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
    // bIsEmpty
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
    // bGetSpace
    xTEST_CASE(cullCaseLoops)
    {
        std::vector<std::tstring_t> vsData;

        m_bRes = CxVolume::bGetPaths(&vsData);

        xFOREACH(std::vector<std::tstring_t>, it, vsData) {
            ulonglong_t ullAvailable = 0ULL;
            ulonglong_t ullTotal     = 0ULL;
            ulonglong_t ullFree      = 0ULL;

            xCHECK_DO(false == CxVolume::bIsReady(*it), continue);

            m_bRes = CxVolume::bGetSpace(*it, &ullAvailable, &ullTotal, &ullFree);
            xTEST_EQ(true, m_bRes);
            xTEST_LESS_EQ(0ULL, ullAvailable);
            xTEST_LESS_EQ(0ULL, ullTotal);
            xTEST_LESS_EQ(0ULL, ullFree);
        }

        xFOREACH(std::vector<std::tstring_t>, it, vsData) {
            ulonglong_t ullAvailable = 0ULL;
            ulonglong_t ullTotal     = 0ULL;
            ulonglong_t ullFree      = 0ULL;

            xCHECK_DO(false == CxVolume::bIsReady(*it), continue);

            m_bRes = CxVolume::bGetSpace(*it, NULL, NULL, NULL);
            xTEST_EQ(true, m_bRes);
            xTEST_LESS_EQ(0ULL, ullAvailable);
            xTEST_LESS_EQ(0ULL, ullTotal);
            xTEST_LESS_EQ(0ULL, ullFree);
        }

        xFOREACH(std::vector<std::tstring_t>, it, vsData) {
            ulonglong_t ullAvailable = 0ULL;
            ulonglong_t ullTotal     = 0ULL;
            ulonglong_t ullFree      = 0ULL;

            xCHECK_DO(false == CxVolume::bIsReady(*it), continue);

            m_bRes = CxVolume::bGetSpace(*it, &ullAvailable, &ullTotal, &ullFree);
            xTEST_EQ(true, m_bRes);
            xTEST_LESS_EQ(0ULL, ullAvailable);
            xTEST_LESS_EQ(0ULL, ullTotal);
            xTEST_LESS_EQ(0ULL, ullFree);

            #if xTEST_IGNORE
                xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
            #endif
        }

        {
            ulonglong_t ullAvailable = 0ULL;
            ulonglong_t ullTotal     = 0ULL;
            ulonglong_t ullFree      = 0ULL;

            m_bRes = CxVolume::bGetSpace(CxConst::xSTR_EMPTY, &ullAvailable, &ullTotal, &ullFree);
            xTEST_EQ(true, m_bRes);
            xTEST_LESS_EQ(0ULL, ullAvailable);
            xTEST_LESS_EQ(0ULL, ullTotal);
            xTEST_LESS_EQ(0ULL, ullFree);

            #if xTEST_IGNORE
                xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
            #endif
        }
    }

    //-------------------------------------
    // bMount, bUnMount
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
    // bGetPaths
    xTEST_CASE(cullCaseLoops)
    {
        std::vector<std::tstring_t> vsVolumePaths;

        m_bRes = CxVolume::bGetPaths(&vsVolumePaths);
        xTEST_EQ(true, m_bRes);

        #if xTEST_IGNORE
            std::tcout << vsVolumePaths << std::endl;
        #endif
    }


    //--------------------------------------------------
    // sGetLabel
    xTEST_CASE(cullCaseLoops)
    {
        std::vector<std::tstring_t> vsVolumePaths;

        m_bRes = CxVolume::bGetPaths(&vsVolumePaths);
        xTEST_EQ(true, m_bRes);

        xFOREACH(std::vector<std::tstring_t>, it, vsVolumePaths) {
            m_sRes = CxVolume::sGetLabel(*it);
            // n/a
            #if xTEST_IGNORE
                std::tcout << m_sRes << std::endl;
            #endif
        }
    }

    //--------------------------------------------------
    // bSetLabel
    xTEST_CASE(cullCaseLoops)
    {
        std::vector<std::tstring_t> vsVolumePaths;

        m_bRes = CxVolume::bGetPaths(&vsVolumePaths);
        xTEST_EQ(true, m_bRes);

        xFOREACH(std::vector<std::tstring_t>, it, vsVolumePaths) {
            m_sRes = CxVolume::sGetLabel(*it);

            xCHECK_DO(false == CxVolume::bIsReady(*it), continue);

            m_bRes = CxVolume::bSetLabel(*it, m_sRes);
            xTEST_EQ(true, m_bRes);
        }
    }

    //-------------------------------------
    // dtGetType
    xTEST_CASE(cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            const std::tstring_t csVolumePath = xT("C:");
        #elif xOS_ENV_UNIX
            const std::tstring_t csVolumePath = xT("\\");
        #endif

        CxVolume::EType dtRes = CxVolume::dtGetType(csVolumePath);
        xTEST_EQ(CxVolume::dtFixed, dtRes);
    }

    //--------------------------------------------------
    // bGetInfo
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            std::vector<std::tstring_t> vsVolumes;

            m_bRes = CxVolume::bGetPaths(&vsVolumes);
            xTEST_EQ(true, m_bRes);

            for (size_t i = 0; i < vsVolumes.size(); ++ i) {
                xCHECK_DO(false == CxVolume::bIsReady(vsVolumes.at(i)), continue);

                std::tstring_t  sDrivePath               = vsVolumes.at(i);
                std::tstring_t  sVolumeName;
                ulong_t         ulVolumeSerialNumber     = 0UL;
                ulong_t         ulMaximumComponentLength = 0UL;
                ulong_t         ulFileSystemFlags        = 0UL;
                std::tstring_t  sFileSystemName;

                m_bRes  = CxVolume::bGetInfo(sDrivePath,
                                             &sVolumeName,
                                             &ulVolumeSerialNumber,
                                             &ulMaximumComponentLength,
                                             &ulFileSystemFlags,
                                             &sFileSystemName);
                xTEST_EQ(true, m_bRes);
            }
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
