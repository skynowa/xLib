/**
 * \file  FileLog.h
 * \brief logging to file
 */


#pragma once

//-------------------------------------------------------------------------------------------------
#include <xLib/Core/Core.h>
#include <xLib/Core/Units.h>
#include "ILog.h"
//-------------------------------------------------------------------------------------------------
namespace xl::log
{

class FileLog final :
    public ILog
    /// logging to file
{
public:
    enum class LogSizes : std::size_t
        /// log size
    {
        DefaultMb    = xMB(20),
        DefaultMaxMb = xMB(50)
    };
    xUSING_CONST(LogSizes);

///\name ctors, dtor
///\{
    explicit  FileLog(std::ctstring_t &filePath);
              FileLog(std::ctstring_t &filePath, cLogSizes fileSizeMaxBytes);
              FileLog(std::ctstring_t &filePath, std::csize_t fileSizeMaxBytes);
	virtual  ~FileLog();
///\}

///\name Overrides
///\{
	void_t write(cLevel level, std::ctstring_t &msg) const final;
///\}

    void_t clear() const;
        ///< clear content
    void_t remove() const;
        ///< delete

private:
    std::tstring_t _filePath;            ///< file path
    std::size_t    _fileSizeMaxBytes {}; ///< maximum file size in bytes

    void_t         _removeIfFull() const;
        ///< delete log, if full
};

} // namespace
//-------------------------------------------------------------------------------------------------
