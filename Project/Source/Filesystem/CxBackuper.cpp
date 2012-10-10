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
CxBackuper::ExErrorType
CxBackuper::etExecute(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDestDirPath,
    std::tstring_t       *psDestFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, csDestDirPath.empty());
    /*DEBUG*/xTEST_PTR(psDestFilePath);

    bool bRv = false;

    (*psDestFilePath).clear();

    bRv = CxFile::bIsExists(csFilePath);
    xCHECK_RET(false == bRv, etDestFileNotExists);

    bRv = CxDir::bIsExists(csDestDirPath);
    xCHECK_DO(false == bRv, CxDir::vCreateForce(csDestDirPath));

    //-------------------------------------
    //process backup period
    std::tstring_t sDateTimeStamp;

    switch (_m_cbpPeriod) {
        //TODO: case bpHourly:  { ; }   break;
        case bpDaily:   { sDateTimeStamp = CxDateTime().dtCurrent().sFormat(CxDateTime::ftDate);     }    break;
        //TODO: case bpWeekly:  { ; }   break;
        //TODO: case bpMonthly: { ; }   break;

        default:        { sDateTimeStamp = CxDateTime().dtCurrent().sFormat(CxDateTime::ftDateTime); }    break;
    }

    sDateTimeStamp = CxString::sReplaceAll(sDateTimeStamp, xT(":"), xT("-"));

    //-------------------------------------
    //format file full name
    std::tstring_t sBackupFilePath =
                        CxPath::sSlashAppend(csDestDirPath) +
                        CxPath::sFileName(csFilePath)       +
                        xT(".bak [") + sDateTimeStamp + xT("]");

    bRv = CxFile::bIsExists(sBackupFilePath);
    xCHECK_DO(true == bRv, *psDestFilePath = sBackupFilePath; return etSuccess);

    //-------------------------------------
    //check for enough space
    ulonglong_t ullTotalFreeBytes = 0ULL;

    try {
        CxVolume::vSpace(csDestDirPath, NULL, NULL, &ullTotalFreeBytes);
    }
    catch (const CxException &) {
        return etUnknown;
    }

    if (static_cast<ulonglong_t>( CxFile::llSize(csFilePath) ) > ullTotalFreeBytes) {
        return etNotEnoughFreeSpace;
    }

    //-------------------------------------
    //copy
    try {
        CxFile::vCopy(csFilePath, sBackupFilePath, true);
    }
    catch (const CxException &) {
        return etCopyingFail;
    }

    //-------------------------------------
    //check for a valid backup
    xCHECK_RET(false                               == CxFile::bIsExists(sBackupFilePath),       etCopyingFail);
    xCHECK_RET(CxFile::llSize(csFilePath)          != CxFile::llSize(sBackupFilePath),          etCopyingFail);
    xCHECK_RET(CxCrc32::ulCalcFileFast(csFilePath) != CxCrc32::ulCalcFileFast(sBackupFilePath), etCopyingFail);

    //[out]
    std::swap(*psDestFilePath, sBackupFilePath);

    return etSuccess;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
