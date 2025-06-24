/**
 * \file  TestMsg.cpp
 * \brief code testing
 */


#if 1
	#include <xLib/Debug/ErrorReport.h>
	#include <xLib/Debug/SourceInfo.h>
	#include <xLib/Core/Format.h>
	#include <xLib/Debug/StackTrace.h>
	#include <xLib/Debug/Debugger.h>
#endif
//-------------------------------------------------------------------------------------------------

namespace xl::test
{

template<typename T1, typename T2>
inline void
testEqMsg_impl(
	const ErrorReport::Type  a_reportType,
	culong_t        a_nativeError,
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
	culong_t nativeError { a_nativeError };

	const SourceInfoOption sourceInfoOption
	{
		a_file, a_line, a_function, a_counter,
		a_val1Str, a_val2Str,
		Format::str(xT("{}"), a_val1),
		Format::str(xT("{}"), a_val2),
		a_op
	};

	SourceInfo       sourceInfo(sourceInfoOption);
	std::ctstring_t &stackTrace = StackTrace().str();

	ErrorReport report(a_reportType, nativeError, sourceInfo, stackTrace, a_msg);
	Debugger().reportMake(report);
}

} // namespace
//-------------------------------------------------------------------------------------------------
