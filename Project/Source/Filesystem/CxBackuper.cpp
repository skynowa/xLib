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

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxBackuper::CxBackuper(
    cExBackupPeriod &a_period
) :
    _period(a_period)
{
}
//------------------------------------------------------------------------------
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
    std::ctstring_t csError_DestFileNotExists  = xT("Destination file not exists");
    std::ctstring_t csError_NotEnoughFreeSpace = xT("Not enough free space");
    std::ctstring_t csError_CopyingFail        = xT("Copying fail");
    std::ctstring_t csError_Unknown            = xT("Unknown error");

    // prepare
    {
        (*a_destFilePath).clear();

        bool_t bRv = CxFile::isExists(a_filePath);
        xCHECK_DO(!bRv, xTHROW() << csError_DestFileNotExists);

        CxDir drDest(a_destDirPath);

        bRv = drDest.isExists();
        xCHECK_DO(!bRv, drDest.pathCreate());
    }

    //-------------------------------------
    // get backup period
    std::tstring_t sDateTimeStamp;

    {
        switch (_period) {
            // TODO: bpHourly:
            case bpDaily:
                sDateTimeStamp = CxDateTime().current()
                                    .format(CxDateTime::ftDate);
                break;
            // TODO: bpWeekly:
            // TODO: bpMonthly:
            default:
                sDateTimeStamp = CxDateTime().current()
                                    .format(CxDateTime::ftDateTime);
                break;
        }

        sDateTimeStamp = CxString::replaceAll(sDateTimeStamp, xT(":"), xT("-"));
    }

    //-------------------------------------
    // format file full name
    std::tstring_t sBackupFilePath =
                        CxPath(a_destDirPath).slashAppend() +
                        CxPath(a_filePath).fileName()       +
                        xT(".bak [") + sDateTimeStamp + xT("]");

    //-------------------------------------
    // check for existence source file
    {
        bRv = CxFile::isExists(sBackupFilePath);
        xCHECK_DO(bRv, *a_destFilePath = sBackupFilePath; return);
    }

    //-------------------------------------
    // check for enough space
    {
        ulonglong_t ullTotalFreeBytes = 0ULL;
        CxVolume::space(a_destDirPath, NULL, NULL, &ullTotalFreeBytes);

        ulonglong_t ullFileSizeBytes  = 0ULL;
        ullFileSizeBytes = static_cast<ulonglong_t>( CxFile::size(a_filePath) );

        xCHECK_DO(ullFileSizeBytes > ullTotalFreeBytes, xTHROW() << csError_NotEnoughFreeSpace);
    }

    //-------------------------------------
    // copy
    {
        CxFile::copy(a_filePath, sBackupFilePath, true);
    }

    //-------------------------------------
    // check for a valid backup
    {
        bRv = CxFile::isExists(sBackupFilePath);
        xCHECK_DO(!bRv, xTHROW() << csError_CopyingFail);

        bRv = (CxFile::size(a_filePath) == CxFile::size(sBackupFilePath));
        xCHECK_DO(!bRv, xTHROW() << csError_CopyingFail);

        bRv = (CxCrc32::calcFileFast(a_filePath) == CxCrc32::calcFileFast(sBackupFilePath));
        xCHECK_DO(!bRv, xTHROW() << csError_CopyingFail);
    }

    // out
    std::swap(*a_destFilePath, sBackupFilePath);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
