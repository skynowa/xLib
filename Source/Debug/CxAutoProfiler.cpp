/****************************************************************************
* Class name:  CxAutoProfiler
* Description: auto code profiling
* File name:   CxAutoProfiler.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     05.07.2010 16:27:50
*
*****************************************************************************/


#include <xLib/Debug/CxAutoProfiler.h>


/****************************************************************************
*    public
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxAutoProfiler (constructor)
CxAutoProfiler::CxAutoProfiler(const tString &csFilePath, CxProfiler::EMode pmMode, LPCTSTR pcszComment, ...) :
    _m_pfProfiler(csFilePath, pmMode),
    _m_sComment  ()
{
    //-------------------------------------
    //format comment
    va_list palArgs = NULL;
    va_start(palArgs, pcszComment);

    _m_sComment = CxString::sFormatV(pcszComment, palArgs);

    va_end(palArgs);
    
    //-------------------------------------
    //start
    _m_pfProfiler.bStart();
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
//DONE: ~CxAutoProfiler (destructor)
/*virtual*/
CxAutoProfiler::~CxAutoProfiler() {
    _m_pfProfiler.bStop(_m_sComment.c_str());
    /*DEBUG*/// n/a
}
//---------------------------------------------------------------------------
