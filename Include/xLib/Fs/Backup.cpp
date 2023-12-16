/**
 * \file   Backup.cpp
 * \brief  backuper
 */


#include "Backup.h"

#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Crypt/Crc32.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/FileIO.h>
#include <xLib/Fs/File.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/Dir.h>
#include <xLib/Fs/Volume.h>


namespace xl::fs
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Backup::Backup(
	std::ctstring_t &a_filePath,
	std::ctstring_t &a_destDirPath,
    cPeriod          a_period
) :
    _filePath(a_filePath),
    _period  (a_period),
    _destDir (a_destDirPath)
{
}
//-------------------------------------------------------------------------------------------------
Backup::Error
Backup::fileExec(
    std::ctstring_t &a_destDirPath,	///<
    std::tstring_t  *a_destFilePath	///< [out]
) const
{
    xTEST(!a_destDirPath.empty());
    xTEST_PTR(a_destFilePath);

    bool_t bRv {};

    // prepare
    {
        a_destFilePath->clear();

        bRv = FileInfo(_filePath).isExists();
        xCHECK_RET(!bRv, Error::DestFileNotExists);

        bRv = _destDir.isExists();
        xCHECK_DO(!bRv, _destDir.pathCreate());
    }

    std::tstring_t dateTimeStamp;
    {
        const DateTime &dateCurrent = DateTime::current();

        switch (_period) {
        case Period::Hourly:
            dateTimeStamp = dateCurrent.format(xT("%Y-%m-%d_%H"), {});
            break;
        case Period::Daily:
            dateTimeStamp = dateCurrent.format(xT("%Y-%m-%d"), {});
            break;
        case Period::Weekly:
            dateTimeStamp = dateCurrent.format(xT("%Y_%U"), {});
            break;
        case Period::Monthly:
            dateTimeStamp = dateCurrent.format(xT("%Y-%m"), {});
            break;
        case Period::Unknown:
            xTEST_FAIL;
            break;
        }

        xCHECK_RET(dateTimeStamp.empty(), Error::PeriodUnknown);
    }

    // format file full name
    std::ctstring_t backupFilePath = Path(a_destDirPath).slashAppend().str() +
        Path(_filePath).fileName() + xT("_[") + dateTimeStamp + xT("]") +
        Path::fileDotExt(Path::FileExt::Backup);

    // check for existence source file
    {
        bRv = FileInfo(backupFilePath).isExists();
        if (bRv) {
            // [out]
            *a_destFilePath = backupFilePath;
            return Error::DestFileAlreadyExists;
        }
    }

    // check for enough space
    {
        Volume volume(a_destDirPath);
        bRv = volume.isSpaceAvailable( static_cast<ulonglong_t>( FileInfo(_filePath).size() ));
        xCHECK_RET(!bRv, Error::NotEnoughFreeSpace);
    }

    // copy
    {
        File file(_filePath);
        file.copy(backupFilePath, true);
    }

    // check for a valid backup
    {
        bRv = FileInfo(backupFilePath).isExists();
        xCHECK_RET(!bRv, Error::CopyFail);

        bRv = (FileInfo(_filePath).size() == FileInfo(backupFilePath).size());
        xCHECK_RET(!bRv, Error::CopyFail);

        bRv = (Crc32().calcFile(_filePath) == Crc32().calcFile(backupFilePath));
        xCHECK_RET(!bRv, Error::CopyFail);
    }

    // [out]
    *a_destFilePath = backupFilePath;

    return Error::Ok;
}
//-------------------------------------------------------------------------------------------------

} // namespace
