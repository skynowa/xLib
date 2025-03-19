/**
 * \file  Test_Impl.h
 * \brief code testing
 */


#pragma once

#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/SourceInfo.h>
#include <xLib/Core/Format.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Debug/StackTrace.h>
//-------------------------------------------------------------------------------------------------
#if 0
	namespace xl::debug
	{

	class ErrorReport;
	class SourceInfoOption;
	class SourceInfo;

	}

	namespace v
	{

	class Format;

	}

	namespace xl::debug
	{

	class Debugger;

	}
#endif


template<typename T1, typename T2>
inline void
testEqMsg_impl(
	const xl::debug::ErrorReport::Type  a_reportType,
	xl::culong_t        a_nativeError,
	std::ctstring_t    &a_file,
	std::csize_t        a_line,
	std::ctstring_t    &a_function,
	std::csize_t        a_counter,
	std::ctstring_t    &a_val1Str,
	std::ctstring_t    &a_val2Str,
	const T1           &a_val1,
	const T2           &a_val2,
	std::ctstring_t    &a_op,
	std::ctstring_t    &a_msg
)
{
	xl::culong_t nativeError { a_nativeError };

	const xl::debug::SourceInfoOption sourceInfoOption
	{
		a_file, a_line, a_function, a_counter,
		a_val1Str, a_val2Str,
		"", // xl::core::Format::str(xT("{}"), a_val1),
		"", // xl::core::Format::str(xT("{}"), a_val2),
		a_op
	};

	xl::debug::SourceInfo       sourceInfo(sourceInfoOption);
	std::ctstring_t &stackTrace = xl::debug::StackTrace().str();

	xl::debug::ErrorReport report(a_reportType, nativeError, sourceInfo, stackTrace, a_msg);
	xl::debug::Debugger().reportMake(report);
}
//-------------------------------------------------------------------------------------------------
