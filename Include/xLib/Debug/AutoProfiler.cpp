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
    cptr_ctchar_t    a_msg, ...
) :
	_profiler(a_filePath)
{
    // format msg
    va_list args;
    xVA_START(args, a_msg);
    _msg = FormatC::strV(a_msg, args);
    xVA_END(args);

    // start
    _profiler.start();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
AutoProfiler::~AutoProfiler()
{
    size_t uiRv = _profiler.stop(xT("%s"), _msg.c_str());
    xUNUSED(uiRv);
}
//-------------------------------------------------------------------------------------------------

} // namespace
