/**
 * \file   Test_Dir.cpp
 * \brief
 */


#include "Test_Dir.h"

#include <xLib/Core/String.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Dir)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Dir::unit()
{
    std::ctstring_t csTempScanDirPath = tempDirPath() + Const::slash() + xT("Scan");
    std::ctstring_t csMask            = xT("*.txt");

#if   xENV_WIN
    std::ctstring_t csFilePath        = tempDirPath() + xT("\\Test.txt");
    std::ctstring_t csRootTestDirPath = tempDirPath() + xT("\\Test_Dir");
    std::ctstring_t csDirPath         = tempDirPath() + xT("\\Test_Dir\\1\\2\\3");
    std::ctstring_t csDirPath2        = tempDirPath() + xT("\\Test_Dir\\1\\2\\3\\4");
    std::ctstring_t csNewFilePath     = tempDirPath() + xT("\\New.Test.txt");
    std::ctstring_t csBakFilePath     = tempDirPath() + xT("\\Test_Static.txt.bak");
    std::ctstring_t csFilePathSt      = tempDirPath() + xT("\\Test_Static.txt");
#elif xENV_UNIX
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
        Dir(csRootTestDirPath).pathDelete();
        Dir(csDirPath).pathCreate();
    }

    /*******************************************************************************
    *    static
    *
    *******************************************************************************/

    xTEST_CASE("create")
    {
        Dir(csDirPath2).create();
    }

    xTEST_CASE("isDir")
    {
        m_bRv = Dir(csDirPath2).isDir();
        xTEST_EQ(m_bRv, true);
    }

    xTEST_CASE("isExists")
    {
        m_bRv = Dir(csDirPath).isExists();
        xTEST_EQ(m_bRv, true);

        m_bRv = Dir(xT("b:")).isExists();
        xTEST_EQ(m_bRv, false);

        m_bRv = Dir(xT("sdfasdf:")).isExists();
        xTEST_EQ(m_bRv, false);

        m_bRv = Dir(xT("C:\\WINDOWS\\NOTEPAD.EXE")).isExists();
        xTEST_EQ(m_bRv, false);

        m_bRv = Dir(xT("C:\\pagefile.sys")).isExists();
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("isEmpty")
    {
        m_bRv = Dir(csDirPath).isEmpty(Const::maskAll());
        xTEST_EQ(m_bRv, false);

        m_bRv = Dir(csDirPath2).isEmpty(Const::maskAll());
        xTEST_EQ(m_bRv, true);

        m_bRv = Dir(tempDirPath()).isEmpty(Const::maskAll());
        xTEST_EQ(m_bRv, false);
    }

    xTEST_CASE("isRoot")
    {
        #if   xENV_WIN
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
        #elif xENV_UNIX
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
            bool_t bRes1 = Dir(sTestData[i][0]).isRoot();
            bool_t bRes2 = String::castBool(sTestData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    xTEST_CASE("setCurrent")
    {
        m_sRv = Dir::current();
        xTEST_EQ(false, m_sRv.empty());

        Dir::setCurrent( tempDirPath() );
        Dir::setCurrent(m_sRv);
    }

    xTEST_CASE("current")
    {
        std::tstring_t sRv = Dir::current();
        xTEST_EQ(m_sRv, sRv);
    }

    xTEST_CASE("temp")
    {
        m_sRv = Dir::temp();
        #if xTEST_IGNORE
            xTRACEV(xT("\tDir::sGetTemp(): %s"), m_sRv.c_str());
        #endif
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("pathCreate")
    {
        Dir(csDirPath).pathCreate();
    }

    xTEST_CASE("copy")
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        std::ctstring_t csDirSource = tempDirPath() + Const::slash() + xT("DirSource");
        std::ctstring_t csDirDest   = tempDirPath() + Const::slash() + xT("DirDest");

        std::ctstring_t sDirPaths[] =
        {
            csDirSource,
            csDirSource + Const::slash() + xT("AA"),
            csDirSource + Const::slash() + xT("AA") + Const::slash() + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPaths); ++ i) {
            Dir(sDirPaths[i]).pathCreate();
        }

        Dir(csDirDest).pathDelete();

        //-------------------------------------
        // vCopy
        Dir(csDirSource).copy(csDirDest, true);
        Dir(csDirDest).remove();
        Dir(csDirSource).copy(csDirDest, false);
        Dir(csDirDest).pathDelete();
        Dir(csDirSource).pathDelete();
    }

    xTEST_CASE("move")
    {
        //-------------------------------------
        // prepare for csTempScanDirPath (create dirs)
        std::ctstring_t csDirSource = tempDirPath() + Const::slash() + xT("Source");
        std::ctstring_t csDirDest   = tempDirPath() + Const::slash() + xT("Dest");

        std::ctstring_t sDirPaths[] =
        {
            csDirSource,
            csDirSource + Const::slash() + xT("dd"),
            csDirSource + Const::slash() + xT("XX") + Const::slash() + xT("111")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPaths); ++ i) {
            Dir(sDirPaths[i]).pathCreate();
        }

        //-------------------------------------
        //bMove
        Dir(csDirSource).move(csDirDest, true);
        Dir(csDirDest).remove();
    }

    xTEST_CASE("pathClear")
    {
        Dir(csDirPath).pathClear();
    }

    xTEST_CASE("remove")
    {
        Dir(csDirPath2).remove();
    }

    xTEST_CASE("tryRemove")
    {
        Dir(csDirPath2).pathCreate();
        Dir(csDirPath2).tryRemove(10, 5);
    }

    xTEST_CASE("pathDelete")
    {
        Dir(csDirPath).pathCreate();
        Dir(csDirPath).pathDelete();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
