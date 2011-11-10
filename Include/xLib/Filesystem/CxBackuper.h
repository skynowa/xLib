/**
 * \file   CxBackuper.h
 * \brief
 */


#ifndef xLib_Filesystem_CxBackuperH
#define xLib_Filesystem_CxBackuperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
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

		explicit             CxBackuper(const EBackupPeriod cbpPeriod);
            ///< constructor
		virtual             ~CxBackuper();
		    ///< destructor

        EErrorType           etExecute (const std::string_t &csFilePath, const std::string_t &csDestDirPath, std::string_t *psDestFilePath);
            ///< backup

    private:
        const EBackupPeriod  _m_cbpPeriod;  ///< backup period

};
//---------------------------------------------------------------------------
#endif //xLib_CxBackuperH
