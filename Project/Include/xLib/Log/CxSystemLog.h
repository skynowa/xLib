/**
 * \file  CxSystemLog.h
 * \brief logging to system log
 */


#ifndef xLib_Log_CxSystemLogH
#define xLib_Log_CxSystemLogH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSystemLog :
    private CxNonCopyable
    /// logging to system event log
{
public:
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

    #if xTEMP_DISABLED
        EVENTLOG_AUDIT_FAILURE  // Failure Audit event
        EVENTLOG_AUDIT_SUCCESS  // Success Audit event
    #endif

             CxSystemLog();
        ///< constructor
    explicit CxSystemLog(const std::tstring_t &csLogName);
        ///< constructor
    virtual ~CxSystemLog();
        ///< destructor

    void     setEnabled (const bool &cbFlag);
        ///< set enabled
    void     write      (const ExLevel &lvLevel, const tchar_t *pcszFormat, ...);
        ///< write to log

private:
    bool     _m_bIsEnable;  ///< is enabled

#if   xOS_ENV_WIN
    HANDLE   _m_SysLog;     ///< event log handle
#endif

    void     _init      (const std::tstring_t &csLogName);
        ///< initiate data
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Log_CxSystemLogH
