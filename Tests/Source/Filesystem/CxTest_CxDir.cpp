/**
 * \file   CxTest_CxDir.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxDir.h>

#include <xLib/Core/CxString.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxDir::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t csTempScanDirPath = tempDirPath() + CxConst::slash() + xT("Scan");
    std::ctstring_t csMask            = xT("*.txt");

#if   xOS_ENV_WIN
    std::ctstring_t csFilePath        = tempDirPath() + xT("\\Test.txt");
    std::ctstring_t csRootTestDirPath = tempDirPath() + xT("\\Test_Dir");
    std::ctstring_t csDirPath         = tempDirPath() + xT("\\Test_Dir\\1\\2\\3");
    std::ctstring_t csDirPath2        = tempDirPath() + xT("\\Test_Dir\\1\\2\\3\\4");
    std::ctstring_t csNewFilePath     = tempDirPath() + xT("\\New.Test.txt");
    std::ctstring_t csBakFilePath     = tempDirPath() + xT("\\Test_Static.txt.bak");
    std::ctstring_t csFilePathSt      = tempDirPath() + xT("\\Test_Static.txt");
#elif xOS_ENV_UNIX
    std::ctstring_t csFilePath        = tempDirPath() + xT("/Test.txt");
    std::ctstring_t csRootTestDirPath = tempDirPath() + xT("/Test_Dir");
    std::ctstring_t csDirPath         = tempDirPath() + xT("/Test_Dir/1/2/3");
    std::ctstring_t csDirPath2        = tempDirPath() + xT("/Test_Dir/1/2/3/4");
    std::ctstring_t csNewFilePath     = tempDirPath() + xT("/New.Test.txt");
    std::ctstring_t csBakFilePath     = tempDirPath() + xT("/Test_Static.txt.bak");
    std::ctstring_t csFilePathSt      = tempDirPath() + xT("/Test_Static.txt");
#endif


    /*******************************************************************************
    *    prepare
    *
    *******************************************************************************/

    {
        CxDir(csRootTestDirPath).pathDelete();
        CxDir(csDirPath).pathCreate();
    }

    /*******************************************************************************
    *    static
    *
    *******************************************************************************/

    xTEST_CASE("CxDir::create", a_caseLoops)
    {
        CxDir(csDirPath2).create();
    }

    xTEST_CASE("CxDir::isDir", a_caseLoops)
    {
        m_bRv = CxDir(csDirPath2).isDir();
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxDir::isExists", a_caseLoops)
    {
        m_bRv = CxDir(csDirPath).isExists();
        xTEST_EQ(true, m_bRv);

        m_bRv = CxDir(xT("b:")).isExists();
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir(xT("sdfasdf:")).isExists();
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir(xT("C:\\WINDOWS\\NOTEPAD.EXE")).isExists();
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir(xT("C:\\pagefile.sys")).isExists();
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDir::isEmpty", a_caseLoops)
    {
        m_bRv = CxDir(csDirPath).isEmpty(CxConst::maskAll());
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir(csDirPath2).isEmpty(CxConst::maskAll());
        xTEST_EQ(true, m_bRv);

        m_bRv = CxDir(tempDirPath()).isEmpty(CxConst::maskAll());
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDir::isRoot", a_caseLoops)
    {
        #if   xOS_ENV_WIN
            std::ctstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("false")},
                {xT("vw4g56be56||||\a\n\t///lk;'"), xT("false")},
                {xT("/"),             xT("false")},
                {xT("\\"),            xT("false")},
                {xT("A:\\"),          xT("true")},
                {xT("D:\\"),          xT("true")},
                {xT("A:/"),           xT("true")},
                {xT("D:/"),           xT("true")},
                {xT("Z::"),           xT("false")},
                {xT("\\\\"),          xT("false")},
                {xT("B:"),            xT("false")},
                {xT("B"),             xT("false")}
            };
        #elif xOS_ENV_UNIX
            std::ctstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("false")},
                {xT("vw4g56be56||||\a\n\t///lk;'"), xT("false")},
                {xT("/"),             xT("true")},
                {xT("\\"),            xT("false")},
                {xT("A:"),            xT("false")},
                {xT("D:/"),           xT("false")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            bool_t bRes1 = CxDir(sTestData[i][0]).isRoot();
            bool_t bRes2 = CxString::castBool(sTestData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    xTEST_CASE("CxDir::setCurrent", a_caseLoops)
    {
        m_sRv = CxDir::current();
        xTEST_EQ(false, m_sRv.empty());

        CxDir::setCurrent( tempDirPath() );
        CxDir::setCurrent(m_sRv);
    }

    xTEST_CASE("CxDir::current", a_caseLoops)
    {
        std::tstring_t sRv = CxDir::current();
        xTEST_EQ(m_sRv, sRv);
    }

    xTEST_CASE("CxDir::temp", a_caseLoops)
    {
        m_sRv = CxDir::temp();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxDir::sGetTemp(): %s"), m_sRv.c_str());
        #endif
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxDir::pathCreate", a_caseLoops)
    {
        CxDir(csDirPath).pathCreate();
    }

    xTEST_CASE("CxDir::copy", a_caseLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        std::ctstring_t csDirSource = tempDirPath() + CxConst::slash() + xT("DirSource");
        std::ctstring_t csDirDest   = tempDirPath() + CxConst::slash() + xT("DirDest");

        std::ctstring_t sDirPaths[] =
        {
            csDirSource,
            csDirSource + CxConst::slash() + xT("AA"),
            csDirSource + CxConst::slash() + xT("AA") + CxConst::slash() + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPaths); ++ i) {
            CxDir(sDirPaths[i]).pathCreate();
        }

        CxDir(csDirDest).pathDelete();

        //-------------------------------------
        // vCopy
        CxDir(csDirSource).copy(csDirDest, true);
        CxDir(csDirDest).remove();
        CxDir(csDirSource).copy(csDirDest, false);
        CxDir(csDirDest).pathDelete();
        CxDir(csDirSource).pathDelete();
    }

    xTEST_CASE("CxDir::move", a_caseLoops)
    {
        //-------------------------------------
        // prepare for csTempScanDirPath (create dirs)
        std::ctstring_t csDirSource = tempDirPath() + CxConst::slash() + xT("Source");
        std::ctstring_t csDirDest   = tempDirPath() + CxConst::slash() + xT("Dest");

        std::ctstring_t sDirPaths[] =
        {
            csDirSource,
            csDirSource + CxConst::slash() + xT("dd"),
            csDirSource + CxConst::slash() + xT("XX") + CxConst::slash() + xT("111")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPaths); ++ i) {
            CxDir(sDirPaths[i]).pathCreate();
        }

        //-------------------------------------
        //bMove
        CxDir(csDirSource).move(csDirDest, true);
        CxDir(csDirDest).remove();
    }

    xTEST_CASE("CxDir::pathClear", a_caseLoops)
    {
        CxDir(csDirPath).pathClear();
    }

    xTEST_CASE("CxDir::remove", a_caseLoops)
    {
        CxDir(csDirPath2).remove();
    }

    xTEST_CASE("CxDir::tryRemove", a_caseLoops)
    {
        CxDir(csDirPath2).pathCreate();
        CxDir(csDirPath2).tryRemove(10, 5);
    }

    xTEST_CASE("CxDir::pathDelete", a_caseLoops)
    {
        CxDir(csDirPath).pathCreate();
        CxDir(csDirPath).pathDelete();
    }
}
//-------------------------------------------------------------------------------------------------
