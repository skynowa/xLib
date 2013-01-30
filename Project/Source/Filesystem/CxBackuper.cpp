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

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//explicit
CxBackuper::CxBackuper(
    const ExBackupPeriod &a_cbpPeriod
) :
    _m_cbpPeriod(a_cbpPeriod)
{

}
//---------------------------------------------------------------------------
/* virtual */
CxBackuper::~CxBackuper() {

}
//---------------------------------------------------------------------------
void
CxBackuper::execute(
    const std::tstring_t &a_csFilePath,
    const std::tstring_t &a_csDestDirPath,
    std::tstring_t       *a_psDestFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_EQ(false, a_csDestDirPath.empty());
    xTEST_PTR(a_psDestFilePath);

    // errors
    const std::tstring_t csError_DestFileNotExists  = xT("Destination file not exists");
    const std::tstring_t csError_Unknown            = xT("Unknown error");
    const std::tstring_t csError_NotEnoughFreeSpace = xT("Not enough free space");
    const std::tstring_t csError_CopyingFail        = xT("Copying fail");

    bool bRv = false;

    (*a_psDestFilePath).clear();

    bRv = CxFile::bIsExists(a_csFilePath);
    xCHECK_DO(false == bRv, xTHROW() << csError_DestFileNotExists);

    CxDir drDest(a_csDestDirPath);

    bRv = drDest.bIsExists();
    xCHECK_DO(false == bRv, drDest.vPathCreate());

    //-------------------------------------
    // process backup period
    std::tstring_t sDateTimeStamp;

    switch (_m_cbpPeriod) {
        // TODO: case bpHourly:  { ; }   break;
        case bpDaily:   { sDateTimeStamp = CxDateTime().current().format(CxDateTime::ftDate);     }  break;
        // TODO: case bpWeekly:  { ; }   break;
        // TODO: case bpMonthly: { ; }   break;

        default:        { sDateTimeStamp = CxDateTime().current().format(CxDateTime::ftDateTime); }  break;
    }

    sDateTimeStamp = CxString::replaceAll(sDateTimeStamp, xT(":"), xT("-"));

    //-------------------------------------
    // format file full name
    std::tstring_t sBackupFilePath =
                        CxPath(a_csDestDirPath).sSlashAppend() +
                        CxPath(a_csFilePath).sFileName()       +
                        xT(".bak [") + sDateTimeStamp + xT("]");

    bRv = CxFile::bIsExists(sBackupFilePath);
    xCHECK_DO(true == bRv, *a_psDestFilePath = sBackupFilePath; return);

    //-------------------------------------
    // check for enough space
    ulonglong_t ullTotalFreeBytes = 0ULL;

    try {
        CxVolume::vSpace(a_csDestDirPath, NULL, NULL, &ullTotalFreeBytes);
    }
    catch (const CxException &) {
        xTHROW() << csError_Unknown;
    }

    if (static_cast<ulonglong_t>( CxFile::llSize(a_csFilePath) ) > ullTotalFreeBytes) {
        xTHROW() << csError_NotEnoughFreeSpace;
    }

    //-------------------------------------
    // copy
    try {
        CxFile::vCopy(a_csFilePath, sBackupFilePath, true);
    }
    catch (const CxException &) {
        xTHROW() << csError_CopyingFail;
    }

    //-------------------------------------
    // check for a valid backup
    xCHECK_DO(false                                 == CxFile::bIsExists(sBackupFilePath),       xTHROW() << csError_CopyingFail);
    xCHECK_DO(CxFile::llSize(a_csFilePath)          != CxFile::llSize(sBackupFilePath),          xTHROW() << csError_CopyingFail);
    xCHECK_DO(CxCrc32::calcFileFast(a_csFilePath) != CxCrc32::calcFileFast(sBackupFilePath), xTHROW() << csError_CopyingFail);

    // [out]
    std::swap(*a_psDestFilePath, sBackupFilePath);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
