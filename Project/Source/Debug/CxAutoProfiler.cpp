/**
 * \file  CxAutoProfiler.cpp
 * \brief auto code profiling
 */


#include <xLib/Debug/CxAutoProfiler.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAutoProfiler::CxAutoProfiler(
    const std::tstring_t     &csFilePath,
    const CxProfiler::ExMode  cpmMode,
    const tchar_t            *pcszComment, ...
) :
    _m_pfProfiler(cpmMode),
    _m_sComment  ()
{
    //-------------------------------------
    //format comment
    va_list palArgs;
    xVA_START(palArgs, pcszComment);

    _m_sComment = CxString::sFormatV(pcszComment, palArgs);

    xVA_END(palArgs);

    //-------------------------------------
    //start
    (void)_m_pfProfiler.bSetLogPath(csFilePath);

    (void)_m_pfProfiler.bStart();
}
//---------------------------------------------------------------------------
/*virtual*/
CxAutoProfiler::~CxAutoProfiler() {
    (void)_m_pfProfiler.bStop(xT("%s"), _m_sComment.c_str());
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
