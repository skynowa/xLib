/**
 * \file   Backup.h
 * \brief  backuper
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

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
	explicit  Backup(std::ctstring_t &filePath, cPeriod period);
	virtual  ~Backup() = default;

	xNO_DEFAULT_CONSTRUCT(Backup)
	xNO_COPY_ASSIGN(Backup)
///@}

    void_t fileExec(std::ctstring_t &destDirPath, std::tstring_t *destFilePath) const /* throw(Exception) */;
        ///< execute file backup

private:
	std::ctstring_t _filePath;
    cPeriod         _period {};  ///< backup period
};

} // namespace
//-------------------------------------------------------------------------------------------------
