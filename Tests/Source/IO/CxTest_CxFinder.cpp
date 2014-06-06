/**
 * \file   CxTest_CxFinder.cpp
 * \brief  test CxFinder
 */


#include <Test/IO/CxTest_CxFinder.h>

#include <xLib/IO/CxPath.h>
#include <xLib/IO/CxFile.h>
#include <xLib/IO/CxFileType.h>
#include <xLib/IO/CxDir.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxFinder::unit(
    culonglong_t &a_caseLoops
)
{
    // prepare
    std::ctstring_t    rootDirPath = tempDirPath() + CxConst::slash() + xT("CxFinder_Dir");
    std::vec_tstring_t dirs;
    std::vec_tstring_t files;

    {
        CxDir(rootDirPath).pathDelete();

        {
            dirs.push_back( rootDirPath + CxConst::slash() + xT("AAA") );
            dirs.push_back( rootDirPath + CxConst::slash() + xT("BBB") );
            dirs.push_back( rootDirPath + CxConst::slash() + xT("CCC") );

            xFOREACH_CONST(std::vec_tstring_t, cit, dirs) {
                CxDir(*cit).pathCreate();
            }

            xTEST_EQ(size_t(3), dirs.size());
        }

        {
            files.push_back( rootDirPath + CxConst::slash() + xT("AAA.h") );
            files.push_back( rootDirPath + CxConst::slash() + xT("BBB.h") );
            files.push_back( rootDirPath + CxConst::slash() + xT("CCC.h") );
            files.push_back( rootDirPath + CxConst::slash() + xT("DDD.h") );
            files.push_back( rootDirPath + CxConst::slash() + xT("AAA.cpp") );
            files.push_back( rootDirPath + CxConst::slash() + xT("BBB.cpp") );
            files.push_back( rootDirPath + CxConst::slash() + xT("CCC.cpp") );
            files.push_back( rootDirPath + CxConst::slash() + xT("DDD.cpp") );

            files.push_back( rootDirPath + CxConst::slash() + xT("File_1") );
            files.push_back( rootDirPath + CxConst::slash() + xT("File_2.log") );
            files.push_back( rootDirPath + CxConst::slash() + xT("AAA") +
                               CxConst::slash() + xT("AA") +
                               CxConst::slash() + xT("File_3.log") );
            files.push_back( rootDirPath + CxConst::slash() + xT("BBB") +
                               CxConst::slash() + xT("BB") +
                               CxConst::slash() + xT("BBB") +
                               CxConst::slash() + xT("File_4.log") );

            xFOREACH_CONST(std::vec_tstring_t, cit, files) {
                CxFile::clear(*cit);
            }

            xTEST_EQ(size_t(12), files.size());
        }
    }

    xTEST_CASE("CxFinder::CxFinder", a_caseLoops)
    {
        const data2_size_t data[] = {
            {CxConst::maskAll(), 12 - 2},
            {xT("*"),            12 - 2},
        #if   xENV_WIN
            {xT("*.*"),          12 - 2},
        #elif xENV_UNIX
            {xT("*.*"),          12 - 3},
        #endif
            {xT("*.h"),          4},
            {xT("*.cpp"),        4},
            {xT("*.txt"),        0},
            {xT("*.log"),        1}
        };

        for (size_t i = 0; i < xARRAY_SIZE2(data); ++ i) {
            std::vec_tstring_t entries;
            std::ctstring_t    filter = data[i].test;
            CxFinder           finder(rootDirPath, filter);

            for ( ; ; ) {
                m_bRv = finder.moveNext();
                xCHECK_DO(!m_bRv, break);

                xCHECK_DO(CxConst::dot()  == finder.entryName(), continue);
                xCHECK_DO(CxConst::dot2() == finder.entryName(), continue);

                // set filter for files
                xCHECK_DO(CxFileType::faDirectory & finder.fileTypes(), continue);
                xTEST_EQ(true, CxFile::isExists( finder.entryPath() ));

                entries.push_back(finder.entryName());
            }

            // CxTracer() << filter << "\n" << xTRACE_VAR(rootDirPath) << entries;
            xTEST_EQ(data[i].expect, entries.size());
        }
    }

    xTEST_CASE("CxFinder::dirs", a_caseLoops)
    {
        // non recursive
        {
            m_vsRv.clear();

            CxFinder::dirs(rootDirPath, CxConst::maskAll(), false, &m_vsRv);
            // CxTracer() << m_vsRv;
            xTEST_EQ(dirs.size(), m_vsRv.size());
        }

        // recursive
        {
            m_vsRv.clear();

            CxFinder::dirs(rootDirPath, CxConst::maskAll(), true, &m_vsRv);
            // CxTracer() << m_vsRv;
            xTEST_EQ(size_t(6), m_vsRv.size());
        }
    }

    xTEST_CASE("CxFinder::files", a_caseLoops)
    {
        // non recursive
        {
            const data2_size_t data[] = {
                {CxConst::maskAll(), 12 - 2},
                {xT("*"),            12 - 2},
            #if   xENV_WIN
                {xT("*.*"),          12 - 2},
            #elif xENV_UNIX
                {xT("*.*"),          12 - 3},
            #endif
                {xT("*.h"),          4},
                {xT("*.cpp"),        4},
                {xT("*.txt"),        0},
                {xT("*.log"),        1}
            };

            for (size_t i = 0; i < xARRAY_SIZE2(data); ++ i) {
                m_vsRv.clear();

                CxFinder::files(rootDirPath, data[i].test, false, &m_vsRv);
                // CxTracer() << m_vsRv;
                xTEST_EQ(data[i].expect, m_vsRv.size());
            }
        }

        // recursive
        {
            const data2_size_t data[] = {
                {CxConst::maskAll(), 12},
                {xT("*"),            12},
            #if   xENV_WIN
                {xT("*.*"),          12},
            #elif xENV_UNIX
                {xT("*.*"),          12 - 1},
            #endif
                {xT("*.h"),          4},
                {xT("*.cpp"),        4},
                {xT("*.txt"),        0},
                {xT("*.log"),        3}
            };

            for (size_t i = 0; i < xARRAY_SIZE2(data); ++ i) {
                m_vsRv.clear();

                CxFinder::files(rootDirPath, data[i].test, true, &m_vsRv);
                // CxTracer() << m_vsRv;
                xTEST_EQ(data[i].expect, m_vsRv.size());
            }
        }
    }

}
//-------------------------------------------------------------------------------------------------
