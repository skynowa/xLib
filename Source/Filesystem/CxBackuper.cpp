/**
 * \file   CxBackuper.cpp
 * \brief
 */


#include <xLib/Filesystem/CxBackuper.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Crypt/CxCrc32.h>
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
    const EBackupPeriod cbpPeriod
) :
    _m_cbpPeriod(cbpPeriod)
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxBackuper::~CxBackuper() {

}
//---------------------------------------------------------------------------
CxBackuper::EErrorType
CxBackuper::etExecute(
    const std::tstring_t &csFilePath,
    const std::tstring_t &csDestDirPath,
    std::tstring_t       *psDestFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(),    etUnknown);
    /*DEBUG*/xASSERT_RET(false == csDestDirPath.empty(), etUnknown);

    EErrorType etRes = etUnknown;
    bool       bRes  = false;

    (*psDestFilePath).clear();

    bRes = CxFile::bIsExists(csFilePath);
    xCHECK_RET(false == bRes, etDestFileNotExists);

    bRes = CxDir::bIsExists(csDestDirPath);
    xCHECK_DO(false == bRes, CxDir::bCreateForce(csDestDirPath));

    //-------------------------------------
    //process backup period
    std::tstring_t sDateTimeStamp;

    switch (_m_cbpPeriod) {
        //TODO: case bpHourly:    { ; }    break;
        case bpDaily:    { sDateTimeStamp = CxDateTime().dtGetCurrent().sFormat(CxDateTime::ftDate);     }    break;
        //TODO: case bpWeekly:    { ; }    break;
        //TODO: case bpMonthly:    { ; }    break;

        default:        { sDateTimeStamp = CxDateTime().dtGetCurrent().sFormat(CxDateTime::ftDateTime); }    break;
    }

    sDateTimeStamp = CxString::sReplaceAll(sDateTimeStamp, xT(":"), xT("-"));

    //-------------------------------------
    //format file full name
    std::tstring_t sBackupFilePath =
                        CxPath::sSlashAppend(csDestDirPath) +
                        CxPath::sGetFullName(csFilePath)    +
                        xT(".bak [") + sDateTimeStamp + xT("]");

    bRes = CxFile::bIsExists(sBackupFilePath);
    xCHECK_DO(true == bRes, *psDestFilePath = sBackupFilePath; return etSuccess);

    //-------------------------------------
    //check for enough space
    ulonglong_t ullTotalFreeBytes = 0ULL;

    bRes = CxVolume::bGetFreeSpace(csDestDirPath, NULL, NULL, &ullTotalFreeBytes);
    xCHECK_RET(false == bRes, etUnknown);

    if (static_cast<ulonglong_t>( CxFile::liGetSize(csFilePath) ) > ullTotalFreeBytes) {
        return etNotEnoughFreeSpace;
    }

    //-------------------------------------
    //copy
    bRes = CxFile::bCopy(csFilePath, sBackupFilePath, true);
    xCHECK_RET(false == bRes, etCopyingFail);

    //-------------------------------------
    //check for a valid backup
    xCHECK_RET(false                               == CxFile::bIsExists(sBackupFilePath),       etCopyingFail);
    xCHECK_RET(CxFile::liGetSize(csFilePath)       != CxFile::liGetSize(sBackupFilePath),       etCopyingFail);
    xCHECK_RET(CxCrc32::ulCalcFileFast(csFilePath) != CxCrc32::ulCalcFileFast(sBackupFilePath), etCopyingFail);

    //[out]
    std::swap(*psDestFilePath, sBackupFilePath);

    return etSuccess;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

