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
    const ExBackupPeriod &a_cbpPeriod
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
CxBackuper::execute(
    std::ctstring_t &a_csFilePath,
    std::ctstring_t &a_csDestDirPath,
    std::tstring_t  *a_psDestFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(false, a_csDestDirPath.empty());
    xTEST_PTR(a_psDestFilePath);

    // errors
    std::ctstring_t csError_DestFileNotExists  = xT("Destination file not exists");
    std::ctstring_t csError_Unknown            = xT("Unknown error");
    std::ctstring_t csError_NotEnoughFreeSpace = xT("Not enough free space");
    std::ctstring_t csError_CopyingFail        = xT("Copying fail");

    bool_t bRv = false;

    (*a_psDestFilePath).clear();

    bRv = CxFile::isExists(a_csFilePath);
    xCHECK_DO(!bRv, xTHROW() << csError_DestFileNotExists);

    CxDir drDest(a_csDestDirPath);

    bRv = drDest.isExists();
    xCHECK_DO(!bRv, drDest.pathCreate());

    //-------------------------------------
    // process backup period
    std::tstring_t sDateTimeStamp;

    switch (_m_cbpPeriod) {
        // TODO: bpHourly:
        case bpDaily:
            sDateTimeStamp = CxDateTime().current().format(CxDateTime::ftDate);
            break;
        // TODO: bpWeekly:
        // TODO: bpMonthly:
        default:
            sDateTimeStamp = CxDateTime().current().format(CxDateTime::ftDateTime);
            break;
    }

    sDateTimeStamp = CxString::replaceAll(sDateTimeStamp, xT(":"), xT("-"));

    //-------------------------------------
    // format file full name
    std::tstring_t sBackupFilePath =
                        CxPath(a_csDestDirPath).slashAppend() +
                        CxPath(a_csFilePath).fileName()       +
                        xT(".bak [") + sDateTimeStamp + xT("]");

    bRv = CxFile::isExists(sBackupFilePath);
    xCHECK_DO(bRv, *a_psDestFilePath = sBackupFilePath; return);

    //-------------------------------------
    // check for enough space
    ulonglong_t ullTotalFreeBytes = 0ULL;

    try {
        CxVolume::space(a_csDestDirPath, NULL, NULL, &ullTotalFreeBytes);
    }
    catch (const CxException &) {
        xTHROW() << csError_Unknown;
    }

    if (static_cast<ulonglong_t>( CxFile::size(a_csFilePath) ) > ullTotalFreeBytes) {
        xTHROW() << csError_NotEnoughFreeSpace;
    }

    //-------------------------------------
    // copy
    try {
        CxFile::copy(a_csFilePath, sBackupFilePath, true);
    }
    catch (const CxException &) {
        xTHROW() << csError_CopyingFail;
    }

    //-------------------------------------
    // check for a valid backup
    xCHECK_DO(false                               == CxFile::isExists(sBackupFilePath),      xTHROW() << csError_CopyingFail);
    xCHECK_DO(CxFile::size(a_csFilePath)          != CxFile::size(sBackupFilePath),          xTHROW() << csError_CopyingFail);
    xCHECK_DO(CxCrc32::calcFileFast(a_csFilePath) != CxCrc32::calcFileFast(sBackupFilePath), xTHROW() << csError_CopyingFail);

    // [out]
    std::swap(*a_psDestFilePath, sBackupFilePath);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
