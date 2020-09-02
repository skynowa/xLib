/**
 * \file   Test_Backup.cpp
 * \brief  test Backup
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Backup)
xTEST_UNIT(Test_Backup)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Backup::unit()
{
    std::ctstring_t filePath  = getData().tempDirPath + Const::slash() + xT("test.txt");
    std::ctstring_t backupDir = getData().tempDirPath + Const::slash() + xT("Backup_dir");

    xTEST_CASE("fileExec")
    {
        // prepare
        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::BinReadWrite);
            file.setSize(100L);

        #if 0
            Tracer() << xTRACE_VAR(DateTime::current().format(xT("%Y-%m-%d_%H"), xT("")));
            Tracer() << xTRACE_VAR(DateTime::current().format(xT("%Y-%m-%d"), xT("")));
            Tracer() << xTRACE_VAR(DateTime::current().format(xT("%Y_%U"), xT("")));
            Tracer() << xTRACE_VAR(DateTime::current().format(xT("%Y-%m"), xT("")));
        #endif
        }

        Backup::cPeriod periods[]
		{
            // Backup::Period::bpUnknown,
            Backup::Period::bpHourly,
            Backup::Period::bpDaily,
            Backup::Period::bpWeekly,
            Backup::Period::bpMonthly
        };

        for (size_t p = 0; p < xARRAY_SIZE(periods); ++ p) {
            for (size_t i = 0; i < 10; ++ i) {
                Backup backuper(filePath, periods[p]);

                xTRY {
                    std::tstring_t backupFilePath;

                    backuper.fileExec(backupDir, &backupFilePath);
                }
                xCATCH_ALL
            }
        }

        Dir(backupDir).pathDelete();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
