/**
 * \file  CxAutoProfiler.cpp
 * \brief auto code profiling
 */


#include <xLib/Debug/CxAutoProfiler.h>

#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxAutoProfiler::CxAutoProfiler(
    const std::tstring_t     &a_csFilePath,
    ctchar_t            *a_pcszComment, ...
) :
    _m_pfProfiler(),
    _m_sComment  ()
{
    //-------------------------------------
    // format comment
    va_list palArgs;
    xVA_START(palArgs, a_pcszComment);
    _m_sComment = CxString::formatV(a_pcszComment, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    // start
    _m_pfProfiler.setLogPath(a_csFilePath);
    _m_pfProfiler.start();
}
//------------------------------------------------------------------------------
/* virtual */
CxAutoProfiler::~CxAutoProfiler() {
    _m_pfProfiler.stop(xT("%s"), _m_sComment.c_str());
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
