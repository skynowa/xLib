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

    explicit        CxBackuper(cExBackupPeriod &period);
        ///< constructor
    virtual        ~CxBackuper();
        ///< destructor

    void_t          fileExec(std::ctstring_t &filePath, std::ctstring_t &destDirPath,
                        std::tstring_t *destFilePath) const;
        ///< backup, throws CxException

private:
    cExBackupPeriod _period;  ///< backup period
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif

