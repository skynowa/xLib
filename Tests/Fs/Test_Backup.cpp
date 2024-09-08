/**
 * \file   Test_Backup.cpp
 * \brief  test Backup
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Backup)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Backup::unit()
{
    std::ctstring_t filePath  = option().tempDirPath + Const::slash() + xT("test.txt");
    std::ctstring_t backupDir = option().tempDirPath + Const::slash() + xT("Backup_dir");

    xTEST_CASE("fileExec")
    {
        // prepare
        {
            FileIO file(filePath);
            file.open(FileIO::OpenMode::BinReadWrite);
            file.setSize(100L);
        }

        Backup::cPeriod periods[]
		{
            // Backup::Period::Unknown,
            Backup::Period::Hourly,
            Backup::Period::Daily,
            Backup::Period::Weekly,
            Backup::Period::Monthly
        };

        for (const auto it_period : periods) {
            for (size_t i = 0; i < 5; ++ i) {
                Backup backup(filePath, backupDir, it_period);

				std::tstring_t backupFilePath;
				const auto errorCode = backup.fileExec(&backupFilePath);
				if (errorCode == Backup::Error::DestFileAlreadyExists) {
					continue;
				}

				xTEST_EQ((int)errorCode, (int)Backup::Error::Ok);
				xTEST(!backupFilePath.empty());
            }
        }

        Dir(backupDir).pathDelete();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
