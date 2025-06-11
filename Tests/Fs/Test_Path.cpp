/**
 * \file   Test_Path.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Path)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Path::unit()
{
	xTEST_CASE("exe")
	{
		const Path path = Path::exe();

		std::ctstring_t &sRv = path.str();
		xTEST(FileInfo(sRv).isExists());
	}

	xTEST_CASE("dll")
	{
		const Path path = Path::dll();

		std::ctstring_t &sRv = path.str();
		if ( !sRv.empty() ) {
		#if (cmOPTION_PROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
			xTEST(FileInfo(m_sRv).isExists());
		#else
			xTEST_NA(sRv);
		#endif
		}
	}

	xTEST_CASE("shell")
	{
		const Path path = Path::shell();

		std::ctstring_t &sRv = path.str();
		xTEST(!sRv.empty());
		xTEST(FileInfo(sRv).isExists());
	}

	xTEST_CASE("homeDir")
	{
		Path path = Path::homeDir();

		std::ctstring_t &sRv = path.str();
		xTEST(!sRv.empty());
		xTEST(Dir(sRv).isExists());
	}

    xTEST_CASE("trashDir")
    {
    	const Path path = Path::trashDir();

		std::ctstring_t &sRv = path.str();
		LogCout() << xPRINT_VAR(sRv);

		if ( isGithubCI() ) {
			xTEST(sRv.empty());
		} else {
			xTEST(!sRv.empty());
			xTEST(Dir(sRv).isExists());
		}
    }

    xTEST_CASE("volume")
    {
	#if   xENV_WIN
		std::ctstring_t filePath = xT("C:\\Test.txt");

		m_sRv = Path(filePath).volume();
		xTEST_EQ(m_sRv, std::tstring_t(xT("C:")));
	#elif xENV_UNIX
		std::ctstring_t filePath = Dir::temp().str();

		m_sRv = Path(filePath).volume();
		xTEST_EQ(m_sRv, std::tstring_t(xT("/")));
	#endif
    }

    xTEST_CASE("dir")
    {
		const data2_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test111\\Test.txt"),                            xT("C:\\Test111")},
			{xT("C:\\Test.txt"),                                     xT("C:")},
			{xT("Test.txt"),                                         xT("")},
			{xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++")}
		};
	#elif xENV_UNIX
		{
			{xT("/home/user/Soft/eclipse/Test.txt"),           xT("/home/user/Soft/eclipse")},
			{xT("/home/Test.txt"),                             xT("/home")},
			{xT("Test.txt"),                                   xT("")},
			{xT("/home/user/Soft/eclipse/pLaunchProject.exe"), xT("/home/user/Soft/eclipse")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).dir();
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("dirName")
    {
		const data2_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test111\\Test.txt"),                            xT("Test111")},
			{xT("C:\\Test.txt"),                                     xT("C:")},
			{xT("Test.txt"),                                         xT("")},
			{xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("Borland C++")}
		};
	#elif xENV_UNIX
		{
			{xT("/home/user/Soft/eclipse/Test.txt"),           xT("eclipse")},
			{xT("/home/Test.txt"),                             xT("home")},
			{xT("Test.txt"),                                   xT("")},
			{xT("/home/user/Soft/eclipse/pLaunchProject.exe"), xT("eclipse")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).dirName();
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("fileName")
    {
		const data2_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test111\\Test.txt"),                            xT("Test.txt")},
			{xT("C:\\Test"),                                         xT("Test")},
			{xT("Test.txt"),                                         xT("Test.txt")},
			{xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject.exe")}
		};
	#elif xENV_UNIX
		{
			{xT("/home/Test111/Test.txt"),                           xT("Test.txt")},
			{xT("/home/Test"),                                       xT("Test")},
			{xT("Test.txt"),                                         xT("Test.txt")},
			{xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("pLaunchProject.exe")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).fileName();
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("fileBaseName")
    {
		const data2_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test111\\Test.txt"),                            xT("Test")},
			{xT("C:\\Test"),                                         xT("Test")},
			{xT("Test.txt"),                                         xT("Test")},
			{xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject")}
		};
	#elif xENV_UNIX
		{
			{xT("/home/Test111/Test.txt"),                           xT("Test")},
			{xT("/home/Test"),                                       xT("Test")},
			{xT("Test.txt"),                                         xT("Test")},
			{xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("pLaunchProject")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).fileBaseName();
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("ext")
    {
		const data2_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test111\\Test.txt"),                            xT("txt")},
			{xT("C:\\Test"),                                         xT("")},
			{xT("Test.txt"),                                         xT("txt")},
			{xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("exe")},
			{xT("D:\\My projects\\Borlan.d C++\\pLaunchProject"),    xT("")},
		};
	#elif xENV_UNIX
		{
			{xT("/home/Test111/Test.txt"),                           xT("txt")},
			{xT("/home/Test"),                                       xT("")},
			{xT("Test.txt"),                                         xT("txt")},
			{xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("exe")},
			{xT("/home/My projects/Borlan.d C++/pLaunchProject"),    xT("")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).ext();
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("split")
    {
        using _data3_bool_t = Data3<std::tstring_t, std::size_t, std::tstring_t>;

		const _data3_bool_t data[]
		{
			{xT("/home/Test111/Test.txt"),                           1, xT("home")},
			{xT("/home/Test"),                                       2, xT("Test")},
			{xT("Test.txt"),                                         0, xT("Test.txt")},
			{xT("/home/My projects/Borland C++/pLaunchProject.exe"), 4, xT("pLaunchProject.exe")},
			{xT(""),                                                 0, xT("")}
		};

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::vec_tstring_t values;
            Path(data[i].test1).split(&values);

            if ( data[i].test1.empty() ) {
                xTEST(values.empty());
                continue;
            }

            std::tstring_t str1 = values[ data[i].test2 ];
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("fileExt")
    {
        m_sRv = Path::fileExt(Path::FileExt::Exe);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("exe")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::FileExt::Dll);
        #if   xENV_WIN
            xTEST_EQ(m_sRv, std::tstring_t(xT("dll")));
        #elif xENV_UNIX
			#if xENV_APPLE
				xTEST_EQ(m_sRv, std::tstring_t(xT("dylib")));
			#else
				xTEST_EQ(m_sRv, std::tstring_t(xT("so")));
			#endif
        #endif

        m_sRv = Path::fileExt(Path::FileExt::Lib);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("lib")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("a")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::FileExt::Obj);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("obj")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("o")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::FileExt::Shell);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("bat")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("sh")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::FileExt::Config);
        xTEST_EQ(std::tstring_t(xT("cfg")), m_sRv);

        m_sRv = Path::fileExt(Path::FileExt::Log);
        xTEST_EQ(std::tstring_t(xT("log")), m_sRv);

        m_sRv = Path::fileExt(Path::FileExt::Db);
        xTEST_EQ(std::tstring_t(xT("db")), m_sRv);

        m_sRv = Path::fileExt(Path::FileExt::Dat);
        xTEST_EQ(std::tstring_t(xT("dat")), m_sRv);

        m_sRv = Path::fileExt(Path::FileExt::Backup);
        xTEST_EQ(std::tstring_t(xT("bak")), m_sRv);

        m_sRv = Path::fileExt(Path::FileExt::Temp);
        xTEST_EQ(std::tstring_t(xT("tmp")), m_sRv);

        m_sRv = Path::fileExt(Path::FileExt::Text);
        xTEST_EQ(std::tstring_t(xT("txt")), m_sRv);
    }

    xTEST_CASE("fileDotExt")
    {
        m_sRv = Path::fileDotExt(Path::FileExt::Exe);
        #if   xENV_WIN
            xTEST_EQ(m_sRv, std::tstring_t(xT(".exe")));
        #elif xENV_UNIX
            xTEST_EQ(m_sRv, std::tstring_t(xT("")));
        #endif

        m_sRv = Path::fileDotExt(Path::FileExt::Text);
        xTEST_EQ(m_sRv, std::tstring_t(xT(".txt")));
    }

    xTEST_CASE("setVolume")
    {
		std::ctstring_t data[][3]
		{
		#if xENV_WIN
			{xT("C:\\Test.doc"),                  xT("F:"),    xT("F:\\Test.doc")},
			{xT("Z:\\okoval@winnerauto.ua.info"), xT("T:"),    xT("T:\\okoval@winnerauto.ua.info")},
			////{xT("TEST_STRING_3.doc"),             xT("R:"),    xT("")},
			{xT("D:\\Test.config"),               xT("A:"),    xT("A:\\Test.config")},
			////{xT("TEST_STRING_3.f"),               xT("B:"),    xT("")}
		#else
			{xT("/home/guest"),                 xT("/"),     xT("/home/guest")},
		#endif
		};

		for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
			std::tstring_t str1 = Path(data[i][0]).setVolume(data[i][1]).str();
			std::tstring_t str2 = Path(data[i][2]).setVolume(data[i][1]).str();
			xTEST_EQ(str1, str2);

			std::tstring_t str3 = Path(data[i][0]).setVolume(data[i][1]).str();
			std::tstring_t str4 = data[i][2];
			xTEST_EQ(str3, str4);
		}
    }

    xTEST_CASE("setDir")
    {
		const data3_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test.doc"),                  xT("F:\\"),      xT("F:\\Test.doc")},
			{xT("Z:\\okoval@winnerauto.ua.info"), xT("T:\\"),      xT("T:\\okoval@winnerauto.ua.info")},
			////{xT("TEST_STRING_3.doc"),         xT("R:\\"),      xT("")},
			{xT("D:\\Test.config"),               xT("A:\\"),      xT("A:\\Test.config")},
			////{xT("TEST_STRING_3.f"),           xT("B:\\"),      xT("")}
			{xT("D:\\Test\\Test.config"),         xT("A:\\"),      xT("A:\\Test.config")},
			{xT("D:\\Test\\Test.config"),         xT("A:\\1\\2"), xT("A:\\1\\2\\Test.config")}

		};
	#elif xENV_UNIX
		{
			{xT("/home/Test.doc"),                  xT("/job"),              xT("/job/Test.doc")},
			{xT("/home/okoval@winnerauto.ua.info"), xT("/job/room"),         xT("/job/room/okoval@winnerauto.ua.info")},
			////{xT("TEST_STRING_3.doc"),           xT("R:\\"),              xT("")},
			{xT("/home/Test.config"),               xT("/school/class/305"), xT("/school/class/305/Test.config")},
			////{xT("TEST_STRING_3.f"),             xT("B:\\"),              xT("")}
			{xT("/home/Test/Test.config"),          xT("/factory/"),         xT("/factory/Test.config")},
			{xT("/home/Test/Test.config"),          xT("/xxx"),              xT("/xxx/Test.config")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str3 = Path(data[i].test1).setDir(data[i].test2).str();
            std::tstring_t str4 = data[i].expect;
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("setFileName")
    {
		std::ctstring_t data[][3]
	#if   xENV_WIN
		{
			/*FilePath*/                          /*NewFileName*/   /*MustBe*/
			{xT("C:\\Test.doc"),                  xT("aaaa.xls"),    xT("C:\\aaaa.xls")},
			{xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty.fdm"),    xT("Z:\\qwerty.fdm")},
			////{xT("TEST_STRING_3.doc"),         xT("xxxxxx.c"),    xT("xxxxxx.c")},
			{xT("D:\\Test.config"),               xT("r.txt"),        xT("D:\\r.txt")},
			////{xT("TEST_STRING_3.f"),           xT("fff.qq"),        xT("fff.qq")}
		};
	#elif xENV_UNIX
		{
			/*FilePath*/                            /*NewFileName*/   /*MustBe*/
			{xT("/home/Test.doc"),                  xT("aaaa.xls"),   xT("/home/aaaa.xls")},
			{xT("/home/okoval@winnerauto.ua.info"), xT("qwerty.fdm"), xT("/home/qwerty.fdm")},
			////{xT("TEST_STRING_3.doc"),           xT("xxxxxx.c"),   xT("xxxxxx.c")},
			{xT("/home/Test.config"),               xT("r.txt"),      xT("/home/r.txt")},
			////{xT("TEST_STRING_3.f"),             xT("fff.qq"),     xT("fff.qq")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i][0]).setFileName(data[i][1]).str();
            std::tstring_t str2 = Path(data[i][2]).setFileName(data[i][1]).str();
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i][0]).setFileName(data[i][1]).str();
            std::tstring_t str4 = data[i][2];
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("setFileBaseName")
    {
		std::ctstring_t data[][3]
	#if   xENV_WIN
		{
			{xT("C:\\Test.doc"),                  xT("xxx"),      xT("C:\\xxx.doc")},
			{xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty"),      xT("Z:\\qwerty.info")},
			////{xT("TEST_STRING_3.doc"),         xT(""),          xT("")},
			////{xT("D:\\Test.config"),               xT(""),          xT("D:\\.config")},
			////{xT("TEST_STRING_3.f"),           xT("B:\\"),      xT("")}
			{xT("D:\\Test\\Test.config"),         xT("rrr"),      xT("D:\\Test\\rrr.config")},
			{xT("D:\\1\\2\\Test\\Test.config"),   xT("yyyyyyyy"), xT("D:\\1\\2\\Test\\yyyyyyyy.config")}

		};
	#elif xENV_UNIX
		{
			{xT("/home/Test.doc"),                  xT("xxx"),      xT("/home/xxx.doc")},
			{xT("/home/okoval@winnerauto.ua.info"), xT("qwerty"),   xT("/home/qwerty.info")},
			////{xT("TEST_STRING_3.doc"),           xT(""),           xT("")},
			////{xT("D:\\Test.config"),             xT(""),       xT("xxxxxxxxxxxxx")},
			////{xT("TEST_STRING_3.f"),             xT("B:\\"),       xT("")}
			{xT("/home/Test/Test.config"),         xT("rrr"),      xT("/home/Test/rrr.config")},
			{xT("/home/1/2/Test/Test.config"),     xT("yyyyyyyy"), xT("/home/1/2/Test/yyyyyyyy.config")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i][0]).setFileBaseName(data[i][1]).str();
            std::tstring_t str2 = Path(data[i][2]).setFileBaseName(data[i][1]).str();
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i][0]).setFileBaseName(data[i][1]).str();
            std::tstring_t str4 = data[i][2];
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("setExt")
    {
        std::ctstring_t data[][3]
		{
            {xT("C:\\Test.doc"),                  xT("xls"),    xT("C:\\Test.xls")},
            {xT("C:\\Test"),                      xT("xls"),    xT("C:\\Test.xls")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("fdm"),    xT("Z:\\okoval@winnerauto.ua.fdm")},
            {xT("TEST_STRING_3.doc"),             xT("xxxxxx"), xT("TEST_STRING_3.xxxxxx")},
            {xT("D:\\Test.config"),               xT("txt"),    xT("D:\\Test.txt")},
            {xT("TEST_STRING_3.f"),               xT("fff"),    xT("TEST_STRING_3.fff")},
            {xT("TEST_STRING_4"),                 xT("fff"),    xT("TEST_STRING_4.fff")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i][0]).setExt(data[i][1]).str();
            std::tstring_t str2 = Path(data[i][2]).setExt(data[i][1]).str();
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i][0]).setExt(data[i][1]).str();
            std::tstring_t str4 = data[i][2];
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("removeExt")
    {
		const data2_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test.111\\Test.txt"),                           xT("C:\\Test.111\\Test")},
			{xT("C:\\Test"),                                         xT("C:\\Test")},
			{xT("Test.txt"),                                         xT("Test")},
			{xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++\\pLaunchProject")}
		};
	#elif xENV_UNIX
		{
			{xT("/home/Test.111/Test.txt"),                          xT("/home/Test.111/Test")},
			{xT("/home/Test"),                                       xT("/home/Test")},
			{xT("Test.txt"),                                         xT("Test")},
			{xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("/home/My projects/Borland C++/pLaunchProject")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).removeExt().str();
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("removeExtIf")
    {
	#if   xENV_WIN
		const data2_tstring_t data[] = {
			{xT("C:\\Test.111\\Test.txt"),                           xT("C:\\Test.111\\Test")},
			{xT("C:\\Test"),                                         xT("C:\\Test")},
			{xT("Test.txt"),                                         xT("Test")},
			{xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++\\pLaunchProject")}
		};
	#elif xENV_UNIX
		const data2_tstring_t data[] = {
			{xT("/home/Test.111/Test.txt"),                          xT("/home/Test.111/Test")},
			{xT("/home/Test"),                                       xT("/home/Test")},
			{xT("Test.txt"),                                         xT("Test")},
			{xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("/home/My projects/Borland C++/pLaunchProject.exe")}
		};
	#endif

        for (const auto &it_data : data) {
            std::tstring_t str = Path(it_data.test).removeExtIf(xT("txt")).str();
            xTEST_EQ(str, it_data.expect);
        }
    }

    xTEST_CASE("isValid")
    {
        // TEST: Path::isValid()
    }

    xTEST_CASE("isNameValid")
    {
        // // a_fileNameValid == nullptr
        {
            {
                const data2_bool_t data[]
            #if   xENV_WIN
                {
                    {xT("CLOCK$"),       false},
                    {xT("AUX"),          false},
                    {xT("CON"),          false},
                    {xT("NUL"),          false},
                    {xT("PRN"),          false},
                    {xT("COM1"),         false},
                    {xT("COM2"),         false},
                    {xT("COM3"),         false},
                    {xT("COM4"),         false},
                    {xT("COM5"),         false},
                    {xT("COM6"),         false},
                    {xT("COM7"),         false},
                    {xT("COM8"),         false},
                    {xT("COM9"),         false},
                    {xT("LPT1"),         false},
                    {xT("LPT2"),         false},
                    {xT("LPT3"),         false},
                    {xT("LPT4"),         false},
                    {xT("LPT5"),         false},
                    {xT("LPT6"),         false},
                    {xT("LPT7"),         false},
                    {xT("LPT8"),         false},
                    {xT("LPT9"),         false},
                    {xT("clock$"),       false},
                    {xT("aux"),          false},
                    {xT("con"),          false},
                    {xT("nul"),          false},
                    {xT("prn"),          false},
                    {xT("com1"),         false},
                    {xT("com2"),         false},
                    {xT("com3"),         false},
                    {xT("com4"),         false},
                    {xT("com5"),         false},
                    {xT("com6"),         false},
                    {xT("com7"),         false},
                    {xT("com8"),         false},
                    {xT("com9"),         false},
                    {xT("LPT1"),         false},
                    {xT("LPT2"),         false},
                    {xT("LPT3"),         false},
                    {xT("LPT4"),         false},
                    {xT("LPT5"),         false},
                    {xT("LPT6"),         false},
                    {xT("LPT7"),         false},
                    {xT("LPT8"),         false},
                    {xT("LPT9"),         false},
                    {xT("clock$.txt"),   false},
                    {xT("aux.txt"),      false},
                    {xT("con.txt"),      false},
                    {xT("nul.txt"),      false},
                    {xT("prn.txt"),      false},
                    {xT("com1.txt"),     false},
                    {xT("com2.txt"),     false},
                    {xT("com3.txt"),     false},
                    {xT("com4.txt"),     false},
                    {xT("com5.txt"),     false},
                    {xT("com6.txt"),     false},
                    {xT("com7.txt"),     false},
                    {xT("com8.txt"),     false},
                    {xT("com9.txt"),     false},
                    {xT("LPT1.txt"),     false},
                    {xT("LPT2.txt"),     false},
                    {xT("LPT3.txt"),     false},
                    {xT("LPT4.txt"),     false},
                    {xT("LPT5.txt"),     false},
                    {xT("LPT6.txt"),     false},
                    {xT("LPT7.txt"),     false},
                    {xT("LPT8.txt"),     false},
                    {xT("LPT9.txt"),     false},
                    {xT("T\t"),          false},
                    {xT("T\n"),          false},
                    {xT("T\r"),          false},
                    {xT("T<"),           false},
                    {xT("T>"),           false},
                    {xT("T:"),           false},
                    {xT("T\""),          false},
                    {xT("T\\"),          false},
                    {xT("T/"),           false},
                    {xT("T*"),           false},
                    {xT("T?"),           false},
                    {xT("T|"),           false},
                    {xT("..."),          false},
                    {xT(" "),            false},
                    {xT("       "),      false},
                    {xT(". .."),         false},
                    {xT(".xxx."),        false},
                    {xT(" dd "),         false},
                    {xT("ff "),          false},
                    {xT("w "),           false},
                    {xT(".."),           false},
                    {xT("."),            false},
                    {xT("Good Data"),    true},
                    {xT("commit"),       true},
                    {xT("console"),      true},
                    {xT("LPT10"),        true},
                    {xT("clock"),        true},
                    {xT(".aux.txt"),     false},
                    {xT("auxx.aux.txt"), true},
                    {xT("nullptr"),         true},
                    {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"), false},
                    {xT(""),             false},
                    {xT("C:\\test\\"),   false},
                    {xT("C:/test/"),     false}
                };
            #elif xENV_UNIX
                {
                    {xT("xxxx"),       true},
                    {xT(""),           false},
                    {xT("/opt/test/"), false},
                    {xT("////////"),   false},
                    {xT("\\\\\\\\\\"), true},
                    {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///a\0me"), false},
                    {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"),   false}
                };
            #endif

                for (size_t i = 0; i < Utils::arraySizeT(data); ++ i) {
                    bool_t bRv1 = Path::isNameValid(data[i].test, nullptr);
                    bool_t bRv2 = data[i].expect;
                    xTEST_EQ(bRv1, bRv2);
                }
            }

            {
			#if xENV_UNIX
				#if xENV_APPLE
					std::ctstring_t data {xT('x'), xT('\0'), xT('/'), xT(':')};

					m_bRv = Path::isNameValid(data, nullptr);
					xTEST(!m_bRv);
				#else
					std::ctstring_t data {xT('x'), xT('\0'), xT('y')};

					m_bRv = Path::isNameValid(data, nullptr);
					xTEST(!m_bRv);
				#endif
			#endif
            }
        }

        // a_fileNameValid != nullptr
        {
            const data2_tstring_t data[]
        #if   xENV_WIN
            {
                {xT("CLOCK$"),       xT("")},
                {xT("AUX"),          xT("")},
                {xT("CON"),          xT("")},
                {xT("NUL"),          xT("")},
                {xT("PRN"),          xT("")},
                {xT("COM1"),         xT("")},
                {xT("COM2"),         xT("")},
                {xT("COM3"),         xT("")},
                {xT("COM4"),         xT("")},
                {xT("COM5"),         xT("")},
                {xT("COM6"),         xT("")},
                {xT("COM7"),         xT("")},
                {xT("COM8"),         xT("")},
                {xT("COM9"),         xT("")},
                {xT("LPT1"),         xT("")},
                {xT("LPT2"),         xT("")},
                {xT("LPT3"),         xT("")},
                {xT("LPT4"),         xT("")},
                {xT("LPT5"),         xT("")},
                {xT("LPT6"),         xT("")},
                {xT("LPT7"),         xT("")},
                {xT("LPT8"),         xT("")},
                {xT("LPT9"),         xT("")},
                {xT("clock$"),       xT("")},
                {xT("aux"),          xT("")},
                {xT("con"),          xT("")},
                {xT("nul"),          xT("")},
                {xT("prn"),          xT("")},
                {xT("com1"),         xT("")},
                {xT("com2"),         xT("")},
                {xT("com3"),         xT("")},
                {xT("com4"),         xT("")},
                {xT("com5"),         xT("")},
                {xT("com6"),         xT("")},
                {xT("com7"),         xT("")},
                {xT("com8"),         xT("")},
                {xT("com9"),         xT("")},
                {xT("LPT1"),         xT("")},
                {xT("LPT2"),         xT("")},
                {xT("LPT3"),         xT("")},
                {xT("LPT4"),         xT("")},
                {xT("LPT5"),         xT("")},
                {xT("LPT6"),         xT("")},
                {xT("LPT7"),         xT("")},
                {xT("LPT8"),         xT("")},
                {xT("LPT9"),         xT("")},
                {xT("clock$.txt"),   xT("")},
                {xT("aux.txt"),      xT("")},
                {xT("con.txt"),      xT("")},
                {xT("nul.txt"),      xT("")},
                {xT("prn.txt"),      xT("")},
                {xT("com1.txt"),     xT("")},
                {xT("com2.txt"),     xT("")},
                {xT("com3.txt"),     xT("")},
                {xT("com4.txt"),     xT("")},
                {xT("com5.txt"),     xT("")},
                {xT("com6.txt"),     xT("")},
                {xT("com7.txt"),     xT("")},
                {xT("com8.txt"),     xT("")},
                {xT("com9.txt"),     xT("")},
                {xT("LPT1.txt"),     xT("")},
                {xT("LPT2.txt"),     xT("")},
                {xT("LPT3.txt"),     xT("")},
                {xT("LPT4.txt"),     xT("")},
                {xT("LPT5.txt"),     xT("")},
                {xT("LPT6.txt"),     xT("")},
                {xT("LPT7.txt"),     xT("")},
                {xT("LPT8.txt"),     xT("")},
                {xT("LPT9.txt"),     xT("")},
                {xT("T\t"),          xT("T")},
                {xT("T\n"),          xT("T")},
                {xT("T\r"),          xT("T")},
                {xT("T<"),           xT("T")},
                {xT("T>"),           xT("T")},
                {xT("T:"),           xT("T")},
                {xT("T\""),          xT("T")},
                {xT("T\\"),          xT("T")},
                {xT("T/"),           xT("T")},
                {xT("T*"),           xT("T")},
                {xT("T?"),           xT("T")},
                {xT("T|"),           xT("T")},
                {xT("..."),          xT("")},
                {xT("Good Data"),    xT("Good Data")},
                {xT("commit"),       xT("commit")},
                {xT("console"),      xT("console")},
                {xT("LPT10"),        xT("LPT10")},
                {xT("clock"),        xT("clock")},
                {xT(".aux.txt"),     xT("")},
                {xT("auxx.aux.txt"), xT("auxx.aux.txt")},
                {xT("nullptr"),         xT("nullptr")},
                {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"),
                	xT("ValidTestName")},
            };
        #elif xENV_UNIX
            {
                {xT("xxxx"),       xT("xxxx")},
                {xT(""),           xT("")},
                {xT("/opt/test/"), xT("opttest")},
                {xT("////////"),   xT("")},
                {xT("\\\\\\\\\\"), xT("\\\\\\\\\\")},
				{xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"),
				#if xENV_APPLE
					xT("?V|||*?\"<>|||al*?\"<>|*?\"<>|*?\"<>|\\i?dT*e*?\"<>|stN*?\"<>|ame")},
				#else
					xT("?V|||:*?\"<>|||a:l:*?\"<>|:*?\"<>|:*?\"<>|\\i?dT*e:*?\"<>|stN:*?\"<>|ame")},
				#endif
            };
        #endif

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                std::tstring_t str;
                m_bRv = Path::isNameValid(data[i].test, &str);
                xTEST(m_bRv);
                xTEST_EQ(str, data[i].expect);

                // TODO: [skynowa] Tests - Path::isNameValid()
            }
        }
    }

    xTEST_CASE("isAbsolute, isRelative")
    {
        /// [TEST] isRelative

        // true
        {
            std::ctstring_t data[]
			{
			#if   xENV_WIN
				xT("C:\\"),
				xT("D:\\Downloads\\XXL\\I_am_a_Champion_-_coach_speech_[RUS_subtitles].flv"),
				xT("C://Windows//calc.exe"),
				xT("\\KASPER")
			#elif xENV_UNIX
				xT("/"),
				xT("/home/user/"),
				xT("/home/user/Downloads/n3242.pdf"),
				xT("/home/user/Downloads/Open source/cexception/vendor/unity/rakefile_helper.rb")
			#endif
            };

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                m_bRv = Path(data[i]).isAbsolute();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t data[]
			{
			#if   xENV_WIN
				xT("../../../Source/Debug/Test.cpp"),
				xT("../../../Source/Fs/Path"),
				xT("Test_Path.cpp"),
				xT("Tests/Source/Core/Test_SystemInfo.cpp"),
				xT("p"),
				xT("1"),
			#elif xENV_UNIX
				xT("../../../Source/Debug/Test.cpp"),
				xT("../../../Source/Fs/Path"),
				xT("Test_Path.cpp"),
				xT("Tests/Source/Core/Test_SystemInfo.cpp"),
				xT("p"),
				xT("1"),
			#endif
            };

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                m_bRv = Path(data[i]).isAbsolute();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("toWin")
    {
        std::ctstring_t unixPath = xT("C:/TestDir");
        std::ctstring_t winPath  = xT("C:\\TestDir");

        m_sRv = Path(unixPath).toWin(false).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));

        m_sRv = Path(unixPath).toWin(true).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

        m_sRv = Path(winPath).toWin(true).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

        m_sRv = Path(winPath).toWin(false).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));
    }

    xTEST_CASE("toUnix")
    {
        std::ctstring_t unixPath = xT("/home/user/Soft/TestDir");
        std::ctstring_t winPath  = xT("\\home\\user\\Soft\\TestDir");

        m_sRv = Path(unixPath).toUnix(false).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));

        m_sRv = Path(unixPath).toUnix(true).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

        m_sRv = Path(winPath).toUnix(true).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

        m_sRv = Path(winPath).toUnix(false).str();
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));
    }

    xTEST_CASE("toNative")
    {
	#if   xENV_WIN
		std::ctstring_t unixPath = xT("C:/TestDir");
		std::ctstring_t winPath  = xT("C:\\TestDir");

		m_sRv = Path(winPath).toNative(false).str();
		xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));

		m_sRv = Path(winPath).toNative(true).str();
		xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

		m_sRv = Path(winPath).toNative(true).str();
		xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

		m_sRv = Path(winPath).toNative(false).str();
		xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));
	#elif xENV_UNIX
		std::ctstring_t unixPath = xT("/home/user/Soft/TestDir");
		std::ctstring_t winPath  = xT("\\home\\user\\Soft\\TestDir");

		m_sRv = Path(winPath).toNative(false).str();
		xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));

		m_sRv = Path(winPath).toNative(true).str();
		xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

		m_sRv = Path(winPath).toNative(true).str();
		xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

		m_sRv = Path(winPath).toNative(false).str();
		xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));
	#endif
    }

    xTEST_CASE("absolute")
    {
        std::vec_tstring_t args;

        ProcessInfo info(Process::currentId());
        info.commandLine(&args);

        m_sRv = Path(args.at(0)).absolute().str();
        xTEST(!m_sRv.empty());
    }

    xTEST_CASE("briefName")
    {
        const data2_tstring_t data[]
		{
            {xT("/val/log/Name"),                   xT("Name")},
            {xT("/val/log/full name"),              xT("ful~")},
            {xT("/val/log/file name with ext"),     xT("fil~")},
            {xT("/val/log/comment"),                xT("com~")},

            {xT("/val/log/Name.exe"),               xT("Name")},
            {xT("/val/log/full name.txt"),          xT("full")},
            {xT("/val/log/file name with ext.doc"), xT("file")},
            {xT("/val/log/comment.pdfx"),           xT("comm")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).briefName(4).str();
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("brief")
    {
        {
		#if   xENV_WIN
			std::tstring_t filePath = xT("C:\\Test.txt");
		#elif xENV_UNIX
			std::tstring_t filePath = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
		#endif

		m_sRv = Path(filePath).brief(4).str();
		#if   xENV_WIN
			xTEST_EQ(std::tstring_t(xT("C:\\Test.txt")), m_sRv);
		#elif xENV_UNIX
			xTEST_EQ(std::tstring_t(xT("/.../filename")), m_sRv);
		#endif
        }

        {
		#if   xENV_WIN
			std::tstring_t filePath = xT("C:\\Test.txt");
		#elif xENV_UNIX
			std::tstring_t filePath = xT("/home/filename");
		#endif

		m_sRv = Path(filePath).brief(200).str();
		#if   xENV_WIN
			xTEST_EQ(std::tstring_t(xT("C:\\Test.txt")), m_sRv);
		#elif xENV_UNIX
			xTEST_EQ(std::tstring_t(xT("/home/filename")), m_sRv);
		#endif
        }

        {
		#if   xENV_WIN
			std::tstring_t filePath = xT("D:\\xVCL\\Include\\xVCL\\Units\\Ui\\vSpeedButton_LoadDrives.cpp");
		#elif xENV_UNIX
			std::tstring_t filePath = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
		#endif

		m_sRv = Path(filePath).brief(15).str();
		#if   xENV_WIN
			xTEST_EQ(std::tstring_t(xT("D:\\...\\vSpeedButton_LoadDrives.cpp")), m_sRv);
		#elif xENV_UNIX
			xTEST_EQ(std::tstring_t(xT("/.../filename")), m_sRv);
		#endif
        }

        {
            std::tstring_t filePath = xT("D:/xVCL\\Include/xVCL\\Units/Ui/Tools/LoadDrives.cpp");

            m_sRv = Path(filePath).brief(15).str();
		#if   xENV_WIN
			xTEST_EQ(std::tstring_t(xT("D:\\...\\LoadDrives.cpp")), m_sRv);
		#elif xENV_UNIX
			xTEST_EQ(std::tstring_t(xT("D:/.../LoadDrives.cpp")), m_sRv);
		#endif
        }
    }

	xTEST_CASE("brief")
	{
		struct DataN
		{
			std::tstring_t filePath;
			std::size_t    leftDirsNum;
			std::size_t    rightDirsNum;
			std::tstring_t expect;
		};

		const DataN data[]
		{
			{xT("D:/xVCL/Include/xVCL/Units/Ui/vSpeedButton_LoadDrives.cpp"),
				2, 2, xT("D:/xVCL/.../Ui/vSpeedButton_LoadDrives.cpp")},
			{xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename"),
				2, 2, xT("/home/...../Debug/filename")},
			{xT("111"), 2, 2, xT("111")},
			{xT("/home/user/Soft"), 10, 10, xT("/home/user/Soft")},
			{xT("/home/user/Soft"), 0, 0, xT("....")},
			{xT("/home/user/Soft"), 2, 10, xT("/home/user/Soft")},
			{xT("/home/user/Soft"), 10, 1, xT("/home/user/Soft")}
		};

		for (const auto &it_data : data) {
			m_sRv = Path(it_data.filePath).brief(it_data.leftDirsNum, it_data.rightDirsNum).str();
			// LogCout() << xTRACE_VAR_2(m_sRv, it_data.expect) << "<<<";
			xTEST_EQ(m_sRv, it_data.expect);
		}
	}

    xTEST_CASE("homeAsBrief")
    {
        const Path path = Path::homeDir();

        std::ctstring_t &homeDir = path.str();

	#if   xENV_WIN
		std::ctstring_t filePath = Format::str(xT("{}\\test"), homeDir);
	#elif xENV_UNIX
		std::ctstring_t filePath = Format::str(xT("{}/tmp"), homeDir);
	#endif

		m_sRv = Path(filePath).homeAsBrief().str();
	#if   xENV_WIN
		xTEST_EQ(m_sRv, std::tstring_t(xT("~\test")));
	#elif xENV_UNIX
		xTEST_EQ(m_sRv, std::tstring_t(xT("~/tmp")));
	#endif
    }

    xTEST_CASE("slashAppend")
    {
		const data2_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test.doc"),                  xT("C:\\Test.doc\\")},
			{xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info\\")},
			{xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc\\")},
			{xT("D:\\Test.config"),               xT("D:\\Test.config\\")},
			{xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f\\")}
		};
	#elif xENV_UNIX
		{
			{xT("/home/Test.doc"),                  xT("/home/Test.doc/")},
			{xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info/")},
			{xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc/")},
			{xT("/home/Test.config"),               xT("/home/Test.config/")},
			{xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f/")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).slashAppend().str();
            std::tstring_t str2 = Path(data[i].expect).slashAppend().str();
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i].test).slashAppend().str();
            std::tstring_t str4 = data[i].expect;
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("slashRemove")
    {
		const data2_tstring_t data[]
	#if   xENV_WIN
		{
			{xT("C:\\Test.doc"),                  xT("C:\\Test.doc")},
			{xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info")},
			{xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc")},
			{xT("D:\\Test.config"),               xT("D:\\Test.config")},
			{xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f")}
		};
	#elif xENV_UNIX
		{
			{xT("/home/Test.doc"),                  xT("/home/Test.doc")},
			{xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info")},
			{xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc")},
			{xT("/home/Test.config"),               xT("/home/Test.config")},
			{xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f")}
		};
	#endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).slashRemove().str();
            std::tstring_t str2 = Path(data[i].expect).slashRemove().str();
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i].test).slashRemove().str();
            std::tstring_t str4 = data[i].expect;
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("maxSize")
    {
        m_stRv = Path::maxSize();
        xTEST_GR(m_stRv, std::size_t{0});
    }

    xTEST_CASE("nameMaxSize")
    {
        m_stRv = Path::nameMaxSize();
        xTEST_LESS(size_t(0), m_stRv);
    }

#if xENV_UNIX
	xTEST_CASE("proc")
	{
		auto condition = [](std::ctstring_t &it_line) -> bool_t
		{
			return it_line.find(xT("vendor_id")) != std::tstring_t::npos;
		};

		auto op = [](std::ctstring_t &a_line) -> std::tstring_t
		{
			std::tstring_t sRv;

			// parse value
			std::csize_t delimPos = a_line.find(xT(":"));
			xTEST_DIFF(delimPos, std::string::npos);

			sRv = a_line.substr(delimPos + 1);
			sRv = String::trimSpace(sRv);

			return sRv;
		};

		m_sRv = Path::proc(xT("/proc/cpuinfo"), condition, op);
		xTEST_EQ(m_sRv, std::tstring_t(xT("GenuineIntel")));
	}

	xTEST_CASE("procValue")
	{
		m_sRv = Path::procValue(xT("/proc/cpuinfo"), xT("vendor_id"));
		xTEST_EQ(m_sRv, std::tstring_t(xT("GenuineIntel")));
	}

	xTEST_CASE("readSymLink")
	{
		m_sRv = Path::readSymLink(xT("/proc/self/exe"));
		xTEST_EQ(Path(m_sRv).fileBaseName(), Path(xFILE).fileBaseName());
	}
#endif

    xTEST_CASE("operator <<")
    {
    	std::ctstring_t filePath = xT("/var/log/test.log");

		std::tstringstream_t ss;
		ss << Path(filePath);

		xTEST_EQ(ss.str(), filePath);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
