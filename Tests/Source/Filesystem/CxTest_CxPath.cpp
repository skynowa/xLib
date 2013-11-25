/**
 * \file   CxTest_CxPath.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxPath.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Sync/CxProcess.h>
#include <xLib/System/CxProcessInfo.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxPath::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxPath::exe", a_caseLoops)
    {
        m_sRv = CxPath::exe();
        xTEST_EQ(true, CxFile::isExists(m_sRv));
    }

    xTEST_CASE("CxPath::exeDir", a_caseLoops)
    {
        m_sRv = CxPath::exeDir();
        xTEST_EQ(true, CxDir(m_sRv).isExists());
    }

    xTEST_CASE("CxPath::dll", a_caseLoops)
    {
        m_sRv = CxPath::dll();
        xTEST_EQ(true, CxFile::isExists(m_sRv));
    }

    xTEST_CASE("CxPath::drive", a_caseLoops)
    {
        #if xOS_ENV_WIN
            std::tstring_t csFilePath = xT("C:\\Test.txt");

            m_sRv = CxPath(csFilePath).drive();
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:")));
        #endif
    }

    xTEST_CASE("CxPath::dir", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("C:\\Test111")},
                {xT("C:\\Test.txt"),                                     xT("C:")},
                {xT("Test.txt"),                                         xT("")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][2] = {
                {xT("/home/user/Soft/eclipse/Test.txt"),           xT("/home/user/Soft/eclipse")},
                {xT("/home/Test.txt"),                             xT("/home")},
                {xT("Test.txt"),                                   xT("")},
                {xT("/home/user/Soft/eclipse/pLaunchProject.exe"), xT("/home/user/Soft/eclipse")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).dir();
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("CxPath::dirName", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test111")},
                {xT("C:\\Test.txt"),                                     xT("C:")},
                {xT("Test.txt"),                                         xT("")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("Borland C++")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][2] = {
                {xT("/home/user/Soft/eclipse/Test.txt"),           xT("eclipse")},
                {xT("/home/Test.txt"),                             xT("home")},
                {xT("Test.txt"),                                   xT("")},
                {xT("/home/user/Soft/eclipse/pLaunchProject.exe"), xT("eclipse")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).dirName();
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("CxPath::fileName", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test.txt")},
                {xT("C:\\Test"),                                         xT("Test")},
                {xT("Test.txt"),                                         xT("Test.txt")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject.exe")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][2] = {
                {xT("/home/Test111/Test.txt"),                           xT("Test.txt")},
                {xT("/home/Test"),                                       xT("Test")},
                {xT("Test.txt"),                                         xT("Test.txt")},
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("pLaunchProject.exe")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).fileName();
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("CxPath::fileBaseName", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test")},
                {xT("C:\\Test"),                                         xT("Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][2] = {
                {xT("/home/Test111/Test.txt"),                           xT("Test")},
                {xT("/home/Test"),                                       xT("Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("pLaunchProject")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).fileBaseName();
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("CxPath::ext", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("txt")},
                {xT("C:\\Test"),                                         xT("")},
                {xT("Test.txt"),                                         xT("txt")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("exe")},
                {xT("D:\\My projects\\Borlan.d C++\\pLaunchProject"),    xT("")},
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][2] = {
                {xT("/home/Test111/Test.txt"),                           xT("txt")},
                {xT("/home/Test"),                                       xT("")},
                {xT("Test.txt"),                                         xT("txt")},
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("exe")},
                {xT("/home/My projects/Borlan.d C++/pLaunchProject"),    xT("")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).ext();
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("CxPath::standartExt", a_caseLoops)
    {
        m_sRv = CxPath::standartExt(CxPath::seExe);
        #if   xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("exe")), m_sRv);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("")), m_sRv);
        #endif

        m_sRv = CxPath::standartExt(CxPath::seDll);
        #if   xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("dll")), m_sRv);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("so")), m_sRv);
        #endif

        m_sRv = CxPath::standartExt(CxPath::seLib);
        #if   xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("lib")), m_sRv);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("a")), m_sRv);
        #endif

        m_sRv = CxPath::standartExt(CxPath::seObj);
        #if   xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("obj")), m_sRv);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("o")), m_sRv);
        #endif

        m_sRv = CxPath::standartExt(CxPath::seShell);
        #if   xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("bat")), m_sRv);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("sh")), m_sRv);
        #endif
    }

    xTEST_CASE("CxPath::setDrive", a_caseLoops)
    {
        #if xOS_ENV_WIN
            std::ctstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("F:"),    xT("F:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("T:"),    xT("T:\\okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),             xT("R:"),    xT("")},
                {xT("D:\\Test.config"),               xT("A:"),    xT("A:\\Test.config")},
                ////{xT("TEST_STRING_3.f"),               xT("B:"),    xT("")}
            };

            for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                std::tstring_t sStr1 = CxPath(sData[i][0]).setDrive(sData[i][1]);
                std::tstring_t sStr2 = CxPath(sData[i][2]).setDrive(sData[i][1]);
                xTEST_EQ(sStr1, sStr2);

                std::tstring_t sStr3 = CxPath(sData[i][0]).setDrive(sData[i][1]);
                std::tstring_t sStr4 = sData[i][2];
                xTEST_EQ(sStr3, sStr4);
            }
        #endif
    }

    xTEST_CASE("CxPath::setDir", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("F:\\"),      xT("F:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("T:\\"),      xT("T:\\okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),         xT("R:\\"),      xT("")},
                {xT("D:\\Test.config"),               xT("A:\\"),      xT("A:\\Test.config")},
                ////{xT("TEST_STRING_3.f"),           xT("B:\\"),      xT("")}
                {xT("D:\\Test\\Test.config"),         xT("A:\\"),      xT("A:\\Test.config")},
                {xT("D:\\Test\\Test.config"),         xT("A:\\1\\2"), xT("A:\\1\\2\\Test.config")}

            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][3] = {
                {xT("/home/Test.doc"),                  xT("/job"),              xT("/job/Test.doc")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("/job/room"),         xT("/job/room/okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),           xT("R:\\"),              xT("")},
                {xT("/home/Test.config"),               xT("/school/class/305"), xT("/school/class/305/Test.config")},
                ////{xT("TEST_STRING_3.f"),             xT("B:\\"),              xT("")}
                {xT("/home/Test/Test.config"),          xT("/factory/"),         xT("/factory/Test.config")},
                {xT("/home/Test/Test.config"),          xT("/xxx"),              xT("/xxx/Test.config")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            //std::tstring_t sStr1 = CxPath::sSetDir(sData[i][0], sData[i][1]);
            //std::tstring_t sStr2 = CxPath::sSetDir(sData[i][2], sData[i][1]);
            //xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath(sData[i][0]).setDir(sData[i][1]);
            std::tstring_t sStr4 = sData[i][2];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxPath::setFileName", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][3] = {
                /*FilePath*/                          /*NewFileName*/   /*MustBe*/
                {xT("C:\\Test.doc"),                  xT("aaaa.xls"),    xT("C:\\aaaa.xls")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty.fdm"),    xT("Z:\\qwerty.fdm")},
                ////{xT("TEST_STRING_3.doc"),         xT("xxxxxx.c"),    xT("xxxxxx.c")},
                {xT("D:\\Test.config"),               xT("r.txt"),        xT("D:\\r.txt")},
                ////{xT("TEST_STRING_3.f"),           xT("fff.qq"),        xT("fff.qq")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][3] = {
                /*FilePath*/                            /*NewFileName*/   /*MustBe*/
                {xT("/home/Test.doc"),                  xT("aaaa.xls"),   xT("/home/aaaa.xls")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("qwerty.fdm"), xT("/home/qwerty.fdm")},
                ////{xT("TEST_STRING_3.doc"),           xT("xxxxxx.c"),   xT("xxxxxx.c")},
                {xT("/home/Test.config"),               xT("r.txt"),      xT("/home/r.txt")},
                ////{xT("TEST_STRING_3.f"),             xT("fff.qq"),     xT("fff.qq")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).setFileName(sData[i][1]);
            std::tstring_t sStr2 = CxPath(sData[i][2]).setFileName(sData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath(sData[i][0]).setFileName(sData[i][1]);
            std::tstring_t sStr4 = sData[i][2];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxPath::setFileBaseName", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("xxx"),      xT("C:\\xxx.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty"),      xT("Z:\\qwerty.info")},
                ////{xT("TEST_STRING_3.doc"),         xT(""),          xT("")},
                ////{xT("D:\\Test.config"),               xT(""),          xT("D:\\.config")},
                ////{xT("TEST_STRING_3.f"),           xT("B:\\"),      xT("")}
                {xT("D:\\Test\\Test.config"),         xT("rrr"),      xT("D:\\Test\\rrr.config")},
                {xT("D:\\1\\2\\Test\\Test.config"),   xT("yyyyyyyy"), xT("D:\\1\\2\\Test\\yyyyyyyy.config")}

            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][3] = {
                {xT("/home/Test.doc"),                  xT("xxx"),      xT("/home/xxx.doc")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("qwerty"),   xT("/home/qwerty.info")},
                ////{xT("TEST_STRING_3.doc"),           xT(""),           xT("")},
                ////{xT("D:\\Test.config"),             xT(""),       xT("xxxxxxxxxxxxx")},
                ////{xT("TEST_STRING_3.f"),             xT("B:\\"),       xT("")}
                {xT("/home/Test/Test.config"),         xT("rrr"),      xT("/home/Test/rrr.config")},
                {xT("/home/1/2/Test/Test.config"),     xT("yyyyyyyy"), xT("/home/1/2/Test/yyyyyyyy.config")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).setFileBaseName(sData[i][1]);
            std::tstring_t sStr2 = CxPath(sData[i][2]).setFileBaseName(sData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath(sData[i][0]).setFileBaseName(sData[i][1]);
            std::tstring_t sStr4 = sData[i][2];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxPath::setExt", a_caseLoops)
    {
        std::ctstring_t sData[][3] = {
            {xT("C:\\Test.doc"),                  xT("xls"),    xT("C:\\Test.xls")},
            {xT("C:\\Test"),                      xT("xls"),    xT("C:\\Test.xls")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("fdm"),    xT("Z:\\okoval@winnerauto.ua.fdm")},
            {xT("TEST_STRING_3.doc"),             xT("xxxxxx"),    xT("TEST_STRING_3.xxxxxx")},
            {xT("D:\\Test.config"),               xT("txt"),    xT("D:\\Test.txt")},
            {xT("TEST_STRING_3.f"),               xT("fff"),    xT("TEST_STRING_3.fff")},
            {xT("TEST_STRING_4"),                 xT("fff"),    xT("TEST_STRING_4.fff")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).setExt(sData[i][1]);
            std::tstring_t sStr2 = CxPath(sData[i][2]).setExt(sData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath(sData[i][0]).setExt(sData[i][1]);
            std::tstring_t sStr4 = sData[i][2];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxPath::removeExt", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][2] = {
                {xT("C:\\Test.111\\Test.txt"),                           xT("C:\\Test.111\\Test")},
                {xT("C:\\Test"),                                         xT("C:\\Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++\\pLaunchProject")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][2] = {
                {xT("/home/Test.111/Test.txt"),                          xT("/home/Test.111/Test")},
                {xT("/home/Test"),                                       xT("/home/Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("/home/My projects/Borland C++/pLaunchProject")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).removeExt();
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("CxPath::removeExtIf", a_caseLoops)
    {
        // TEST: CxPath::sRemoveExtIf

        //#if   xOS_ENV_WIN
        //    std::ctstring_t sData[][2] = {
        //        {xT("C:\\Test.111\\Test.txt"),                           xT("C:\\Test.111\\Test")},
        //        {xT("C:\\Test"),                                         xT("C:\\Test")},
        //        {xT("Test.txt"),                                         xT("Test")},
        //        {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++\\pLaunchProject")}
        //    };
        //#elif xOS_ENV_UNIX
        //    std::ctstring_t sData[][2] = {
        //        {xT("/home/Test.111/Test.txt"),                          xT("/home/Test.111/Test")},
        //        {xT("/home/Test"),                                       xT("/home/Test")},
        //        {xT("Test.txt"),                                         xT("Test")},
        //        {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("/home/My projects/Borland C++/pLaunchProject")}
        //    };
        //#endif

        //for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
        //    std::tstring_t sStr1 = CxPath::removeExtIf(sData[i][0]);
        //    std::tstring_t sStr2 = sData[i][1];
        //    xTEST_EQ(sStr1, sStr2);
        //}
    }

    xTEST_CASE("CxPath::isValid", a_caseLoops)
    {
        // TEST: CxPath::isValid
    }

    xTEST_CASE("CxPath::isNameValid", a_caseLoops)
    {
        struct SData {
            std::tstring_t sFileName;
            bool_t           bIsValid;
        };

    #if   xOS_ENV_WIN
        const SData cdData[] =
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
            {xT("NULL"),         true},
            {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"), false},
            {xT(""),             false},
            {xT("C:\\test\\"),   false},
            {xT("C:/test/"),     false}
        };
    #elif xOS_ENV_UNIX
        const SData cdData[] =
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

        for (size_t i = 0; i < xARRAY_SIZE2(cdData); ++ i) {
            bool_t bRv1 = CxPath::isNameValid(cdData[i].sFileName);
            bool_t bRv2 = cdData[i].bIsValid;
            xTEST_EQ(bRv1, bRv2);
        }

    #if xOS_ENV_UNIX
        {
            std::string sData;
            sData.push_back('x');
            sData.push_back('\0');
            sData.push_back('y');

            m_bRv = CxPath::isNameValid(sData);
            xTEST_EQ(false, m_bRv);
        }
    #endif
    }

    xTEST_CASE("CxPath::isAbsolute", a_caseLoops)
    {
        // true
        {
            std::ctstring_t casData[] = {
                #if   xOS_ENV_WIN
                    xT("C:\\"),
                    xT("D:\\Downloads\\XXL\\I_am_a_Champion_-_coach_speech_[RUS_subtitles].flv"),
                    xT("C://Windows//calc.exe"),
                    xT("\\KASPER")
                #elif xOS_ENV_UNIX
                    xT("/"),
                    xT("/home/user/"),
                    xT("/home/user/Downloads/n3242.pdf"),
                    xT("/home/user/Downloads/Open source/cexception/vendor/unity/rakefile_helper.rb")
                #endif
            };

            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
                m_bRv = CxPath(casData[i]).isAbsolute();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t casData[] = {
                #if   xOS_ENV_WIN
                    xT("../../../Source/Debug/CxTest.cpp"),
                    xT("../../../Source/Filesystem/CxPath"),
                    xT("CxTest_CxPath.cpp"),
                    xT("Tests/Source/Core/CxTest_CxSystemInfo.cpp"),
                    xT("p"),
                    xT("1"),
                #elif xOS_ENV_UNIX
                    xT("../../../Source/Debug/CxTest.cpp"),
                    xT("../../../Source/Filesystem/CxPath"),
                    xT("CxTest_CxPath.cpp"),
                    xT("Tests/Source/Core/CxTest_CxSystemInfo.cpp"),
                    xT("p"),
                    xT("1"),
                #endif
            };

            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
                m_bRv = CxPath(casData[i]).isAbsolute();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxPath::toWin", a_caseLoops)
    {
        std::ctstring_t csUnixPath = xT("C:/TestDir");
        std::ctstring_t csWinPath  = xT("C:\\TestDir");

        m_sRv = CxPath(csUnixPath).toWin(false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));

        m_sRv = CxPath(csUnixPath).toWin(true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

        m_sRv = CxPath(csWinPath).toWin(true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

        m_sRv = CxPath(csWinPath).toWin(false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));
    }

    xTEST_CASE("CxPath::toUnix", a_caseLoops)
    {
        std::ctstring_t csUnixPath = xT("/home/user/Soft/TestDir");
        std::ctstring_t csWinPath  = xT("\\home\\user\\Soft\\TestDir");

        m_sRv = CxPath(csUnixPath).toUnix(false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));

        m_sRv = CxPath(csUnixPath).toUnix(true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

        m_sRv = CxPath(csWinPath).toUnix(true);
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

        m_sRv = CxPath(csWinPath).toUnix(false);
        xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));
    }

    xTEST_CASE("CxPath::toNative", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t csUnixPath = xT("C:/TestDir");
            std::ctstring_t csWinPath  = xT("C:\\TestDir");

            m_sRv = CxPath(csWinPath).toNative(false);
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));

            m_sRv = CxPath(csWinPath).toNative(true);
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

            m_sRv = CxPath(csWinPath).toNative(true);
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir\\")));

            m_sRv = CxPath(csWinPath).toNative(false);
            xTEST_EQ(m_sRv, std::tstring_t(xT("C:\\TestDir")));
        #elif xOS_ENV_UNIX
            std::ctstring_t csUnixPath = xT("/home/user/Soft/TestDir");
            std::ctstring_t csWinPath  = xT("\\home\\user\\Soft\\TestDir");

            m_sRv = CxPath(csWinPath).toNative(false);
            xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));

            m_sRv = CxPath(csWinPath).toNative(true);
            xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

            m_sRv = CxPath(csWinPath).toNative(true);
            xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir/")));

            m_sRv = CxPath(csWinPath).toNative(false);
            xTEST_EQ(m_sRv, std::tstring_t(xT("/home/user/Soft/TestDir")));
        #endif
    }

    xTEST_CASE("CxPath::absolute", a_caseLoops)
    {
        std::vec_tstring_t vsArgs;

        CxProcessInfo info;
        info.setProcessId(CxProcess::currentId());
        info.commandLine(&vsArgs);

        m_sRv = CxPath(vsArgs.at(0)).absolute();
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxPath::shortName", a_caseLoops)
    {
        std::ctstring_t sData[][2] = {
            {xT("Name"),                   xT("Name")},
            {xT("full name"),              xT("ful~")},
            {xT("file name with ext"),     xT("fil~")},
            {xT("comment"),                xT("com~")},

            {xT("Name.exe"),               xT("Name")},
            {xT("full name.txt"),          xT("full")},
            {xT("file name with ext.doc"), xT("file")},
            {xT("comment.pdfx"),           xT("comm")},
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::shortName(sData[i][0], 4);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    xTEST_CASE("CxPath::brief", a_caseLoops)
    {
        {
            #if   xOS_ENV_WIN
                std::tstring_t sFilePath = xT("C:\\Test.txt");
            #elif xOS_ENV_UNIX
                std::tstring_t sFilePath = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
            #endif

            m_sRv = CxPath(sFilePath).brief(4);
            #if   xOS_ENV_WIN
                xTEST_EQ(std::tstring_t(xT("C:\\Test.txt")), m_sRv);
            #elif xOS_ENV_UNIX
                xTEST_EQ(std::tstring_t(xT("/.../filename")), m_sRv);
            #endif
        }

        {
            #if   xOS_ENV_WIN
                std::tstring_t sFilePath = xT("C:\\Test.txt");
            #elif xOS_ENV_UNIX
                std::tstring_t sFilePath = xT("/home/filename");
            #endif

            m_sRv = CxPath(sFilePath).brief(200);
            #if   xOS_ENV_WIN
                xTEST_EQ(std::tstring_t(xT("C:\\Test.txt")), m_sRv);
            #elif xOS_ENV_UNIX
                xTEST_EQ(std::tstring_t(xT("/home/filename")), m_sRv);
            #endif
        }

        {
            #if   xOS_ENV_WIN
                std::tstring_t sFilePath = xT("D:\\xVCL\\Include\\xVCL\\Units\\Gui\\vSpeedButton_LoadDrives.cpp");
            #elif xOS_ENV_UNIX
                std::tstring_t sFilePath = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
            #endif

            m_sRv = CxPath(sFilePath).brief(15);
            #if   xOS_ENV_WIN
                xTEST_EQ(std::tstring_t(xT("D:\\...\\vSpeedButton_LoadDrives.cpp")), m_sRv);
            #elif xOS_ENV_UNIX
                xTEST_EQ(std::tstring_t(xT("/.../filename")), m_sRv);
            #endif
        }

        {
            std::tstring_t sFilePath = xT("D:/xVCL\\Include/xVCL\\Units/Gui/Tools/LoadDrives.cpp");

            m_sRv = CxPath(sFilePath).brief(15);
            #if   xOS_ENV_WIN
                xTEST_EQ(std::tstring_t(xT("D:\\...\\LoadDrives.cpp")), m_sRv);
            #elif xOS_ENV_UNIX
                xTEST_EQ(std::tstring_t(xT("D:/.../LoadDrives.cpp")), m_sRv);
            #endif
        }
    }

    xTEST_CASE("CxPath::setNameValid", a_caseLoops)
    {
    #if   xOS_ENV_WIN
        std::ctstring_t asData[][2] =
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
            {xT("NULL"),         xT("NULL")},
            {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"), xT("ValidTestName")},
        };
    #elif xOS_ENV_UNIX
        std::ctstring_t asData[][2] =
        {
            {xT("xxxx"),       xT("xxxx")},
            {xT(""),           xT("")},
            {xT("/opt/test/"), xT("opttest")},
            {xT("////////"),   xT("")},
            {xT("\\\\\\\\\\"), xT("\\\\\\\\\\")},
            {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"), xT("?V|||:*?\"<>|||a:l:*?\"<>|:*?\"<>|:*?\"<>|\\i?dT*e:*?\"<>|stN:*?\"<>|ame")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(asData); ++ i) {
            std::tstring_t sStr1 = CxPath::setNameValid(asData[i][0]);
            std::tstring_t sStr2 = CxPath::setNameValid(asData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath::setNameValid(asData[i][0]);
            std::tstring_t sStr4 = asData[i][1];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxPath::slashAppend", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("C:\\Test.doc\\")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info\\")},
                {xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc\\")},
                {xT("D:\\Test.config"),               xT("D:\\Test.config\\")},
                {xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f\\")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][3] = {
                {xT("/home/Test.doc"),                  xT("/home/Test.doc/")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info/")},
                {xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc/")},
                {xT("/home/Test.config"),               xT("/home/Test.config/")},
                {xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f/")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).slashAppend();
            std::tstring_t sStr2 = CxPath(sData[i][1]).slashAppend();
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath(sData[i][0]).slashAppend();
            std::tstring_t sStr4 = sData[i][1];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxPath::slashRemove", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("C:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info")},
                {xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc")},
                {xT("D:\\Test.config"),               xT("D:\\Test.config")},
                {xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sData[][3] = {
                {xT("/home/Test.doc"),                  xT("/home/Test.doc")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info")},
                {xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc")},
                {xT("/home/Test.config"),               xT("/home/Test.config")},
                {xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath(sData[i][0]).slashRemove();
            std::tstring_t sStr2 = CxPath(sData[i][1]).slashRemove();
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath(sData[i][0]).slashRemove();
            std::tstring_t sStr4 = sData[i][1];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    xTEST_CASE("CxPath::maxSize", a_caseLoops)
    {
        m_stRv = CxPath::maxSize();
        xTEST_LESS(size_t(0), m_stRv);
    }

    xTEST_CASE("CxPath::nameMaxSize", a_caseLoops)
    {
        m_stRv = CxPath::nameMaxSize();
        xTEST_LESS(size_t(0), m_stRv);
    }

#if xOS_ENV_UNIX
    xTEST_CASE("CxPath::proc", a_caseLoops)
    {
        // TEST: CxPath::proc
    }

    xTEST_CASE("CxPath::procValue", a_caseLoops)
    {
        // TEST: CxPath::procValue
    }
#endif
}
//------------------------------------------------------------------------------
