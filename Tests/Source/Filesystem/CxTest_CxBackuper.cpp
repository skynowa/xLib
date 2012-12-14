/**
 * \file   CxTest_CxBackuper.cpp
 * \brief  test CxBackuper
 */


#include <Test/Filesystem/CxTest_CxBackuper.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>


//---------------------------------------------------------------------------
CxTest_CxBackuper::CxTest_CxBackuper() {

}
//---------------------------------------------------------------------------
CxTest_CxBackuper::~CxTest_CxBackuper() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxBackuper::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath  = sTempDirPath() + CxConst::xSLASH + xT("Test_backup.txt");
    const std::tstring_t csBackupDir = sTempDirPath() + CxConst::xSLASH + xT("Backup_dir");


    xTEST_CASE("CxBackuper::vExecute", cullCaseLoops)
    {
        const long_t cliFileSize = 100L;

        {
            CxFile F;

            F.vCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            F.vResize(cliFileSize);
        }

        for (size_t i = 0; i < 10; ++ i) {
            CxBackuper bkBackuper(CxBackuper::bpDaily);

            std::tstring_t sBackupFilePath;

            xTRY {
                bkBackuper.vExecute(csFilePath, csBackupDir, &sBackupFilePath);
            }
            xCATCH_ALL;
        }

        CxDir(csBackupDir).vDeletePath();
    }
}
//---------------------------------------------------------------------------
