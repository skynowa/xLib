/**
 * \file   CxTest_CxDir.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxDir.h>


//---------------------------------------------------------------------------
CxTest_CxDir::CxTest_CxDir() {

}
//---------------------------------------------------------------------------
CxTest_CxDir::~CxTest_CxDir() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxDir::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::string_t csTempScanDirPath = sGetWorkDirPath() + CxConst::xSLASH + xT("Scan");
    const std::string_t csMask            = xT("*.txt");

#if defined(xOS_ENV_WIN)
    const std::string_t csFilePath        = sGetWorkDirPath() + xT("\\Test.txt");
    const std::string_t csRootTestDirPath = sGetWorkDirPath() + xT("\\Test_Dir");
    const std::string_t csDirPath         = sGetWorkDirPath() + xT("\\Test_Dir\\1\\2\\3");
    const std::string_t csDirPath2        = sGetWorkDirPath() + xT("\\Test_Dir\\1\\2\\3\\4");
    const std::string_t csNewFilePath        = sGetWorkDirPath() + xT("\\New.Test.txt");
    const std::string_t csBakFilePath        = sGetWorkDirPath() + xT("\\Test_Static.txt.bak");
    const std::string_t csFilePathSt        = sGetWorkDirPath() + xT("\\Test_Static.txt");
#elif defined(xOS_ENV_UNIX)
    const std::string_t csFilePath        = sGetWorkDirPath() + xT("/Test.txt");
    const std::string_t csRootTestDirPath = sGetWorkDirPath() + xT("/Test_Dir");
    const std::string_t csDirPath         = sGetWorkDirPath() + xT("/Test_Dir/1/2/3");
    const std::string_t csDirPath2        = sGetWorkDirPath() + xT("/Test_Dir/1/2/3/4");
    const std::string_t csNewFilePath     = sGetWorkDirPath() + xT("/New.Test.txt");
    const std::string_t csBakFilePath     = sGetWorkDirPath() + xT("/Test_Static.txt.bak");
    const std::string_t csFilePathSt      = sGetWorkDirPath() + xT("/Test_Static.txt");
#endif

    /****************************************************************************
    *    prepare
    *
    *****************************************************************************/

    {
        m_bRes = CxDir::bDeleteForce(csRootTestDirPath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bCreateForce(csDirPath);
        xTEST_DIFF(FALSE, m_bRes);
    }

    /****************************************************************************
    *    static
    *
    *****************************************************************************/

    //-------------------------------------
    //bCreate
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bCreate(csDirPath2);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsDir
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bIsDir(csDirPath2);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bIsExists(csDirPath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bIsExists(xT("y:"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxDir::bIsExists(xT("sdfasdf:"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxDir::bIsExists(xT("C:\\WINDOWS\\NOTEPAD.EXE"));
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxDir::bIsExists(xT("C:\\pagefile.sys"));
        xTEST_EQ(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsEmpty
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bIsEmpty(csDirPath, CxConst::xMASK_ALL);
        xTEST_EQ(FALSE, m_bRes);

        m_bRes = CxDir::bIsEmpty(csDirPath2, CxConst::xMASK_ALL);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bIsEmpty(sGetWorkDirPath(), CxConst::xMASK_ALL);
        xTEST_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bIsRoot
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const std::string_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("FALSE")},
                {xT(""),              xT("FALSE")},
                {xT("/"),             xT("FALSE")},
                {xT("\\"),            xT("FALSE")},
                {xT("A:\\"),          xT("TRUE")},
                {xT("D:\\"),          xT("TRUE")},
                {xT("A:/"),           xT("TRUE")},
                {xT("D:/"),           xT("TRUE")},
                {xT("Z::"),           xT("FALSE")},
                {xT("\\\\"),          xT("FALSE")},
                {xT("B:"),            xT("FALSE")},
                {xT("B"),             xT("FALSE")}
            };
        #elif defined(xOS_ENV_UNIX)
            const std::string_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("FALSE")},
                {xT(""),              xT("FALSE")},
                {xT("/"),             xT("TRUE")},
                {xT("\\"),            xT("FALSE")},
                {xT("A:"),            xT("FALSE")},
                {xT("D:/"),           xT("FALSE")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            BOOL bRes1 = CxDir::bIsRoot(sTestData[i][0]);
            BOOL bRes2 = CxString::bStrToBool(sTestData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    //-------------------------------------
    //bSetCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxDir::sGetCurrent();
        xTEST_EQ(false, m_sRes.empty());

        m_bRes = CxDir::bSetCurrent( sGetWorkDirPath() );
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bSetCurrent(m_sRes);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //sGetCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
        std::string_t sRes = CxDir::sGetCurrent();
        xTEST_EQ(m_sRes, sRes);
    }

    //-------------------------------------
    //sGetTempPath
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = CxDir::sGetTemp();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxDir::sGetTemp(): %s"), m_sRes.c_str());
        #endif
        xTEST_EQ(false, m_sRes.empty());
    }

    //-------------------------------------
    //bCreateForce
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bCreateForce(csDirPath);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bCopy
    xTEST_BLOCK(cullBlockLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::string_t csDirSource = sGetWorkDirPath() + CxConst::xSLASH + xT("Source");
        const std::string_t csDirDest   = sGetWorkDirPath() + CxConst::xSLASH + xT("Dest");

        const std::string_t sDirPathes[] =
        {
            csDirSource,
            csDirSource + CxConst::xSLASH + xT("AA"),
            csDirSource + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            m_bRes = CxDir::bCreateForce(sDirPathes[i]);
            xTEST_DIFF(FALSE, m_bRes);
        }

        m_bRes = CxDir::bDeleteForce(csDirDest);
        xTEST_DIFF(FALSE, m_bRes);

        //-------------------------------------
        //bCopy
        m_bRes = CxDir::bCopy(csDirSource, csDirDest, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDelete(csDirDest);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bCopy(csDirSource, csDirDest, FALSE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDeleteForce(csDirDest);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDeleteForce(csDirSource);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bMove
    xTEST_BLOCK(cullBlockLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::string_t csDirSource = sGetWorkDirPath() + CxConst::xSLASH + xT("Source");
        const std::string_t csDirDest   = sGetWorkDirPath() + CxConst::xSLASH + xT("Dest");

        const std::string_t sDirPathes[] =
        {
            csDirSource,
            csDirSource + CxConst::xSLASH + xT("dd"),
            csDirSource + CxConst::xSLASH + xT("XX") + CxConst::xSLASH + xT("111")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            m_bRes = CxDir::bCreateForce(sDirPathes[i]);
            xTEST_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //bMove
        m_bRes = CxDir::bMove(csDirSource, csDirDest, TRUE);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDelete(csDirDest);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bFindDirs
    xTEST_BLOCK(cullBlockLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::string_t sDirPathes[] =
        {
            csTempScanDirPath + CxConst::xSLASH + xT("A"),
            csTempScanDirPath + CxConst::xSLASH + xT("B"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            m_bRes = CxDir::bCreateForce(sDirPathes[i]);
            xTEST_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //bFindDirs
        {
            m_vsRes.clear();
            m_bRes = CxDir::bFindDirs(csTempScanDirPath, CxConst::xMASK_ALL, FALSE, &m_vsRes);
            xTEST_DIFF(FALSE, m_bRes);
            //CxString::vStdVectorPrintT(m_vsRes);

            xTEST_EQ((size_t)2, m_vsRes.size());
        }

        //-------------------------------------
        //bFindDirs
        {
            m_vsRes.clear();
            m_bRes = CxDir::bFindDirs(csTempScanDirPath, CxConst::xMASK_ALL, TRUE, &m_vsRes);
            xTEST_DIFF(FALSE, m_bRes);
            //CxString::vStdVectorPrintT(m_vsRes);

            xTEST_EQ(xARRAY_SIZE(sDirPathes), m_vsRes.size());
        }
    }

    //-------------------------------------
    //bFindFiles
    xTEST_BLOCK(cullBlockLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create files)
        const std::string_t g_sFilePathes[] =
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

            m_bRes = sfFile.bCreate(g_sFilePathes[i], CxFile::omWrite, TRUE);
            xTEST_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //bFindFiles
        {
            m_vsRes.clear();
            m_bRes = CxDir::bFindFiles(csTempScanDirPath, CxConst::xMASK_ALL, FALSE, &m_vsRes);
            xTEST_DIFF(FALSE, m_bRes);
            //CxString::vStdVectorPrintT(m_vsRes);

            xTEST_EQ((size_t)2, m_vsRes.size());
        }

        //-------------------------------------
        //bFindFiles
        {
            m_vsRes.clear();
            m_bRes = CxDir::bFindFiles(csTempScanDirPath, CxConst::xMASK_ALL, TRUE, &m_vsRes);
            xTEST_DIFF(FALSE, m_bRes);
            //CxString::vStdVectorPrintT(m_vsRes);

            xTEST_EQ(xARRAY_SIZE(g_sFilePathes), m_vsRes.size());
        }
    }

    //-------------------------------------
    //bClearForce
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bClearForce(csDirPath);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bDelete(csDirPath2);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bTryDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bCreateForce(csDirPath2);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bTryDelete(csDirPath2, 10, 5);
        xTEST_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bDeleteForce
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bCreateForce(csDirPath);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDeleteForce(csDirPath);
        xTEST_DIFF(FALSE, m_bRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
