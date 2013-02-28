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
void
CxTest_CxFinder::unit(
    culonglong_t &cullCaseLoops
)
{
    //-------------------------------------
    // prepare
    const std::tstring_t csRootDirPath = tempDirPath() + CxConst::xSLASH + xT("CxFinder_Dir");
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
            std::vec_tstring_t   vsEntries;
            const std::tstring_t csFilter = adtData[i].sFilter;
            CxFinder             fnFinder(csRootDirPath, csFilter);

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

}
//------------------------------------------------------------------------------
