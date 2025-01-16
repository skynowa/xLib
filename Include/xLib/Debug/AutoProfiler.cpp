/**
 * \file  AutoProfiler.cpp
 * \brief auto code profiling
 */


#include "AutoProfiler.h"

#include <xLib/Core/FormatC.h>


namespace xl::debug
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
AutoProfiler::AutoProfiler(
    std::ctstring_t &a_filePath,
    cptr_ctchar_t    a_comment, ...
)
{
    // format comment
    va_list args;
    xVA_START(args, a_comment);
    _comment = FormatC::strV(a_comment, args);
    xVA_END(args);

    // start
    _profiler.setLogPath(a_filePath);
    _profiler.start();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
AutoProfiler::~AutoProfiler()
{
    size_t uiRv = _profiler.stop(xT("%s"), _comment.c_str());
    xUNUSED(uiRv);
}
//-------------------------------------------------------------------------------------------------

} // namespace
