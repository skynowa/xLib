/**
 * \file  TestMsg.h
 * \brief code testing
 */


#pragma once

#if 0
	#include <xLib/Debug/ErrorReport.h>
	#include <xLib/Debug/SourceInfo.h>
	#include <xLib/Core/Format.h>
	#include <xLib/Debug/StackTrace.h>
	#include <xLib/Debug/Debugger.h>
#endif
//-------------------------------------------------------------------------------------------------
#if 1

namespace xl::debug
{

class ErrorReport;
class ErrorReport {
public:
    enum class Type;  // Forward declaration
};
class SourceInfoOption;
class SourceInfo;
class StackTrace;
class Debugger;

}

namespace core
{

template<typename StreamT>
class FormatT;

}

#endif

namespace xl::test
{

template<typename T1, typename T2>
inline void
testEqMsg_impl(
	const ErrorReport::Type  a_reportType,
	culong_t            a_nativeError,
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
);

} // namespace
//-------------------------------------------------------------------------------------------------
