/**
 * \file  AutoProfiler.h
 * \brief auto code profiling
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Debug/Profiler.h>
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{

class AutoProfiler
    /// auto profiling code
{
public:
///@name ctors, dtor
///@{
			 AutoProfiler(std::ctstring_t &filePath, cptr_ctchar_t comment, ...);
	virtual ~AutoProfiler();

    xNO_DEFAULT_CONSTRUCT(AutoProfiler)
    xNO_COPY_ASSIGN(AutoProfiler)
///@}

private:
    Profiler       _profiler;   ///< profiler
    std::tstring_t _comment;    ///< comment
};

} // namespace
//-------------------------------------------------------------------------------------------------
