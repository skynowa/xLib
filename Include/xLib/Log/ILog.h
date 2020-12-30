/**
 * \file  ILog.h
 * \brief logging interface
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::log
{

class xNO_VTABLE ILog
    /// logging interface
    /// TODO: https://oopscenities.net/2011/04/30/c-the-curiously-recurring-template-pattern/#more-21
{
public:
    enum class Level
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
    xUSING_CONST(Level);

///@name ctors, dtor
///@{
			 ILog() = default;
	virtual ~ILog() = 0;

	xNO_COPY_ASSIGN(ILog)
///@}

    void_t         setEnabled(cbool_t flag);
        ///< set enabled
    bool_t         isEnabled() const;
        ///< set enabled

    virtual void_t write(cptr_ctchar_t format, ...) const = 0;
        ///< write to log
    virtual void_t write(cLevel level, cptr_ctchar_t format, ...) const = 0;
        ///< write to log

protected:
    std::tostringstream_t _oss; ///< string stream
    std::tstring_t        _levelString(cLevel level) const;

private:
    bool_t _isEnable {true};  ///< is enabled
};

} // namespace
//-------------------------------------------------------------------------------------------------
