/**
 * \file   CxTest_CxVolume.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxVolume.h>

#include <xLib/Core/CxConst.h>

//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxVolume::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxVolume::type", a_cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t csVolumePath = xT("C:");
        #elif xOS_ENV_UNIX
            std::ctstring_t csVolumePath = xT("/");
        #endif

        CxVolume::ExType dtRes = CxVolume(csVolumePath).type();
        xUNUSED(dtRes);
        // CxTracer() << xTRACE_VAR(dtRes);
        // TEST: xTEST_EQ(CxVolume::dtFixed, dtRes);
    }

    xTEST_CASE("CxVolume::label", a_cullCaseLoops)
    {
        std::vec_tstring_t vsVolumePaths;

        CxVolume::paths(&vsVolumePaths);

        xFOREACH(std::vec_tstring_t, it, vsVolumePaths) {
            m_sRv = CxVolume(*it).label();
            xTEST_NA(m_sRv);

            #if xTEST_IGNORE
                std::tcout << m_sRv << std::endl;
            #endif
        }
    }

    xTEST_CASE("CxVolume::isValid", a_cullCaseLoops)
    {
        // true
        {
            std::vec_tstring_t vsData;

            CxVolume::paths(&vsData);

            xFOREACH(std::vec_tstring_t, it, vsData) {
                m_bRv = CxVolume(*it).isValid();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t csData[] = {
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
                m_bRv = CxVolume(csData[i]).isValid();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxVolume::isReady", a_cullCaseLoops)
    {
        // true
        {
            #if   xOS_ENV_WIN
                std::ctstring_t  g_csVolumePathWithSlash     = xT("C:\\");
                std::ctstring_t  g_csVolumeePathWithoutSlash = xT("C:");
            #elif xOS_ENV_UNIX
                std::ctstring_t  g_csVolumePathWithSlash     = xT("/");
                std::ctstring_t  g_csVolumeePathWithoutSlash = xT("/");
            #endif

            m_bRv = CxVolume(g_csVolumePathWithSlash).isReady();
            xTEST_EQ(true, m_bRv);

            m_bRv = CxVolume(g_csVolumeePathWithoutSlash).isReady();
            xTEST_EQ(true, m_bRv);
        }

        // false
        {
            #if   xOS_ENV_WIN
                std::ctstring_t  g_csVolumePathWithSlash     = xT("B:\\");
                std::ctstring_t  g_csVolumeePathWithoutSlash = xT("B:");
            #elif xOS_ENV_UNIX
                std::ctstring_t  g_csVolumePathWithSlash     = xT("/mnqwioe54oq389cp3qm49/");
                std::ctstring_t  g_csVolumeePathWithoutSlash = xT("/mnqwioe54oq389cp3qm49");
            #endif

            m_bRv = CxVolume(g_csVolumePathWithSlash).isReady();
            xTEST_EQ(false, m_bRv);

            m_bRv = CxVolume(g_csVolumeePathWithoutSlash).isReady();
            xTEST_EQ(false, m_bRv);
        }
    }

    xTEST_CASE("CxVolume::isEmpty", a_cullCaseLoops)
    {
        // true
        {
            // TEST: CxVolume::bIsEmpty
            #if xTODO
                #if   xOS_ENV_WIN
                    std::ctstring_t  g_csVolumePathWithSlash     = xT("B:\\");
                    std::ctstring_t  g_csVolumeePathWithoutSlash = xT("B:");
                #elif xOS_ENV_UNIX
                    std::ctstring_t  g_csVolumePathWithSlash     = xT("/home/mnqwioe54oq389cp3qm49/");
                    std::ctstring_t  g_csVolumeePathWithoutSlash = xT("/home/mnqwioe54oq389cp3qm49");
                #endif

                m_bRv = CxVolume(g_csVolumePathWithSlash).bIsEmpty();
                xTEST_EQ(true, m_bRv);

                m_bRv = CxVolume(g_csVolumeePathWithoutSlash).bIsEmpty();
                xTEST_EQ(true, m_bRv);
            #endif
        }

        // false
        {
            #if   xOS_ENV_WIN
                std::ctstring_t  g_csVolumePathWithSlash     = xT("C:\\");
                std::ctstring_t  g_csVolumeePathWithoutSlash = xT("C:");
            #elif xOS_ENV_UNIX
                std::ctstring_t  g_csVolumePathWithSlash     = xT("/");
                std::ctstring_t  g_csVolumeePathWithoutSlash = xT("/FLASH_4GB/");
            #endif

            #if xTEMP_DISABLED
                m_bRv = CxVolume(g_csVolumePathWithSlash).bIsEmpty();
                xTEST_EQ(false, m_bRv);

                m_bRv = CxVolume(g_csVolumeePathWithoutSlash).bIsEmpty();
                xTEST_EQ(false, m_bRv);
            #endif
        }
    }

    xTEST_CASE("CxVolume::mount unMount", a_cullCaseLoops)
    {
    #if xTEST_IGNORE
        #if   xOS_ENV_WIN
            std::ctstring_t csSourcePath = xT("\\\\KSF\\Files\\INSTALL");
            std::ctstring_t csDestPath   = xT("T:");
        #elif xOS_ENV_UNIX
            std::ctstring_t csSourcePath = xT("~");
            std::ctstring_t csDestPath   = xT("~\test_volume");
        #endif

        CxVolume(csSourcePath).vMount(csDestPath);
        CxVolume(csDestPath).vUnMount(true);
    #endif
    }

    xTEST_CASE("CxVolume::space", a_cullCaseLoops)
    {
        std::vec_tstring_t vsData;

        CxVolume::paths(&vsData);

        xFOREACH(std::vec_tstring_t, it, vsData) {
            ulonglong_t ullAvailable = 0ULL;
            ulonglong_t ullTotal     = 0ULL;
            ulonglong_t ullFree      = 0ULL;

            xCHECK_DO(!CxVolume(*it).isReady(), continue);

            CxVolume::space(*it, &ullAvailable, &ullTotal, &ullFree);
            xTEST_DIFF(0ULL, ullAvailable);
            xTEST_DIFF(0ULL, ullTotal);
            xTEST_DIFF(0ULL, ullFree);
        }

        xFOREACH(std::vec_tstring_t, it, vsData) {
            ulonglong_t ullAvailable = 0ULL;
            ulonglong_t ullTotal     = 0ULL;
            ulonglong_t ullFree      = 0ULL;

            xCHECK_DO(!CxVolume(*it).isReady(), continue);

            CxVolume::space(*it, NULL, NULL, NULL);
            xTEST_DIFF(0ULL, ullAvailable);
            xTEST_DIFF(0ULL, ullTotal);
            xTEST_DIFF(0ULL, ullFree);
        }

        xFOREACH(std::vec_tstring_t, it, vsData) {
            ulonglong_t ullAvailable = 0ULL;
            ulonglong_t ullTotal     = 0ULL;
            ulonglong_t ullFree      = 0ULL;

            xCHECK_DO(!CxVolume(*it).isReady(), continue);

            CxVolume::space(*it, &ullAvailable, &ullTotal, &ullFree);
            xTEST_DIFF(0ULL, ullAvailable);
            xTEST_DIFF(0ULL, ullTotal);
            xTEST_DIFF(0ULL, ullFree);

            #if xTEST_IGNORE
                xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
            #endif
        }

        {
            ulonglong_t ullAvailable = 0ULL;
            ulonglong_t ullTotal     = 0ULL;
            ulonglong_t ullFree      = 0ULL;

            CxVolume::space(CxConst::strEmpty(), &ullAvailable, &ullTotal, &ullFree);
            xTEST_DIFF(0ULL, ullAvailable);
            xTEST_DIFF(0ULL, ullTotal);
            xTEST_DIFF(0ULL, ullFree);

            #if xTEST_IGNORE
                xTRACEV(xT("ullAvailable: %lld, ullTotal: %lld, ullFree: %lld"), ullAvailable, ullTotal, ullFree);
            #endif
        }
    }

    xTEST_CASE("CxVolume::paths", a_cullCaseLoops)
    {
        std::vec_tstring_t vsVolumePaths;

        CxVolume::paths(&vsVolumePaths);
        xTEST_EQ(false, vsVolumePaths.empty());
    }
}
//------------------------------------------------------------------------------
