/**
 * \file   CxTest_CxPath.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxPath.h>

#include <xLib/Common/CxCommandLine.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>


//---------------------------------------------------------------------------
CxTest_CxPath::CxTest_CxPath() {

}
//---------------------------------------------------------------------------
CxTest_CxPath::~CxTest_CxPath() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxPath::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //-------------------------------------
    //vars
    std::vector<std::tstring_t> vsRes;

//    #if xOS_ENV_WIN
//        const std::tstring_t csFilePath    = xT("C:\\Test.txt");
//        const std::tstring_t csNewFilePath = xT("C:\\New.Test.txt");
//        const std::tstring_t csBakFilePath = xT("C:\\Test_Static.txt.bak");
//        const std::tstring_t csFilePathSt  = xT("C:\\Test_Static.txt");
//        const std::tstring_t csFileName    = xT("TestName");
//        const std::tstring_t csFileExt     = xT("doc");
//    #elif xOS_ENV_UNIX
//        const std::tstring_t csFilePath    = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
//        const std::tstring_t csNewFilePath = xT("/home/user/Soft/New.Test.txt");
//        const std::tstring_t csBakFilePath = xT("/home/user/Soft/Test_Static.txt.bak");
//        const std::tstring_t csFilePathSt  = xT("/home/user/Soft/Test_Static.txt");
//        const std::tstring_t csFileName    = xT("TestName");
//        const std::tstring_t csFileExt     = xT("doc");
//    #endif

    //-------------------------------------
    //sGetExe
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxPath::sGetExe();
        xTEST_EQ(true, CxFile::bIsExists(m_sRes));
    }

    //-------------------------------------
    //sGetDll
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxPath::sGetDll();
        xTEST_EQ(true, CxFile::bIsExists(m_sRes));
    }

    //-------------------------------------
    //sGetExeDir
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxPath::sGetExeDir();
        xTEST_EQ(true, CxDir::bIsExists(m_sRes));
    }

    //-------------------------------------
    //sGetDrive
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            std::tstring_t csFilePath = xT("C:\\Test.txt");

            m_sRes = CxPath::sGetDrive(csFilePath);
            xTEST_EQ(m_sRes, std::tstring_t(xT("C:")));
        #endif
    }

    //-------------------------------------
    //sGetDir
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("C:\\Test111")},
                {xT("C:\\Test.txt"),                                     xT("C:")},
                {xT("Test.txt"),                                         xT("")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][2] = {
                {xT("/home/user/Soft/eclipse/Test.txt"),           xT("/home/user/Soft/eclipse")},
                {xT("/home/Test.txt"),                             xT("/home")},
                {xT("Test.txt"),                                   xT("")},
                {xT("/home/user/Soft/eclipse/pLaunchProject.exe"), xT("/home/user/Soft/eclipse")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sGetDir(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //sGetDirName
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test111")},
                {xT("C:\\Test.txt"),                                     xT("C:")},
                {xT("Test.txt"),                                         xT("")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("Borland C++")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][2] = {
                {xT("/home/user/Soft/eclipse/Test.txt"),           xT("eclipse")},
                {xT("/home/Test.txt"),                             xT("home")},
                {xT("Test.txt"),                                   xT("")},
                {xT("/home/user/Soft/eclipse/pLaunchProject.exe"), xT("eclipse")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sGetDirName(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //sGetFullName
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test.txt")},
                {xT("C:\\Test"),                                         xT("Test")},
                {xT("Test.txt"),                                         xT("Test.txt")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject.exe")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][2] = {
                {xT("/home/Test111/Test.txt"),                           xT("Test.txt")},
                {xT("/home/Test"),                                       xT("Test")},
                {xT("Test.txt"),                                         xT("Test.txt")},
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("pLaunchProject.exe")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sGetFullName(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //sGetName
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("Test")},
                {xT("C:\\Test"),                                         xT("Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][2] = {
                {xT("/home/Test111/Test.txt"),                           xT("Test")},
                {xT("/home/Test"),                                       xT("Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("pLaunchProject")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sGetName(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //sGetExt
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][2] = {
                {xT("C:\\Test111\\Test.txt"),                            xT("txt")},
                {xT("C:\\Test"),                                         xT("")},
                {xT("Test.txt"),                                         xT("txt")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("exe")},
                {xT("D:\\My projects\\Borlan.d C++\\pLaunchProject"),    xT("")},
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][2] = {
                {xT("/home/Test111/Test.txt"),                           xT("txt")},
                {xT("/home/Test"),                                       xT("")},
                {xT("Test.txt"),                                         xT("txt")},
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("exe")},
                {xT("/home/My projects/Borlan.d C++/pLaunchProject"),    xT("")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sGetExt(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //sGetStandartExt
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = CxPath::sGetStandartExt(CxPath::seExe);
        #if xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("exe")), m_sRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("")), m_sRes);
        #endif

        m_sRes = CxPath::sGetStandartExt(CxPath::seDll);
        #if xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("dll")), m_sRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("so")), m_sRes);
        #endif

        m_sRes = CxPath::sGetStandartExt(CxPath::seLib);
        #if xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("lib")), m_sRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("a")), m_sRes);
        #endif

        m_sRes = CxPath::sGetStandartExt(CxPath::seObj);
        #if xOS_ENV_WIN
            xTEST_EQ(std::tstring_t(xT("obj")), m_sRes);
        #elif xOS_ENV_UNIX
            xTEST_EQ(std::tstring_t(xT("o")), m_sRes);
        #endif
    }

    //-------------------------------------
    //sSetDrive
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("F:"),    xT("F:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("T:"),    xT("T:\\okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),             xT("R:"),    xT("")},
                {xT("D:\\Test.config"),               xT("A:"),    xT("A:\\Test.config")},
                ////{xT("TEST_STRING_3.f"),               xT("B:"),    xT("")}
            };

            for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
                std::tstring_t sStr1 = CxPath::sSetDrive(sData[i][0], sData[i][1]);
                std::tstring_t sStr2 = CxPath::sSetDrive(sData[i][2], sData[i][1]);
                xTEST_EQ(sStr1, sStr2);

                std::tstring_t sStr3 = CxPath::sSetDrive(sData[i][0], sData[i][1]);
                std::tstring_t sStr4 = sData[i][2];
                xTEST_EQ(sStr3, sStr4);
            }
        #endif
    }

    //-------------------------------------
    //sSetDir
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("F:\\"),      xT("F:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("T:\\"),      xT("T:\\okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),         xT("R:\\"),      xT("")},
                {xT("D:\\Test.config"),               xT("A:\\"),      xT("A:\\Test.config")},
                ////{xT("TEST_STRING_3.f"),           xT("B:\\"),      xT("")}
                {xT("D:\\Test\\Test.config"),         xT("A:\\"),      xT("A:\\Test.config")},
                {xT("D:\\Test\\Test.config"),         xT("A:\\1\\2"), xT("A:\\1\\2\\Test.config")}

            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][3] = {
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

            std::tstring_t sStr3 = CxPath::sSetDir(sData[i][0], sData[i][1]);
            std::tstring_t sStr4 = sData[i][2];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sSetFullName
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][3] = {
                /*FilePath*/                          /*NewFileName*/   /*MustBe*/
                {xT("C:\\Test.doc"),                  xT("aaaa.xls"),    xT("C:\\aaaa.xls")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty.fdm"),    xT("Z:\\qwerty.fdm")},
                ////{xT("TEST_STRING_3.doc"),         xT("xxxxxx.c"),    xT("xxxxxx.c")},
                {xT("D:\\Test.config"),               xT("r.txt"),        xT("D:\\r.txt")},
                ////{xT("TEST_STRING_3.f"),           xT("fff.qq"),        xT("fff.qq")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][3] = {
                /*FilePath*/                            /*NewFileName*/   /*MustBe*/
                {xT("/home/Test.doc"),                  xT("aaaa.xls"),   xT("/home/aaaa.xls")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("qwerty.fdm"), xT("/home/qwerty.fdm")},
                ////{xT("TEST_STRING_3.doc"),           xT("xxxxxx.c"),   xT("xxxxxx.c")},
                {xT("/home/Test.config"),               xT("r.txt"),      xT("/home/r.txt")},
                ////{xT("TEST_STRING_3.f"),             xT("fff.qq"),     xT("fff.qq")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sSetFullName(sData[i][0], sData[i][1]);
            std::tstring_t sStr2 = CxPath::sSetFullName(sData[i][2], sData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath::sSetFullName(sData[i][0], sData[i][1]);
            std::tstring_t sStr4 = sData[i][2];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sSetName
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("xxx"),      xT("C:\\xxx.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty"),      xT("Z:\\qwerty.info")},
                ////{xT("TEST_STRING_3.doc"),         xT(""),          xT("")},
                ////{xT("D:\\Test.config"),               xT(""),          xT("D:\\.config")},
                ////{xT("TEST_STRING_3.f"),           xT("B:\\"),      xT("")}
                {xT("D:\\Test\\Test.config"),         xT("rrr"),      xT("D:\\Test\\rrr.config")},
                {xT("D:\\1\\2\\Test\\Test.config"),   xT("yyyyyyyy"), xT("D:\\1\\2\\Test\\yyyyyyyy.config")}

            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][3] = {
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
            std::tstring_t sStr1 = CxPath::sSetName(sData[i][0], sData[i][1]);
            std::tstring_t sStr2 = CxPath::sSetName(sData[i][2], sData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath::sSetName(sData[i][0], sData[i][1]);
            std::tstring_t sStr4 = sData[i][2];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sSetExt
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sData[][3] = {
            {xT("C:\\Test.doc"),                  xT("xls"),    xT("C:\\Test.xls")},
            {xT("C:\\Test"),                      xT("xls"),    xT("C:\\Test.xls")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("fdm"),    xT("Z:\\okoval@winnerauto.ua.fdm")},
            {xT("TEST_STRING_3.doc"),             xT("xxxxxx"),    xT("TEST_STRING_3.xxxxxx")},
            {xT("D:\\Test.config"),               xT("txt"),    xT("D:\\Test.txt")},
            {xT("TEST_STRING_3.f"),               xT("fff"),    xT("TEST_STRING_3.fff")},
            {xT("TEST_STRING_4"),                 xT("fff"),    xT("TEST_STRING_4.fff")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sSetExt(sData[i][0], sData[i][1]);
            std::tstring_t sStr2 = CxPath::sSetExt(sData[i][2], sData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath::sSetExt(sData[i][0], sData[i][1]);
            std::tstring_t sStr4 = sData[i][2];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sRemoveExt
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][2] = {
                {xT("C:\\Test.111\\Test.txt"),                           xT("C:\\Test.111\\Test")},
                {xT("C:\\Test"),                                         xT("C:\\Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++\\pLaunchProject")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][2] = {
                {xT("/home/Test.111/Test.txt"),                          xT("/home/Test.111/Test")},
                {xT("/home/Test"),                                       xT("/home/Test")},
                {xT("Test.txt"),                                         xT("Test")},
                {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("/home/My projects/Borland C++/pLaunchProject")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sRemoveExt(sData[i][0]);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //--------------------------------------------------
    //bIsValid
    xTEST_CASE(cullCaseLoops)
    {
        //TODO: bIsValid
    }

    //--------------------------------------------------
    //bIsNameValid
    xTEST_CASE(cullCaseLoops)
    {
        //TODO: bIsNameValid
    }

    //--------------------------------------------------
    //bIsAbsolute
    xTEST_CASE(cullCaseLoops)
    {
        // true
        {
            const std::tstring_t casData[] = {
                #if xOS_ENV_WIN
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
                m_bRes = CxPath::bIsAbsolute(casData[i]);
                xTEST_EQ(true, m_bRes);
            }
        }

        // false
        {
            const std::tstring_t casData[] = {
                #if xOS_ENV_WIN
                    xT("../../../Source/Debug/CxTest.cpp"),
                    xT("../../../Source/Filesystem/CxPath"),
                    xT("CxTest_CxPath.cpp"),
                    xT("Tests/Source/Common/CxTest_CxSystemInfo.cpp"),
                    xT("p"),
                    xT("1"),
                #elif xOS_ENV_UNIX
                    xT("../../../Source/Debug/CxTest.cpp"),
                    xT("../../../Source/Filesystem/CxPath"),
                    xT("CxTest_CxPath.cpp"),
                    xT("Tests/Source/Common/CxTest_CxSystemInfo.cpp"),
                    xT("p"),
                    xT("1"),
                #endif
            };

            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {
                m_bRes = CxPath::bIsAbsolute(casData[i]);
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //-------------------------------------
    //sSetValidName
    xTEST_CASE(cullCaseLoops)
    {
    #if xOS_ENV_WIN
        const std::tstring_t sTestData[][2] =
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
        const std::tstring_t sTestData[][2] =
        {
            {xT("xxxx"),       xT("xxxx")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            std::tstring_t sStr1 = CxPath::sSetValidName(sTestData[i][0]);
            std::tstring_t sStr2 = CxPath::sSetValidName(sTestData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath::sSetValidName(sTestData[i][0]);
            std::tstring_t sStr4 = sTestData[i][1];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sToWin
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csUnixPath = xT("C:/TestDir");
        const std::tstring_t csWinPath  = xT("C:\\TestDir");

        m_sRes = CxPath::sToWin(csUnixPath, false);
        xTEST_EQ(m_sRes, std::tstring_t(xT("C:\\TestDir")));

        m_sRes = CxPath::sToWin(csUnixPath, true);
        xTEST_EQ(m_sRes, std::tstring_t(xT("C:\\TestDir\\")));

        m_sRes = CxPath::sToWin(csWinPath, true);
        xTEST_EQ(m_sRes, std::tstring_t(xT("C:\\TestDir\\")));

        m_sRes = CxPath::sToWin(csWinPath, false);
        xTEST_EQ(m_sRes, std::tstring_t(xT("C:\\TestDir")));
    }

    //-------------------------------------
    //sToUnix
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csUnixPath = xT("/home/user/Soft/TestDir");
        const std::tstring_t csWinPath  = xT("\\home\\user\\Soft\\TestDir");

        m_sRes = CxPath::sToUnix(csUnixPath,  false);
        xTEST_EQ(m_sRes, std::tstring_t(xT("/home/user/Soft/TestDir")));

        m_sRes = CxPath::sToUnix(csUnixPath,  true);
        xTEST_EQ(m_sRes, std::tstring_t(xT("/home/user/Soft/TestDir/")));

        m_sRes = CxPath::sToUnix(csWinPath,  true);
        xTEST_EQ(m_sRes, std::tstring_t(xT("/home/user/Soft/TestDir/")));

        m_sRes = CxPath::sToUnix(csWinPath,  false);
        xTEST_EQ(m_sRes, std::tstring_t(xT("/home/user/Soft/TestDir")));
    }

    //--------------------------------------------------
    //sToCurrentOs
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t csUnixPath = xT("C:/TestDir");
            const std::tstring_t csWinPath  = xT("C:\\TestDir");

            m_sRes = CxPath::sToCurrentOs(csWinPath,  false);
            xTEST_EQ(m_sRes, std::tstring_t(xT("C:\\TestDir")));

            m_sRes = CxPath::sToCurrentOs(csWinPath,  true);
            xTEST_EQ(m_sRes, std::tstring_t(xT("C:\\TestDir\\")));

            m_sRes = CxPath::sToCurrentOs(csWinPath,  true);
            xTEST_EQ(m_sRes, std::tstring_t(xT("C:\\TestDir\\")));

            m_sRes = CxPath::sToCurrentOs(csWinPath,  false);
            xTEST_EQ(m_sRes, std::tstring_t(xT("C:\\TestDir")));
        #elif xOS_ENV_UNIX
            const std::tstring_t csUnixPath = xT("/home/user/Soft/TestDir");
            const std::tstring_t csWinPath  = xT("\\home\\user\\Soft\\TestDir");

            m_sRes = CxPath::sToCurrentOs(csWinPath,  false);
            xTEST_EQ(m_sRes, std::tstring_t(xT("/home/user/Soft/TestDir")));

            m_sRes = CxPath::sToCurrentOs(csWinPath,  true);
            xTEST_EQ(m_sRes, std::tstring_t(xT("/home/user/Soft/TestDir/")));

            m_sRes = CxPath::sToCurrentOs(csWinPath,  true);
            xTEST_EQ(m_sRes, std::tstring_t(xT("/home/user/Soft/TestDir/")));

            m_sRes = CxPath::sToCurrentOs(csWinPath,  false);
            xTEST_EQ(m_sRes, std::tstring_t(xT("/home/user/Soft/TestDir")));
        #endif
    }

    //-------------------------------------
    //sGetAbsolute
    xTEST_CASE(cullCaseLoops)
    {
        std::vector<std::tstring_t> vsArgs;

        m_bRes = CxCommandLine::bGetArgs(&vsArgs);
        xTEST_EQ(true, m_bRes);

        m_sRes = CxPath::sGetAbsolute(vsArgs.at(0));
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //sGetShortName
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sData[][2] = {
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
            std::tstring_t sStr1 = CxPath::sGetShortName(sData[i][0], 4);
            std::tstring_t sStr2 = sData[i][1];
            xTEST_EQ(sStr1, sStr2);
        }
    }

    //-------------------------------------
    //sGetShort
    xTEST_CASE(cullCaseLoops)
    {
        {
            #if xOS_ENV_WIN
                std::tstring_t sFilePath = xT("C:\\Test.txt");
            #elif xOS_ENV_UNIX
                std::tstring_t sFilePath = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
            #endif

	        m_sRes = CxPath::sGetShort(sFilePath, 4);
            #if defined(xOS_ENV_WIN)
                xTEST_EQ(std::tstring_t(xT("C:\\Test.txt")), m_sRes);
            #elif defined(xOS_ENV_UNIX)
                xTEST_EQ(std::tstring_t(xT("/.../filename")), m_sRes);
            #endif
        }

        {
            #if xOS_ENV_WIN
                std::tstring_t sFilePath = xT("C:\\Test.txt");
            #elif xOS_ENV_UNIX
                std::tstring_t sFilePath = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
            #endif

	        m_sRes = CxPath::sGetShort(sFilePath, 200);
            #if defined(xOS_ENV_WIN)
                xTEST_EQ(std::tstring_t(xT("/.../filename")), m_sRes);
            #elif defined(xOS_ENV_UNIX)

            #endif
        }

        {
            #if xOS_ENV_WIN
                std::tstring_t sFilePath = xT("D:\\xVCL\\Include\\xVCL\\Units\\Gui\\vSpeedButton_LoadDrives.cpp");
            #elif xOS_ENV_UNIX
                std::tstring_t sFilePath = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
            #endif

	        m_sRes = CxPath::sGetShort(sFilePath, 15);
            #if defined(xOS_ENV_WIN)
                xTEST_EQ(std::tstring_t(xT("D:\\...\\vSpeedButton_LoadDrives.cpp")), m_sRes);
            #elif defined(xOS_ENV_UNIX)
                xTEST_EQ(std::tstring_t(xT("/.../filename")), m_sRes);
            #endif
        }
    }

    //-------------------------------------
    //sSlashAppend
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("C:\\Test.doc\\")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info\\")},
                {xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc\\")},
                {xT("D:\\Test.config"),               xT("D:\\Test.config\\")},
                {xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f\\")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][3] = {
                {xT("/home/Test.doc"),                  xT("/home/Test.doc/")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info/")},
                {xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc/")},
                {xT("/home/Test.config"),               xT("/home/Test.config/")},
                {xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f/")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sSlashAppend(sData[i][0]);
            std::tstring_t sStr2 = CxPath::sSlashAppend(sData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath::sSlashAppend(sData[i][0]);
            std::tstring_t sStr4 = sData[i][1];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //-------------------------------------
    //sSlashRemove
    xTEST_CASE(cullCaseLoops)
    {
        #if xOS_ENV_WIN
            const std::tstring_t sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("C:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info")},
                {xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc")},
                {xT("D:\\Test.config"),               xT("D:\\Test.config")},
                {xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f")}
            };
        #elif xOS_ENV_UNIX
            const std::tstring_t sData[][3] = {
                {xT("/home/Test.doc"),                  xT("/home/Test.doc")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info")},
                {xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc")},
                {xT("/home/Test.config"),               xT("/home/Test.config")},
                {xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            std::tstring_t sStr1 = CxPath::sSlashRemove(sData[i][0]);
            std::tstring_t sStr2 = CxPath::sSlashRemove(sData[i][1]);
            xTEST_EQ(sStr1, sStr2);

            std::tstring_t sStr3 = CxPath::sSlashRemove(sData[i][0]);
            std::tstring_t sStr4 = sData[i][1];
            xTEST_EQ(sStr3, sStr4);
        }
    }

    //--------------------------------------------------
    //uiGetMaxSize
    xTEST_CASE(cullCaseLoops)
    {
        m_uiRes = CxPath::uiGetMaxSize();
        xTEST_LESS(0U, m_uiRes);
    }

    //--------------------------------------------------
    //uiGetNameMaxSize
    xTEST_CASE(cullCaseLoops)
    {
        m_uiRes = CxPath::uiGetNameMaxSize();
        xTEST_LESS(0U, m_uiRes);
    }

    return true;
}
//---------------------------------------------------------------------------
