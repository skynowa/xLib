/**
 * \file   Backup.h
 * \brief  backuper
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class Backup
    /// backuper
{
public:
    enum class Period
        /// backup period
    {
        bpUnknown,
        bpHourly,
        bpDaily,
        bpWeekly,
        bpMonthly
    };
    xUSING_CONST(Period);

    explicit  Backup(cPeriod period);
        ///< constructor
    virtual  ~Backup() = default;
        ///< destructor

    void_t    fileExec(std::ctstring_t &filePath, std::ctstring_t &destDirPath,
                  std::tstring_t *destFilePath) const /* throw(Exception) */;
        ///< execute file backup

private:
    cPeriod   _period {};  ///< backup period

    xNO_COPY_ASSIGN(Backup)
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
