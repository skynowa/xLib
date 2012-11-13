/**
 * \file   CxTest_CxDir.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxDir.h>

#include <xLib/Common/CxString.h>


//---------------------------------------------------------------------------
CxTest_CxDir::CxTest_CxDir() {

}
//---------------------------------------------------------------------------
CxTest_CxDir::~CxTest_CxDir() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxDir::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csTempScanDirPath = sTempDirPath() + CxConst::xSLASH + xT("Scan");
    const std::tstring_t csMask            = xT("*.txt");

#if   xOS_ENV_WIN
    const std::tstring_t csFilePath        = sTempDirPath() + xT("\\Test.txt");
    const std::tstring_t csRootTestDirPath = sTempDirPath() + xT("\\Test_Dir");
    const std::tstring_t csDirPath         = sTempDirPath() + xT("\\Test_Dir\\1\\2\\3");
    const std::tstring_t csDirPath2        = sTempDirPath() + xT("\\Test_Dir\\1\\2\\3\\4");
    const std::tstring_t csNewFilePath     = sTempDirPath() + xT("\\New.Test.txt");
    const std::tstring_t csBakFilePath     = sTempDirPath() + xT("\\Test_Static.txt.bak");
    const std::tstring_t csFilePathSt      = sTempDirPath() + xT("\\Test_Static.txt");
#elif xOS_ENV_UNIX
    const std::tstring_t csFilePath        = sTempDirPath() + xT("/Test.txt");
    const std::tstring_t csRootTestDirPath = sTempDirPath() + xT("/Test_Dir");
    const std::tstring_t csDirPath         = sTempDirPath() + xT("/Test_Dir/1/2/3");
    const std::tstring_t csDirPath2        = sTempDirPath() + xT("/Test_Dir/1/2/3/4");
    const std::tstring_t csNewFilePath     = sTempDirPath() + xT("/New.Test.txt");
    const std::tstring_t csBakFilePath     = sTempDirPath() + xT("/Test_Static.txt.bak");
    const std::tstring_t csFilePathSt      = sTempDirPath() + xT("/Test_Static.txt");
#endif



    xTEST_CASE(CxDir::vFindDirs, cullCaseLoops)
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
xTRACE_POINT;
        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            CxDir::vCreateForce(sDirPathes[i]);
        }
xTRACE_POINT;
        {
            m_vsRv.clear();
xTRACE_POINT;
            CxDir::vFindDirs(csTempScanDirPath, CxConst::xMASK_ALL, false, &m_vsRv);
            //CxString::vStdVectorPrintT(m_vsRv);
xTRACE_POINT;
            xTEST_EQ((size_t)2, m_vsRv.size());
        }
xTRACE_POINT;
        {
            m_vsRv.clear();
            CxDir::vFindDirs(csTempScanDirPath, CxConst::xMASK_ALL, true, &m_vsRv);
            //CxString::vStdVectorPrintT(m_vsRv);

            xTEST_EQ(xARRAY_SIZE(sDirPathes), m_vsRv.size());
        }
xTRACE_POINT;
    }

    xTEST_CASE(CxDir::vFindFiles, cullCaseLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create files)
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

            sfFile.vCreate(g_sFilePathes[i], CxFile::omWrite, true);
        }

        {
            m_vsRv.clear();
            CxDir::vFindFiles(csTempScanDirPath, CxConst::xMASK_ALL, false, &m_vsRv);
            //CxString::vStdVectorPrintT(m_vsRv);

            xTEST_EQ((size_t)2, m_vsRv.size());
        }

        {
            m_vsRv.clear();
            CxDir::vFindFiles(csTempScanDirPath, CxConst::xMASK_ALL, true, &m_vsRv);
            //CxString::vStdVectorPrintT(m_vsRv);

            xTEST_EQ(xARRAY_SIZE(g_sFilePathes), m_vsRv.size());
        }
    }











    /****************************************************************************
    *    prepare
    *
    *****************************************************************************/

    {
        CxDir::vDeleteForce(csRootTestDirPath);
        CxDir::vCreateForce(csDirPath);
    }

    /****************************************************************************
    *    static
    *
    *****************************************************************************/

    xTEST_CASE(CxDir::vCreate, cullCaseLoops)
    {
        CxDir::vCreate(csDirPath2);
    }

    xTEST_CASE(CxDir::bIsDir, cullCaseLoops)
    {
        m_bRv = CxDir::bIsDir(csDirPath2);
        xTEST_EQ(true, m_bRv);
    }

    xTEST_CASE(CxDir::bIsExists, cullCaseLoops)
    {
        m_bRv = CxDir::bIsExists(csDirPath);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxDir::bIsExists(xT("b:"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir::bIsExists(xT("sdfasdf:"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir::bIsExists(xT("C:\\WINDOWS\\NOTEPAD.EXE"));
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir::bIsExists(xT("C:\\pagefile.sys"));
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE(CxDir::bIsEmpty, cullCaseLoops)
    {
        m_bRv = CxDir::bIsEmpty(csDirPath, CxConst::xMASK_ALL);
        xTEST_EQ(false, m_bRv);

        m_bRv = CxDir::bIsEmpty(csDirPath2, CxConst::xMASK_ALL);
        xTEST_EQ(true, m_bRv);

        m_bRv = CxDir::bIsEmpty(sTempDirPath(), CxConst::xMASK_ALL);
        xTEST_EQ(false, m_bRv);
    }

    xTEST_CASE(CxDir::bIsRoot, cullCaseLoops)
    {
        #if   xOS_ENV_WIN
            const std::tstring_t sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("false")},
                {xT(""),              xT("false")},
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
                {xT(""),              xT("false")},
                {xT("/"),             xT("true")},
                {xT("\\"),            xT("false")},
                {xT("A:"),            xT("false")},
                {xT("D:/"),           xT("false")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            bool bRes1 = CxDir::bIsRoot(sTestData[i][0]);
            bool bRes2 = CxString::bStrToBool(sTestData[i][1]);
            xTEST_EQ(bRes1, bRes2);
        }
    }

    xTEST_CASE(CxDir::vSetCurrent, cullCaseLoops)
    {
        m_sRv = CxDir::sCurrent();
        xTEST_EQ(false, m_sRv.empty());

        CxDir::vSetCurrent( sTempDirPath() );
        CxDir::vSetCurrent(m_sRv);
    }

    xTEST_CASE(CxDir::sCurrent, cullCaseLoops)
    {
        std::tstring_t sRv = CxDir::sCurrent();
        xTEST_EQ(m_sRv, sRv);
    }

    xTEST_CASE(CxDir::sTemp, cullCaseLoops)
    {
        m_sRv = CxDir::sTemp();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxDir::sGetTemp(): %s"), m_sRv.c_str());
        #endif
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE(CxDir::vCreateForce, cullCaseLoops)
    {
        CxDir::vCreateForce(csDirPath);
    }

    xTEST_CASE(CxDir::vCopy, cullCaseLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::tstring_t csDirSource = sTempDirPath() + CxConst::xSLASH + xT("DirSource");
        const std::tstring_t csDirDest   = sTempDirPath() + CxConst::xSLASH + xT("DirDest");

        const std::tstring_t sDirPathes[] =
        {
            csDirSource,
            csDirSource + CxConst::xSLASH + xT("AA"),
            csDirSource + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA")
        };
xTRACE_POINT;
        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            CxDir::vCreateForce(sDirPathes[i]);
        }
xTRACE_POINT;
        CxDir::vDeleteForce(csDirDest);
xTRACE_POINT
        //-------------------------------------
        //bCopy
        CxDir::vCopy(csDirSource, csDirDest, true);
xTRACE_POINT
        CxDir::vDelete(csDirDest);
xTRACE_POINT
        CxDir::vCopy(csDirSource, csDirDest, false);
xTRACE_POINT
        CxDir::vDeleteForce(csDirDest);
xTRACE_POINT
        CxDir::vDeleteForce(csDirSource);
xTRACE_POINT
    }

    xTEST_CASE(CxDir::vMove, cullCaseLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::tstring_t csDirSource = sTempDirPath() + CxConst::xSLASH + xT("Source");
        const std::tstring_t csDirDest   = sTempDirPath() + CxConst::xSLASH + xT("Dest");

        const std::tstring_t sDirPathes[] =
        {
            csDirSource,
            csDirSource + CxConst::xSLASH + xT("dd"),
            csDirSource + CxConst::xSLASH + xT("XX") + CxConst::xSLASH + xT("111")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            CxDir::vCreateForce(sDirPathes[i]);
        }

        //-------------------------------------
        //bMove
        CxDir::vMove(csDirSource, csDirDest, true);
        CxDir::vDelete(csDirDest);
    }

    xTEST_CASE(CxDir::vClearForce, cullCaseLoops)
    {
        CxDir::vClearForce(csDirPath);
    }

    xTEST_CASE(CxDir::vDelete, cullCaseLoops)
    {
        CxDir::vDelete(csDirPath2);
    }

    xTEST_CASE(CxDir::vTryDelete, cullCaseLoops)
    {
        CxDir::vCreateForce(csDirPath2);
        CxDir::vTryDelete(csDirPath2, 10, 5);
    }

    xTEST_CASE(CxDir::vDeleteForce, cullCaseLoops)
    {
        CxDir::vCreateForce(csDirPath);
        CxDir::vDeleteForce(csDirPath);
    }
}
//---------------------------------------------------------------------------
