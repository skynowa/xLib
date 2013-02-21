/**
 * \file   CxTest_CxDir.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxDir.h>

#include <xLib/Common/CxString.h>


//------------------------------------------------------------------------------
CxTest_CxDir::CxTest_CxDir() {

}
//------------------------------------------------------------------------------
CxTest_CxDir::~CxTest_CxDir() {

}
//------------------------------------------------------------------------------
/* virtual */
void
CxTest_CxDir::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csTempScanDirPath = tempDirPath() + CxConst::xSLASH + xT("Scan");
    const std::tstring_t csMask            = xT("*.txt");

#if   xOS_ENV_WIN
    const std::tstring_t csFilePath        = tempDirPath() + xT("\\Test.txt");
    const std::tstring_t csRootTestDirPath = tempDirPath() + xT("\\Test_Dir");
    const std::tstring_t csDirPath         = tempDirPath() + xT("\\Test_Dir\\1\\2\\3");
    const std::tstring_t csDirPath2        = tempDirPath() + xT("\\Test_Dir\\1\\2\\3\\4");
    const std::tstring_t csNewFilePath     = tempDirPath() + xT("\\New.Test.txt");
    const std::tstring_t csBakFilePath     = tempDirPath() + xT("\\Test_Static.txt.bak");
    const std::tstring_t csFilePathSt      = tempDirPath() + xT("\\Test_Static.txt");
#elif xOS_ENV_UNIX
    const std::tstring_t csFilePath        = tempDirPath() + xT("/Test.txt");
    const std::tstring_t csRootTestDirPath = tempDirPath() + xT("/Test_Dir");
    const std::tstring_t csDirPath         = tempDirPath() + xT("/Test_Dir/1/2/3");
    const std::tstring_t csDirPath2        = tempDirPath() + xT("/Test_Dir/1/2/3/4");
    const std::tstring_t csNewFilePath     = tempDirPath() + xT("/New.Test.txt");
    const std::tstring_t csBakFilePath     = tempDirPath() + xT("/Test_Static.txt.bak");
    const std::tstring_t csFilePathSt      = tempDirPath() + xT("/Test_Static.txt");
