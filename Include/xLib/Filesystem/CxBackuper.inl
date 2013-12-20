/**
 * \file   CxBackuper.cpp
 * \brief
 */


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
inline
CxBackuper::CxBackuper(
    cExPeriod &a_period
) :
    _period(a_period)
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxBackuper::fileExec(
    std::ctstring_t &a_filePath,
    std::ctstring_t &a_destDirPath,
    std::tstring_t  *a_destFilePath
) const /* throw(CxException) */
{
    xTEST_EQ(false, a_filePath.empty());
    xTEST_EQ(false, a_destDirPath.empty());
    xTEST_PTR(a_destFilePath);

    bool_t bRv = false;

    // errors
    std::ctstring_t errorDestFileNotExists  = xT("CxBackuper - Destination file not exists");
    std::ctstring_t errorNotEnoughFreeSpace = xT("CxBackuper - Not enough free space");
    std::ctstring_t errorCopyingFail        = xT("CxBackuper - Copying fail");
    std::ctstring_t errorUnknown            = xT("CxBackuper - Unknown error");

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
        // TODO: bpHourly:
        case bpDaily:
            dateTimeStamp = CxDateTime().current().format("YYYY-MM-DD");
            break;
        // TODO: bpWeekly:
        // TODO: bpMonthly:
        default:
            dateTimeStamp = CxDateTime().current().format("HH-MM");
            break;
        }

        dateTimeStamp = CxString::replaceAll(dateTimeStamp, xT(":"), xT("-"));
    }

    //-------------------------------------
    // format file full name
    std::tstring_t backupFilePath = CxPath(a_destDirPath).slashAppend() +
        CxPath(a_filePath).fileName() + xT(".bak [") + dateTimeStamp + xT("]");

    //-------------------------------------
    // check for existence source file
    {
        bRv = CxFile::isExists(backupFilePath);
        xCHECK_DO(bRv, *a_destFilePath = backupFilePath; return);
    }

    //-------------------------------------
    // check for enough space
    {
        ulonglong_t fileSizeBytes = 0ULL;
        fileSizeBytes = static_cast<ulonglong_t>( CxFile::size(a_filePath) );

        CxVolume volume(a_destDirPath);
        bRv = volume.isSpaceEnough(fileSizeBytes);
        xCHECK_DO(!bRv, xTHROW_REPORT(errorNotEnoughFreeSpace));
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
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));

        bRv = (CxFile::size(a_filePath) == CxFile::size(backupFilePath));
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));

        bRv = (CxCrc32().calcFile(a_filePath) == CxCrc32().calcFile(backupFilePath));
        xCHECK_DO(!bRv, xTHROW_REPORT(errorCopyingFail));
    }

    // out
    a_destFilePath->swap(backupFilePath);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
