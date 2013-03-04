/**
 * \file   CxTest_CxFinder.cpp
 * \brief  test CxFinder
 */


#include <Test/Filesystem/CxTest_CxFinder.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileAttribute.h>
#include <xLib/Filesystem/CxDir.h>


//------------------------------------------------------------------------------
CxTest_CxFinder::CxTest_CxFinder() {

}
//------------------------------------------------------------------------------
CxTest_CxFinder::~CxTest_CxFinder() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFinder::unit(
    culonglong_t &cullCaseLoops
)
{
    //-------------------------------------
    // prepare
    std::ctstring_t    csRootDirPath = tempDirPath() + CxConst::xSLASH + xT("CxFinder_Dir");
    std::vec_tstring_t vsDirs;
    std::vec_tstring_t vsFiles;

    {
        {
            vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("AAA") );
            vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("BBB") );
            vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("CCC") );

            xFOREACH_CONST(std::vec_tstring_t, cit, vsDirs) {
                CxDir(*cit).pathCreate();
            }
        }

        {
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("AAA.h") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("BBB.h") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("CCC.h") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("AAA.cpp") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("BBB.cpp") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("CCC.cpp") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("DDD.cpp") );

            xFOREACH_CONST(std::vec_tstring_t, cit, vsFiles) {
                CxFile::textWrite(*cit, CxConst::xSTR_EMPTY);
            }
        }

    }

    xTEST_CASE("CxFinder::CxFinder", cullCaseLoops)
    {
        xTEST_EQ(size_t(3), vsDirs.size());
        xTEST_EQ(size_t(7), vsFiles.size());

        struct SData {
            std::tstring_t sFilter;
            size_t         uiEntriesNum;
        };

        SData adtData[] = {
            {CxConst::xMASK_ALL, 7},
            {xT("*"),            7},
            {xT("*.*"),          7},
            {xT("*.h"),          3},
            {xT("*.cpp"),        4},
            {xT("*.txt"),        0}
        };

        for (size_t i = 0; i < xARRAY_SIZE2(adtData); ++ i) {
            std::vec_tstring_t vsEntries;
            std::ctstring_t    csFilter = adtData[i].sFilter;
            CxFinder           fnFinder(csRootDirPath, csFilter);

            m_bRv = fnFinder.moveFirst();
            if (0 == adtData[i].uiEntriesNum) {
                xTEST_EQ(false, m_bRv);
            } else {
                xTEST_EQ(true, m_bRv);

                if (
                    (CxConst::xDOT  != fnFinder.entryName()) &&
                    (CxConst::x2DOT != fnFinder.entryName())
                )
                {
                    vsEntries.push_back(fnFinder.entryName());
                }

                for ( ; fnFinder.moveNext(); ) {
                #if   xOS_ENV_WIN
                    if (! (fnFinder.attributes() & CxFileAttribute::faDirectory))
                #elif xOS_ENV_UNIX
                    if (fnFinder.attributes() & CxFileAttribute::faRegularFile)
                #endif

                    {
                        xCHECK_DO(CxConst::xDOT  == fnFinder.entryName(), continue);
                        xCHECK_DO(CxConst::x2DOT == fnFinder.entryName(), continue);

                        vsEntries.push_back(fnFinder.entryName());
                    }
                }
            } // if (0 == adtData[i].uiEntriesNum)

            xTEST_EQ(adtData[i].uiEntriesNum, vsEntries.size());
        }
    }


    std::ctstring_t csTempScanDirPath = tempDirPath() + CxConst::xSLASH + xT("Scan");
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

    xTEST_CASE("CxFinder::dirsFind", cullCaseLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        std::ctstring_t sDirPathes[] =
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

            CxFinder::dirs(csTempScanDirPath, CxConst::xMASK_ALL, false, &m_vsRv);
            xTEST_EQ(size_t(2), m_vsRv.size());
        }

        {
            m_vsRv.clear();
            CxFinder::dirs(csTempScanDirPath, CxConst::xMASK_ALL, true, &m_vsRv);
            xTEST_EQ(xARRAY_SIZE(sDirPathes), m_vsRv.size());
        }
    }

    xTEST_CASE("CxFinder::filesFind", cullCaseLoops)
    {
        //-------------------------------------
        // prepare for csTempScanDirPath (create files)
        std::ctstring_t g_sFilePathes[] =
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
            CxFinder::files(csTempScanDirPath, CxConst::xMASK_ALL, false, &m_vsRv);
            xTEST_EQ(size_t(2), m_vsRv.size());
        }

        {
            m_vsRv.clear();
            CxFinder::files(csTempScanDirPath, CxConst::xMASK_ALL, true, &m_vsRv);
            xTEST_EQ(xARRAY_SIZE(g_sFilePathes), m_vsRv.size());
        }
    }
}
//------------------------------------------------------------------------------
