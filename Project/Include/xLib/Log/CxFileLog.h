/**
 * \file  CxFileLog.h
 * \brief logging to file
 */


#pragma once

#include <xLib/Core/xCore.h>

#if   xOS_ENV_WIN
    #include <xLib/Sync/CxIpcMutex.h>
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

    explicit          CxFileLog(culong_t &culMaxFileSizeBytes);
        ///< constructor
    virtual          ~CxFileLog();
        ///< destructor

    void_t            setFilePath(std::ctstring_t &csFilePath);
        ///< set log path
    std::ctstring_t & filePath() const xWARN_UNUSED_RV;
        ///< get log path

    void_t            write(ctchar_t *pcszFormat, ...);
        ///< write
    void_t            clear();
        ///< clear content
    void_t            remove();
        ///< delete

private:
    std::tstring_t    _m_sFilePath;            ///< file path
    ulong_t           _m_ulMaxFileSizeBytes;   ///< maximum file size in bytes

#if xTODO
    CxAutoIpcMutex    _m_mtFile;
#endif

    void_t            _vRemoveIfFull();
        ///< delete log, if full
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
