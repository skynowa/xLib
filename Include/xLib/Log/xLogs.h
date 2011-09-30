/**
 * \file  xLogs.h
 * \brief logging
 */


#ifndef xLib_Logs_xLogH
#define xLib_Logs_xLogH
//---------------------------------------------------------------------------
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxTraceLog.h>
#include <xLib/Log/CxFileLog.h>
#include <xLib/Log/CxSystemLog.h>

#if defined(xOS_ENV_WIN)
    #include <xLib/Log/Win/CxWndLog.h>
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Logs_xLogH
