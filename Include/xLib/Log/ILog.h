/**
 * \file  ILog.h
 * \brief logging interface
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, log)

class xNO_VTABLE ILog
    /// logging interface
{
public:
    enum ExLevel
        /// log level
    {
        lvUnknown = - 1,
        lvEmerg,
        lvAlert,
        lvCritical,
        lvError,
        lvWarning,
        lvNotice,
        lvInfo,
        lvDebug,
        lvPlain
    };
    typedef const ExLevel cExLevel;

                    ILog();
        ///< constructor
    virtual        ~ILog() = 0;
        ///< destructor

    void_t          setEnabled(cbool_t &flag);
        ///< set enabled
    bool_t          isEnabled() const;
        ///< set enabled

    virtual void_t  write(ctchar_t *format, ...) const = 0;
        ///< write to log
    virtual void_t  write(cExLevel &level, ctchar_t *format, ...) const = 0;
        ///< write to log

protected:
    std::tostringstream_t _oss; ///< string stream
    std::tstring_t  _levelString(cExLevel &level) const;

private:
    bool_t          _isEnable;  ///< is enabled

    xNO_COPY_ASSIGN(ILog)
};

xNAMESPACE_END2(xlib, log)
//-------------------------------------------------------------------------------------------------
#include "ILog.inl"
