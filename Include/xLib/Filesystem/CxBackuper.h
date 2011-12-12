/**
 * \file   CxBackuper.h
 * \brief
 */


#ifndef xLib_Filesystem_CxBackuperH
#define xLib_Filesystem_CxBackuperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxBackuper :
    public CxNonCopyable
    /// backup file
{
    public:
        enum EErrorType
            /// error type
        {
            etUnknown,
            etSuccess,
            etDestFileNotExists,
            etNotEnoughFreeSpace,
            etCopyingFail
        };

        enum EBackupPeriod
            /// backup period
        {
            bpUnknown,
            //TODO: bpHourly,
            bpDaily
            //TODO: bpWeekly,
            //TODO: bpMonthly
        };

        explicit            CxBackuper(const EBackupPeriod cbpPeriod);
            ///< constructor
        virtual            ~CxBackuper();
            ///< destructor

        EErrorType          etExecute (const std::tstring_t &csFilePath, const std::tstring_t &csDestDirPath, std::tstring_t *psDestFilePath);
            ///< backup

    private:
        const EBackupPeriod _m_cbpPeriod;  ///< backup period

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxBackuperH
