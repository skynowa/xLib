/**
 * \file  CxAutoProfiler.cpp
 * \brief auto code profiling
 */


#include <xLib/Debug/CxAutoProfiler.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxAutoProfiler
CxAutoProfiler::CxAutoProfiler(
    const std::tstring      &csFilePath,
    const CxProfiler::EMode  cpmMode,
    LPCTSTR                  pcszComment, ...
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
    _m_pfProfiler.bSetLogPath(csFilePath);
    /*DEBUG*/

    _m_pfProfiler.bStart();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxAutoProfiler
/*virtual*/
CxAutoProfiler::~CxAutoProfiler() {
    _m_pfProfiler.bStop(_m_sComment.c_str());
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
