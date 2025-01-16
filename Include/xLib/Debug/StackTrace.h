/**
 * \file  StackTrace.h
 * \brief Stackrace of the caller function
 *
 * \see
 * https://github.com/jeremy-rifkin/cpptrace
 * https://gist.github.com/jvranish/4441299
 * https://github.com/ianlancetaylor/libbacktrace
 * https://stackoverflow.com/questions/3899870/how-to-print-a-stack-trace-whenever-a-certain-function-is-called
 * https://chromium.googlesource.com/external/github.com/abseil/abseil-cpp/+/HEAD/absl/debugging/internal/demangle.cc
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/IStr.h>
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{

struct StackTraceOption
    /// StackTrace options
{
    cint_t  skipFramesNum     {2};	// REVIEW: skipFramesNum
    cbool_t isReverse         {false};
    cbool_t isWrapFilePaths   {true};
    cbool_t isFuncArgsDisable {true};
};
xUSING_CONST(StackTraceOption);

class StackTrace :
	public IStr
    /// stack trace
{
public:
///\name ctors, dtor
///\{
			  StackTrace();
	explicit  StackTrace(cStackTraceOption &option);
	virtual  ~StackTrace() = default;

    xNO_COPY_ASSIGN(StackTrace);
///\}

///\name Overrides
///\{
	std::tstring_t str() const final;
		///< get stack trace with format output
///\}

private:
    cStackTraceOption _option {}; ///< option

    void_t _format(std::vector<std::vec_tstring_t> &stack, std::tstring_t *stackStr) const;
        ///< format stack trace

xPLATFORM_IMPL:
	static constexpr std::size_t _framesMax
	#if   xENV_WIN
		#if (xOS_WIN_VER <= xOS_WIN_S03)
		   /**
			* MSDN: Windows Server 2003 and Windows XP
			* The sum of the FramesToSkip and FramesToCapture parameters must be less than 63
			*/
			{62UL};
		#else
			{USHRT_MAX};
		#endif
	#elif xENV_UNIX
		{255};
			///< custom define, this should be enough
	#endif
		///< maximum frames for stack trace

    void_t _get_impl(std::vector<std::vec_tstring_t> *stack) const;

#if xENV_UNIX
    static
    void_t _addr2Line(cptr_cvoid_t symbolAddress, std::tstring_t *filePath,
    			std::tstring_t *functionName, std::tstring_t *sourceLine);
#endif
    void_t _funcArgsDisable(std::tstring_t *functionName) const;
    void_t _wrapFilePaths(std::tstring_t *modulePath, std::tstring_t *filePath) const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
