/**
 * \file  CxEventLog.cpp
 * \brief logging to system event log
 */


#include <xLib/Log/Win/CxEventLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>


#if defined(xOS_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxEventLog ()
CxEventLog::CxEventLog() {

}
//---------------------------------------------------------------------------
//DONE: ~CxEventLog ()
CxEventLog::~CxEventLog() {

}
//---------------------------------------------------------------------------
#elif defined(xOS_LINUX)

#endif
