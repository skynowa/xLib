/**
 * \file  AutoProfiler.inl
 * \brief auto code profiling
 */


#include <xLib/Core/String.h>


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
AutoProfiler::AutoProfiler(
    std::ctstring_t &a_filePath,
    ctchar_t        *a_comment, ...
) :
    _profiler(),
    _comment ()
{
    // format comment
    va_list args;
    xVA_START(args, a_comment);
    _comment = String::formatV(a_comment, args);
    xVA_END(args);

    // start
    _profiler.setLogPath(a_filePath);
    _profiler.start();
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
AutoProfiler::~AutoProfiler()
{
    size_t uiRv = _profiler.stop(xT("%s"), _comment.c_str());
    xUNUSED(uiRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
