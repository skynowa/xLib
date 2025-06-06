/**
 * \file  TraceStream.cpp
 * \brief Tracing to debugger, std::cout
 */


#include "TraceStream.h"

#include <xLib/Core/Const.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>


namespace xl::log
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
TraceStream::TraceStream() :
	TraceStream(ILog::Level::Trace)
{
}
//-------------------------------------------------------------------------------------------------
TraceStream::TraceStream(
	ILog::cLevel a_level
) :
	_level{a_level}
{
}
//-------------------------------------------------------------------------------------------------
TraceStream::~TraceStream()
{
	Trace trace;
	trace.write(_level, _os.str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
