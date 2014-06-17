/**
 * \file   CxBackup.inl
 * \brief  backuper
 */


#include <xLib/Core/CxString.h>
#include <xLib/Core/CxDateTime.h>
#include <xLib/Crypt/CxCrc32.h>
#include <xLib/Debug/CxException.h>
#include <xLib/IO/CxPath.h>
#include <xLib/IO/CxFile.h>
#include <xLib/IO/CxDir.h>
#include <xLib/IO/CxVolume.h>


xNAMESPACE_BEGIN2(xlib, io)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxBackup::CxBackup(
    cExPeriod &a_period
) :
    _period(a_period)
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxBackup::fileExec(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_destDirPath,
    std::tstring_t  *a_destFilePath
) const /* throw(CxException) */
{
    xTEST_EQ(a_filePath.empty(), false);
    xTEST_EQ(a_destDirPath.empty(), false);
    xTEST_PTR(a_destFilePath);

    // errors
    std::ctstring_t errorDestFileNotExists  = xT("CxBackup - Destination file not exists");
    std::ctstring_t errorNotEnoughFreeSpace = xT("CxBackup - Not enough free space");
    std::ctstring_t errorCopyingFail        = xT("CxBackup - Copying fail");
    std::ctstring_t errorUnknown            = xT("CxBackup - Unknown error");

    bool_t bRv = false;

    // prepare
    {
        a_destFilePath->clear();

        bRv = CxFile::isExists(a_filePath);
        xCHECK_DO(!bRv, xTHROW_REPORT(errorDestFileNotExists));

        CxDir dest(a_destDirPath);

        bRv = dest.isExists();
        xCHECK_DO(!bRv, dest.pathCreate());
    }

    std::tstring_t dateTimeStamp;
    {
        switch (_period) {
        case bpHourly:
            // format: 2013-12-21_23
            dateTimeStamp = CxDateTime::current().format(xT("%Y-%m-%d_%H"), xT(""));
            break;
        case bpDaily:
            // format: 2013-12-21
            dateTimeStamp = CxDateTime::current().format(xT("%Y-%m-%d"), xT(""));
            break;
        case bpWeekly:
            // format: 2013_01
            dateTimeStamp = CxDateTime::current().format(xT("%Y_%U"), xT(""));
            break;
        case bpMonthly:
            // format: 2013-12
            dateTimeStamp = CxDateTime::current().format(xT("%Y-%m"), xT(""));
            break;
        case bpUnknown:
        default:
            xTEST_FAIL;
            return;
            break;
        }
    }

    // format file full name
    std::ctstring_t backupFilePath = CxPath(a_destDirPath).slashAppend() +
        CxPath(a_filePath).fileName() + xT("_[") + dateTimeStamp + xT("].bak");

    // check for existence source file
    {
        bRv = CxFile::isExists(backupFilePath);
        xCHECK_DO(bRv, *a_destFilePath = backupFilePath; return);
    }

    // check for enough space
    {
        CxVolume volume(a_destDirPath);
        bRv = volume.isSpaceEnough( CxFile::size(a_filePath) );
        xCHECK_DO(!bRv, xTHROW_REPORT(errorNotEnoughFreeSpace));
    }

    // copy
    {
        CxFile::copy(a_filePath, backupFilePath, true);
    }

    // check for a valid backup
    {
        bRv = CxFile::isExists(backupFilePath);
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));

        bRv = (CxFile::size(a_filePath) == CxFile::size(backupFilePath));
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));

        bRv = (CxCrc32().calcFile(a_filePath) == CxCrc32().calcFile(backupFilePath));
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));
    }

    // out
    *a_destFilePath = backupFilePath;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, io)
