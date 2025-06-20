/**
 * \file   Test_Volume.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Volume)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Volume::unit()
{
    xTEST_CASE("type")
    {
        std::ctstring_t volumePath =
		#if xENV_WIN
			xT("C:");
		#else
			xT("/");
		#endif

        Volume::Type dtRes = Volume(volumePath).type();
        xTEST_EQ((int)Volume::Type::Fixed, (int)dtRes);
    }

    xTEST_CASE("fileSystem")
    {
        std::vec_tstring_t volumePaths;
        Volume::paths(&volumePaths);
        xTEST(!volumePaths.empty());

        for (const auto &itvolumePath : volumePaths) {
            m_sRv = Volume(itvolumePath).fileSystem();
            xTEST(!m_sRv.empty());
        }

		m_sRv = Volume("/").fileSystem();
		xTEST(!m_sRv.empty());
		LogCout() << xTRACE_VAR(m_sRv);
    }

    xTEST_CASE("label")
    {
        std::vec_tstring_t volumePaths;
        Volume::paths(&volumePaths);

        for (const auto &it : volumePaths) {
            m_sRv = Volume(it).label();
            xTEST_NA(m_sRv);
        }
    }

    xTEST_CASE("isValid")
    {
        // true
        {
            std::vec_tstring_t volumePaths;
            Volume::paths(&volumePaths);

            for (const auto &it : volumePaths) {
                m_bRv = Volume(it).isValid();
                xTEST(m_bRv);
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
                xTEST(!m_bRv);
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
            xTEST(m_bRv);

            m_bRv = Volume(volumePathWithoutSlash).isReady();
            xTEST(m_bRv);
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
            xTEST(!m_bRv);

            m_bRv = Volume(volumePathWithoutSlash).isReady();
            xTEST(!m_bRv);
        }
    }

    xTEST_CASE("isEmpty")
    {
        // true
        {
        #if   xENV_WIN
            std::ctstring_t volumePathWithSlash    = xT("B:\\");
            std::ctstring_t volumePathWithoutSlash = xT("B:");
        #elif xENV_UNIX
            std::ctstring_t volumePathWithSlash    = xT("/home/mnqwioe54oq389cp3qm49/");
            std::ctstring_t volumePathWithoutSlash = xT("/home/mnqwioe54oq389cp3qm49");
        #endif

            m_bRv = Volume(volumePathWithSlash).isEmpty();
            xTEST(m_bRv);

            m_bRv = Volume(volumePathWithoutSlash).isEmpty();
            xTEST(m_bRv);
        }

        // false
        {
        #if   xENV_WIN
            std::ctstring_t volumePathWithSlash    = xT("C:\\");
            std::ctstring_t volumePathWithoutSlash = xT("C:");
        #elif xENV_UNIX
            std::ctstring_t volumePathWithSlash    = xT("/");
            std::ctstring_t volumePathWithoutSlash = xT("/tmp");
        #endif

            m_bRv = Volume(volumePathWithSlash).isEmpty();
            xTEST(!m_bRv);

            m_bRv = Volume(volumePathWithoutSlash).isEmpty();
            xTEST(!m_bRv);
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

    xTEST_CASE("isSpaceAvailable")
    {
        std::vec_tstring_t volumes;
        volumes.push_back( Path::homeDir().str() );

        for (const auto &it : volumes) {
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

                m_bRv = volume.isSpaceAvailable(needBytes);
                xTEST_EQ(m_bRv, bRv);
            }
        }
    }

    xTEST_CASE("space")
    {
        std::vec_tstring_t volumePaths;
        volumePaths.push_back( Path::homeDir().str() );

        for (const auto &it : volumePaths) {
            // xCHECK_DO(!Volume(it).isReady(), continue);

            ulonglong_t total     {};
            ulonglong_t available {};
            ulonglong_t free      {};
            Volume::space(it, &total, &available, &free);
            xTEST_DIFF(total, 0ULL);
            xTEST_DIFF(available, 0ULL);
            xTEST_DIFF(free, 0ULL);
        }

        for (const auto &it : volumePaths) {
            // xCHECK_DO(!Volume(it).isReady(), continue);

            ulonglong_t total     {};
            ulonglong_t available {};
            ulonglong_t free      {};
            Volume::space(it, nullptr, nullptr, nullptr);
            xTEST_EQ(total, 0ULL);
            xTEST_EQ(available, 0ULL);
            xTEST_EQ(free, 0ULL);
        }

        for (const auto &it : volumePaths) {
            // xCHECK_DO(!Volume(it).isReady(), continue);

            ulonglong_t total     {};
            ulonglong_t available {};
            ulonglong_t free      {};
            Volume::space(it, &total, &available, &free);
            xTEST_DIFF(total, 0ULL);
            xTEST_DIFF(available, 0ULL);
            xTEST_DIFF(free, 0ULL);

            // LogCout() << xTRACE_VAR_3(available, total, free);
        }

        {
            ulonglong_t total     {};
            ulonglong_t available {};
            ulonglong_t free      {};
            Volume::space(Const::strEmpty(), &total, &available, &free);
            xTEST_DIFF(total, 0ULL);
            xTEST_DIFF(available, 0ULL);
            xTEST_DIFF(free, 0ULL);

            culonglong_t usedPct = (total - available) * 100 / total;
            xTEST_DIFF(usedPct, 0ULL);

			// LogCout() << xTRACE_VAR_4(total, available, free, usedPct);
        }
    }

    xTEST_CASE("paths")
    {
        std::vec_tstring_t volumePaths;
        Volume::paths(&volumePaths);
        xTEST(!volumePaths.empty());
        // LogCout() << xTRACE_VAR(volumePaths);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
