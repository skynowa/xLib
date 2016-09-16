/**
 * \file   Test_Finder.cpp
 * \brief  test Finder
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xlib;

xTEST_CLASS(Test_Finder)
xTEST_UNIT(Test_Finder)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Finder::unit()
{
    // prepare
    std::ctstring_t    rootDirPath = data.tempDirPath + Const::slash() + xT("Finder_Dir");
    std::vec_tstring_t dirs;
    std::vec_tstring_t files;

    {
        Dir(rootDirPath).pathDelete();

        {
            dirs.push_back( rootDirPath + Const::slash() + xT("AAA") );
            dirs.push_back( rootDirPath + Const::slash() + xT("BBB") );
            dirs.push_back( rootDirPath + Const::slash() + xT("CCC") );

            xFOR_EACH_CONST(std::vec_tstring_t, cit, dirs) {
                Dir(*cit).pathCreate();
            }

            xTEST_EQ(size_t(3), dirs.size());
        }

        {
            files.push_back( rootDirPath + Const::slash() + xT("AAA.h") );
            files.push_back( rootDirPath + Const::slash() + xT("BBB.h") );
            files.push_back( rootDirPath + Const::slash() + xT("CCC.h") );
            files.push_back( rootDirPath + Const::slash() + xT("DDD.h") );
            files.push_back( rootDirPath + Const::slash() + xT("AAA.cpp") );
            files.push_back( rootDirPath + Const::slash() + xT("BBB.cpp") );
            files.push_back( rootDirPath + Const::slash() + xT("CCC.cpp") );
            files.push_back( rootDirPath + Const::slash() + xT("DDD.cpp") );

            files.push_back( rootDirPath + Const::slash() + xT("File_1") );
            files.push_back( rootDirPath + Const::slash() + xT("File_2.log") );
            files.push_back( rootDirPath + Const::slash() + xT("AAA") +
                               Const::slash() + xT("AA") +
                               Const::slash() + xT("File_3.log") );
            files.push_back( rootDirPath + Const::slash() + xT("BBB") +
                               Const::slash() + xT("BB") +
                               Const::slash() + xT("BBB") +
                               Const::slash() + xT("File_4.log") );

            xFOR_EACH_CONST(std::vec_tstring_t, cit, files) {
                File::clear(*cit);
            }

            xTEST_EQ(size_t(12), files.size());
        }
    }

    xTEST_CASE("Finder")
    {
        const data2_size_t data[] = {
            {Const::maskAll(), 12 - 2},
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
            Finder           finder(rootDirPath, filter);

            for ( ; ; ) {
                m_bRv = finder.moveNext();
                xCHECK_DO(!m_bRv, break);

                xCHECK_DO(Const::dot()  == finder.entryName(), continue);
                xCHECK_DO(Const::dot2() == finder.entryName(), continue);

                // set filter for files
                xCHECK_DO(FileType::faDirectory & finder.fileTypes(), continue);
                xTEST_EQ(true, File::isExists( finder.entryPath() ));

                entries.push_back(finder.entryName());
            }

            // Tracer() << filter << "\n" << xTRACE_VAR(rootDirPath) << entries;
            xTEST_EQ(data[i].expect, entries.size());
        }
    }

    xTEST_CASE("dirs")
    {
        // non recursive
        {
            m_vsRv.clear();

            Finder::dirs(rootDirPath, Const::maskAll(), false, &m_vsRv);
            // Tracer() << m_vsRv;
            xTEST_EQ(dirs.size(), m_vsRv.size());
        }

        // recursive
        {
            m_vsRv.clear();

            Finder::dirs(rootDirPath, Const::maskAll(), true, &m_vsRv);
            // Tracer() << m_vsRv;
            xTEST_EQ(size_t(6), m_vsRv.size());
        }
    }

    xTEST_CASE("files")
    {
        // non recursive
        {
            const data2_size_t data[] = {
                {Const::maskAll(), 12 - 2},
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

                Finder::files(rootDirPath, data[i].test, false, &m_vsRv);
                // Tracer() << m_vsRv;
                xTEST_EQ(data[i].expect, m_vsRv.size());
            }
        }

        // recursive
        {
            const data2_size_t data[] = {
                {Const::maskAll(), 12},
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

                Finder::files(rootDirPath, data[i].test, true, &m_vsRv);
                // Tracer() << m_vsRv;
                xTEST_EQ(data[i].expect, m_vsRv.size());
            }
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
