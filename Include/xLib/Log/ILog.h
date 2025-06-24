/**
 * \file  ILog.h
 * \brief logging
 *
 * \libs
 *
 * - https://github.com/gabime/spdlog
 * - https://userver.tech/df/d0c/md_en_2userver_2logging.html
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
//-------------------------------------------------------------------------------------------------
namespace xl::log
{

class ILog
    /// logging
{
public:
	enum class Level
        /// log level
	{
		Trace    = 0,
		Debug    = 1,
		Info     = 2,
		Warning  = 3,
		Error    = 4,
		Critical = 5	/// TODO: as CRIT, FATAL
	};
	xUSING_CONST(Level);

///\name ctors, dtor
///\{
			 ILog() = default;
	virtual ~ILog() = 0;

	xNO_COPY_ASSIGN(ILog);
///\}

    void_t setEnabled(cbool_t flag);
        ///< set enabled

    template<typename... Args>
    void_t trace(cptr_ctchar_t fmt, Args &&... args) const;
    template<typename... Args>
    void_t debug(cptr_ctchar_t fmt, Args &&... args) const;
    template<typename... Args>
    void_t info(cptr_ctchar_t fmt, Args &&... args) const;
    template<typename... Args>
    void_t warning(cptr_ctchar_t fmt, Args &&... args) const;
    template<typename... Args>
    void_t error(cptr_ctchar_t fmt, Args &&... args) const;
    template<typename... Args>
    void_t critical(cptr_ctchar_t fmt, Args &&... args) const;

protected:
    virtual void_t write(cLevel level, std::ctstring_t &msg) const = 0;
        ///< write to log (with EOL)

protected:
    bool_t _isEnable {true};  ///< is enabled

///\name Level views (choose any you like)
///\{
	std::tstring_t _levelString(cLevel level) const;
	std::tstring_t _levelIcon(cLevel level) const;
///\}
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "ILog.inl"
//-------------------------------------------------------------------------------------------------
/**
 * \file  ILog.h
 *
 * \todo
 *
 * - https://oopscenities.net/2011/04/30/c-the-curiously-recurring-template-pattern/#more-21
 * - class LogItem:
 *
 *   - Date
 *   - Level
 *   - module path
 *   - pid
 *   - tid
 *   - SourceInfo
 *   - BuildInfo
 *   - NativeError
 *   - StackTrace
 *   - infoAdd
 *
 * - Setter proxy class
 * - logIf() - with some condition
 *
 * \done
 *
 * - write as trace(), debug(), info(), ...
 * - operator <<
 * - Color support
 */
