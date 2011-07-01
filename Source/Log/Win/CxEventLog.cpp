/****************************************************************************
* Class name:  CxEventLog
* Description: logging to "Event Log"
* File name:   CxEventLog.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:52:35
*
*****************************************************************************/



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
