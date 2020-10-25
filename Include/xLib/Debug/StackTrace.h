/**
 * \file   StackTrace.h
 * \brief  stackrace of the caller function
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{

struct StackTraceData
    /// StackTrace data
{
    cint_t  skipFramesNum {0};
    cbool_t isWrapFilePaths {true};
    cbool_t isFuncParamsDisable {true};
};
xUSING_CONST(StackTraceData);

class StackTrace
    /// stack trace
{
public:
///@name ctors, dtor
///@{
	explicit  StackTrace(cStackTraceData &data = cStackTraceData());
	virtual  ~StackTrace() = default;

    xNO_COPY_ASSIGN(StackTrace)
///@}

    std::tstring_t toString() const;
        ///< get stack trace with format output

private:
    cStackTraceData _data; ///< data

    void_t _format(std::vector<std::vec_tstring_t> &stack, std::tstring_t *stackStr) const;
        ///< format stack trace

xPLATFORM_IMPL:
	// xSTACK_TRACE_FRAMES_MAX
	static constexpr auto xSTACK_TRACE_FRAMES_MAX
	#if   xENV_WIN
		#if (xOS_WIN_VER <= xOS_WIN_S03)
		   /**
			* MSDN: Windows Server 2003 and Windows XP
			*
			* The sum of the FramesToSkip and FramesToCapture parameters must be less than 63
			*/
			{62UL};
		#else
			{USHRT_MAX};
		#endif
	#elif xENV_UNIX
		{256};
			///< custom define, this should be enough
	#endif
		///< maximum frames for stack trace

    void_t _get_impl(std::vector<std::vec_tstring_t> *stack) const;

#if xENV_UNIX
    static
    void_t _addr2Line(cptr_cvoid_t symbolAddress, std::tstring_t *filePath,
    			std::tstring_t *functionName, ulong_t *sourceLine);
#endif
};

} // namespace
//-------------------------------------------------------------------------------------------------
