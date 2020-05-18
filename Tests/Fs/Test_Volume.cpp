/**
 * \file   Test_Volume.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Volume)
xTEST_UNIT(Test_Volume)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Volume::unit()
{
#if xENV_WIN
    xTEST_CASE("type")
    {

        std::ctstring_t volumePath = xT("C:");

        Volume::Type dtRes = Volume(volumePath).type();
        xTEST_EQ(Volume::dtFixed, dtRes);
    }
#endif

    xTEST_CASE("fileSystem")
    {
        std::vec_tstring_t volumePaths;

        Volume::paths(&volumePaths);
        xTEST_EQ(false, volumePaths.empty());

        for (auto &it : volumePaths) {
            m_sRv = Volume(it).fileSystem();
            xUNUSED(m_sRv);

            // Trace() << xTRACE_VAR(m_sRv);
        }
    }

    xTEST_CASE("label")
    {
        std::vec_tstring_t volumePaths;

        Volume::paths(&volumePaths);

        for (auto &it : volumePaths) {
            m_sRv = Volume(it).label();
            xTEST_NA(m_sRv);

            // Trace() << xTRACE_VAR(m_sRv);
        }
    }

    xTEST_CASE("isValid")
    {
        // true
        {
            std::vec_tstring_t volumePaths;

            Volume::paths(&volumePaths);

            for (auto &it : volumePaths) {
                m_bRv = Volume(it).isValid();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t data[]
			{
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
                m_bRv = Volume(data[i]).isValid();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("isReady")
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

            m_bRv = Volume(volumePathWithSlash).isReady();
            xTEST_EQ(m_bRv, true);

            m_bRv = Volume(volumePathWithoutSlash).isReady();
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

            m_bRv = Volume(volumePathWithSlash).isReady();
            xTEST_EQ(m_bRv, false);

            m_bRv = Volume(volumePathWithoutSlash).isReady();
            xTEST_EQ(m_bRv, false);
        }
    }

    xTEST_CASE("isEmpty")
    {
        // true
        {
            // TEST: Volume::isEmpty()
        #if   xENV_WIN
            std::ctstring_t volumePathWithSlash    = xT("B:\\");
            std::ctstring_t volumePathWithoutSlash = xT("B:");
        #elif xENV_UNIX
            std::ctstring_t volumePathWithSlash    = xT("/home/mnqwioe54oq389cp3qm49/");
            std::ctstring_t volumePathWithoutSlash = xT("/home/mnqwioe54oq389cp3qm49");
        #endif

            m_bRv = Volume(volumePathWithSlash).isEmpty();
            xTEST_EQ(m_bRv, true);

            m_bRv = Volume(volumePathWithoutSlash).isEmpty();
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
            m_bRv = Volume(volumePathWithSlash).isEmpty();
            xTEST_EQ(m_bRv, false);

            m_bRv = Volume(volumePathWithoutSlash).isEmpty();
            xTEST_EQ(m_bRv, false);
        #endif
        }
    }

    xTEST_CASE("mount, unMount")
    {
    #if xTEST_IGNORE
    #if   xENV_WIN
        std::ctstring_t sourcePath = xT("\\\\KSF\\Files\\INSTALL");
        std::ctstring_t destPath   = xT("T:");
    #elif xENV_UNIX
        std::ctstring_t sourcePath = xT("~");
        std::ctstring_t destPath   = xT("~\test_volume");
    #endif

        Volume(sourcePath).mount(destPath);
        Volume(destPath).unMount(true);
    #endif
    }

    xTEST_CASE("isSpaceEnough")
    {
        std::vec_tstring_t volumes;
        volumes.push_back( User().homeDir() );

        for (auto &it : volumes) {
            const Data2<ulonglong_t, bool_t> data[]
			{
                {0ULL, true},
                {1ULL, true},
                {(std::numeric_limits<std::size_t>::max)(), false}
            };

            for (size_t i = 0; i < Utils::arraySizeT(data); ++ i) {
                culonglong_t needBytes = data[i].test;
                cbool_t      bRv       = data[i].expect;

                Volume volume(it);
                // xCHECK_DO(!volume.isReady(), continue);

                m_bRv = volume.isSpaceEnough(needBytes);
                xTEST_EQ(m_bRv, bRv);
            }
        }
    }

    xTEST_CASE("space")
    {
        std::vec_tstring_t volumePaths;
        volumePaths.push_back( User().homeDir() );

        for (auto &it : volumePaths) {
            ulonglong_t available {};
            ulonglong_t total     {};
            ulonglong_t free      {};

            // xCHECK_DO(!Volume(it).isReady(), continue);

            Volume::space(it, &available, &total, &free);
            xTEST_DIFF(0ULL, available);
            xTEST_DIFF(0ULL, total);
            xTEST_DIFF(0ULL, free);
        }

        for (auto &it : volumePaths) {
            ulonglong_t available {};
            ulonglong_t total     {};
            ulonglong_t free      {};

            // xCHECK_DO(!Volume(it).isReady(), continue);

            Volume::space(it, nullptr, nullptr, nullptr);
            xTEST_EQ(0ULL, available);
            xTEST_EQ(0ULL, total);
            xTEST_EQ(0ULL, free);
        }

        for (auto &it : volumePaths) {
            ulonglong_t available {};
            ulonglong_t total     {};
            ulonglong_t free      {};

            // xCHECK_DO(!Volume(it).isReady(), continue);

            Volume::space(it, &available, &total, &free);
            xTEST_DIFF(0ULL, available);
            xTEST_DIFF(0ULL, total);
            xTEST_DIFF(0ULL, free);

            Cout() << xTRACE_VAR_3(available, total, free);
        }

        {
            ulonglong_t available {};
            ulonglong_t total     {};
            ulonglong_t free      {};

            Volume::space(Const::strEmpty(), &available, &total, &free);
            xTEST_DIFF(0ULL, available);
            xTEST_DIFF(0ULL, total);
            xTEST_DIFF(0ULL, free);

            Cout() << xTRACE_VAR_3(available, total, free);
        }
    }

    xTEST_CASE("paths")
    {
        std::vec_tstring_t volumePaths;

        Volume::paths(&volumePaths);
        xTEST_EQ(false, volumePaths.empty());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
