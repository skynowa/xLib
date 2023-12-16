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
        Unknown,
        Hourly,
        Daily,
        Weekly,
        Monthly
    };
    xUSING_CONST(Period);

///\name ctors, dtor
///\{
	explicit  Backup(std::ctstring_t &filePath, cPeriod period);
	virtual  ~Backup() = default;

	xNO_DEFAULT_CONSTRUCT(Backup)
	xNO_COPY_ASSIGN(Backup)
///\}

	enum class Error
        /// errors codes
	{
		Ok                    = 0, ///< Success
		DestFileNotExists     = 1, ///< Destination file not exists
		NotEnoughFreeSpace    = 2, ///< Not enough free space
		CopyFail              = 3, ///< Copy fail
		DestFileAlreadyExists = 4, ///< Destination file already exists
		Internal              = 5, ///< Internal
		Unknown               = 6  ///< Unknown
	};
	xUSING_CONST(Error);

	Error fileExec(std::ctstring_t &destDirPath, std::tstring_t *destFilePath) const;
        ///< execute file backup

private:
	std::ctstring_t _filePath;
    cPeriod         _period {};  ///< backup period
};

} // namespace
//-------------------------------------------------------------------------------------------------
