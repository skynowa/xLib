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
CxTest_CxBackuper::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath  = tempDirPath() + CxConst::xSLASH + xT("Test_backup.txt");
    const std::tstring_t csBackupDir = tempDirPath() + CxConst::xSLASH + xT("Backup_dir");


    xTEST_CASE("CxBackuper::execute", cullCaseLoops)
    {
        const long_t cliFileSize = 100L;

        {
            CxFile F;

            F.create(csFilePath, CxFile::omBinCreateReadWrite, true);
            F.resize(cliFileSize);
        }

        for (size_t i = 0; i < 10; ++ i) {
            CxBackuper bkBackuper(CxBackuper::bpDaily);

            std::tstring_t sBackupFilePath;

            xTRY {
                bkBackuper.execute(csFilePath, csBackupDir, &sBackupFilePath);
            }
            xCATCH_ALL;
        }

        CxDir(csBackupDir).pathDelete();
    }
}
//---------------------------------------------------------------------------
