/**
 * \file  ILog.h
 * \brief logging interface
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, log)

class xNO_VTABLE ILog
    /// logging interface
    /// TODO: https://oopscenities.net/2011/04/30/c-the-curiously-recurring-template-pattern/#more-21
{
public:
    enum Level
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
    xTYPEDEF_CONST(Level);

                    ILog();
        ///< constructor
    virtual        ~ILog() = 0;
        ///< destructor

    void_t          setEnabled(cbool_t &flag);
        ///< set enabled
    bool_t          isEnabled() const;
        ///< set enabled

    virtual void_t  write(cptr_ctchar_t format, ...) const = 0;
        ///< write to log
    virtual void_t  write(cLevel &level, cptr_ctchar_t format, ...) const = 0;
        ///< write to log

protected:
    std::tostringstream_t _oss; ///< string stream
    std::tstring_t  _levelString(cLevel &level) const;

private:
    bool_t          _isEnable;  ///< is enabled

    xNO_COPY_ASSIGN(ILog)
};

xNAMESPACE_END2(xl, log)
//-------------------------------------------------------------------------------------------------
