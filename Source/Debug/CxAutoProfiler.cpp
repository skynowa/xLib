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
    const std::string_t      &csFilePath,
    const CxProfiler::EMode  cpmMode,
    const char_t             *pcszComment, ...
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
    (void)_m_pfProfiler.bStop(_m_sComment.c_str());
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
