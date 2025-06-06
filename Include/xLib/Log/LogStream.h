/**
 * \file  LogStream.h
 * \brief Logging to stream
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
#include "ILog.h"
#include "Trace.h"
#include "FileLog.h"
#include "SystemLog.h"
//-------------------------------------------------------------------------------------------------
namespace xl::log
{

template<class LogT, ILog::Level level>
class LogStream final
	/// Tracing to debugger, std::cout
{
public:
///\name ctors, dtor
///\{
	LogStream() = default;

	~LogStream()
	{
		LogT().write(_level, _os.str());
	}

	xNO_COPY_ASSIGN(LogStream);
///\}

///\name operators
///\{
	template<typename T>
	LogStream & operator << (const T &a_value)
	{
		_os << a_value;
		return *this;
	}

	LogStream & operator << (std::tostream_t &(*a_manip)(std::tostream_t &))
	{
		_os << a_manip;
		return *this;
	}
///\}

private:
	ILog::cLevel _level {level};
	OStream      _os;
};

#if 0
	using TraceStream  = LogStream<Trace,     ILog::Level::Trace>;
	using FileStream   = LogStream<FileLog,   ILog::Level::Trace>;
	using SystemStream = LogStream<SystemLog, ILog::Level::Trace>;
#else
	#define LOG_STREAM_FACTORY(a_alias, a_log)	\
		using a_alias           = LogStream<a_log, ILog::Level::Trace>; \
		\
		using a_alias##Trace    = LogStream<a_log, ILog::Level::Trace>; \
		using a_alias##Debug    = LogStream<a_log, ILog::Level::Debug>; \
		using a_alias##Info     = LogStream<a_log, ILog::Level::Info>; \
		using a_alias##Warning  = LogStream<a_log, ILog::Level::Warning>; \
		using a_alias##Error    = LogStream<a_log, ILog::Level::Error>; \
		using a_alias##Critical = LogStream<a_log, ILog::Level::Critical>

	LOG_STREAM_FACTORY(LogTrace, Trace);
	LOG_STREAM_FACTORY(LogFile,  FileLog);
	LOG_STREAM_FACTORY(LogSys,   SystemLog);

	#undef LOG_STREAM_FACTORY
#endif


} // namespace
//-------------------------------------------------------------------------------------------------
