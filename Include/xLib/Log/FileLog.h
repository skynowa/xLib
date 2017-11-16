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
xNAMESPACE_BEGIN2(xl, log)

class FileLog :
    public ILog
    /// logging to file
{
public:
    enum LogSizes
        /// log size
    {
        lsDefaultMb    = xMB(20),
        lsDefaultMaxMb = xMB(50)
    };

                   FileLog();
        ///< constructor
    explicit       FileLog(std::csize_t &fileSizeMaxBytes);
        ///< constructor
    virtual       ~FileLog();
        ///< destructor

    void_t         setFilePath(std::ctstring_t &filePath);
        ///< set log path
    std::tstring_t filePath() const xWARN_UNUSED_RV;
        ///< get log path

    template<typename T>
    FileLog &      operator << (const T &valueT);
        ///< operator <<

    virtual void_t write(cptr_ctchar_t format, ...) const xOVERRIDE;
        ///< write to log
    virtual void_t write(cLevel &level, cptr_ctchar_t format, ...) const xOVERRIDE;
        ///< write to log
    void_t         clear() const;
        ///< clear content
    void_t         remove() const;
        ///< delete

private:
    std::tstring_t _filePath;            ///< file path
    std::size_t    _fileSizeMaxBytes;    ///< maximum file size in bytes

    void_t         _removeIfFull() const;
        ///< delete log, if full
};

xNAMESPACE_END2(xl, log)
//-------------------------------------------------------------------------------------------------
#include "FileLog.inl"

#if cmOPTION_PROJECT_HEADER_ONLY
    #include "FileLog.cpp"
#endif
