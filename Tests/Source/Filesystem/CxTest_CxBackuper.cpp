/**
 * \file   CxTest_CxBackuper.cpp
 * \brief  test CxBackuper
 */


#include <Test/Filesystem/CxTest_CxBackuper.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxBackuper::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath  = tempDirPath() + CxConst::slash() + xT("test.txt");
    std::ctstring_t backupDir = tempDirPath() + CxConst::slash() + xT("CxBackup_dir");


    xTEST_CASE("CxBackuper::fileExec", a_caseLoops)
    {
        // prepare
        {
            CxFile F;

            F.create(filePath, CxFile::omBinCreateReadWrite, true);
            F.resize(100L);

        #if 1
            CxTracer() << xTRACE_VAR(CxDateTime::current().format(xT("%Y-%m-%d_%H"), xT("")));
            CxTracer() << xTRACE_VAR(CxDateTime::current().format(xT("%Y-%m-%d"), xT("")));
            CxTracer() << xTRACE_VAR(CxDateTime::current().format(xT("%Y_%U"), xT("")));
            CxTracer() << xTRACE_VAR(CxDateTime::current().format(xT("%Y-%m"), xT("")));
        #endif
        }

        CxBackuper::cExPeriod periods[] = {
            // CxBackuper::bpUnknown,
            CxBackuper::bpHourly,
            CxBackuper::bpDaily,
            CxBackuper::bpWeekly,
            CxBackuper::bpMonthly
        };

        for (size_t p = 0; p < xARRAY_SIZE(periods); ++ p) {
            for (size_t i = 0; i < 10; ++ i) {
                CxBackuper backuper(periods[p]);

                xTRY {
                    std::tstring_t backupFilePath;

                    backuper.fileExec(filePath, backupDir, &backupFilePath);
                }
                xCATCH_ALL
            }
        }

        CxDir(backupDir).pathDelete();
    }
}
//-------------------------------------------------------------------------------------------------
