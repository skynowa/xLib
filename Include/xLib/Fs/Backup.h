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

///@name ctors, dtor
///@{
	explicit  Backup(cPeriod period);
	virtual  ~Backup() = default;

	xNO_DEFAULT_CONSTRUCT(Backup)
	xNO_COPY_ASSIGN(Backup)
///@}

    void_t    fileExec(std::ctstring_t &filePath, std::ctstring_t &destDirPath,
                  std::tstring_t *destFilePath) const /* throw(Exception) */;
        ///< execute file backup

private:
    cPeriod   _period {};  ///< backup period
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
