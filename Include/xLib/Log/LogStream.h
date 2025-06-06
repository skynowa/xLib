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

template<class LogT, ILog::Level levelT>
class LogStream final
	/// Tracing to debugger, std::cout
{
public:
///\name ctors, dtor
///\{

#if 0
	LogStream() :
		LogStream(levelT)
	{
	}

	LogStream(ILog::cLevel a_level) :
		_level{a_level}
	{
	}
#else
	LogStream() = default;
#endif

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
	ILog::cLevel _level {levelT};
	OStream      _os;
};

using TraceStream  = LogStream<Trace, ILog::Level::Trace>;
using FileStream   = LogStream<FileLog, ILog::Level::Trace>;
using SystemStream = LogStream<SystemLog, ILog::Level::Trace>;

} // namespace
//-------------------------------------------------------------------------------------------------
