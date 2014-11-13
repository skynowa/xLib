/**
 * \file   Test_Backup.cpp
 * \brief  test Backup
 */


#include <Test/IO/Test_Backup.h>

#include <xLib/IO/File.h>
#include <xLib/IO/Dir.h>
#include <xLib/Debug/Exception.h>

//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Backup::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath  = tempDirPath() + Const::slash() + xT("test.txt");
    std::ctstring_t backupDir = tempDirPath() + Const::slash() + xT("Backup_dir");


    xTEST_CASE("Backup::fileExec", a_caseLoops)
    {
        // prepare
        {
            File F;

            F.create(filePath, File::omBinCreateReadWrite);
            F.resize(100L);

        #if 0
            Tracer() << xTRACE_VAR(DateTime::current().format(xT("%Y-%m-%d_%H"), xT("")));
            Tracer() << xTRACE_VAR(DateTime::current().format(xT("%Y-%m-%d"), xT("")));
            Tracer() << xTRACE_VAR(DateTime::current().format(xT("%Y_%U"), xT("")));
            Tracer() << xTRACE_VAR(DateTime::current().format(xT("%Y-%m"), xT("")));
        #endif
        }

        Backup::cExPeriod periods[] = {
            // Backup::bpUnknown,
            Backup::bpHourly,
            Backup::bpDaily,
            Backup::bpWeekly,
            Backup::bpMonthly
        };

        for (size_t p = 0; p < xARRAY_SIZE(periods); ++ p) {
            for (size_t i = 0; i < 10; ++ i) {
                Backup backuper(periods[p]);

                xTRY {
                    std::tstring_t backupFilePath;

                    backuper.fileExec(filePath, backupDir, &backupFilePath);
                }
                xCATCH_ALL
            }
        }

        Dir(backupDir).pathDelete();
    }
}
//-------------------------------------------------------------------------------------------------
