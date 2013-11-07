/**
 * \file   CxBackuper.cpp
 * \brief
 */


#include <xLib/Filesystem/CxBackuper.h>

#include <xLib/Core/CxString.h>
#include <xLib/Core/CxDateTime.h>
#include <xLib/Crypt/CxCrc32.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxVolume.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE_HO
CxBackuper::CxBackuper(
    cExBackupPeriod &a_period
) :
    _period(a_period)
{
}
//-------------------------------------------------------------------------------------------------
xINLINE_HO void_t
CxBackuper::fileExec(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_destDirPath,
    std::tstring_t  *a_destFilePath
) const
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(false, a_destDirPath.empty());
    xTEST_PTR(a_destFilePath);

    bool_t bRv = false;

    // errors
    std::ctstring_t error_DestFileNotExists  = xT("Destination file not exists");
    std::ctstring_t error_NotEnoughFreeSpace = xT("Not enough free space");
    std::ctstring_t error_CopyingFail        = xT("Copying fail");
    std::ctstring_t error_Unknown            = xT("Unknown error");

    // prepare
    {
        a_destFilePath->clear();

        bool_t bRv = CxFile::isExists(a_filePath);
        xCHECK_DO(!bRv, xTHROW() << error_DestFileNotExists);

        CxDir dest(a_destDirPath);

        bRv = dest.isExists();
        xCHECK_DO(!bRv, dest.pathCreate());
    }

    //-------------------------------------
    // get backup period
    std::tstring_t dateTimeStamp;

    {
        switch (_period) {
        // TODO: bpHourly:
        case bpDaily:
            dateTimeStamp = CxDateTime().current()
                                .format(CxDateTime::ftDate);
            break;
        // TODO: bpWeekly:
        // TODO: bpMonthly:
        default:
            dateTimeStamp = CxDateTime().current()
                                .format(CxDateTime::ftDateTime);
            break;
        }

        dateTimeStamp = CxString::replaceAll(dateTimeStamp, xT(":"), xT("-"));
    }

    //-------------------------------------
    // format file full name
    std::tstring_t backupFilePath =
                        CxPath(a_destDirPath).slashAppend() +
                        CxPath(a_filePath).fileName()       +
                        xT(".bak [") + dateTimeStamp + xT("]");

    //-------------------------------------
    // check for existence source file
    {
        bRv = CxFile::isExists(backupFilePath);
        xCHECK_DO(bRv, *a_destFilePath = backupFilePath; return);
    }

    //-------------------------------------
    // check for enough space
    {
        ulonglong_t totalFreeBytes = 0ULL;
        CxVolume::space(a_destDirPath, NULL, NULL, &totalFreeBytes);

        ulonglong_t fileSizeBytes  = 0ULL;
        fileSizeBytes = static_cast<ulonglong_t>( CxFile::size(a_filePath) );

        xCHECK_DO(fileSizeBytes > totalFreeBytes, xTHROW() << error_NotEnoughFreeSpace);
    }

    //-------------------------------------
    // copy
    {
        CxFile::copy(a_filePath, backupFilePath, true);
    }

    //-------------------------------------
    // check for a valid backup
    {
        bRv = CxFile::isExists(backupFilePath);
        xCHECK_DO(!bRv, xTHROW() << error_CopyingFail);

        bRv = (CxFile::size(a_filePath) == CxFile::size(backupFilePath));
        xCHECK_DO(!bRv, xTHROW() << error_CopyingFail);

        bRv = (CxCrc32::calcFileFast(a_filePath) == CxCrc32::calcFileFast(backupFilePath));
        xCHECK_DO(!bRv, xTHROW() << error_CopyingFail);
    }

    // out
    std::swap(*a_destFilePath, backupFilePath);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
