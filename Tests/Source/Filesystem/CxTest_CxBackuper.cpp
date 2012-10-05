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
bool
CxTest_CxBackuper::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t csFilePath  = sGetTempDirPath() + CxConst::xSLASH + xT("Test.txt");
    const std::tstring_t csBackupDir = sGetTempDirPath() + CxConst::xSLASH + xT("Backup_dir");


    //--------------------------------------------------
    //bBackup
    xTEST_CASE(cullCaseLoops)
    {
        const long_t cliFileSize = 100L;

        {
            CxFile F;

            m_bRv = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_EQ(true, m_bRv);

            m_bRv = F.bResize(cliFileSize);
            xTEST_EQ(true, m_bRv);
        }

        for (size_t i = 0; i < 10; ++ i) {
            CxBackuper bkBackuper(CxBackuper::bpDaily);

            std::tstring_t sBackupFilePath;

            CxBackuper::ExErrorType etRes = bkBackuper.etExecute(csFilePath, csBackupDir, &sBackupFilePath);
            xTEST_EQ(CxBackuper::etSuccess, etRes);
            xTEST_EQ(false, sBackupFilePath.empty())
        }

        CxDir::vDeleteForce(csBackupDir);
    }

    return true;
}
//---------------------------------------------------------------------------
