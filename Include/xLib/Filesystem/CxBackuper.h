/**
 * \file   CxBackuper.h
 * \brief
 */


#pragma once

#ifndef xLib_CxBackuperH
#define xLib_CxBackuperH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxBackuper
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
    virtual        ~CxBackuper() {}
        ///< destructor

    void_t          fileExec(std::ctstring_t &filePath, std::ctstring_t &destDirPath,
                        std::tstring_t *destFilePath) const;
        ///< backup, throws CxException

private:
    cExBackupPeriod _period;  ///< backup period

xNO_COPY_ASSIGN(CxBackuper)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxBackuper.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxBackuperH
