/**
 * \file   Test_Path.cpp
 * \brief
 */


#include "Test_Path.h"

#include <xLib/IO/File.h>
#include <xLib/IO/Dir.h>
#include <xLib/Sync/Process.h>
#include <xLib/System/ProcessInfo.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Path)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Path::unit()
{
    xTEST_CASE("exe")
    {
        m_sRv = Path::exe();
        xTEST_EQ(true, File::isExists(m_sRv));
    }

    xTEST_CASE("exeDir")
    {
        m_sRv = Path::exeDir();
        xTEST_EQ(true, Dir(m_sRv).isExists());
    }

    xTEST_CASE("dll")
    {
        m_sRv = Path::dll();
    #if (cmOPTION_PROJECT_LIB_SHARE || cmOPTION_PROJECT_LIB_MODULE)
        xTEST_EQ(File::isExists(m_sRv), true);
    #else
        xTEST_NA(m_sRv);
    #endif
    }

    xTEST_CASE("drive")
    {
        #if xENV_WIN
            std::ctstring_t filePath = xT("C:\\Test.txt");

            m_sRv = Path(filePath).drive();
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:")));
        #endif
    }

    xTEST_CASE("dir")
    {
        #if   xENV_WIN
            const data2_tstring_t data[] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("C:\\Test111")},
                {xT("C:\\Test.txt"),                                     xT("C:")},
                {xT("Test.txt"),                                         xT("")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++")}
            };
        #elif xENV_UNIX
            const data2_tstring_t data[] = {
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
        #if   xENV_WIN
            const data2_tstring_t data[] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test111")},
                {xT("C:\\Test.txt"),                                     xT("C:")},
                {xT("Test.txt"),                                         xT("")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("Borland C++")}
            };
        #elif xENV_UNIX
            const data2_tstring_t data[] = {
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
        #if   xENV_WIN
            const data2_tstring_t data[] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test.txt")},
                {xT("C:\\Test"),                                         xT("Test")},
                {xT("Test.txt"),                                         xT("Test.txt")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject.exe")}
            };
        #elif xENV_UNIX
            const data2_tstring_t data[] = {
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
        #if   xENV_WIN
            const data2_tstring_t data[] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test")},
                {xT("C:\\Test"),                                         xT("Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject")}
            };
        #elif xENV_UNIX
            const data2_tstring_t data[] = {
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
        #if   xENV_WIN
            const data2_tstring_t data[] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("txt")},
                {xT("C:\\Test"),                                         xT("")},
                {xT("Test.txt"),                                         xT("txt")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("exe")},
                {xT("D:\\My projects\\Borlan.d C++\\pLaunchProject"),    xT("")},
            };
        #elif xENV_UNIX
            const data2_tstring_t data[] = {
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

    xTEST_CASE("fileExt")
    {
        m_sRv = Path::fileExt(Path::seExe);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("exe")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::seDll);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("dll")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("so")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::seLib);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("lib")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("a")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::seObj);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("obj")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("o")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::seShell);
        #if   xENV_WIN
            xTEST_EQ(std::tstring_t(xT("bat")), m_sRv);
        #elif xENV_UNIX
            xTEST_EQ(std::tstring_t(xT("sh")), m_sRv);
        #endif

        m_sRv = Path::fileExt(Path::seConfig);
        xTEST_EQ(std::tstring_t(xT("cfg")), m_sRv);

        m_sRv = Path::fileExt(Path::seLog);
        xTEST_EQ(std::tstring_t(xT("log")), m_sRv);

        m_sRv = Path::fileExt(Path::seDb);
        xTEST_EQ(std::tstring_t(xT("db")), m_sRv);

        m_sRv = Path::fileExt(Path::seDat);
        xTEST_EQ(std::tstring_t(xT("dat")), m_sRv);

        m_sRv = Path::fileExt(Path::seBackup);
        xTEST_EQ(std::tstring_t(xT("bak")), m_sRv);

        m_sRv = Path::fileExt(Path::seTemp);
        xTEST_EQ(std::tstring_t(xT("tmp")), m_sRv);

        m_sRv = Path::fileExt(Path::seText);
        xTEST_EQ(std::tstring_t(xT("txt")), m_sRv);
    }

    xTEST_CASE("setDrive")
    {
        #if xENV_WIN
            std::ctstring_t data[][3] = {
                {xT("C:\\Test.doc"),                  xT("F:"),    xT("F:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("T:"),    xT("T:\\okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),             xT("R:"),    xT("")},
                {xT("D:\\Test.config"),               xT("A:"),    xT("A:\\Test.config")},
                ////{xT("TEST_STRING_3.f"),               xT("B:"),    xT("")}
            };

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                std::tstring_t str1 = Path(data[i][0]).setDrive(data[i][1]);
                std::tstring_t str2 = Path(data[i][2]).setDrive(data[i][1]);
                xTEST_EQ(str1, str2);

                std::tstring_t str3 = Path(data[i][0]).setDrive(data[i][1]);
                std::tstring_t str4 = data[i][2];
                xTEST_EQ(str3, str4);
            }
        #endif
    }

    xTEST_CASE("setDir")
    {
        #if   xENV_WIN
            const data3_tstring_t data[] = {
                {xT("C:\\Test.doc"),                  xT("F:\\"),      xT("F:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("T:\\"),      xT("T:\\okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),         xT("R:\\"),      xT("")},
                {xT("D:\\Test.config"),               xT("A:\\"),      xT("A:\\Test.config")},
                ////{xT("TEST_STRING_3.f"),           xT("B:\\"),      xT("")}
                {xT("D:\\Test\\Test.config"),         xT("A:\\"),      xT("A:\\Test.config")},
                {xT("D:\\Test\\Test.config"),         xT("A:\\1\\2"), xT("A:\\1\\2\\Test.config")}

            };
        #elif xENV_UNIX
            const data3_tstring_t data[] = {
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
            //std::tstring_t str1 = Path::sSetDir(data[i][0], data[i][1]);
            //std::tstring_t str2 = Path::sSetDir(data[i][2], data[i][1]);
            //xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i].test1).setDir(data[i].test2);
            std::tstring_t str4 = data[i].expect;
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("setFileName")
    {
        #if   xENV_WIN
            std::ctstring_t data[][3] = {
                /*FilePath*/                          /*NewFileName*/   /*MustBe*/
                {xT("C:\\Test.doc"),                  xT("aaaa.xls"),    xT("C:\\aaaa.xls")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty.fdm"),    xT("Z:\\qwerty.fdm")},
                ////{xT("TEST_STRING_3.doc"),         xT("xxxxxx.c"),    xT("xxxxxx.c")},
                {xT("D:\\Test.config"),               xT("r.txt"),        xT("D:\\r.txt")},
                ////{xT("TEST_STRING_3.f"),           xT("fff.qq"),        xT("fff.qq")}
            };
        #elif xENV_UNIX
            std::ctstring_t data[][3] = {
                /*FilePath*/                            /*NewFileName*/   /*MustBe*/
                {xT("/home/Test.doc"),                  xT("aaaa.xls"),   xT("/home/aaaa.xls")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("qwerty.fdm"), xT("/home/qwerty.fdm")},
                ////{xT("TEST_STRING_3.doc"),           xT("xxxxxx.c"),   xT("xxxxxx.c")},
                {xT("/home/Test.config"),               xT("r.txt"),      xT("/home/r.txt")},
                ////{xT("TEST_STRING_3.f"),             xT("fff.qq"),     xT("fff.qq")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i][0]).setFileName(data[i][1]);
            std::tstring_t str2 = Path(data[i][2]).setFileName(data[i][1]);
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i][0]).setFileName(data[i][1]);
            std::tstring_t str4 = data[i][2];
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("setFileBaseName")
    {
        #if   xENV_WIN
            std::ctstring_t data[][3] = {
                {xT("C:\\Test.doc"),                  xT("xxx"),      xT("C:\\xxx.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty"),      xT("Z:\\qwerty.info")},
                ////{xT("TEST_STRING_3.doc"),         xT(""),          xT("")},
                ////{xT("D:\\Test.config"),               xT(""),          xT("D:\\.config")},
                ////{xT("TEST_STRING_3.f"),           xT("B:\\"),      xT("")}
                {xT("D:\\Test\\Test.config"),         xT("rrr"),      xT("D:\\Test\\rrr.config")},
                {xT("D:\\1\\2\\Test\\Test.config"),   xT("yyyyyyyy"), xT("D:\\1\\2\\Test\\yyyyyyyy.config")}

            };
        #elif xENV_UNIX
            std::ctstring_t data[][3] = {
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
            std::tstring_t str1 = Path(data[i][0]).setFileBaseName(data[i][1]);
            std::tstring_t str2 = Path(data[i][2]).setFileBaseName(data[i][1]);
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i][0]).setFileBaseName(data[i][1]);
            std::tstring_t str4 = data[i][2];
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("setExt")
    {
        std::ctstring_t data[][3] = {
            {xT("C:\\Test.doc"),                  xT("xls"),    xT("C:\\Test.xls")},
            {xT("C:\\Test"),                      xT("xls"),    xT("C:\\Test.xls")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("fdm"),    xT("Z:\\okoval@winnerauto.ua.fdm")},
            {xT("TEST_STRING_3.doc"),             xT("xxxxxx"),    xT("TEST_STRING_3.xxxxxx")},
            {xT("D:\\Test.config"),               xT("txt"),    xT("D:\\Test.txt")},
            {xT("TEST_STRING_3.f"),               xT("fff"),    xT("TEST_STRING_3.fff")},
            {xT("TEST_STRING_4"),                 xT("fff"),    xT("TEST_STRING_4.fff")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i][0]).setExt(data[i][1]);
            std::tstring_t str2 = Path(data[i][2]).setExt(data[i][1]);
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i][0]).setExt(data[i][1]);
            std::tstring_t str4 = data[i][2];
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("removeExt")
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
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("/home/My projects/Borland C++/pLaunchProject")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).removeExt();
            std::tstring_t str2 = data[i].expect;
            xTEST_EQ(str1, str2);
        }
    }

    xTEST_CASE("removeExtIf")
    {
        // TEST: Path::removeExtIf()

        //#if   xENV_WIN
        //    const data2_tstring_t data[] = {
        //        {xT("C:\\Test.111\\Test.txt"),                           xT("C:\\Test.111\\Test")},
        //        {xT("C:\\Test"),                                         xT("C:\\Test")},
        //        {xT("Test.txt"),                                         xT("Test")},
        //        {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++\\pLaunchProject")}
        //    };
        //#elif xENV_UNIX
        //    const data2_tstring_t data[] = {
        //        {xT("/home/Test.111/Test.txt"),                          xT("/home/Test.111/Test")},
        //        {xT("/home/Test"),                                       xT("/home/Test")},
        //        {xT("Test.txt"),                                         xT("Test")},
        //        {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("/home/My projects/Borland C++/pLaunchProject")}
        //    };
        //#endif

        //for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
        //    std::tstring_t str1 = Path::removeExtIf(data[i][0]);
        //    std::tstring_t str2 = data[i][1];
        //    xTEST_EQ(str1, str2);
        //}
    }

    xTEST_CASE("isValid")
    {
        // TEST: Path::isValid()
    }

    xTEST_CASE("isNameValid")
    {
        // // a_fileNameValid == xPTR_NULL
        {
            {
            #if   xENV_WIN
                const data2_bool_t data[] =
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
                    {xT("xPTR_NULL"),         true},
                    {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"), false},
                    {xT(""),             false},
                    {xT("C:\\test\\"),   false},
                    {xT("C:/test/"),     false}
                };
            #elif xENV_UNIX
                const data2_bool_t data[] =
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

                for (size_t i = 0; i < xARRAY_SIZE2(data); ++ i) {
                    bool_t bRv1 = Path::isNameValid(data[i].test);
                    bool_t bRv2 = data[i].expect;
                    xTEST_EQ(bRv1, bRv2);
                }
            }

        #if xENV_UNIX
            {
                std::string data;
                data.push_back('x');
                data.push_back('\0');
                data.push_back('y');

                m_bRv = Path::isNameValid(data);
                xTEST_EQ(m_bRv, false);
            }
        #endif
        }

        // a_fileNameValid != xPTR_NULL
        {
        #if   xENV_WIN
            const data2_tstring_t data[] =
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
                {xT("xPTR_NULL"),         xT("xPTR_NULL")},
                {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"), xT("ValidTestName")},
            };
        #elif xENV_UNIX
            const data2_tstring_t data[] =
            {
                {xT("xxxx"),       xT("xxxx")},
                {xT(""),           xT("")},
                {xT("/opt/test/"), xT("opttest")},
                {xT("////////"),   xT("")},
                {xT("\\\\\\\\\\"), xT("\\\\\\\\\\")},
                {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"), xT("?V|||:*?\"<>|||a:l:*?\"<>|:*?\"<>|:*?\"<>|\\i?dT*e:*?\"<>|stN:*?\"<>|ame")},
            };
        #endif

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                std::tstring_t str;
                m_bRv = Path::isNameValid(data[i].test, &str);
                xTEST_EQ(m_bRv, true);
                xTEST_EQ(str,   data[i].expect);

                // TODO: Tests - Path::isNameValid()
            }
        }
    }

    xTEST_CASE("isAbsolute")
    {
        // true
        {
            std::ctstring_t data[] = {
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
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t data[] = {
                #if   xENV_WIN
                    xT("../../../Source/Debug/Test.cpp"),
                    xT("../../../Source/IO/Path"),
                    xT("Test_Path.cpp"),
                    xT("Tests/Source/Core/Test_SystemInfo.cpp"),
                    xT("p"),
                    xT("1"),
                #elif xENV_UNIX
                    xT("../../../Source/Debug/Test.cpp"),
                    xT("../../../Source/IO/Path"),
                    xT("Test_Path.cpp"),
                    xT("Tests/Source/Core/Test_SystemInfo.cpp"),
                    xT("p"),
                    xT("1"),
                #endif
            };

            for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
                m_bRv = Path(data[i]).isAbsolute();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("toWin")
    {
        std::ctstring_t unixPath = xT("C:/TestDir");
        std::ctstring_t winPath  = xT("C:\\TestDir");

        m_sRv = Path(unixPath).toWin(false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));

        m_sRv = Path(unixPath).toWin(true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

        m_sRv = Path(winPath).toWin(true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

        m_sRv = Path(winPath).toWin(false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));
    }

    xTEST_CASE("toUnix")
    {
        std::ctstring_t unixPath = xT("/home/user/Soft/TestDir");
        std::ctstring_t winPath  = xT("\\home\\user\\Soft\\TestDir");

        m_sRv = Path(unixPath).toUnix(false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));

        m_sRv = Path(unixPath).toUnix(true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

        m_sRv = Path(winPath).toUnix(true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

        m_sRv = Path(winPath).toUnix(false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));
    }

    xTEST_CASE("toNative")
    {
        #if   xENV_WIN
            std::ctstring_t unixPath = xT("C:/TestDir");
            std::ctstring_t winPath  = xT("C:\\TestDir");

            m_sRv = Path(winPath).toNative(false);
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));

            m_sRv = Path(winPath).toNative(true);
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

            m_sRv = Path(winPath).toNative(true);
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

            m_sRv = Path(winPath).toNative(false);
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));
        #elif xENV_UNIX
            std::ctstring_t unixPath = xT("/home/user/Soft/TestDir");
            std::ctstring_t winPath  = xT("\\home\\user\\Soft\\TestDir");

            m_sRv = Path(winPath).toNative(false);
            xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));

            m_sRv = Path(winPath).toNative(true);
            xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

            m_sRv = Path(winPath).toNative(true);
            xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

            m_sRv = Path(winPath).toNative(false);
            xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));
        #endif
    }

    xTEST_CASE("absolute")
    {
        std::vec_tstring_t args;

        ProcessInfo info;
        info.setProcessId(Process::currentId());
        info.commandLine(&args);

        m_sRv = Path(args.at(0)).absolute();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("shortName")
    {
        const data2_tstring_t data[] = {
            {xT("Name"),                   xT("Name")},
            {xT("full name"),              xT("ful~")},
            {xT("file name with ext"),     xT("fil~")},
            {xT("comment"),                xT("com~")},

            {xT("Name.exe"),               xT("Name")},
            {xT("full name.txt"),          xT("full")},
            {xT("file name with ext.doc"), xT("file")},
            {xT("comment.pdfx"),           xT("comm")},
        };

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path::shortName(data[i].test, 4);
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

            m_sRv = Path(filePath).brief(4);
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

            m_sRv = Path(filePath).brief(200);
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

            m_sRv = Path(filePath).brief(15);
            #if   xENV_WIN
                xTEST_EQ(std::tstring_t(xT("D:\\...\\vSpeedButton_LoadDrives.cpp")), m_sRv);
            #elif xENV_UNIX
                xTEST_EQ(std::tstring_t(xT("/.../filename")), m_sRv);
            #endif
        }

        {
            std::tstring_t filePath = xT("D:/xVCL\\Include/xVCL\\Units/Ui/Tools/LoadDrives.cpp");

            m_sRv = Path(filePath).brief(15);
            #if   xENV_WIN
                xTEST_EQ(std::tstring_t(xT("D:\\...\\LoadDrives.cpp")), m_sRv);
            #elif xENV_UNIX
                xTEST_EQ(std::tstring_t(xT("D:/.../LoadDrives.cpp")), m_sRv);
            #endif
        }
    }

    xTEST_CASE("slashAppend")
    {
        #if   xENV_WIN
            const data2_tstring_t data[] = {
                {xT("C:\\Test.doc"),                  xT("C:\\Test.doc\\")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info\\")},
                {xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc\\")},
                {xT("D:\\Test.config"),               xT("D:\\Test.config\\")},
                {xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f\\")}
            };
        #elif xENV_UNIX
            const data2_tstring_t data[] = {
                {xT("/home/Test.doc"),                  xT("/home/Test.doc/")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info/")},
                {xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc/")},
                {xT("/home/Test.config"),               xT("/home/Test.config/")},
                {xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f/")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).slashAppend();
            std::tstring_t str2 = Path(data[i].expect).slashAppend();
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i].test).slashAppend();
            std::tstring_t str4 = data[i].expect;
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("slashRemove")
    {
        #if   xENV_WIN
            const data2_tstring_t data[] = {
                {xT("C:\\Test.doc"),                  xT("C:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info")},
                {xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc")},
                {xT("D:\\Test.config"),               xT("D:\\Test.config")},
                {xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f")}
            };
        #elif xENV_UNIX
            const data2_tstring_t data[] = {
                {xT("/home/Test.doc"),                  xT("/home/Test.doc")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info")},
                {xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc")},
                {xT("/home/Test.config"),               xT("/home/Test.config")},
                {xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(data); ++ i) {
            std::tstring_t str1 = Path(data[i].test).slashRemove();
            std::tstring_t str2 = Path(data[i].expect).slashRemove();
            xTEST_EQ(str1, str2);

            std::tstring_t str3 = Path(data[i].test).slashRemove();
            std::tstring_t str4 = data[i].expect;
            xTEST_EQ(str3, str4);
        }
    }

    xTEST_CASE("maxSize")
    {
        m_stRv = Path::maxSize();
        xTEST_LESS(size_t(0), m_stRv);
    }

    xTEST_CASE("nameMaxSize")
    {
        m_stRv = Path::nameMaxSize();
        xTEST_LESS(size_t(0), m_stRv);
    }

#if xENV_UNIX
    xTEST_CASE("proc")
    {
        // TEST: Path::proc()
    }

    xTEST_CASE("procValue")
    {
        // TEST: Path::procValue()
    }
#endif

    return true;
}
//-------------------------------------------------------------------------------------------------
