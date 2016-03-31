/**
 * \file   Backup.h
 * \brief  backuper
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, io)

class Backup
    /// backuper
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
    xTYPEDEF_CONST(ExPeriod);

    explicit  Backup(cExPeriod &period);
        ///< constructor
    virtual  ~Backup() {}
        ///< destructor

    void_t    fileExec(std::ctstring_t &filePath, std::ctstring_t &destDirPath,
                  std::tstring_t *destFilePath) const /* throw(Exception) */;
        ///< execute file backup

private:
    cExPeriod _period;  ///< backup period

    xNO_COPY_ASSIGN(Backup)
};

xNAMESPACE_END2(xlib, io)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Backup.cpp"
#endif
