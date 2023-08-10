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
        lsDefaultMb    = xMB(20),
        lsDefaultMaxMb = xMB(50)
    };
    xUSING_CONST(LogSizes);

///\name ctors, dtor
///\{
			  FileLog();
	explicit  FileLog(cLogSizes fileSizeMaxBytes);
	explicit  FileLog(std::csize_t fileSizeMaxBytes);
	virtual  ~FileLog();
///\}

///\name operators
///\{
	template<typename T>
	FileLog &      operator << (const T &valueT);
///\}

    void_t         setFilePath(std::ctstring_t &filePath);
        ///< set log path
    std::tstring_t filePath() const;
        ///< get log path

///\name Overrides
///\{
	void_t         write(cptr_ctchar_t format, ...) const final;
	void_t         write(cLevel level, cptr_ctchar_t format, ...) const final;
///\}

    void_t         clear() const;
        ///< clear content
    void_t         remove() const;
        ///< delete

private:
    std::tstring_t _filePath;            ///< file path
    std::size_t    _fileSizeMaxBytes {}; ///< maximum file size in bytes

    void_t         _removeIfFull() const;
        ///< delete log, if full
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "FileLog.inl"
