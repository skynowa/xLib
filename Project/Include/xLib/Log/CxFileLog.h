/**
 * \file  CxFileLog.h
 * \brief logging to file
 */


#pragma once

#include <xLib/Core/xCore.h>

#if   xOS_ENV_WIN
    #include <Sync/CxIpcMutex.h>
#elif xOS_ENV_UNIX

#endif
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFileLog :
    private CxNonCopyable
    /// logging to file
{
public:
    enum ExLogSizes
        /// log size
    {
        lsDefaultSize    = 20  * 1024 * 1024,
        lsDefaultMaxSize = 200 * 1024 * 1024,
        lsLimitSize      = 500 * 1024 * 1024
    };

    explicit          CxFileLog(culong_t &maxFileSizeBytes);
        ///< constructor
    virtual          ~CxFileLog();
        ///< destructor

    void_t            setFilePath(std::ctstring_t &filePath);
        ///< set log path
    std::ctstring_t & filePath() const xWARN_UNUSED_RV;
        ///< get log path

    void_t            write(ctchar_t *format, ...);
        ///< write
    void_t            clear();
        ///< clear content
    void_t            remove();
        ///< delete

private:
    std::tstring_t    _filePath;            ///< file path
    ulong_t           _maxFileSizeBytes;   ///< maximum file size in bytes

#if xTODO
    CxAutoIpcMutex    _mutex;
#endif

    void_t            _removeIfFull();
        ///< delete log, if full
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Log/CxFileLog.cpp>
#endif
