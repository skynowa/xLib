/**
 * \file   CxBackup.h
 * \brief  filesystem backuper
 */


#pragma once

#ifndef xLib_CxBackupH
#define xLib_CxBackupH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, filesystem)

class CxBackup
    /// filesystem backuper
{
public:
    enum ExPeriod
        /// backup period
    {
        bpUnknown,
        bpHourly,
        bpDaily,
        bpWeekly,
        bpMonthly
    };
    typedef const ExPeriod cExPeriod;

    explicit  CxBackup(cExPeriod &period);
        ///< constructor
    virtual  ~CxBackup() {}
        ///< destructor

    void_t    fileExec(std::ctstring_t &filePath, std::ctstring_t &destDirPath,
                  std::tstring_t *destFilePath) const /* throw(CxException) */;
        ///< execute file backup

private:
    cExPeriod _period;  ///< backup period

    xNO_COPY_ASSIGN(CxBackup)
};

xNAMESPACE2_END(xlib, filesystem)
//-------------------------------------------------------------------------------------------------
#include "CxBackup.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxBackupH
