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
    std::vec_tstring_t   vsDirs;

    {
        vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("AAA") );
        vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("BBB") );
        vsDirs.push_back( csRootDirPath + CxConst::xSLASH + xT("CCC") );

        xFOREACH_CONST(std::vec_tstring_t, cit, vsDirs) {
            CxDir::vCreatePath(*cit);
        }
    }

    xTEST_CASE("CxFinder::CxFinder", cullCaseLoops)
    {
        std::vec_tstring_t vsEntries;
        CxFinder           fnFinder(csRootDirPath);

        m_bRv = fnFinder.bFirst();
        xTEST_EQ(true, m_bRv);

        do {
            // dirs
            if (CxFileAttribute::faDirectory == (fnFinder.faAttributes() & CxFileAttribute::faDirectory)) {
                std::tstring_t sFileName = fnFinder.sFileName();
                // CxTracer() << xTRACE_VAR(sFileName);

                // skip "." ".."
                xCHECK_DO(CxConst::xDOT  == sFileName, continue);
                xCHECK_DO(CxConst::x2DOT == sFileName, continue);

                std::tstring_t sDirPath = CxPath::sSlashAppend(fnFinder.sRootDirPath()) + sFileName;

                vsEntries.push_back(sDirPath);
            }
            // files, etc
            else {
                xNA;
            }
        }
        while (true == fnFinder.bNext());

        fnFinder.vClose();

        xTEST_EQ(vsDirs, vsEntries);
    }
}
//---------------------------------------------------------------------------
