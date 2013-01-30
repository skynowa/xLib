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
    private CxNonCopyable
    /// backup file
{
public:
    enum ExBackupPeriod
        /// backup period
    {
        bpUnknown,
        //TODO: bpHourly,
        bpDaily
        //TODO: bpWeekly,
        //TODO: bpMonthly
    };

    explicit             CxBackuper(const ExBackupPeriod &cbpPeriod);
        ///< constructor
    virtual             ~CxBackuper();
        ///< destructor

    void                 vExecute  (const std::tstring_t &csFilePath, const std::tstring_t &csDestDirPath, std::tstring_t *psDestFilePath);
        ///< backup

private:
    const ExBackupPeriod _m_cbpPeriod;  ///< backup period
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_CxBackuperH
