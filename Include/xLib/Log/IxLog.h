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
xNAMESPACE_BEGIN(xlib)

class IxLog
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

                    IxLog();
        ///< constructor
    virtual        ~IxLog() = 0;
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
    std::tstring_t  _levelToString(cExLevel &level) const;

private:
    bool_t          _isEnable;  ///< is enabled

    xNO_COPY_ASSIGN(IxLog)
};

xNAMESPACE_END(xlib)
//-------------------------------------------------------------------------------------------------
#include "IxLog.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_IxLogH
