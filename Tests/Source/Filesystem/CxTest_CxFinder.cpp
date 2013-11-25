/**
 * \file   CxTest_CxFinder.cpp
 * \brief  test CxFinder
 */


#include <Test/Filesystem/CxTest_CxFinder.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileType.h>
#include <xLib/Filesystem/CxDir.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFinder::unit(
    culonglong_t &a_caseLoops
)
{
    //-------------------------------------
    // prepare
    struct SData {
        std::tstring_t sFilter;
        size_t         uiEntriesNum;
    };

    std::ctstring_t    csRootDirPath = tempDirPath() + CxConst::slash() + xT("CxFinder_Dir");
    std::vec_tstring_t vsDirs;
    std::vec_tstring_t vsFiles;

    {
        CxDir(csRootDirPath).pathDelete();

        {
            vsDirs.push_back( csRootDirPath + CxConst::slash() + xT("AAA") );
            vsDirs.push_back( csRootDirPath + CxConst::slash() + xT("BBB") );
            vsDirs.push_back( csRootDirPath + CxConst::slash() + xT("CCC") );

            xFOREACH_CONST(std::vec_tstring_t, cit, vsDirs) {
                CxDir(*cit).pathCreate();
            }

            xTEST_EQ(size_t(3), vsDirs.size());
        }

        {
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("AAA.h") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("BBB.h") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("CCC.h") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("DDD.h") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("AAA.cpp") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("BBB.cpp") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("CCC.cpp") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("DDD.cpp") );

            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("File_1") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("File_2.log") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("AAA") +
                               CxConst::slash() + xT("AA") +
                               CxConst::slash() + xT("File_3.log") );
            vsFiles.push_back( csRootDirPath + CxConst::slash() + xT("BBB") +
                               CxConst::slash() + xT("BB") +
                               CxConst::slash() + xT("BBB") +
                               CxConst::slash() + xT("File_4.log") );

            xFOREACH_CONST(std::vec_tstring_t, cit, vsFiles) {
                CxFile::textWrite(*cit, CxConst::strEmpty());
            }

            xTEST_EQ(size_t(12), vsFiles.size());
        }
    }

    xTEST_CASE("CxFinder::CxFinder", a_caseLoops)
    {
        SData adtData[] = {
            {CxConst::maskAll(), 12 - 2},
            {xT("*"),            12 - 2},
        #if xOS_ENV_WIN
            {xT("*.*"),          12 - 2},
        #else
            {xT("*.*"),          12 - 3},
        #endif
            {xT("*.h"),          4},
            {xT("*.cpp"),        4},
            {xT("*.txt"),        0},
            {xT("*.log"),        1}
        };

        for (size_t i = 0; i < xARRAY_SIZE2(adtData); ++ i) {
            std::vec_tstring_t vsEntries;
            std::ctstring_t    csFilter = adtData[i].sFilter;
            CxFinder           fnFinder(csRootDirPath, csFilter);

            xFOREVER {
                m_bRv = fnFinder.moveNext();
                xCHECK_DO(!m_bRv, break);

                xCHECK_DO(CxConst::dot()  == fnFinder.entryName(), continue);
                xCHECK_DO(CxConst::dot2() == fnFinder.entryName(), continue);

                // set filter for files
                xCHECK_DO(CxFileType::faDirectory & fnFinder.fileTypes(), continue);
                xTEST_EQ(true, CxFile::isExists( fnFinder.entryPath() ));

                vsEntries.push_back(fnFinder.entryName());
            }

            // CxTracer() << csFilter << "\n" << xTRACE_VAR(csRootDirPath) << vsEntries;
            xTEST_EQ(adtData[i].uiEntriesNum, vsEntries.size());
        }
    }

    xTEST_CASE("CxFinder::dirs", a_caseLoops)
    {
        // non recursive
        {
            m_vsRv.clear();

            CxFinder::dirs(csRootDirPath, CxConst::maskAll(), false, &m_vsRv);
            // CxTracer() << m_vsRv;
            xTEST_EQ(vsDirs.size(), m_vsRv.size());
        }

        // recursive
        {
            m_vsRv.clear();

            CxFinder::dirs(csRootDirPath, CxConst::maskAll(), true, &m_vsRv);
            // CxTracer() << m_vsRv;
            xTEST_EQ(size_t(6), m_vsRv.size());
        }
    }

    xTEST_CASE("CxFinder::files", a_caseLoops)
    {
        // non recursive
        {
            SData adtData[] = {
                {CxConst::maskAll(), 12 - 2},
                {xT("*"),            12 - 2},
            #if xOS_ENV_WIN
                {xT("*.*"),          12 - 2},
            #else
                {xT("*.*"),          12 - 3},
            #endif
                {xT("*.h"),          4},
                {xT("*.cpp"),        4},
                {xT("*.txt"),        0},
                {xT("*.log"),        1}
            };

            for (size_t i = 0; i < xARRAY_SIZE2(adtData); ++ i) {
                m_vsRv.clear();

                CxFinder::files(csRootDirPath, adtData[i].sFilter, false, &m_vsRv);
                // CxTracer() << m_vsRv;
                xTEST_EQ(adtData[i].uiEntriesNum, m_vsRv.size());
            }
        }

        // recursive
        {
            SData adtData[] = {
                {CxConst::maskAll(), 12},
                {xT("*"),            12},
            #if xOS_ENV_WIN
                {xT("*.*"),          12},
            #else
                {xT("*.*"),          12 - 1},
            #endif
                {xT("*.h"),          4},
                {xT("*.cpp"),        4},
                {xT("*.txt"),        0},
                {xT("*.log"),        3}
            };

            for (size_t i = 0; i < xARRAY_SIZE2(adtData); ++ i) {
                m_vsRv.clear();

                CxFinder::files(csRootDirPath, adtData[i].sFilter, true, &m_vsRv);
                // CxTracer() << m_vsRv;
                xTEST_EQ(adtData[i].uiEntriesNum, m_vsRv.size());
            }
        }
    }

}
//------------------------------------------------------------------------------
