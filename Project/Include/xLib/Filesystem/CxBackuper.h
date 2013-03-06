/**
 * \file   CxBackuper.h
 * \brief
 */


#ifndef xLib_Filesystem_CxBackuperH
#define xLib_Filesystem_CxBackuperH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
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
    typedef const ExBackupPeriod cExBackupPeriod;

    explicit        CxBackuper(cExBackupPeriod &cbpPeriod);
        ///< constructor
    virtual        ~CxBackuper();
        ///< destructor

    void_t          fileExec  (std::ctstring_t &csFilePath,
                               std::ctstring_t &csDestDirPath,
                               std::tstring_t  *psDestFilePath) const throw (CxException);
        ///< backup

private:
    cExBackupPeriod _m_cbpPeriod;  ///< backup period
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_CxBackuperH
