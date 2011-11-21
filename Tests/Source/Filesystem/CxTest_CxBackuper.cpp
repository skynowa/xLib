/**
 * \file   CxTest_CxBackuper.cpp
 * \brief  test CxBackuper
 */


#include <Test/Filesystem/CxTest_CxBackuper.h>


//---------------------------------------------------------------------------
CxTest_CxBackuper::CxTest_CxBackuper() {

}
//---------------------------------------------------------------------------
CxTest_CxBackuper::~CxTest_CxBackuper() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxBackuper::bUnit(
    const ulonglong_t cullBlockLoops
)
{
    const std::tstring_t csFilePath  = sGetWorkDirPath() + CxConst::xSLASH + xT("Test.txt");
    const std::tstring_t csBackupDir = sGetWorkDirPath() + CxConst::xSLASH + xT("Backup_dir");


    //--------------------------------------------------
    //bBackup
    xTEST_CASE(cullBlockLoops)
    {
        const long_t cliFileSize = 100L;

        {
            CxFile F;

            m_bRes = F.bCreate(csFilePath, CxFile::omBinCreateReadWrite, true);
            xTEST_DIFF(false, m_bRes);

            m_bRes = F.bResize(cliFileSize);
            xTEST_DIFF(false, m_bRes);
        }

        for (size_t i = 0; i < 10; ++ i) {
            CxBackuper bkBackuper(CxBackuper::bpDaily);

            std::tstring_t sBackupFilePath;

            CxBackuper::EErrorType etRes = bkBackuper.etExecute(csFilePath, csBackupDir, &sBackupFilePath);
            xTEST_EQ(CxBackuper::etSuccess, etRes);
            xTEST_EQ(false, sBackupFilePath.empty())
        }

        m_bRes = CxDir::bDeleteForce(csBackupDir);
        xTEST_DIFF(false, m_bRes);
    }

    return true;
}
//---------------------------------------------------------------------------
