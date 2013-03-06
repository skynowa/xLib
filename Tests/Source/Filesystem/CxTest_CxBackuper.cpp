/**
 * \file   CxTest_CxBackuper.cpp
 * \brief  test CxBackuper
 */


#include <Test/Filesystem/CxTest_CxBackuper.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>


//------------------------------------------------------------------------------
CxTest_CxBackuper::CxTest_CxBackuper() {

}
//------------------------------------------------------------------------------
CxTest_CxBackuper::~CxTest_CxBackuper() {

}
//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxBackuper::unit(
    culonglong_t &cullCaseLoops
)
{
    std::ctstring_t csFilePath  = tempDirPath() + CxConst::xSLASH + xT("Test_backup.txt");
    std::ctstring_t csBackupDir = tempDirPath() + CxConst::xSLASH + xT("Backup_dir");


    xTEST_CASE("CxBackuper::fileExec", cullCaseLoops)
    {
        clong_t cliFileSize = 100L;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinCreateReadWrite, true);
            F.resize(cliFileSize);
        }

        for (size_t i = 0; i < 10; ++ i) {
            CxBackuper bkBackuper(CxBackuper::bpDaily);

            std::tstring_t sBackupFilePath;

            xTRY {
                bkBackuper.fileExec(csFilePath, csBackupDir, &sBackupFilePath);
            }
            xCATCH_ALL;
        }

        CxDir(csBackupDir).pathDelete();
    }
}
//------------------------------------------------------------------------------
