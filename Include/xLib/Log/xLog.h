/**
 * \file  xLog.h
 * \brief logging
 */


#ifndef xLib_Log_xLogH
#define xLib_Log_xLogH
//---------------------------------------------------------------------------
#include <xLib/Log/CxConsoleLog.h>
#include <xLib/Log/CxFileLog.h>
#include <xLib/Log/CxTraceLog.h>

#if defined(xOS_WIN)
    #include <xLib/Log/Win/CxEventLog.h>
    #include <xLib/Log/Win/CxWndLog.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Log_xLogH