#endif


    xTEST_CASE("CxDir::dirsFind", cullCaseLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::tstring_t sDirPathes[] =
        {
            csTempScanDirPath + CxConst::xSLASH + xT("A"),
            csTempScanDirPath + CxConst::xSLASH + xT("B"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            CxDir(sDirPathes[i]).pathCreate();
        }

        {
            m_vsRv.clear();

            CxDir(csTempScanDirPath).dirsFind(CxConst::xMASK_ALL, false, &m_vsRv);
            // TODO: CxString::vStdVectorPrintT(m_vsRv);

            xTEST_EQ((size_t)2, m_vsRv.size());
        }

        {
            m_vsRv.clear();
            CxDir(csTempScanDirPath).dirsFind(CxConst::xMASK_ALL, true, &m_vsRv);
            //CxString::vStdVectorPrintT(m_vsRv);

            xTEST_EQ(xARRAY_SIZE(sDirPathes), m_vsRv.size());
        }
    }

    xTEST_CASE("CxDir::filesFind", cullCaseLoops)
    {
        //-------------------------------------
        // prepare for csTempScanDirPath (create files)
        const std::tstring_t g_sFilePathes[] =
        {
            csTempScanDirPath + CxConst::xSLASH + xT("File_1"),
            csTempScanDirPath + CxConst::xSLASH + xT("File_2"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("File_3"),
            csTempScanDirPath + CxConst::xSLASH + xT("B") + CxConst::xSLASH + xT("File_4"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("File_5"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA") + CxConst::xSLASH + xT("File_6")
        };

        for (size_t i = 0; i < xARRAY_SIZE(g_sFilePathes); ++ i) {
            CxFile sfFile;

            sfFile.create(g_sFilePathes[i], CxFile::omWrite, true);
        }

        {
            m_vsRv.clear();
            CxDir(csTempScanDirPath).filesFind(CxConst::xMASK_ALL, false, &m_vsRv);
            //CxString::vStdVectorPrintT(m_vsRv);

            xTEST_EQ((size_t)2, m_vsRv.size());
        }

        {
            m_vsRv.clear();
            CxDir(csTempScanDirPath).filesFind(CxConst::xMASK_ALL, true, &m_vsRv);
            //CxString::vStdVectorPrintT(m_vsRv);

            xTEST_EQ(xARRAY_SIZE(g_sFilePathes), m_vsRv.size());
        }
    }

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

    xTEST_CASE("CxDir::create", cullCaseLoops)
    {
        CxDir(csDirPath2).create();
    }

    xTEST_CASE("CxDir::isDir", cullCaseLoops)
    {
        m_bRv = CxDir(csDirPath2).isDir();
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE("CxDir::isExists", cullCaseLoops)
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

    xTEST_CASE("CxDir::isEmpty", cullCaseLoops)
    {
        m_bRv = CxDir(csDirPath).isEmpty(CxConst::xMASK_ALL);
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir(csDirPath2).isEmpty(CxConst::xMASK_ALL);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxDir(tempDirPath()).isEmpty(CxConst::xMASK_ALL);
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE("CxDir::isRoot", cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            const std::tstring_t sTestData[][2] = {
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
            const std::tstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("false")},
                {xT("vw4g56be56||||\a\n\t///lk;'"), xT("false")},
                {xT("/"),             xT("true")},
                {xT("\\"),            xT("false")},
                {xT("A:"),            xT("false")},
                {xT("D:/"),           xT("false")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            bool bRes1 = CxDir(sTestData[i][0]).isRoot();
            bool bRes2 = CxString::strToBool(sTestData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    xTEST_CASE("CxDir::setCurrent", cullCaseLoops)
    {
        m_sRv = CxDir::current();
        xTEST_EQ(false, m_sRv.empty());

        CxDir::setCurrent( tempDirPath() );
        CxDir::setCurrent(m_sRv);
    }

    xTEST_CASE("CxDir::current", cullCaseLoops)
    {
        std::tstring_t sRv = CxDir::current();
        xTEST_EQ(m_sRv, sRv);
    }

    xTEST_CASE("CxDir::temp", cullCaseLoops)
    {
        m_sRv = CxDir::temp();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxDir::sGetTemp(): %s"), m_sRv.c_str());
        #endif
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("CxDir::pathCreate", cullCaseLoops)
    {
        CxDir(csDirPath).pathCreate();
    }

    xTEST_CASE("CxDir::copy", cullCaseLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::tstring_t csDirSource = tempDirPath() + CxConst::xSLASH + xT("DirSource");
        const std::tstring_t csDirDest   = tempDirPath() + CxConst::xSLASH + xT("DirDest");

        const std::tstring_t sDirPathes[] =
        {
            csDirSource,
            csDirSource + CxConst::xSLASH + xT("AA"),
            csDirSource + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            CxDir(sDirPathes[i]).pathCreate();
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

    xTEST_CASE("CxDir::move", cullCaseLoops)
    {
        //-------------------------------------
        // prepare for csTempScanDirPath (create dirs)
        const std::tstring_t csDirSource = tempDirPath() + CxConst::xSLASH + xT("Source");
        const std::tstring_t csDirDest   = tempDirPath() + CxConst::xSLASH + xT("Dest");

        const std::tstring_t sDirPathes[] =
        {
            csDirSource,
            csDirSource + CxConst::xSLASH + xT("dd"),
            csDirSource + CxConst::xSLASH + xT("XX") + CxConst::xSLASH + xT("111")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            CxDir(sDirPathes[i]).pathCreate();
        }

        //-------------------------------------
        //bMove
        CxDir(csDirSource).move(csDirDest, true);
        CxDir(csDirDest).remove();
    }

    xTEST_CASE("CxDir::pathClear", cullCaseLoops)
    {
        CxDir(csDirPath).pathClear();
    }

    xTEST_CASE("CxDir::remove", cullCaseLoops)
    {
        CxDir(csDirPath2).remove();
    }

    xTEST_CASE("CxDir::tryRemove", cullCaseLoops)
    {
        CxDir(csDirPath2).pathCreate();
        CxDir(csDirPath2).tryRemove(10, 5);
    }

    xTEST_CASE("CxDir::pathDelete", cullCaseLoops)
    {
        CxDir(csDirPath).pathCreate();
        CxDir(csDirPath).pathDelete();
    }
}
//------------------------------------------------------------------------------
