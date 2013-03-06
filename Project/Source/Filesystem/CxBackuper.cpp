/**
 * \file   CxBackuper.cpp
 * \brief
 */


#include <xLib/Filesystem/CxBackuper.h>

#include <xLib/Common/CxString.h>
#include <xLib/Common/CxDateTime.h>
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
//explicit
CxBackuper::CxBackuper(
    cExBackupPeriod &a_cbpPeriod
) :
    _m_cbpPeriod(a_cbpPeriod)
{

}
//------------------------------------------------------------------------------
/* virtual */
CxBackuper::~CxBackuper() {

}
//------------------------------------------------------------------------------
void_t
CxBackuper::fileExec(
    std::ctstring_t &a_csFilePath,
    std::ctstring_t &a_csDestDirPath,
    std::tstring_t  *a_psDestFilePath
) const
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(false, a_csDestDirPath.empty());
    xTEST_PTR(a_psDestFilePath);

    bool_t bRv = false;

    // errors
    std::ctstring_t csError_DestFileNotExists  = xT("Destination file not exists");
    std::ctstring_t csError_NotEnoughFreeSpace = xT("Not enough free space");
    std::ctstring_t csError_CopyingFail        = xT("Copying fail");
    std::ctstring_t csError_Unknown            = xT("Unknown error");

    // prepare
    {
        (*a_psDestFilePath).clear();

        bool_t bRv = CxFile::isExists(a_csFilePath);
        xCHECK_DO(!bRv, xTHROW() << csError_DestFileNotExists);

        CxDir drDest(a_csDestDirPath);

        bRv = drDest.isExists();
        xCHECK_DO(!bRv, drDest.pathCreate());
    }

    //-------------------------------------
    // get backup period
    std::tstring_t sDateTimeStamp;

    {
        switch (_m_cbpPeriod) {
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
                        CxPath(a_csDestDirPath).slashAppend() +
                        CxPath(a_csFilePath).fileName()       +
                        xT(".bak [") + sDateTimeStamp + xT("]");

    //-------------------------------------
    // check for existence source file
    {
        bRv = CxFile::isExists(sBackupFilePath);
        xCHECK_DO(bRv, *a_psDestFilePath = sBackupFilePath; return);
    }

    //-------------------------------------
    // check for enough space
    {
        ulonglong_t ullTotalFreeBytes = 0ULL;

        CxVolume::space(a_csDestDirPath, NULL, NULL, &ullTotalFreeBytes);

        bRv = (static_cast<ulonglong_t>( CxFile::size(a_csFilePath) ) <= ullTotalFreeBytes);
        xCHECK_DO(!bRv, xTHROW() << csError_NotEnoughFreeSpace);
    }

    //-------------------------------------
    // copy
    {
        CxFile::copy(a_csFilePath, sBackupFilePath, true);
    }

    //-------------------------------------
    // check for a valid backup
    {
        bRv = CxFile::isExists(sBackupFilePath);
        xCHECK_DO(!bRv, xTHROW() << csError_CopyingFail);

        bRv = (CxFile::size(a_csFilePath) == CxFile::size(sBackupFilePath));
        xCHECK_DO(!bRv, xTHROW() << csError_CopyingFail);

        bRv = (CxCrc32::calcFileFast(a_csFilePath) == CxCrc32::calcFileFast(sBackupFilePath));
        xCHECK_DO(!bRv, xTHROW() << csError_CopyingFail);
    }

    // out
    std::swap(*a_psDestFilePath, sBackupFilePath);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
