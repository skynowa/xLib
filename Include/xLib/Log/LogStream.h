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

template<class LogT>
class LogStream final
	/// Tracing to debugger, std::cout
{
public:
///\name ctors, dtor
///\{
	LogStream() :
		LogStream(ILog::Level::Trace)
	{
	}

	LogStream(ILog::cLevel a_level) :
		_level{a_level}
	{
	}

	~LogStream()
	{
		LogT().write(_level, _os.str());
	}

	xNO_COPY_ASSIGN(LogStream);
///\}

	template<typename T>
	LogStream & operator << (const T &a_value)
	{
		_os << a_value;
		return *this;
	}

private:
	ILog::cLevel _level {};
	OStream      _os;
};

using TraceStream  = LogStream<Trace>;
using FileStream   = LogStream<FileLog>;
using SystemStream = LogStream<SystemLog>;

} // namespace
//-------------------------------------------------------------------------------------------------
