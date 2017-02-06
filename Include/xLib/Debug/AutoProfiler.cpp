/**
 * \file  AutoProfiler.inl
 * \brief auto code profiling
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "AutoProfiler.h"
#endif

#include <xLib/Core/Format.h>


xNAMESPACE_BEGIN2(xl, debug)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
AutoProfiler::AutoProfiler(
    std::ctstring_t &a_filePath,
    cptr_ctchar_t    a_comment, ...
) :
    _profiler(),
    _comment ()
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
xINLINE
AutoProfiler::~AutoProfiler()
{
    size_t uiRv = _profiler.stop(xT("%s"), _comment.c_str());
    xUNUSED(uiRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
