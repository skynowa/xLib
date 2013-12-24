/**
 * \file  CxSystemLog.h
 * \brief logging to system log
 */


#pragma once

#ifndef xLib_CxSystemLogH
#define xLib_CxSystemLogH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include "IxLog.h"
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSystemLog :
    public IxLog
    /// logging to system event log
{
public:
#if xTEMP_DISABLED
    enum ExLevel
        /// log level
    {
    #if   xOS_ENV_WIN
        lvEmerg    = EVENTLOG_ERROR_TYPE,
        lvAlert    = EVENTLOG_ERROR_TYPE,
        lvCritical = EVENTLOG_ERROR_TYPE,
        lvError    = EVENTLOG_ERROR_TYPE,
        lvWarning  = EVENTLOG_WARNING_TYPE,
        lvNotice   = EVENTLOG_SUCCESS,
        lvInfo     = EVENTLOG_INFORMATION_TYPE,
        lvDebug    = EVENTLOG_INFORMATION_TYPE
    #elif xOS_ENV_UNIX
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
#endif

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

    virtual void_t write(const ExLevel &level, ctchar_t *format, ...) const xOVERRIDE;
        ///< write to log

private:
#if xOS_ENV_WIN
    HANDLE   _sysLog;     ///< event log handle
#endif

    void_t   _construct(std::ctstring_t &logName);
        ///< initiate data
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxSystemLog.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSystemLogH
