/**
 * \file  CxFileLog.h
 * \brief logging to file
 */


#pragma once

#ifndef xLib_CxFileLogH
#define xLib_CxFileLogH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFileLog
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
    virtual          ~CxFileLog() {}
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
    ulong_t           _maxFileSizeBytes;    ///< maximum file size in bytes

#if xTODO
    CxAutoIpcMutex    _mutex;
#endif

    void_t            _removeIfFull();
        ///< delete log, if full

xNO_COPY_ASSIGN(CxFileLog)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Log/CxFileLog.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxFileLogH
