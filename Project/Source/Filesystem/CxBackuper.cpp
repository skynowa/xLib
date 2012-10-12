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
    const ExBackupPeriod &cbpPeriod
) :
    _m_cbpPeriod(cbpPeriod)
{

}
//---------------------------------------------------------------------------
/* virtual */
CxBackuper::~CxBackuper() {

}
//---------------------------------------------------------------------------
void
CxBackuper::vExecute(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDestDirPath,
    std::tstring_t       *psDestFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, csDestDirPath.empty());
    /*DEBUG*/xTEST_PTR(psDestFilePath);

    // errors
    const std::tstring_t csError_DestFileNotExists  = xT("Destination file not exists");
    const std::tstring_t csError_Unknown            = xT("Unknown error");
    const std::tstring_t csError_NotEnoughFreeSpace = xT("Not enough free space");
    const std::tstring_t csError_CopyingFail        = xT("Copying fail");

    bool bRv = false;

    (*psDestFilePath).clear();

    bRv = CxFile::bIsExists(csFilePath);
    xCHECK_DO(false == bRv, xTHROW() << csError_DestFileNotExists);

    bRv = CxDir::bIsExists(csDestDirPath);
    xCHECK_DO(false == bRv, CxDir::vCreateForce(csDestDirPath));

    //-------------------------------------
    // process backup period
    std::tstring_t sDateTimeStamp;

    switch (_m_cbpPeriod) {
        //TODO: case bpHourly:  { ; }   break;
        case bpDaily:   { sDateTimeStamp = CxDateTime().dtCurrent().sFormat(CxDateTime::ftDate);     }  break;
        //TODO: case bpWeekly:  { ; }   break;
        //TODO: case bpMonthly: { ; }   break;

        default:        { sDateTimeStamp = CxDateTime().dtCurrent().sFormat(CxDateTime::ftDateTime); }  break;
    }

    sDateTimeStamp = CxString::sReplaceAll(sDateTimeStamp, xT(":"), xT("-"));

    //-------------------------------------
    // format file full name
    std::tstring_t sBackupFilePath =
                        CxPath::sSlashAppend(csDestDirPath) +
                        CxPath::sFileName(csFilePath)       +
                        xT(".bak [") + sDateTimeStamp + xT("]");

    bRv = CxFile::bIsExists(sBackupFilePath);
    xCHECK_DO(true == bRv, *psDestFilePath = sBackupFilePath; return);

    //-------------------------------------
    // check for enough space
    ulonglong_t ullTotalFreeBytes = 0ULL;

    try {
        CxVolume::vSpace(csDestDirPath, NULL, NULL, &ullTotalFreeBytes);
    }
    catch (const CxException &) {
        xTHROW() << csError_Unknown;
    }

    if (static_cast<ulonglong_t>( CxFile::llSize(csFilePath) ) > ullTotalFreeBytes) {
        xTHROW() << csError_NotEnoughFreeSpace;
    }

    //-------------------------------------
    // copy
    try {
        CxFile::vCopy(csFilePath, sBackupFilePath, true);
    }
    catch (const CxException &) {
        xTHROW() << csError_CopyingFail;
    }

    //-------------------------------------
    // check for a valid backup
    xCHECK_DO(false                               == CxFile::bIsExists(sBackupFilePath),       xTHROW() << csError_CopyingFail);
    xCHECK_DO(CxFile::llSize(csFilePath)          != CxFile::llSize(sBackupFilePath),          xTHROW() << csError_CopyingFail);
    xCHECK_DO(CxCrc32::ulCalcFileFast(csFilePath) != CxCrc32::ulCalcFileFast(sBackupFilePath), xTHROW() << csError_CopyingFail);

    // [out]
    std::swap(*psDestFilePath, sBackupFilePath);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
