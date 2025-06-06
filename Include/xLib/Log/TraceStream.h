/**
 * \file  TraceStream.h
 * \brief Tracing to debugger, std::cout
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/OStream.h>
#include "ILog.h"
#include "Trace.h"
//-------------------------------------------------------------------------------------------------
namespace xl::log
{

class TraceStream final
	/// Tracing to debugger, std::cout
{
public:
///\name ctors, dtor
///\{
	TraceStream() :
		TraceStream(ILog::Level::Trace)
	{
	}

	TraceStream(ILog::cLevel a_level) :
		_level{a_level}
	{
	}

	~TraceStream()
	{
		Trace trace;
		trace.write(_level, _os.str());
	}

	xNO_COPY_ASSIGN(TraceStream);
///\}

	template<typename T>
	TraceStream & operator << (const T &a_value)
	{
		_os << a_value;
		return *this;
	}

private:
	ILog::cLevel _level {};
	OStream      _os;
};

} // namespace
//-------------------------------------------------------------------------------------------------
