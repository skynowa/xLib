/**
 * \file   CxBackuper.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
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
                               std::tstring_t  *psDestFilePath) const;
        ///< backup, throws CxException

private:
    cExBackupPeriod _m_cbpPeriod;  ///< backup period
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
