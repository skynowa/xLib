/**
 * \file   Backup.inl
 * \brief  backuper
 */


#include "Backup.h"

#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/Volume.h>


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Backup::Backup(
    cPeriod &a_period
) :
    _period(a_period)
{
}
//-------------------------------------------------------------------------------------------------
void_t
Backup::fileExec(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_destDirPath,
    std::tstring_t  *a_destFilePath
) const /* throw(Exception) */
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(a_destDirPath.empty(), false);
    xTEST_PTR(a_destFilePath);

    // errors
    std::ctstring_t errorDestFileNotExists  = xT("Backup - Destination file not exists");
    std::ctstring_t errorNotEnoughFreeSpace = xT("Backup - Not enough free space");
    std::ctstring_t errorCopyingFail        = xT("Backup - Copying fail");
    std::ctstring_t errorUnknown            = xT("Backup - Unknown error");

    bool_t bRv = false;

    // prepare
    {
        a_destFilePath->clear();

        bRv = File::isExists(a_filePath);
        xCHECK_DO(!bRv, xTHROW_REPORT(errorDestFileNotExists));

        Dir dest(a_destDirPath);

        bRv = dest.isExists();
        xCHECK_DO(!bRv, dest.pathCreate());
    }

    std::tstring_t dateTimeStamp;
    {
        switch (_period) {
        case Period::bpHourly:
            // format: 2013-12-21_23
            dateTimeStamp = DateTime::current().format(xT("%Y-%m-%d_%H"), xT(""));
            break;
        case Period::bpDaily:
            // format: 2013-12-21
            dateTimeStamp = DateTime::current().format(xT("%Y-%m-%d"), xT(""));
            break;
        case Period::bpWeekly:
            // format: 2013_01
            dateTimeStamp = DateTime::current().format(xT("%Y_%U"), xT(""));
            break;
        case Period::bpMonthly:
            // format: 2013-12
            dateTimeStamp = DateTime::current().format(xT("%Y-%m"), xT(""));
            break;
        case Period::bpUnknown:
        default:
            xTEST_FAIL;
            return;
            break;
        }
    }

    // format file full name
    std::ctstring_t backupFilePath = Path(a_destDirPath).slashAppend() +
        Path(a_filePath).fileName() + xT("_[") + dateTimeStamp + xT("].") +
        Path::fileExt(Path::FileExt::seBackup);

    // check for existence source file
    {
        bRv = File::isExists(backupFilePath);
        xCHECK_DO(bRv, *a_destFilePath = backupFilePath; return);
    }

    // check for enough space
    {
        Volume volume(a_destDirPath);
        bRv = volume.isSpaceEnough( static_cast<culonglong_t>( File::size(a_filePath) ));
        xCHECK_DO(!bRv, xTHROW_REPORT(errorNotEnoughFreeSpace));
    }

    // copy
    {
        File::copy(a_filePath, backupFilePath, true);
    }

    // check for a valid backup
    {
        bRv = File::isExists(backupFilePath);
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));

        bRv = (File::size(a_filePath) == File::size(backupFilePath));
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));

        bRv = (Crc32().calcFile(a_filePath) == Crc32().calcFile(backupFilePath));
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));
    }

    // out
    *a_destFilePath = backupFilePath;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
