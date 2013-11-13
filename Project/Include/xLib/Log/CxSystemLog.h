/**
 * \file  CxSystemLog.h
 * \brief logging to system log
 */


#pragma once

#ifndef xLib_CxSystemLogH
#define xLib_CxSystemLogH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSystemLog
    /// logging to system event log
{
public:
    enum ExLevel
        /// log level
    {
    #if xOS_ENV_WIN
        lvEmerg    = EVENTLOG_ERROR_TYPE,
        lvAlert    = EVENTLOG_ERROR_TYPE,
        lvCritical = EVENTLOG_ERROR_TYPE,
        lvError    = EVENTLOG_ERROR_TYPE,
        lvWarning  = EVENTLOG_WARNING_TYPE,
        lvNotice   = EVENTLOG_SUCCESS,
        lvInfo     = EVENTLOG_INFORMATION_TYPE,
        lvDebug    = EVENTLOG_INFORMATION_TYPE
    #else
        lvEmerg    = 0,
        lvAlert    = 1,
        lvCritical = 2,
        lvError    = 3,
        lvWarning  = 4,
        lvNotice   = 5,
        lvInfo     = 6,
        lvDebug    = 7
    #endif
    };

    #if xTEMP_DISABLED
        EVENTLOG_AUDIT_FAILURE  // Failure Audit event
        EVENTLOG_AUDIT_SUCCESS  // Success Audit event
    #endif

             CxSystemLog();
        ///< constructor
    explicit CxSystemLog(std::ctstring_t &logName);
        ///< constructor
    virtual ~CxSystemLog();
        ///< destructor

    void_t   setEnabled(cbool_t &flag);
        ///< set enabled
    void_t   write(const ExLevel &level, ctchar_t *format, ...);
        ///< write to log

private:
    bool_t   _isEnable;  ///< is enabled

#if xOS_ENV_WIN
    HANDLE   _sysLog;     ///< event log handle
#endif

    void_t   _construct(std::ctstring_t &logName);
        ///< initiate data

xNO_COPY_ASSIGN(CxSystemLog)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Log/CxSystemLog.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSystemLogH
