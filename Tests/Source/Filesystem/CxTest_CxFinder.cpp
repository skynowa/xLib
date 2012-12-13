/**
 * \file   CxTest_CxFinder.cpp
 * \brief  test CxFinder
 */


#include <Test/Filesystem/CxTest_CxFinder.h>

#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileAttribute.h>
#include <xLib/Filesystem/CxDir.h>


//---------------------------------------------------------------------------
CxTest_CxFinder::CxTest_CxFinder() {

}
//---------------------------------------------------------------------------
CxTest_CxFinder::~CxTest_CxFinder() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxFinder::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    //-------------------------------------
    // prepare
    const std::tstring_t csRootDirPath = sTempDirPath() + CxConst::xSLASH + xT("CxFinder_Dir");
    std::vec_tstring_t vsDirs;
    std::vec_tstring_t vsFiles;

    {
        {
            vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("AAA") );
            vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("BBB") );
            vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("CCC") );

            xFOREACH_CONST(std::vec_tstring_t, cit, vsDirs) {
                CxDir(*cit).vCreatePath();
            }
        }

        {
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("AAA.h") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("BBB.h") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("CCC.h") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("AAA.cpp") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("BBB.cpp") );
            vsFiles.push_back( csRootDirPath + CxConst::xSLASH + xT("CCC.cpp") );

            xFOREACH_CONST(std::vec_tstring_t, cit, vsFiles) {
                CxFile::vTextWrite(*cit, CxConst::xSTR_EMPTY);
            }
        }

    }

    xTEST_CASE("CxFinder::CxFinder", cullCaseLoops)
    {
        std::vec_tstring_t   vsEntries;
        const std::tstring_t csFilter = xT("*.h");
        CxFinder             fnFinder(csRootDirPath, csFilter);

        m_bRv = fnFinder.bFirst();
        xTEST_EQ(true, m_bRv);
        CxTracer() << "First: " << xTRACE_VAR(fnFinder.sFileName());

        while ( fnFinder.bNext() ) {
            // filter by file type
        #if   xOS_ENV_WIN
            if (CxFileAttribute::faDirectory   != (fnFinder.faAttributes() & CxFileAttribute::faDirectory))
        #elif xOS_ENV_UNIX
            if (CxFileAttribute::faRegularFile == (fnFinder.faAttributes() & CxFileAttribute::faRegularFile))
        #endif
            
            {
                CxTracer() << xTRACE_VAR(fnFinder.sFileName());

                // skip "." ".."
                xCHECK_DO(CxConst::xDOT  == fnFinder.sFileName(), continue);
                xCHECK_DO(CxConst::x2DOT == fnFinder.sFileName(), continue);

                std::tstring_t sDirPath = fnFinder.sRootDirPath() + CxConst::xSLASH + fnFinder.sFileName();

                vsEntries.push_back(sDirPath);
            }
        }

        // xTEST_EQ(vsDirs, vsEntries);
    }
}
//---------------------------------------------------------------------------
