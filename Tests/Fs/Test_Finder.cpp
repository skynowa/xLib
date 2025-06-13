/**
 * \file   Test_Finder.cpp
 * \brief  test Finder
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Finder)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Finder::unit()
{
    // prepare
    std::ctstring_t    rootDirPath = option().tempDirPath + Const::slash() + xT("Finder_Dir");
    std::vec_tstring_t dirs;

    {
        Dir(rootDirPath).pathDelete();

        {
            dirs.push_back( rootDirPath + Const::slash() + xT("AAA") );
            dirs.push_back( rootDirPath + Const::slash() + xT("BBB") );
            dirs.push_back( rootDirPath + Const::slash() + xT("CCC") );

            for (const auto &it_dir : dirs) {
                Dir(it_dir).pathCreate();
            }

            xTEST_EQ(size_t(3), dirs.size());
        }

        {
    		std::vec_tstring_t files;
            files.push_back( rootDirPath + Const::slash() + xT("AAA.h") );
            files.push_back( rootDirPath + Const::slash() + xT("BBB.h") );
            files.push_back( rootDirPath + Const::slash() + xT("CCC.h") );
            files.push_back( rootDirPath + Const::slash() + xT("DDD.h") );
            files.push_back( rootDirPath + Const::slash() + xT("AAA.cpp") );
            files.push_back( rootDirPath + Const::slash() + xT("BBB.cpp") );
            files.push_back( rootDirPath + Const::slash() + xT("CCC.cpp") );
            files.push_back( rootDirPath + Const::slash() + xT("DDD.cpp") );

            files.push_back( rootDirPath + Const::slash() + xT("File_1") );
            files.push_back( rootDirPath + Const::slash() + xT("File_2.log") );
            files.push_back( rootDirPath + Const::slash() + xT("AAA") +
                               Const::slash() + xT("AA") +
                               Const::slash() + xT("File_3.log") );
            files.push_back( rootDirPath + Const::slash() + xT("BBB") +
                               Const::slash() + xT("BB") +
                               Const::slash() + xT("BBB") +
                               Const::slash() + xT("File_4.log") );

            for (const auto &it_file : files) {
				FileIO file(it_file);
				file.open(FileIO::OpenMode::Write);
				file.clear();
            }

            xTEST_EQ(size_t(12), files.size());
        }
    }

    xTEST_CASE("Finder")
    {
        const data2_size_t data[]
        {
            {Const::maskAll(), 12 - 2},
            {xT("*"),          12 - 2},
        #if   xENV_WIN
            {xT("*.*"),        12 - 2},
        #elif xENV_UNIX
            {xT("*.*"),        12 - 3},
        #endif
            {xT("*.h"),        4},
            {xT("*.cpp"),      4},
            {xT("*.txt"),      0},
            {xT("*.log"),      1}
        };

        for (const auto &it_data : data) {
            std::vec_tstring_t entries;
            std::ctstring_t    filter = it_data.test;
            Finder             finder(rootDirPath, filter);

            for ( ; ; ) {
                m_bRv = finder.moveNext();
                xCHECK_DO(!m_bRv, break);

                xCHECK_DO(Const::dot()  == finder.entryName(), continue);
                xCHECK_DO(Const::dot2() == finder.entryName(), continue);

                // set filter for files
                xCHECK_DO(static_cast<int_t>(FileType::Type::Directory) & finder.fileTypes(),
                	continue);
                xTEST(FileInfo(finder.entryPath()).isExists());

                entries.push_back(finder.entryName());
            }

            // LogCout() << filter << "\n" << xTRACE_VAR(rootDirPath) << entries;
            xTEST_EQ(it_data.expect, entries.size());
        }
    }

    xTEST_CASE("dirs")
    {
        // non recursive
        {
            m_vsRv.clear();

            Finder::dirs(rootDirPath, Const::maskAll(), false, &m_vsRv);
            // LogCout() << m_vsRv;
            xTEST_EQ(dirs.size(), m_vsRv.size());
        }

        // recursive
        {
            m_vsRv.clear();

            Finder::dirs(rootDirPath, Const::maskAll(), true, &m_vsRv);
            // LogCout() << m_vsRv;
            xTEST_EQ(size_t(6), m_vsRv.size());
        }
    }

    xTEST_CASE("files")
    {
        // non recursive
        {
            const data2_size_t data[]
            {
                {Const::maskAll(), 12 - 2},
                {xT("*"),          12 - 2},
            #if   xENV_WIN
                {xT("*.*"),        12 - 2},
            #elif xENV_UNIX
                {xT("*.*"),        12 - 3},
            #endif
                {xT("*.h"),        4},
                {xT("*.cpp"),      4},
                {xT("*.txt"),      0},
                {xT("*.log"),      1}
            };

            for (const auto &it_data : data) {
                m_vsRv.clear();

                Finder::files(rootDirPath, it_data.test, false, &m_vsRv);
                // LogCout() << m_vsRv;
                xTEST_EQ(it_data.expect, m_vsRv.size());
            }
        }

        // recursive
        {
            const data2_size_t data[]
            {
                {Const::maskAll(), 12},
                {xT("*"),          12},
            #if   xENV_WIN
                {xT("*.*"),        12},
            #elif xENV_UNIX
                {xT("*.*"),        12 - 1},
            #endif
                {xT("*.h"),        4},
                {xT("*.cpp"),      4},
                {xT("*.txt"),      0},
                {xT("*.log"),      3}
            };

            for (const auto &it_data : data) {
                m_vsRv.clear();

                Finder::files(rootDirPath, it_data.test, true, &m_vsRv);
                // LogCout() << m_vsRv;
                xTEST_EQ(it_data.expect, m_vsRv.size());
            }
        }
    }

	xTEST_CASE("file")
	{
		struct DataN
		{
			std::cvec_tstring_t dirPaths;
			std::ctstring_t     fileName;
			cbool_t             isRecursively;
			std::ctstring_t     expect;
		};

		const DataN data[]
		{
		#if   xENV_WIN
			{{xT("C:\\Windows\\System32\\Temp"), xT("C:\\Windows\\System32")},
				xT("attrib.exe"),
				false,
				xT("C:\\Windows\\System32\\attrib.exe")}
		#elif xENV_UNIX
			{{xT("/usr/include"), xT("/usr/local/include"), xT("/usr/bin")},
				xT("git"),
				false,
				xT("/usr/bin/git")}
		#endif
		};

		for (const auto &it_data : data) {
			m_sRv = Finder::file(it_data.dirPaths, it_data.fileName, it_data.isRecursively);
			// LogCout() << xTRACE_VAR(m_sRv);
			xTEST_EQ(m_sRv, it_data.expect);
		}
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
