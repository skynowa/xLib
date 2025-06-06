/**
 * \file  ILog.h
 * \brief logging
 *
 * \libs
 *
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
		Off      = 0,
		Trace    = 1,
		Debug    = 2,
		Info     = 3,
		Warning  = 4,
		Error    = 5,
		Critical = 6
	};
	xUSING_CONST(Level);

///\name ctors, dtor
///\{
			 ILog() = default;
	virtual ~ILog() = 0;

	xNO_COPY_ASSIGN(ILog);
///\}

    void_t         setEnabled(cbool_t flag);
        ///< set enabled

    virtual void_t write(cLevel level, std::ctstring_t &msg) const = 0;
        ///< write to log (with EOL)

    template<typename... Args>
    void_t trace(cptr_ctchar_t fmt, Args&&... args) const;
    template<typename... Args>
    void_t debug(cptr_ctchar_t fmt, Args&&... args) const;
    template<typename... Args>
    void_t info(cptr_ctchar_t fmt, Args&&... args) const;
    template<typename... Args>
    void_t warning(cptr_ctchar_t fmt, Args&&... args) const;
    template<typename... Args>
    void_t error(cptr_ctchar_t fmt, Args&&... args) const;
    template<typename... Args>
    void_t critical(cptr_ctchar_t fmt, Args&&... args) const;

#if 1
	template <typename T>
	ILog & operator << (const T& value)
	{
		OStream os;
		os << value;

		write(Level::Trace, os.str()); // Calls overridden method

		return *this;
	}
#endif

protected:
    bool_t _isEnable {true};  ///< is enabled

    std::tstring_t _levelString(cLevel level) const;
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
 * - operator <<
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
 */
