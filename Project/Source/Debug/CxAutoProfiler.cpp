/**
 * \file  CxAutoProfiler.cpp
 * \brief auto code profiling
 */


#include <xLib/Debug/CxAutoProfiler.h>

#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxAutoProfiler::CxAutoProfiler(
    std::ctstring_t &a_filePath,
    ctchar_t        *a_comment, ...
) :
    _profiler(),
    _comment ()
{
    //-------------------------------------
    // format comment
    va_list palArgs;
    xVA_START(palArgs, a_comment);
    _comment = CxString::formatV(a_comment, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    // start
    _profiler.setLogPath(a_filePath);
    _profiler.start();
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxAutoProfiler::~CxAutoProfiler()
{
    size_t uiRv = _profiler.stop(xT("%s"), _comment.c_str());
    xUNUSED(uiRv);
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
