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

    explicit  CxBackuper(cExPeriod &period);
        ///< constructor
    virtual  ~CxBackuper() {}
        ///< destructor

    void_t    fileExec(std::ctstring_t &filePath, std::ctstring_t &destDirPath,
                  std::tstring_t *destFilePath) const /* throw(CxException) */;
        ///< execute file backup

private:
    cExPeriod _period;  ///< backup period

    xNO_COPY_ASSIGN(CxBackuper)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxBackuper.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxBackuperH
