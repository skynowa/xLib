/**
 * \file  CxAutoProfiler.cpp
 * \brief auto code profiling
 */


#include <xLib/Debug/CxAutoProfiler.h>

#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoProfiler::CxAutoProfiler(
    const std::tstring_t     &a_csFilePath,
    const tchar_t            *a_pcszComment, ...
) :
    _m_pfProfiler(),
    _m_sComment  ()
{
    //-------------------------------------
    // format comment
    va_list palArgs;
    xVA_START(palArgs, a_pcszComment);
    _m_sComment = CxString::sFormatV(a_pcszComment, palArgs);
    xVA_END(palArgs);

    //-------------------------------------
    // start
    _m_pfProfiler.vSetLogPath(a_csFilePath);
    _m_pfProfiler.vStart();
}
//---------------------------------------------------------------------------
/* virtual */
CxAutoProfiler::~CxAutoProfiler() {
    _m_pfProfiler.vStop(xT("%s"), _m_sComment.c_str());
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
