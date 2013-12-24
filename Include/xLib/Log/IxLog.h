/**
 * \file  IxLog.h
 * \brief logging interface
 */


#pragma once

#ifndef xLib_IxLogH
#define xLib_IxLogH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class IxLog
    /// logging interface
{
public:
    enum ExLevel
        /// log level
    {
        lvEmerg,
        lvAlert,
        lvCritical,
        lvError,
        lvWarning,
        lvNotice,
        lvInfo,
        lvDebug
    };

                    IxLog();
        ///< constructor
    explicit        IxLog(std::ctstring_t &logName);
        ///< constructor
    virtual        ~IxLog() = 0;
        ///< destructor

    void_t          setEnabled(cbool_t &flag);
        ///< set enabled
    bool_t          isEnabled() const;
        ///< set enabled

    template<class T>
    virtual IxLog & operator << (const T &valueT) = 0;
        ///< write to log with operator <<
    virtual void_t  write(const ExLevel &level, ctchar_t *format, ...) const = 0;
        ///< write to log

private:
    bool_t          _isEnable;  ///< is enabled

    xNO_COPY_ASSIGN(IxLog)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "IxLog.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_IxLogH
