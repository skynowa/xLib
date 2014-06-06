/**
 * \file   CxTest_CxVolume.cpp
 * \brief
 */


#include <Test/IO/CxTest_CxVolume.h>

#include <xLib/Core/CxConst.h>

//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxVolume::unit(
    culonglong_t &a_caseLoops
)
{
#if xENV_WIN
    xTEST_CASE("CxVolume::type", a_caseLoops)
    {

        std::ctstring_t volumePath = xT("C:");

        CxVolume::ExType dtRes = CxVolume(volumePath).type();
        xTEST_EQ(CxVolume::dtFixed, dtRes);
    }
#endif

    xTEST_CASE("CxVolume::fileSystem", a_caseLoops)
    {
        std::vec_tstring_t volumePaths;

        CxVolume::paths(&volumePaths);
        xTEST_EQ(false, volumePaths.empty());

        xFOREACH_CONST(std::vec_tstring_t, it_path, volumePaths) {
            m_sRv = CxVolume(*it_path).fileSystem();
            xUNUSED(m_sRv);

            // CxTrace() << xTRACE_VAR(m_sRv);
        }
    }

    xTEST_CASE("CxVolume::label", a_caseLoops)
    {
        std::vec_tstring_t volumePaths;

        CxVolume::paths(&volumePaths);

        xFOREACH(std::vec_tstring_t, it, volumePaths) {
            m_sRv = CxVolume(*it).label();
            xTEST_NA(m_sRv);

            #if xTEST_IGNORE
                std::tcout << m_sRv << std::endl;
            #endif
        }
    }

    xTEST_CASE("CxVolume::isValid", a_caseLoops)
    {
        // true
        {
            std::vec_tstring_t volumePaths;

            CxVolume::paths(&volumePaths);

            xFOREACH(std::vec_tstring_t, it, volumePaths) {
                m_bRv = CxVolume(*it).isValid();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t data[] = {
                #if   xENV_WIN
                    xT("1"),
                    xT("0"),
                    xT("xxxxxx"),
                    xT("-C:"),
                    xT("*T")
                #elif xENV_UNIX
                    xT("1"),
                    xT("0"),
                    xT("xxxxxx"),
                    xT("-/etc"),
                    xT("*/home")
                #endif
            };

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                m_bRv = CxVolume(data[i]).isValid();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("CxVolume::isReady", a_caseLoops)
    {
        // true
        {
            #if   xENV_WIN
                std::ctstring_t volumePathWithSlash    = xT("C:\\");
                std::ctstring_t volumePathWithoutSlash = xT("C:");
            #elif xENV_UNIX
                std::ctstring_t volumePathWithSlash    = xT("/");
                std::ctstring_t volumePathWithoutSlash = xT("/");
            #endif

            m_bRv = CxVolume(volumePathWithSlash).isReady();
            xTEST_EQ(m_bRv, true);

            m_bRv = CxVolume(volumePathWithoutSlash).isReady();
            xTEST_EQ(m_bRv, true);
        }

        // false
        {
            #if   xENV_WIN
                std::ctstring_t volumePathWithSlash    = xT("B:\\");
                std::ctstring_t volumePathWithoutSlash = xT("B:");
            #elif xENV_UNIX
                std::ctstring_t volumePathWithSlash    = xT("/mnqwioe54oq389cp3qm49/");
                std::ctstring_t volumePathWithoutSlash = xT("/mnqwioe54oq389cp3qm49");
            #endif

            m_bRv = CxVolume(volumePathWithSlash).isReady();
            xTEST_EQ(m_bRv, false);

            m_bRv = CxVolume(volumePathWithoutSlash).isReady();
            xTEST_EQ(m_bRv, false);
        }
    }

    xTEST_CASE("CxVolume::isEmpty", a_caseLoops)
    {
        // true
        {
            // TEST: CxVolume::isEmpty()
            #if   xENV_WIN
                std::ctstring_t volumePathWithSlash    = xT("B:\\");
                std::ctstring_t volumePathWithoutSlash = xT("B:");
            #elif xENV_UNIX
                std::ctstring_t volumePathWithSlash    = xT("/home/mnqwioe54oq389cp3qm49/");
                std::ctstring_t volumePathWithoutSlash = xT("/home/mnqwioe54oq389cp3qm49");
            #endif

            m_bRv = CxVolume(volumePathWithSlash).isEmpty();
            xTEST_EQ(m_bRv, true);

            m_bRv = CxVolume(volumePathWithoutSlash).isEmpty();
            xTEST_EQ(m_bRv, true);
        }

        // false
        {
            #if   xENV_WIN
                std::ctstring_t volumePathWithSlash    = xT("C:\\");
                std::ctstring_t volumePathWithoutSlash = xT("C:");
            #elif xENV_UNIX
                std::ctstring_t volumePathWithSlash    = xT("/");
                std::ctstring_t volumePathWithoutSlash = xT("/FLASH_4GB/");
            #endif

            #if xTEMP_DISABLED
                m_bRv = CxVolume(volumePathWithSlash).isEmpty();
                xTEST_EQ(m_bRv, false);

                m_bRv = CxVolume(volumePathWithoutSlash).isEmpty();
                xTEST_EQ(m_bRv, false);
            #endif
        }
    }

    xTEST_CASE("CxVolume::mount unMount", a_caseLoops)
    {
    #if xTEST_IGNORE
        #if   xENV_WIN
            std::ctstring_t sourcePath = xT("\\\\KSF\\Files\\INSTALL");
            std::ctstring_t destPath   = xT("T:");
        #elif xENV_UNIX
            std::ctstring_t sourcePath = xT("~");
            std::ctstring_t destPath   = xT("~\test_volume");
        #endif

        CxVolume(sourcePath).mount(destPath);
        CxVolume(destPath).unMount(true);
    #endif
    }

    xTEST_CASE("CxVolume::isSpaceEnough", a_caseLoops)
    {
        std::vec_tstring_t volumes;
        volumes.push_back( CxSystemInfo().userHomeDir() );

        xFOREACH(std::vec_tstring_t, it, volumes) {
            const CxTestData2<ulonglong_t, bool_t> data[] = {
                {0ULL, true},
                {1ULL, true},
                {(std::numeric_limits<std::size_t>::max)(), false}
            };

            for (size_t i = 0; i < xARRAY_SIZE2(data); ++ i) {
                culonglong_t needBytes = data[i].test;
                cbool_t      bRv       = data[i].expect;

                CxVolume volume(*it);
                // xCHECK_DO(!volume.isReady(), continue);

                m_bRv = volume.isSpaceEnough(needBytes);
                xTEST_EQ(m_bRv, bRv);
            }
        }
    }

    xTEST_CASE("CxVolume::space", a_caseLoops)
    {
        std::vec_tstring_t volumePaths;
        volumePaths.push_back( CxSystemInfo().userHomeDir() );

        xFOREACH(std::vec_tstring_t, it, volumePaths) {
            ulonglong_t available = 0ULL;
            ulonglong_t total     = 0ULL;
            ulonglong_t free      = 0ULL;

            // xCHECK_DO(!CxVolume(*it).isReady(), continue);

            CxVolume::space(*it, &available, &total, &free);
            xTEST_DIFF(0ULL, available);
            xTEST_DIFF(0ULL, total);
            xTEST_DIFF(0ULL, free);
        }

        xFOREACH(std::vec_tstring_t, it, volumePaths) {
            ulonglong_t available = 0ULL;
            ulonglong_t total     = 0ULL;
            ulonglong_t free      = 0ULL;

            // xCHECK_DO(!CxVolume(*it).isReady(), continue);

            CxVolume::space(*it, NULL, NULL, NULL);
            xTEST_EQ(0ULL, available);
            xTEST_EQ(0ULL, total);
            xTEST_EQ(0ULL, free);
        }

        xFOREACH(std::vec_tstring_t, it, volumePaths) {
            ulonglong_t available = 0ULL;
            ulonglong_t total     = 0ULL;
            ulonglong_t free      = 0ULL;

            // xCHECK_DO(!CxVolume(*it).isReady(), continue);

            CxVolume::space(*it, &available, &total, &free);
            xTEST_DIFF(0ULL, available);
            xTEST_DIFF(0ULL, total);
            xTEST_DIFF(0ULL, free);

            #if xTEST_IGNORE
                xTRACEV(xT("available: %lld, total: %lld, free: %lld"), available, total, free);
            #endif
        }

        {
            ulonglong_t available = 0ULL;
            ulonglong_t total     = 0ULL;
            ulonglong_t free      = 0ULL;

            CxVolume::space(CxConst::strEmpty(), &available, &total, &free);
            xTEST_DIFF(0ULL, available);
            xTEST_DIFF(0ULL, total);
            xTEST_DIFF(0ULL, free);

            #if xTEST_IGNORE
                xTRACEV(xT("available: %lld, total: %lld, free: %lld"), available, total, free);
            #endif
        }
    }

    xTEST_CASE("CxVolume::paths", a_caseLoops)
    {
        std::vec_tstring_t volumePaths;

        CxVolume::paths(&volumePaths);
        xTEST_EQ(false, volumePaths.empty());
    }
}
//-------------------------------------------------------------------------------------------------
